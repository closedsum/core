// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Enhanced/CsManager_EnhancedInput_WithGameplayTag.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Enhanced/Data/CsLibrary_EnhancedInput_WithGameplayTag_DataRootSet.h"
#include "Object/CsLibrary_Object.h"
#include "CsLibrary_Valid_GameplayTags.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Enhanced/Data/CsData_EnhancedInput_WithGameplayTag.h"
// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h" // TODO: Move to Library
// Input
#include "Enhanced/CsEnhancedInputListener.h"
#include "EnhancedInputSubsystems.h" // TODO: Move to Library
#include "EnhancedInputComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_EnhancedInput_WithGameplayTag)

// Cached
#pragma region

namespace NCsManagerEnhancedInputWithGameplayTag
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_EnhancedInput_WithGameplayTag, Init);
			// Events
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_EnhancedInput_WithGameplayTag, OnAction);
		}
	}
}

#pragma endregion Cached

UCsManager_EnhancedInput_WithGameplayTag::UCsManager_EnhancedInput_WithGameplayTag() :
	bShutdown(false)
{
}

#define USING_NS_CACHED using namespace NCsManagerEnhancedInputWithGameplayTag::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsManagerEnhancedInputWithGameplayTag::NCached; \
	const FString& Context = Str::__FunctionName

using EventType = NCsInput::NWithGameplayTag::FEvent;

// UObject Interface
#pragma region

void UCsManager_EnhancedInput_WithGameplayTag::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
}

