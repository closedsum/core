// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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