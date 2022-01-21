// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

#include "CsData_DamageCollision.generated.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NCollision
		{
			/**
			* Interface to describe the collision of Damage. This should be used with
			* the interface "base" NCsDamage::NData::IData.
			*/
			struct CSDMG_API ICollision : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ICollision(){}

				virtual bool IgnoreHitResultObject() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSDMG_API UCsData_DamageCollision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the collision of Damage. This should be used with 
* the interface "base" ICsData_Damage.
*/
class CSDMG_API ICsData_DamageCollision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual bool IgnoreHitResultObject() const = 0;
};