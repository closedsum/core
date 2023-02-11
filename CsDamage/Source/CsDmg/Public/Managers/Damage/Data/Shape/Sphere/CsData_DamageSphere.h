// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_DamageSphere.generated.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NShape
		{
			namespace NSphere
			{
				/**
				* Interface to describe the Sphere shape of Damage. 
				* This should be used with the interface "base" NCsDamage::NData::IData.
				*/
				struct CSDMG_API ISphere : public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~ISphere(){}
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_DamageSphere : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the Sphere shape of Damage.
* This should be used with the interface "base" NCsDamage::NData::IData.
*/
class CSDMG_API ICsData_DamageSphere : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:
};