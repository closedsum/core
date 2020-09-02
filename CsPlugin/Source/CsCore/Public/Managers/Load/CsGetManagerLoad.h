// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerLoad.generated.h"

class UCsManager_Load;

UINTERFACE(Blueprintable)
class UCsGetManagerLoad : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerLoad
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Load* GetManager_Load() const = 0;

	virtual void SetManager_Load(UCsManager_Load* InManager) = 0;
};