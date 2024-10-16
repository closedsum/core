// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Components/ActorComponent.h"
// Interface
#include "Shutdown/CsShutdown.h"
#include "Managers/Input/CsManager_Input_WithGameplayTag.h"
#include "Managers/Input/Event/CsManager_Input_WithGameplayTag_Event.h"
// Types
#include "InputAction.h"

#include "CsManager_EnhancedInput_WithGameplayTag.generated.h"

class APlayerContoller;
class UCsEnhancedInputListener;

UCLASS(BlueprintType, Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsManager_EnhancedInput_WithGameplayTag : public UActorComponent,
																			public ICsShutdown,
																			public ICsManager_Input_WithGameplayTag,
																			public ICsManager_Input_WithGameplayTag_Event
{
	GENERATED_BODY()

	UCsManager_EnhancedInput_WithGameplayTag();

private:

	using OnPressedRawEventType = NCsInput::NWithGameplayTag::NManager::NEvent::NRaw::FOnPressed;
	using OnReleasedRawEventType = NCsInput::NWithGameplayTag::NManager::NEvent::NRaw::FOnReleased;
	using OnActionRawEventType = NCsInput::NWithGameplayTag::NManager::NEvent::NRaw::FOnAction;
	using OnActionEventType = NCsInput::NWithGameplayTag::NManager::NEvent::FOnAction;
	using EventType = NCsInput::NWithGameplayTag::FEvent;

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
protected:

	virtual void OnRegister() override;

	virtual void OnUnregister() override;

#pragma endregion UActorComponent Interface

// ICsShutdown
#pragma region
public:

	void Shutdown();

	FORCEINLINE bool HasShutdown() const { return bShutdown; }

#pragma endregion ICsShutdown

// Shutdown
#pragma region
private:

	bool bShutdown;

#pragma endregion Shutdown

// ICsManager_Input_WithGameplayTag
#pragma region
public:

	void Init();

	void PostProcessInput(const float DeltaTime, const bool bGamePaused);

	FORCEINLINE bool HasMapping(const FGameplayTag& Tag) const { return IndexByMappingTagMap.Find(Tag) != nullptr; }

	FORCEINLINE void SetMappingActive(const FGameplayTag& Tag)
	{
		check(HasMapping(Tag));

		MappingInfos[IndexByMappingTagMap[Tag]].bActive = true;
	}

	void SetMappingInactive(const FGameplayTag& Tag)
	{
		check(HasMapping(Tag))

		MappingInfos[IndexByMappingTagMap[Tag]].bActive = false;
	}

#pragma endregion ICsManager_Input_WithGameplayTag

// ICsManager_Input_WithGameplayTag_Event
#pragma region
public:

	FORCEINLINE OnPressedRawEventType& GetOnPressed_Raw_Event() { return OnPressed_Raw_Event; }
	FORCEINLINE FCsManagerInputWithGameplayTag_OnPressed_Raw& GetOnPressed_Raw_ScriptEvent() { return OnPressed_Raw_ScriptEvent; }

	FORCEINLINE OnReleasedRawEventType& GetOnReleased_Raw_Event() { return OnReleased_Raw_Event; }
	FORCEINLINE FCsManagerInputWithGameplayTag_OnReleased_Raw& GetOnReleased_Raw_ScriptEvent() { return OnReleased_Raw_ScriptEvent; }

	FORCEINLINE OnActionRawEventType& GetOnAction_Raw_Event() { return OnAction_Raw_Event; }
	FORCEINLINE FCsManagerInputWithGameplayTag_OnAction_Raw& GetOnAction_Raw_ScriptEvent() { return OnAction_Raw_ScriptEvent; }

	FORCEINLINE OnActionEventType& GetOnAction_Event() { return OnAction_Event; }
	FORCEINLINE FCsManagerInputWithGameplayTag_OnAction& GetOnAction_ScriptEvent() { return OnAction_ScriptEvent; }

#pragma endregion ICsManager_Input_WithGameplayTag_Event

// Manager_Input_WithGameplayTag_Event
#pragma region
public:

	OnPressedRawEventType OnPressed_Raw_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsInputWithGameplayTag|Managers|Input")
	FCsManagerInputWithGameplayTag_OnPressed_Raw OnPressed_Raw_ScriptEvent;

	OnReleasedRawEventType OnReleased_Raw_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsInputWithGameplayTag|Managers|Input")
	FCsManagerInputWithGameplayTag_OnReleased_Raw OnReleased_Raw_ScriptEvent;

	OnActionRawEventType OnAction_Raw_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsInputWithGameplayTag|Managers|Input")
	FCsManagerInputWithGameplayTag_OnAction_Raw OnAction_Raw_ScriptEvent;

	OnActionEventType OnAction_Event;

	UPROPERTY(BlueprintAssignable, Category = "CsInputWithGameplayTag|Managers|Input")
	FCsManagerInputWithGameplayTag_OnAction OnAction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "CsInputWithGameplayTag|Managers|Input")
	FCsManagerInputWithGameplayTag_OnAction2 OnAction2_ScriptEvent;
	
#pragma endregion Manager_Input_WithGameplayTag_Event

// Owner
#pragma region
private:

	APlayerController* OwnerAsController;

#pragma endregion Owner

// Tags
#pragma region
private:

	// Mapping Context Maps

	TArray<FGameplayTag> MappingTags;

		// <Mapping Tag, Index>
	TMap<FGameplayTag, int32> IndexByMappingTagMap;

	struct FMappingInfo
	{
	public:

		FGameplayTag Tag;

		bool bActive;

		FMappingInfo() :
			Tag(),
			bActive(true) // TEMP: For testing
		{
		}

		FORCEINLINE bool IsActive() const { return bActive; }
		FORCEINLINE bool IsBlocked() const { return !IsActive(); }
	};

		// [Mapping Index] = Mapping Info
	TArray<FMappingInfo> MappingInfos;

		// [Action Index] = Mapping Index
	TArray<int32> MappingIndexByActionIndex;

	// Input Action Maps
	
		// <Mapping Tag, <Action Tags>>
	TMap<FGameplayTag, TArray<FGameplayTag>> ActionTagsByMappingTagMap;
		// <Action Tag, Mapping Tag>
	TMap<FGameplayTag, FGameplayTag> MappingTagByActionTagMap;

	struct FActionInfo
	{
	public:

		int32 MappingIndex;
		
		FGameplayTag Tag;

		uint32 EventMask;

		bool bActive;

		FActionInfo() :
			MappingIndex(INDEX_NONE),
			Tag(),
			EventMask(0),
			bActive(true)
		{
		}

		FORCEINLINE bool IsActive() const { return bActive; }
		FORCEINLINE bool IsBlocked() const { return !IsActive(); }

		FORCEINLINE bool CanChangeToEvent(const ECsInputActionEvent& Event) const
		{
			return CS_TEST_BLUEPRINT_BITFLAG(EventMask, Event);
		}
	};

		// [Index] = Action Info
	TArray<FActionInfo> ActionInfos;

		// <Action Tag, Index>
	TMap<FGameplayTag, int32> IndexByActionTagMap;

		// <Unique Id, Index>
	TMap<uint32, int32> IndexByActionUniqueIdMap;

#pragma endregion Tags

// Listeners
#pragma region
private:

	TArray<UCsEnhancedInputListener*> Listeners;
	
#pragma endregion Listeners

// Events
#pragma region
private:

	void OnAction(const int32& ActionIndex, const FInputActionInstance& ActionInstance);

#pragma endregion Events

// Input
#pragma region
private:

	TArray<EventType> QueuedEvents;

	// [Action Index] = Event
	TArray<EventType> LastEvents;
	
	TArray<bool> ActionsProcessedThisFrame;

#pragma endregion Input
};