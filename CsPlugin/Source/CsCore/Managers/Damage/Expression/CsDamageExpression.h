// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Engine/EngineTypes.h"
#include "CsDamageExpression.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSCORE_API UCsDamageExpression : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe Damage. Other interfaces can be "added" on top of this to 
* expose more functionality (i.e. ICsDamageShape, ... etc)
*/
class CSCORE_API ICsDamageExpression : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Get the amount of damage.
	* 
	* return Damage.
	*/
	virtual float GetDamage() const = 0;

	/**
	* Get the type of damage.
	*
	* return Damage Type.
	*/
	virtual const FECsDamageType& GetType() const = 0;
};