void UCsManager_EnhancedInput_WithGameplayTag::OnUnregister()
{
	Shutdown();

	Super::OnUnregister();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_EnhancedInput_WithGameplayTag::OnRegister()
{
	Super::OnRegister();

	//OwnerAsController = Cast<APlayerController>(GetOwner());

	//Init();
}

#pragma endregion UActorComponent Interface

// ICsShutdown
#pragma region

void UCsManager_EnhancedInput_WithGameplayTag::Shutdown()
{
	for (UCsEnhancedInputListener* Listener : Listeners)
	{
		// TODO: Add SafeRemoveFromRoot
		if (IsValid(Listener) &&
			Listener->IsRooted())
		{
			Listener->RemoveFromRoot();
		}
		CsObjectLibrary::SafeMarkAsGarbage(Listener);
	}
	Listeners.Reset();

	bShutdown = true;
}

#pragma endregion ICsShutdown

void UCsManager_EnhancedInput_WithGameplayTag::Init()
{
	SET_CONTEXT(Init);

	bShutdown = false;

	OwnerAsController = Cast<APlayerController>(GetOwner());

	// Get Local Player
	UPlayer* Player			  = OwnerAsController->Player.Get();
	ULocalPlayer* LocalPlayer = CS_CAST_CHECKED(Player, UPlayer, ULocalPlayer);

	// Add Mapping Contexts
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	CS_IS_PENDING_KILL_CHECKED(Subsystem)

	typedef NCsInput::NEnhanced::NWithGameplayTag::NDataRootSet::FLibrary DataRootSetLibrary;

	UCsData_EnhancedInput_WithGameplayTag* Data = DataRootSetLibrary::GetDataChecked(Context, this);

	for (const FCsEnhancedInput_WithGameplayTag_MappingInfo& MappingInfo : Data->Inner.MappingInfos)
	{
		CS_IS_VALID_CHECKED(MappingInfo);

		Subsystem->AddMappingContext(MappingInfo.MappingContext, 0);

		ActionTagsByMappingTagMap.Add(MappingInfo.Tag);
	}

	// Setup Listeners
	{
		int32 ActionIndex = 0;

		for (const FCsEnhancedInput_WithGameplayTag_MappingInfo& MappingInfo : Data->Inner.MappingInfos)
		{
			for (const FCsEnhancedInput_WithGameplayTag_ActionInfo& ActionInfo : MappingInfo.ActionInfos)
			{
				++ActionIndex;
			}
		}

		Listeners.Reset(ActionIndex);
	
		for (int32 I = 0; I < ActionIndex; ++I)
		{
			UCsEnhancedInputListener* Listener = NewObject<UCsEnhancedInputListener>(this);
			Listener->Init(I);

			Listeners.Add(Listener);
		}
	}

	// Add Bindings and Setup Maps
	UInputComponent* InputComponent = OwnerAsController->InputComponent.Get();
	UEnhancedInputComponent* EIC	= CS_CAST_CHECKED(InputComponent, UInputComponent, UEnhancedInputComponent);

	MappingTags.Reset(Data->Inner.MappingInfos.Num());

	int32 MappingIndex = 0;
	int32 ActionIndex = 0;

	for (const FCsEnhancedInput_WithGameplayTag_MappingInfo& MappingInfo : Data->Inner.MappingInfos)
	{
		MappingTags.Add(MappingInfo.Tag);
		IndexByMappingTagMap.Add(MappingInfo.Tag, MappingIndex);

		FMappingInfo& MInfo = MappingInfos.AddDefaulted_GetRef();
		MInfo.Tag		    = MappingInfo.Tag;

		UInputMappingContext* IMC = MappingInfo.MappingContext;

		for (const FCsEnhancedInput_WithGameplayTag_ActionInfo& ActionInfo : MappingInfo.ActionInfos)
		{
			MappingIndexByActionIndex.Add(MappingIndex);
			MappingTagByActionTagMap.Add(ActionInfo.Tag, MappingInfo.Tag);
			LastEvents.AddDefaulted();

			FActionInfo& AInfo = ActionInfos.AddDefaulted_GetRef();
			AInfo.MappingIndex = MappingIndex;
			AInfo.Tag		   = ActionInfo.Tag;
			AInfo.EventMask	   = NCsInputActionEvent ::ToMask(ActionInfo.Events);

			IndexByActionTagMap.Add(ActionInfo.Tag, ActionIndex);

			EIC->BindAction(ActionInfo.Action, ETriggerEvent::Triggered, Listeners[ActionIndex], &UCsEnhancedInputListener::OnAction);
			Listeners[ActionIndex]->OnAction_Event.BindUObject(this, &UCsManager_EnhancedInput_WithGameplayTag::OnAction);

			IndexByActionUniqueIdMap.Add(ActionInfo.Action->GetUniqueID(), ActionIndex);
			++ActionIndex;
		}
		++MappingIndex;
	}

	QueuedEvents.Reset(ActionIndex);
	ActionsProcessedThisFrame.Reset(ActionIndex);

	for (int32 I = 0; I < ActionIndex; ++I)
	{
		ActionsProcessedThisFrame.Add(false);
	}
}

void UCsManager_EnhancedInput_WithGameplayTag::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	const int32 ActionCount = ActionsProcessedThisFrame.Num();

	for (int32 I = 0; I < ActionCount; ++I)
	{
		ActionsProcessedThisFrame[I] = false;
	}

	typedef UCsManager_EnhancedInput_WithGameplayTag::FMappingInfo MappingInfoType;
	typedef UCsManager_EnhancedInput_WithGameplayTag::FActionInfo ActionInfoType;

	const int32 Count = QueuedEvents.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		EventType& Event = QueuedEvents[I];

		const int32& MappingIndex	       = Event.MappingIndex;
		const MappingInfoType& MappingInfo = MappingInfos[MappingIndex];

		if (MappingInfo.IsBlocked())
			continue;

		const int32& ActionIndex		 = Event.ActionIndex;
		const ActionInfoType& ActionInfo = ActionInfos[ActionIndex];

		if (ActionInfo.IsBlocked())
			continue;

		EventType& Last_Event = LastEvents[ActionIndex];

		// TODO: Add Logging
		
		// FirstPressed | Pressed | FirstReleased | Released
		if (Event.Value.GetValueType() == EInputActionValueType::Boolean)
		{
			// Check against the Last Event
			if (Last_Event.IsValid())
			{
				// (FirstPressed | Pressed) -> Pressed
				if (NCsInputActionEvent::IsFirstPressedOrPressed(Last_Event.Event))
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::Pressed))
					{
						Event.Event							   = ECsInputActionEvent::Pressed;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
				// (FirstReleased | Released) -> Released
				else
				if (NCsInputActionEvent::IsFirstReleasedOrReleased(Last_Event.Event))		
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::Released))
					{
						Event.Event							   = ECsInputActionEvent::Released;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
			}
			else
			{
				// FirstPressed
				if (Event.Value.Get<bool>())
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstPressed))
					{
						Event.Event							   = ECsInputActionEvent::FirstPressed;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
				// FirstReleased
				else
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstReleased))
					{
						Event.Event							   = ECsInputActionEvent::FirstReleased;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
			}
		}
		// FirstStationary | Stationary | FirstMoved | Moved
		else
		{
			// NOTE: For now, assume the "Stationary" Value for any input is 0.0f
			
			// Check against the Last Event
			if (Last_Event.IsValid())
			{
				// (FirstMoved | Moved) -> (Moved | FirstStationary)
				if (NCsInputActionEvent::IsFirstMovedOrMoved(Last_Event.Event))
				{
					// Moved
					if (Event.Value.IsNonZero())
					{
						if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::Moved))
						{
							Event.Event							   = ECsInputActionEvent::Moved;
							ActionsProcessedThisFrame[ActionIndex] = true;
						}
					}
					// FirstStationary (NOTE: It's possible for a (FirstMoved | Moved) -> FirstStationary
					else
					{
						if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstStationary))
						{
							Event.Event							   = ECsInputActionEvent::FirstStationary;
							ActionsProcessedThisFrame[ActionIndex] = true;
						}
					}
				}
				// (FirstStationary | Stationary) -> (Stationary | FirstMoved)
				else
				if (NCsInputActionEvent::IsFirstStationaryOrStationary(Last_Event.Event))		
				{
					// FirstMoved
					if (Event.Value.IsNonZero())
					{
						if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstMoved))
						{
							Event.Event							   = ECsInputActionEvent::FirstMoved;
							ActionsProcessedThisFrame[ActionIndex] = true;
						}
					}
					// Stationary
					else
					{
						if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::Stationary))
						{
							Event.Event							   = ECsInputActionEvent::Stationary;
							ActionsProcessedThisFrame[ActionIndex] = true;
						}
					}
				}
			}
			else
			{
				// FirstMovied
				if (Event.Value.IsNonZero())
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstMoved))
					{
						Event.Event							   = ECsInputActionEvent::FirstMoved;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
				// FirstStationary
				else
				{
					if (ActionInfo.CanChangeToEvent(ECsInputActionEvent::FirstStationary))
					{
						Event.Event							   = ECsInputActionEvent::FirstStationary;
						ActionsProcessedThisFrame[ActionIndex] = true;
					}
				}
			}
		}

		if (ActionsProcessedThisFrame[ActionIndex])
		{
			Last_Event = Event;

			OnAction_Event.Broadcast(Event);
			// NOTE: For scripts (i.e. Python) that don't handle const ref properly
		#if WITH_EDITOR
			OnAction2_ScriptEvent.Broadcast(EventType::Make(Event));
		#endif // #if WITH_EDITOR
			OnAction_Raw_ScriptEvent.Broadcast(EventType::Make(Event));
		}
	}

	QueuedEvents.Reset(QueuedEvents.Max());

	// Reset / Clear any Last_Events
	for (int32 I = 0; I < ActionCount; ++I)
	{
		if (!ActionsProcessedThisFrame[I])
			LastEvents[I].Reset();
	}
}

