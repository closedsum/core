// Copyright 2017-2024 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Components/CsWidgetInteractionComponent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/GameEvent/CsLibrary_Coordinator_GameEvent.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Library/CsLibrary_Math.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Player
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"
// UI
#include "Components/WidgetComponent.h"
// Input
#include "InputCoreTypes.h"

// Cached
#pragma region

namespace NCsWidgetInteractionComponent
{
	namespace NCached
	{
		namespace Str
		{
			// UObject Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsWidgetInteractionComponent, BeginDestroy);
			// UActorComponent Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsWidgetInteractionComponent, BeginPlay);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsWidgetInteractionComponent, OnProcessGameEventInfo);
		}
	}
}

#pragma endregion Cached

UCsWidgetInteractionComponent::UCsWidgetInteractionComponent(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	OnProcessGameEventInfoHandleMap(),
	Internal_ComponentsToIgnoreOnTrace()
{
}

#define USING_NS_CACHED using namespace NCsWidgetInteractionComponent::NCached;
#define SET_CONTEXT(__FunctionName) using namespace NCsWidgetInteractionComponent::NCached; \
	const FString& Context = Str::__FunctionName
#define GameEventCoordinatorLibrary NCsGameEvent::NCoordinator::FLibrary
#define GameInstanceLibrary NCsGameInstance::FLibrary

// UObject Interface
#pragma region

void UCsWidgetInteractionComponent::BeginDestroy()
{
	SET_CONTEXT(BeginDestroy);

	Super::BeginDestroy();

	if (UObject* GameInstance = GameInstanceLibrary::GetSafeAsObject(this))
	{
		if (GameEventCoordinatorLibrary::SafeIsActive(GameInstance))
		{
			typedef NCsGameEvent::NCoordinator::FOnProcessGameEventInfo DelegateType;
			typedef EMCsGameEventCoordinatorGroup GroupMapType;
			typedef FECsGameEventCoordinatorGroup GroupType;

			for (const TPair<GroupType, FDelegateHandle>& Pair : OnProcessGameEventInfoHandleMap)
			{
				const GroupType& Group		  = Pair.Key;
				const FDelegateHandle& Handle = Pair.Value;

				DelegateType& Delegate = GameEventCoordinatorLibrary::GetOnProcessGameEventInfo_EventChecked(Context, GameInstance, Group);

				Delegate.Remove(Handle);
			}
		}
	}
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsWidgetInteractionComponent::BeginPlay()
{
	SET_CONTEXT(BeginPlay);

	Super::BeginPlay();

	if (UObject* GameInstance = GameInstanceLibrary::GetSafeAsObject(this))
	{
		if (GameEventCoordinatorLibrary::SafeIsActive(GameInstance))
		{
			typedef NCsGameEvent::NCoordinator::FOnProcessGameEventInfo DelegateType;
			typedef EMCsGameEventCoordinatorGroup GroupMapType;
			typedef FECsGameEventCoordinatorGroup GroupType;

			for (const GroupType& Group : GroupMapType::Get())
			{
				DelegateType& Delegate = GameEventCoordinatorLibrary::GetOnProcessGameEventInfo_EventChecked(Context, GameInstance, Group);

				OnProcessGameEventInfoHandleMap.Add(Group, Delegate.AddUObject(this, &UCsWidgetInteractionComponent::OnProcessGameEventInfo));
			}
		}
	}
}

#pragma endregion UActorComponent Interface

void UCsWidgetInteractionComponent::OnProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Info)
{
	using namespace NCsWidgetInteractionComponent::NCached;

	// Check to forward input to Widget Interaction Component

	if (!IsComponentTickEnabled())
		return;

	if (InteractionSource != EWidgetInteractionSource::Custom)
		return;

	const FECsGameEvent& Event = Info.Event;

	// Default__MousePositionXY__ 
	if (Event == NCsGameEvent::Default__MousePositionXY__)
	{
		//const FCsGameEventInfo& MousePositionXYEvent = 

		CustomHitResult.Reset(0.0f, false);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		checkf(PlayerController, TEXT("UCsWidgetInteractionComponent::OnProcessGameEventInfo: PlayerController is NULL."));

		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		checkf(LocalPlayer, TEXT("UCsWidgetInteractionComponent::OnProcessGameEventInfo: LocalPlayer is NULL for PlayerController: %s."), *(PlayerController->GetName()));

		checkf(LocalPlayer->ViewportClient, TEXT("UCsWidgetInteractionComponent::OnProcessGameEventInfo: ViewportClient is NUll for LocalPlayer: %s."), *(LocalPlayer->GetName()));

		FVector2d MousePosition;

		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			FVector3d WorldOrigin;
			FVector3d WorldDirection;

			if (UGameplayStatics::DeprojectScreenToWorld(PlayerController, MousePosition, WorldOrigin, WorldDirection))
			{
				// NOTE: For actors placed in the level and if in the process of a seamless level transition,
				//		 check if Manager_Trace is valid.
				if (UCsManager_Trace::IsValid(GetWorld()->GetGameState()))
				{
					UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(GetWorld()->GetGameState());

					typedef NCsTrace::NRequest::FRequest RequestType;

					RequestType* Request    = Manager_Trace->AllocateRequest();
					Request->ProfileName	= Name::OnProcessGameEventInfo;
					Request->Type			= ECsTraceType::Line;
					Request->Method			= ECsTraceMethod::Multi;
					Request->Query			= ECsTraceQuery::Channel;
					Request->Start			= CsMathLibrary::Convert(WorldOrigin);
					Request->End			= CsMathLibrary::Convert(WorldOrigin + WorldDirection * InteractionDistance);
					Request->Channel		= TraceChannel;

					Internal_ComponentsToIgnoreOnTrace.Reset(Internal_ComponentsToIgnoreOnTrace.Max());
					GetRelatedComponentsToIgnoreInAutomaticHitTesting(Internal_ComponentsToIgnoreOnTrace);

					Request->Params = FCollisionQueryParams::DefaultQueryParam;
					Request->Params.AddIgnoredComponents(Internal_ComponentsToIgnoreOnTrace);

					typedef NCsTrace::NResponse::FResponse ResponseType;

					if (ResponseType* Response = Manager_Trace->Trace(Request))
					{
						TArray<FHitResult>& OutHits = Response->OutHits;

						for (const FHitResult& HitResult : OutHits)
						{
							if (UWidgetComponent* HitWidgetComponent = Cast<UWidgetComponent>(HitResult.GetComponent()))
							{
								if (HitWidgetComponent->IsVisible())
								{
									CustomHitResult = HitResult;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	// Default__MouseLeftButtonPressed__
	if (Event == NCsGameEvent::Default__MouseLeftButtonPressed__)
	{
		PressPointerKey(EKeys::LeftMouseButton);
		ReleasePointerKey(EKeys::LeftMouseButton);
	}
	// Default__MouseRightButtonPressed__
	if (Event == NCsGameEvent::Default__MouseRightButtonPressed__)
	{
		PressPointerKey(EKeys::RightMouseButton);
		ReleasePointerKey(EKeys::RightMouseButton);
	}
}

#undef USING_NS_CACHED
#undef SET_CONTEXT
#undef GameEventCoordinatorLibrary
#undef GameInstanceLibrary