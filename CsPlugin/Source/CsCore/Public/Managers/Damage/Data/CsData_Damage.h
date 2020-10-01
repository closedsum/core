// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Engine/EngineTypes.h"
#include "CsData_Damage.generated.h"
#pragma once

UINTERFACE(BlueprintType)
class CSCORE_API UCsData_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

/**
* Interface to describe Damage. Other interfaces can be "added" on top of this to 
* expose more functionality (i.e. ICsData_DamageShape, ... etc)
*/
class CSCORE_API ICsData_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	* Get the amount of damage.
	* 
	* return Damage Value.
	*/
	virtual const NCsDamage::NValue::IValue* GetValue() const = 0;

	/**
	* Get the type of damage.
	*
	* return Damage Type.
	*/
	virtual const FECsDamageType& GetType() const = 0;
};