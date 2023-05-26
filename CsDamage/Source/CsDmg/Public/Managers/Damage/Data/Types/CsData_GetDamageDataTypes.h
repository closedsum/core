// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

#include "CsData_GetDamageDataTypes.generated.h"

namespace NCsData
{
	/**
	* Interface to describe getting the types of Damage Data.
	*/
	struct CSDMG_API IGetDamageDataTypes : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IGetDamageDataTypes(){}

		virtual const TArray<FECsDamageData>& GetDamageDataTypes() const = 0;
	};
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_GetDamageDataTypes : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe getting the types of Damage Data.
*/
class CSDMG_API ICsData_GetDamageDataTypes : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const TArray<FECsDamageData>& GetDamageDataTypes() const = 0;
};