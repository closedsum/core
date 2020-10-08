// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_DamageCollision.generated.h"
#pragma once

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
			struct CSCORE_API ICollision : public ICsGetInterfaceMap
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
class CSCORE_API UCsData_DamageCollision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe the collision of Damage. This should be used with 
* the interface "base" ICsData_Damage.
*/
class CSCORE_API ICsData_DamageCollision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual bool IgnoreHitResultObject() const = 0;
};