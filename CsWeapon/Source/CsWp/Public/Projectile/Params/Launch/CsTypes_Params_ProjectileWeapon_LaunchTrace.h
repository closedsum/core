// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/Trace/CsTypes_Trace.h"

#include "CsTypes_Params_ProjectileWeapon_LaunchTrace.generated.h"
#pragma once

// ProjectileWeaponLaunchTraceStart
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchTraceStart : uint8
{
	LaunchLocation							UMETA(DisplayName = "Owner"),
	Camera									UMETA(DisplayName = "Bone"),
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
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type ECsProjectileWeaponLaunchTraceStart_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponLaunchTraceStart

USTRUCT(BlueprintType)
struct CSWP_API FCsScriptProjectileWeaponLaunchTraceParams
{
	GENERATED_USTRUCT_BODY()

	ECsProjectileWeaponLaunchLocation Location;

	// Direction

	ECsTraceType TraceType;

	ECsTraceMethod TraceMethod;

	ECsProjectileWeaponLaunchTraceStart TraceStart;

	// TraceDirection

	float TraceDistance;

	FCsScriptProjectileWeaponLaunchTraceParams()
	{
	}
};