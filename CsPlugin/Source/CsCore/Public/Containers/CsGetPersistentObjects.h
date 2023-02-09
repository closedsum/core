// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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