// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Params_ProjectileWeapon_Launch.generated.h"

// ProjectileWeaponLaunchLocation
#pragma region

/**
* Describes the different methods to get the Location a Projectile is Launched 
* from a Projectile Weapon.
*  Projectile is an object that implements the interface: ICsProjectile
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchLocation : uint8
{
	/** Owner's Location. If the Owner is of type: AActor, then it will
		GetActorLocation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the 
		Weapon, use the Bone / Socket location. */
	Bone									UMETA(DisplayName = "Bone"),
	/** SceneComponent's Location. The Component is marked as the Launch Component Location. */
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchLocation_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponLaunchLocation : public TCsEnumMap<ECsProjectileWeaponLaunchLocation>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchLocation, ECsProjectileWeaponLaunchLocation)
};

namespace NCsProjectileWeaponLaunchLocation
{
	typedef ECsProjectileWeaponLaunchLocation Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchLocation_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				* Describes the different methods to get the Location a Projectile will Launch
				* from a Projectile Weapon.
				*  Projectile is an object that implements the interface: ICsProjectile
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				enum class ELocation : uint8
				{
					/** Owner's Location. If the Owner is of type: AActor, then it will
						be GetActorLocation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the
						Weapon, use the Bone / Socket location. */
					Bone,
					/** SceneComponent's Location. The Component is marked as the Launch Component Location. */
					Component,
					Custom,
					ELocation_MAX
				};

				struct CSWP_API EMLocation : public TCsEnumMap<ELocation>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMLocation, ELocation)
				};

				namespace NLocation
				{
					typedef ELocation Type;

					namespace Ref
					{
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Custom;
						extern CSWP_API const Type ELocation_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchLocation

// ProjectileWeaponLaunchLocationOffsetSpace
#pragma region

/**
* Describes the "Space" the location offset is applied to the Location a Projectile
* is Launched from a Projectile Weapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchLocationOffsetSpace : uint8
{
	/** The offset is applied directly in World Space. */
	None												UMETA(DisplayName = "None"),
	/** Owner's Rotation. If the Owner is of type: AActor, then it will
		GetActorRotation(). */
	Owner												UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone / Socket's rotation. */
	Bone												UMETA(DisplayName = "Bone"),
	/** SceneComponent's Rotation. The Component is marked as the Launch Component Direction. */
	Component											UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation. */
	Camera												UMETA(DisplayName = "Camera"),
	Custom												UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchLocationOffsetSpace_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponLaunchLocationOffsetSpace : public TCsEnumMap<ECsProjectileWeaponLaunchLocationOffsetSpace>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchLocationOffsetSpace, ECsProjectileWeaponLaunchLocationOffsetSpace)
};

namespace NCsProjectileWeaponLaunchLocationOffsetSpace
{
	typedef ECsProjectileWeaponLaunchLocationOffsetSpace Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchLocationOffsetSpace_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NLocation
				{
					/**
					* Describes the "Space" the location offset is applied to the Location a Projectile
					* is Launched from a Projectile Weapon.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*/
					enum class EOffsetSpace : uint8
					{
						/** The offset is applied directly in World Space. */
						None,
						/** Owner's Rotation. If the Owner is of type: AActor, then it will
							be GetActorRotation(). */
						Owner,
						/** If there is a SkeletalMesh that acts as the root object for the Weapon,
							use the Bone / Socket's rotation. */
						Bone,
						/** SceneComponent's Rotation. The Component is marked as the Launch Component Direction. */
						Component,
						/** Owner's Camera's Rotation. */
						Camera,
						Custom,
						EOffsetSpace_MAX
					};

					struct CSWP_API EMOffsetSpace : public TCsEnumMap<EOffsetSpace>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMOffsetSpace, EOffsetSpace)
					};

					namespace NOffsetSpace
					{
						typedef EOffsetSpace Type;

						namespace Ref
						{
							extern CSWP_API const Type None;
							extern CSWP_API const Type Owner;
							extern CSWP_API const Type Bone;
							extern CSWP_API const Type Component;
							extern CSWP_API const Type Camera;
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EOffsetSpace_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchLocationOffsetSpace

// ProjectileWeaponLaunchDirection
#pragma region

/**
* Describes the different methods to get the Direction a Projectile is Launched 
* from a Projectile Weapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchDirection : uint8
{
	/** Owner's Rotation. If the Owner is of type: AActor, then it will
		GetActorRotation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a SkeletalMesh that acts as the root object for the Weapon,
		use the Bone / Socket's rotation. */
	Bone									UMETA(DisplayName = "Bone"),
	/** SceneComponent's Rotation. The Component is marked as the Launch Component Direction. */
	Component								UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation. */
	Camera									UMETA(DisplayName = "Camera"),
	/** A trace is used to determine the direction. The start and end points of the
		trace are determined by other parameters. */
	Trace									UMETA(DisplayName = "Trace"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchDirection_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponLaunchDirection : public TCsEnumMap<ECsProjectileWeaponLaunchDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchDirection, ECsProjectileWeaponLaunchDirection)
};

namespace NCsProjectileWeaponLaunchDirection
{
	typedef ECsProjectileWeaponLaunchDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Trace;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				/**
				* Describes the different methods to get the Direction a Projectile is Launched
				* from a Projectile Weapon.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				enum class EDirection : uint8
				{
					/** Owner's Rotation. If the Owner is of type: AActor, then it will
						be GetActorRotation(). */
					Owner,
					/** If there is a SkeletalMesh that acts as the root object for the Weapon,
						use the Bone / Socket's rotation. */
					Bone,
					/** SceneComponent's Rotation. The Component is marked as the Launch Component Direction. */
					Component,
					/** Owner's Camera's Rotation. */
					Camera,
					/** A trace is used to determine the direction. The start and end points of the
						trace are determined by other parameters. */
					Trace,
					Custom,
					EDirection_MAX
				};

				struct CSWP_API EMDirection : public TCsEnumMap<EDirection>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
				};

				namespace NDirection
				{
					typedef EDirection Type;

					namespace Ref
					{
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Bone;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Camera;
						extern CSWP_API const Type Trace;
						extern CSWP_API const Type Custom;
						extern CSWP_API const Type EDirection_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchDirection