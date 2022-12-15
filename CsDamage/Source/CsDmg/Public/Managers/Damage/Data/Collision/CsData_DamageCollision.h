// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Damage_Collision.h"
#include "Engine/EngineTypes.h"

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

			#define CollisionMethodType NCsDamage::NCollision::EMethod

				virtual const CollisionMethodType& GetCollisionMethod() const = 0;

				virtual const ECollisionChannel& GetCollisionChannel() const = 0;

			#undef CollisionMethodType
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

#define CollisionMethodType NCsDamage::NCollision::EMethod

	virtual const CollisionMethodType& GetCollisionMethod() const = 0;

	virtual const ECollisionChannel& GetCollisionChannel() const = 0;

#undef CollisionMethodType
};