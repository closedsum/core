// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerFXActor.generated.h"

class UCsManager_FX_Actor;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerFXActor : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSCORE_API ICsGetManagerFXActor
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_FX_Actor* GetManager_FX_Actor() const = 0;

	virtual void SetManager_FX_Actor(UCsManager_FX_Actor* InManager) = 0;
};