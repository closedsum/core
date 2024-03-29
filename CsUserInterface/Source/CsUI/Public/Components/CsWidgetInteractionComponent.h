// Copyright 2017-2024 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Components/WidgetInteractionComponent.h"
// Types
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"

#include "CsWidgetInteractionComponent.generated.h"

class UPrimitiveComponent;

UCLASS(Blueprintable, ClassGroup = "UserInterface",  meta = (BlueprintSpawnableComponent))
class CSUI_API UCsWidgetInteractionComponent : public UWidgetInteractionComponent
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region
public:

	virtual void BeginPlay() override;

#pragma endregion UActorComponent Interface

protected:

	TMap<FECsGameEventCoordinatorGroup, FDelegateHandle> OnProcessGameEventInfoHandleMap;

	TArray<UPrimitiveComponent*> Internal_ComponentsToIgnoreOnTrace;

	void OnProcessGameEventInfo(const FECsGameEventCoordinatorGroup& Group, const FCsGameEventInfo& Infos);
};