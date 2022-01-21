// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerSave.generated.h"

class UCsManager_Save;

UINTERFACE(Blueprintable)
class UCsGetManagerSave : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerSave
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Save* GetManager_Save() const = 0;

	virtual void SetManager_Save(UCsManager_Save* InManager) = 0;
};