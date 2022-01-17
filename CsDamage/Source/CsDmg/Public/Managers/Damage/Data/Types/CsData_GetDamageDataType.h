// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

#include "CsData_GetDamageDataType.generated.h"

namespace NCsData
{
	/**
	* Interface to describe getting the type of Damage Data.
	*/
	struct CSDMG_API IGetDamageDataType : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IGetDamageDataType(){}

		virtual const FECsDamageData& GetDamageDataType() const = 0;
	};
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_GetDamageDataType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe getting the type of Damage Data.
*/
class CSDMG_API ICsData_GetDamageDataType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const FECsDamageData& GetDamageDataType() const = 0;
};