// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerSingleton.generated.h"

class UCsManager_Singleton;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerSingleton : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerSingleton
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Singleton* GetManager_Singleton() const = 0;
};