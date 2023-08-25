// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetPersistentObjects.generated.h"

class UObject;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetPersistentObjects : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetPersistentObjects
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual TArray<UObject*>& GetPersistentObjects() = 0;
};