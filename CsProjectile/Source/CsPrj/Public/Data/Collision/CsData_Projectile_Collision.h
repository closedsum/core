// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Collision.h"

#include "CsData_Projectile_Collision.generated.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
			/**
			* Interface for describing any collision associated with a Projectile.
			*/
			struct CSPRJ_API ICollision : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

				/**
				*
				*
				* return
				*/
				virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

				/**
				*
				*/
				virtual const float& GetCollisionRadius() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_Collision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for describing any collision associated with a Projectile.
*/
class CSPRJ_API ICsData_Projectile_Collision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

	/**
	*
	*/
	virtual const float& GetCollisionRadius() const = 0;
};