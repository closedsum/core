// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsWpLog.h"

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

// FCsProjectileWeapon_Launch_LocationParams
#pragma region

// NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NLocation, FParams)

/**
* Describes any Location information related to Launching a Projectile from a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Launch_LocationParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a Projectile will be launched from a Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchLocation Type;

	/** Describes the "Space" the location offset is applied to the Location a Projectile is Launched. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchLocationOffsetSpace OffsetSpace;

	/** Describes which components (Pitch, Yaw, and/or Roll) or Rotation / Direction from LocationOffsetSpace will
		affect the LocationOffset. Components NOT affected will result the LocationOffset applied "directly" in World Space. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 OffsetSpaceRules;

	/** The offset to apply to the Rotation determined from LocationOffsetSpace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FRotator OffsetSpaceOffset;

	/** An offset applied to the start position a Projectile will be Launched. 
		This is always applied in the "Space" defined by LocationOffsetSpace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FVector Offset;

	FCsProjectileWeapon_Launch_LocationParams() :
		Type(ECsProjectileWeaponLaunchLocation::Owner),
		OffsetSpace(ECsProjectileWeaponLaunchLocationOffsetSpace::Owner),
		OffsetSpaceRules(CS_ROTATION_FLAGS_YAW),
		OffsetSpaceOffset(0.0f),
		Offset(0.0f)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

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
					* Describes any Location information related to Launching a Projectile from a Projectile Weapon.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSWP_API FParams
					{
					#define LocationType NCsWeapon::NProjectile::NParams::NLaunch::ELocation
					#define LocationOffsetSpace NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace

					private:

						/** Describes the different methods to get the Location from which a Projectile will be launched from a Weapon. */
						CS_DECLARE_MEMBER_WITH_PROXY(Type, LocationType)
						/** Describes the "Space" the location offset is applied to the Location a Projectile is Launched. */
						CS_DECLARE_MEMBER_WITH_PROXY(OffsetSpace, LocationOffsetSpace)
						/** Describes which components (Pitch, Yaw, and/or Roll) or Rotation / Direction from LocationOffsetSpace will
							affect the LocationOffset. Components NOT affected will result the LocationOffset applied "directly" in World Space. */
						CS_DECLARE_MEMBER_WITH_PROXY(OffsetSpaceRules, int32)
						/** The offset to apply to the Rotation determined from LocationOffsetSpace. */
						CS_DECLARE_MEMBER_WITH_PROXY(OffsetSpaceOffset, FRotator)
						/** An offset applied to the start position a Projectile will be Launched. 
							This is always applied in the "Space" defined by LocationOffsetSpace. */
						CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, LocationType::Owner),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(OffsetSpace, LocationOffsetSpace::Owner),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(OffsetSpaceRules, CS_ROTATION_FLAGS_YAW),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(OffsetSpaceOffset, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(Type);
							CS_CTOR_SET_MEMBER_PROXY(OffsetSpace);
							CS_CTOR_SET_MEMBER_PROXY(OffsetSpaceRules);
							CS_CTOR_SET_MEMBER_PROXY(OffsetSpaceOffset);
							CS_CTOR_SET_MEMBER_PROXY(Offset);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, LocationType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OffsetSpace, LocationOffsetSpace)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OffsetSpaceRules, int32)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(OffsetSpaceOffset, FRotator)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector)
					
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef LocationType
					#undef LocationOffsetSpace
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_LocationParams

// FCsProjectileWeapon_Launch_DirectionParams
#pragma region

// NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NDirection, FParams)

/**
* Describes any Direction information related to Launching a Projectile from a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Launch_DirectionParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Direction a Projectile will be Launched. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchDirection Type;

	/** An offset applied to the start direction a Projectile will be Launched.  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FRotator Offset;

	/** Whether the Direction from which the Projectile will be launched from a Weapon should be inverted (multiplied by -1.0f). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	bool bInvert;

	/** Describes which components (Pitch, Yaw, and/or Roll) will be used for the Direction a Projectile will be Launched. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 Rules;

	FCsProjectileWeapon_Launch_DirectionParams() :
		Type(ECsProjectileWeaponLaunchDirection::Owner),
		Offset(0.0f),
		bInvert(false),
		Rules(CS_ROTATION_FLAGS_NONE)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NDirection
				{
					/**
					* Describes any Direction information related to Launching a Projectile from a Projectile Weapon.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSWP_API FParams
					{
					#define DirectionType NCsWeapon::NProjectile::NParams::NLaunch::EDirection

					private:

						/** Describes the different methods to get the Direction a Projectile will be Launched. */
						CS_DECLARE_MEMBER_WITH_PROXY(Type, DirectionType)
						/** An offset applied to the start direction a Projectile will be Launched.  */
						CS_DECLARE_MEMBER_WITH_PROXY(Offset, FRotator)
						/** Whether the Direction from which the Projectile will be launched from a Weapon should be inverted (multiplied by -1.0f). */
						CS_DECLARE_MEMBER_WITH_PROXY(bInvert, bool)
						/** Describes which components (Pitch, Yaw, and/or Roll) will be used for the Direction a Projectile will be Launched. */
						CS_DECLARE_MEMBER_WITH_PROXY(Rules, int32)
						

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, DirectionType::Owner),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bInvert, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Rules, CS_ROTATION_FLAGS_YAW)
						{
							CS_CTOR_SET_MEMBER_PROXY(Type);
							CS_CTOR_SET_MEMBER_PROXY(Offset);
							CS_CTOR_SET_MEMBER_PROXY(bInvert);
							CS_CTOR_SET_MEMBER_PROXY(Rules);			
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, DirectionType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FRotator)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInvert, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Rules, int32)
					
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

					#undef DirectionType
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_DirectionParams