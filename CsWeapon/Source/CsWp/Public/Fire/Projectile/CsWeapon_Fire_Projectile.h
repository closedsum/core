// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsWeapon_Fire_Projectile.generated.h"

namespace NCsWeapon
{
	namespace NFire
	{
		namespace NProjectile
		{
			namespace NLaunch
			{
				namespace NPayload
				{
					/**
					* Describes any information for a "Shot" (i.e. the Projectile being "launched").
					*  Projectile is an object that implements the interface: ICsProjectile
					*/
					struct CSWP_API FShot
					{
					public:

						/** Whether to use a predefined / cached Location the Projectile is "launched" from. */
						bool bCachedLocation;
						/** The predefined / cached Location the Projectile is "launched" from.
							NOTE: bCachedLocation MUST be TRUE. */
						FVector CachedLocation;
						/** Whether to use a predefined / cached Direction the Projectile is "launched" from. */
						bool bCachedDirection;
						/** The predefined / cached Direction the Projectile is "launched" from.
							NOTE: bCachedDirection MUST be TRUE. */
						FVector CachedDirection;

						FShot() :
							bCachedLocation(false),
							CachedLocation(0.0f),
							bCachedDirection(false),
							CachedDirection(0.0f)
						{
						}

						FORCEINLINE bool UseCachedLocation() const { return bCachedLocation; }

						FORCEINLINE void SetCachedLocation(const FVector& Value)
						{
							CachedLocation  = Value;
							bCachedLocation = true;
						}

						FORCEINLINE bool UseCachedDirection() const { return bCachedDirection; }

						FORCEINLINE void SetCachedDirection(const FVector& Value)
						{
							CachedDirection  = Value;
							bCachedDirection = true;
						}
					};

					/** 
					* Describes any information for Spread being applied to a "Shot" (i.e. the Projectile being "launched" ).
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSWP_API FSpread
					{
					public:

					// Location

						/** Whether an offset should be applied to Location the Projectile is "launched" from. */
						bool bOffset;
						FVector Offset;

					// Direction

						/** The Axis to apply any Yaw or Pitch to the Direction the Projectile is "launched" from. 
							NOTE: This is a Mask based on ECsRotationRules. 
								  Pitch = 1 << 0 = 1
								  Yaw	= 1 << 1 = 2
								  Roll	= 1 << 2 = 4
								  Pitch + Yaw + Roll = 7
								  Pitch + Yaw = 3 */
						int32 Axis;

						/** Whether to apply any Yaw to the Direction along Axis. */
						bool bYaw;
						/** The Yaw to apply to the Direction along Axis. */
						float Yaw;

						/** Whether to apply any Pitch to the Direction along Axis. */
						bool bPitch;
						/** The Pitch to apply to the Direction along Axis. */
						float Pitch;

						FSpread() :
							bOffset(false),
							Offset(0.0f),
							Axis(0),
							bYaw(false),
							Yaw(0.0f),
							bPitch(false),
							Pitch(0.0f)
						{
						}

						FORCEINLINE bool HasOffset() const { return bOffset; }
				
						FORCEINLINE void SetOffset(const FVector& Value)
						{
							if (Value != FVector::ZeroVector)
							{
								Offset = Value;
								bOffset = true;
							}
						}

						FORCEINLINE bool HasYaw() const { return bYaw; }

						FORCEINLINE void SetYaw(const float& Value)
						{
							if (Value != 0.0f)
							{
								Yaw = Value;
								bYaw = true;
							}
						}

						FORCEINLINE bool HasPitch() const { return bPitch; }

						FORCEINLINE void SetPitch(const float& Value)
						{
							if (Value != 0.0f)
							{
								Pitch = Value;
								bPitch = true;
							}
						}
					};

					/**
					* Describes any information for a Projectile being "launched".
					*  Projectile is an object that implements the interface: ICsProjectile
					*/
					struct CSWP_API FPayload
					{
					private:

						using ShotType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FShot;
						using SpreadType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FSpread;

					public:

						ShotType Shot;

						/** Whether to use any Spread applied to the "launch". */
						bool bSpread;

						SpreadType Spread;

						FPayload() :
							Shot(),
							bSpread(false),
							Spread()
						{
						}
			
						FORCEINLINE bool HasSpread() const { return bSpread; }
					};
				}
			}
		}
	}
}

UINTERFACE(BlueprintType)
class CSWP_API UCsWeapon_Fire_Projectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class USceneComponent;

/**
* Interface that describes "launching" a Projectile for a "Shot" in a Fire Action for a Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*  A Fire Action can be comprised of many (one or more) "Shots".
*  This interface is typically implemented as a component of a Weapon.
*/
class CSWP_API ICsWeapon_Fire_Projectile
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using PayloadType = NCsWeapon::NFire::NProjectile::NLaunch::NPayload::FPayload;
	};

public:

	/**
	* Set a Component to use as the Location at which a Projectile is "launched".
	* 
	* @param Component
	*/
	virtual void SetLaunchComponentLocation(USceneComponent* Component) = 0;
	
	/**
	* Set a Component to use as the Direction a Projectile is "launched".
	* 
	* @param Component
	*/
	virtual void SetLaunchComponentDirection(USceneComponent* Component) = 0;

	/**
	* Get the Location a Projectile should be "launched" from based on a Payload.
	* 
	* @param Payload.
	*/
	virtual FVector GetLaunchLocation(const _::PayloadType& Payload) = 0;

	/**
	* Get the Location a Projectile should be "launched" from.
	*  NOTE: This assumes a "default" Payload.
	*/
	virtual FVector GetLaunchLocation() = 0;


	virtual FVector GetLaunchDirection(const _::PayloadType& LaunchPayload) = 0;


	virtual FVector GetLaunchDirection()  = 0;

	virtual void Launch(const _::PayloadType& LaunchPayload) = 0;

	virtual void Clear() = 0;
};