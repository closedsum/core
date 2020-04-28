// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Types
#include "Managers/Input/CsTypes_Input.h"
#include "CsVrPlayer.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSVR_API UCsVrPlayer : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsMotionController;

class CSVR_API ICsVrPlayer
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual ICsMotionController* GetMotionController(const ECsControllerHand& Hand) = 0;
};