// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/Trace/CsTypes_Trace.h"
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_Params_ProjectileWeapon_LaunchTrace.generated.h"

// ProjectileWeaponLaunchTraceStart
#pragma region

/**
* Describes how the start of a trace should be chosen.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchTraceStart : uint8
{
	/** The launch location (the result from ILaunch::GetLocationType()) is used. */
	LaunchLocation							UMETA(DisplayName = "Launch Location"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		be GetActorLocation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
		use the Bone's location. */
	Bone									UMETA(DisplayName = "Bone"),
	/** SceneComponent's Location. The Component is marked as the Launch Component Transform. */
	Component								UMETA(DisplayName = "Component"),
	/** Owner's Camera's Location. */
	Camera									UMETA(DisplayName = "Camera"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchTraceStart_MAX	UMETA(Hidden), 
};

struct CSWP_API EMCsProjectileWeaponLaunchTraceStart : public TCsEnumMap<ECsProjectileWeaponLaunchTraceStart>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchTraceStart, ECsProjectileWeaponLaunchTraceStart)
};

namespace NCsProjectileWeaponLaunchTraceStart
{
	typedef ECsProjectileWeaponLaunchTraceStart Type;

	namespace Ref
	{
		extern CSWP_API const Type LaunchLocation;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchTraceStart_MAX;
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
				namespace NTrace
				{
					/**
					* Describes how the start of a trace should be chosen.
					*/
					enum class EStart : uint8 
					{
						/** The launch location (the result from ILaunch::GetLocationType()) is used. 
							See NCsWeapon::NCsProjectile::NParams::NLaunch::ELocation. */
						LaunchLocation,
						/** Owner's Location. If the Owner is of type: AActor, then it will
							be GetActorLocation(). */
						Owner,
						/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
							use the Bone's location. */
						Bone,
						/** SceneComponent's Location. The Component is marked as the Launch Component Transform. */
						Component,
						/** Owner's Camera's Location. */
						Camera,
						Custom,
						EStart_MAX
					};

					struct CSWP_API EMStart : public TCsEnumMap<EStart>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMStart, EStart)
					};

					namespace NStart
					{
						typedef EStart Type;

						namespace Ref
						{
							extern CSWP_API const Type LaunchLocation;
							extern CSWP_API const Type Owner;
							extern CSWP_API const Type Bone;
							extern CSWP_API const Type Component;
							extern CSWP_API const Type Camera;
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EStart_MAX;
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchTraceStart

// ProjectileWeaponLaunchTraceDirection
#pragma region

/**
* Describes how the direction (end) of a trace should be chosen. The normalized
* direction is used to project outward GetTraceDistance() from the start of the
* trace.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchTraceDirection : uint8
{
	/** Owner's Rotation (forward). If the Owner is of type: AActor, then use
		get the Owner's forward vector. */
	Owner										UMETA(DisplayName = "Owner"),
	/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
		then use the Bone's rotation (to normalized vector). */
	Bone										UMETA(DisplayName = "Bone"),
	/** SceneComponent's Rotation. The Component is marked as the Launch Component Transform. */
	Component									UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation (forward). */
	Camera										UMETA(DisplayName = "Camera"),
	Custom										UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchTraceDirection_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponLaunchTraceDirection : public TCsEnumMap<ECsProjectileWeaponLaunchTraceDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchTraceDirection, ECsProjectileWeaponLaunchTraceDirection)
};

namespace NCsProjectileWeaponLaunchTraceDirection
{
	typedef ECsProjectileWeaponLaunchTraceDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchTraceDirection_MAX;
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
				namespace NTrace
				{
					/**
					* Describes how the direction (end) of a trace should be chosen. The normalized
					* direction is used to project outward GetTraceDistance() from the start of the 
					* trace.
					*/
					enum class EDirection : uint8
					{
						/** Owner's Rotation (forward). If the Owner is of type: AActor, then use 
							get the Owner's forward vector. */
						Owner,
						/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
							then use the Bone's rotation (to normalized vector). */
						Bone,
						/** SceneComponent's Rotation. The Component is marked as the Launch Component Transform. */
						Component,
						/** Owner's Camera's Rotation (forward). */
						Camera,
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
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EDirection_MAX;
						}
					}
				}
			}
		}
	}
}
#pragma endregion ProjectileWeaponLaunchTraceDirection

// FCsProjectileWeapon_LaunchTraceParams
#pragma region

// NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, FImpl)

/**
* Describes any information related to Launching a Projectile using a Trace from a Projectile Weapon.
* The trace may determine the Location and/or Direction with which to Launch the Projectile.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_LaunchTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the different methods to get the Location from which a Projectile will be launched from a Weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchLocation LocationType;

	/** Describes the "Space" the location offset is applied to the Location a Projectile is Launched. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchLocationOffsetSpace LocationOffsetSpace;

	/** Describes which components (Pitch, Yaw, and/or Roll) or Rotation / Direction from LocationOffsetSpace will
		affect the LocationOffset. Components NOT affected will result the LocationOffset applied "directly" in World Space. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 LocationOffsetSpaceRules;

	/** The offset to apply to the Rotation determined from LocationOffsetSpace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FRotator LocationOffsetSpaceOffset;

	/** An offset applied to the start position a Projectile will be Launched. 
		This is always applied in the "Space" defined by LocationOffsetSpace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FVector LocationOffset;

	/** Describes the different methods to get the Direction a Projectile will be Launched. . */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchDirection DirectionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FRotator DirectionOffset;

	/** Whether the Direction from which the Projectile will be launched from a Weapon should be inverted (multiplied by -1.0f). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	bool bInvertDirection;

	/** Describes which components (Pitch, Yaw, and/or Roll) will be used for the Direction a Projectile will be Launched. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsTraceType TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsTraceMethod TraceMethod;

	/** Describes how the start of a trace should be chosen. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchTraceStart TraceStartType;

	/** Describes how the direction (end) of a trace should be chosen. The normalized
		direction is used to project outward GetTraceDistance() from the start of the
		trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchTraceDirection TraceDirectionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TraceDistance;

	FCsProjectileWeapon_LaunchTraceParams() :
		LocationType(ECsProjectileWeaponLaunchLocation::Owner),
		LocationOffsetSpace(ECsProjectileWeaponLaunchLocationOffsetSpace::Owner),
		LocationOffsetSpaceRules(CS_ROTATION_FLAGS_YAW),
		LocationOffsetSpaceOffset(0.0f),
		LocationOffset(0.0f),
		DirectionType(ECsProjectileWeaponLaunchDirection::Owner),
		DirectionOffset(0.0f),
		bInvertDirection(false),
		DirectionRules(CS_ROTATION_FLAGS_NONE),
		TraceType(ECsTraceType::Line),
		TraceMethod(ECsTraceMethod::Single),
		TraceStartType(ECsProjectileWeaponLaunchTraceStart::LaunchLocation),
		TraceDirectionType(ECsProjectileWeaponLaunchTraceDirection::Owner),
		TraceDistance(1000.0f)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl

	ParamsType* AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	ParamsType* AddSafeToSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

private:

	ParamsType* AddSafeToSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

public:

	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;

#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsProjectileWeapon_LaunchTraceParams