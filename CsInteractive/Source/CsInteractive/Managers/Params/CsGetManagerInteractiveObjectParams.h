// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerInteractiveObjectParams.generated.h"

class UCsManager_InteractiveObject_Params;

UINTERFACE(Blueprintable)
class UCsGetManagerInteractiveObjectParams : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerInteractiveObjectParams
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_InteractiveObject_Params* GetManager_InteractiveObject_Params() const = 0;

	virtual void SetManager_InteractiveObject_Params(UCsManager_InteractiveObject_Params* InManager) = 0;
};