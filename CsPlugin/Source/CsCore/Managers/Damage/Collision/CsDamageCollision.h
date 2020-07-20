// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "CsDamageCollision.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSCORE_API UCsDamageCollision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the collision of Damage. This should be used with 
* the interface "base" ICsDamageExpression.
*/
class CSCORE_API ICsDamageCollision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual bool IgnoreHitResultObject() const = 0;
};