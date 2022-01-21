// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"

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

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams

	virtual void OnConstructObject(const ConstructParamsType& Params) = 0;

#undef ConstructParamsType
};