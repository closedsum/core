// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Damage_Collision.h"

#include "CsData_DamageCollision.generated.h"

namespace NCsDamage
{
	namespace NData
	{
		namespace NCollision
		{
			/**
			* Interface to describe the collision of Damage. 
			*  This should be used with the interface "base" NCsDamage::NData::IData.
			*/
			struct CSDMG_API ICollision : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ICollision(){}

			#define CollisionInfoType NCsDamage::NCollision::FInfo

				/**
				* Get any information related to Collision for Damage.
				* 
				* return Collision Info.
				*/
				virtual const CollisionInfoType& GetCollisionInfo() const = 0;

			#undef CollisionInfoType
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
* Interface to describe the collision of Damage. 
*  This should be used with the interface "base" ICsData_Damage.
*/
class CSDMG_API ICsData_DamageCollision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

#define CollisionInfoType NCsDamage::NCollision::FInfo

	/**
	* Get any information related to Collision for Damage.
	*
	* return Collision Info.
	*/
	virtual const CollisionInfoType& GetCollisionInfo() const = 0;

#undef CollisionInfoType
};