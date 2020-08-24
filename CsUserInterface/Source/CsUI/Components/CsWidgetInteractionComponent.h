// Copyright 2017 Respawn Entertainment, Inc. All rights reserved.
#pragma once
#include "Components/WidgetInteractionComponent.h"
// Types
#include "Managers/Input/CsTypes_Input.h"

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

	FDelegateHandle OnProcessGameEventInfoHandle;

	TArray<UPrimitiveComponent*> Internal_ComponentsToIgnoreOnTrace;

	void OnProcessGameEventInfo(const FCsGameEventInfo& Infos);
};