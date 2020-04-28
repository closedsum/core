// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "CsMotionController.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSVR_API UCsMotionController : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class USceneComponent;

class CSVR_API ICsMotionController
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ECsControllerHand GetHand() const = 0;

	virtual USceneComponent* GetVisualComponent() const = 0;

	virtual USceneComponent* GetInteractingComponent() const = 0;
};