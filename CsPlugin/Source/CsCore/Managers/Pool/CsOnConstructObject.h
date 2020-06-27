// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsOnConstructObject.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsOnConstructObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsOnConstructObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void OnConstructObject() = 0;
};