// Events
#pragma region

void UCsManager_EnhancedInput_WithGameplayTag::OnAction(const int32& ActionIndex, const FInputActionInstance& ActionInstance)
{
	SET_CONTEXT(OnAction);

	CS_IS_PENDING_KILL_CHECKED(ActionInstance.GetSourceAction())

	EventType& Event   = QueuedEvents.AddDefaulted_GetRef();

	Event.ActionIndex  = ActionIndex;
	Event.MappingIndex = ActionInfos[ActionIndex].MappingIndex;
	Event.Tag		   = ActionInfos[ActionIndex].Tag;
	Event.Value		   = ActionInstance.GetValue();

	// Broadcast "Raw" Events
	{
		// FirstPressed | Pressed | FirstReleased | Released
		if (Event.Value.GetValueType() == EInputActionValueType::Boolean)
		{
			// FirstPressed | Pressed
			if (Event.Value.Get<bool>())
			{
				Event.Event = ECsInputActionEvent::FirstPressed;

				OnPressed_Raw_Event.Broadcast(Event);
				OnPressed_Raw_ScriptEvent.Broadcast(EventType::Make(Event));
			}
			// FirstReleased | Released
			else
			{
				Event.Event = ECsInputActionEvent::FirstReleased;

				OnReleased_Raw_Event.Broadcast(Event);
				OnReleased_Raw_ScriptEvent.Broadcast(EventType::Make(Event));
			}
		}
		// FirstStationary | Stationary | FirstMoved | Moved
		else
		{
			Event.Event = ECsInputActionEvent::FirstMoved;

			OnAction_Raw_Event.Broadcast(Event);
			OnAction_Raw_ScriptEvent.Broadcast(EventType::Make(Event));
		}
	}
}

#pragma endregion Events

#undef USING_NS_CACHED
#undef SET_CONTEXT