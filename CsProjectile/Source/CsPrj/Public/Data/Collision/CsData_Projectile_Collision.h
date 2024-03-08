// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Collision/CsTypes_Collision.h"

#include "CsData_Projectile_Collision.generated.h"

class UObject;

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

			public:

				virtual ~ICollision() {}

				/**
				* Get the collision information (i.e. response, overlap, hit events, ... etc)
				*
				* return Preset
				*/
				virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

				/**
				* Get the radius of the collision sphere
				* 
				* return Radius
				*/
				virtual const float& GetCollisionRadius() const = 0;

				/**
				* Get the number of hits before the projectile
				* is stopped (and / or deallocated if pooled).
				* NOTE:
				* - Collision detection is captured via CollisionComponent->OnComponentHit.
				* - GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful.
				* 
				* return Count
				*/
				virtual const int32& GetHitCount() const = 0;

				/**
				* Whether to ignore an object (AActor or UPrimitiveComponent) the projectile has collided with after
				* the first collision.
				* 
				* return
				*/
				virtual const bool& IgnoreHitObjectAfterHit() const = 0;

				/**
				* Get the list of classes to ignore for colliding objects.
				* 
				* return
				*/
				virtual const TArray<TSubclassOf<UObject>>& GetIgnoreHitObjectClasses() const = 0;
			};
		}
	}
}

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_Projectile_Collision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UObject;

/**
* Interface for describing any collision associated with a Projectile.
*/
class CSPRJ_API ICsData_Projectile_Collision : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	* Get the collision information (i.e. response, overlap, hit events, ... etc)
	*
	* return Preset
	*/
	virtual const FCsCollisionPreset& GetCollisionPreset() const = 0;

	/**
	* Get the radius of the collision sphere
	* 
	* return Radius
	*/
	virtual const float& GetCollisionRadius() const = 0;

	/**
	* Get the number of hits before the projectile
	* is stopped (and / or deallocated if pooled).
	* NOTE:
	* - Collision detection is captured via CollisionComponent->OnComponentHit.
	* - GetCollisionPreset().bSimulationGeneratesHitEvents MUST be true for the count to be meaningful.
	*
	* return Count
	*/
	virtual const int32& GetHitCount() const = 0;

	/**
	* Whether to ignore an object (AActor or UPrimitiveComponent) the projectile has collided with after
	* the first collision.
	*
	* return
	*/
	virtual const bool& IgnoreHitObjectAfterHit() const = 0;

	/**
	* Get the list of classes to ignore for colliding objects.
	*
	* return
	*/
	virtual const TArray<TSubclassOf<UObject>>& GetIgnoreHitObjectClasses() const = 0;
};