// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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