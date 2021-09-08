// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerData.generated.h"

class UCsManager_Data;

UINTERFACE(Blueprintable)
class UCsGetManagerData : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerData
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Data* GetManager_Data() const = 0;

	virtual void SetManager_Data(UCsManager_Data* InManager) = 0;
};