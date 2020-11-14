// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/Trace/CsTypes_Trace.h"
#include "Types/CsTypes_Math.h"

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

namespace NCsWeapon {
	namespace NProjectile {
		namespace NParams {
			namespace NLaunch {
				struct FTraceEmu; } } } }

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponLaunchTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchLocation Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsRotationRules"))
	int32 DirectionRules;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceType TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceMethod TraceMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchTraceStart TraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponLaunchTraceDirection TraceDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TraceDistance;

	FCsProjectileWeaponLaunchTraceParams() :
		Location(ECsProjectileWeaponLaunchLocation::Owner),
		Direction(ECsProjectileWeaponLaunchDirection::Owner),
		DirectionRules(CS_ROTATION_FLAGS_NONE),
		TraceType(ECsTraceType::Line),
		TraceMethod(ECsTraceMethod::Single),
		TraceStart(ECsProjectileWeaponLaunchTraceStart::LaunchLocation),
		TraceDirection(ECsProjectileWeaponLaunchTraceDirection::Owner),
		TraceDistance(1000.0f)
	{
	}

#define EmuType NCsWeapon::NProjectile::NParams::NLaunch::FTraceEmu

	void CopyParams(EmuType* Emu);

#undef EmuType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsScriptProjectileWeaponLaunchTraceParams