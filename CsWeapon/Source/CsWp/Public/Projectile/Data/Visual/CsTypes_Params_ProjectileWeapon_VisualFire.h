// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Params_ProjectileWeapon_VisualFire.generated.h"
#pragma once

// ProjectileWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponVisualFireAttach : uint8
{
	None									UMETA(DisplayName = "None"),
	Owner									UMETA(DisplayName = "Owner"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponVisualFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsProjectileWeaponVisualFireAttach : public TCsEnumMap<ECsProjectileWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponVisualFireAttach, ECsProjectileWeaponVisualFireAttach)
};

namespace NCsProjectileWeaponVisualFireAttach
{
	typedef ECsProjectileWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsProjectileWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion ProjectileWeaponLaunchTraceStart

// FCsProjectileWeaponVisualFireParams
#pragma region

// NCsWeapon::NProjectile::NData::NVisual::NFire::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NData, NVisual, NFire, FParams)

USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeaponVisualFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsProjectileWeaponVisualFireAttach Attach;

	FCsProjectileWeaponVisualFireParams() :
		FX(),
		Attach(ECsProjectileWeaponVisualFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams

	void CopyParams(ParamsType* Params);

#undef ParamsType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsProjectileWeaponVisualFireParams