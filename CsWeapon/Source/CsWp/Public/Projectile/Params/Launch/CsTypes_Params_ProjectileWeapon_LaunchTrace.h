// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/Trace/CsTypes_Trace.h"
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_Params_ProjectileWeapon_LaunchTrace.generated.h"
#pragma once

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

#pragma endregion ProjectileWeaponLaunchTraceDirection

// FCsScriptProjectileWeaponLaunchTraceParams
#pragma region

// NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, FImpl)

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponLaunchTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchLocation LocationType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchDirection DirectionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceType TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceMethod TraceMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchTraceStart TraceStartType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchTraceDirection TraceDirectionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TraceDistance;

	FCsProjectileWeaponLaunchTraceParams() :
		LocationType(ECsProjectileWeaponLaunchLocation::Owner),
		DirectionType(ECsProjectileWeaponLaunchDirection::Owner),
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

	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;

#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsScriptProjectileWeaponLaunchTraceParams