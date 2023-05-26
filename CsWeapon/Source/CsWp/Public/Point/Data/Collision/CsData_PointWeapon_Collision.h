// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Collision/CsTypes_Collision.h"

#include "CsData_PointWeapon_Collision.generated.h"

class UObject;

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NData
		{
			namespace NCollision
			{
				/**
				* Interface for describing any collision associated with a Point Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon.
				*  Point Weapon is an object that implements the interface: ICsPointWeapon.
				*/
				struct CSWP_API ICollision : public ICsGetInterfaceMap
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
					* Get the list of classes to ignore for colliding objects.
					* 
					* return
					*/
					virtual const TArray<TSubclassOf<UObject>>& GetIgnoreHitObjectClasses() const = 0;
				};
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsData_PointWeapon_Collision : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class UObject;

/**
* Interface for describing any collision associated with a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
class CSWP_API ICsData_PointWeapon_Collision : public ICsGetInterfaceMap
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
	* Get the list of classes to ignore for colliding objects.
	*
	* return
	*/
	virtual const TArray<TSubclassOf<UObject>>& GetIgnoreHitObjectClasses() const = 0;
};