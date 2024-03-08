// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Params_BeamWeapon_VisualFire.generated.h"
#pragma once

// BeamWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsBeamWeaponVisualFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsBeamWeaponVisualFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsBeamWeaponVisualFireAttach : public TCsEnumMap<ECsBeamWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamWeaponVisualFireAttach, ECsBeamWeaponVisualFireAttach)
};

namespace NCsBeamWeaponVisualFireAttach
{
	typedef ECsBeamWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsBeamWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion BeamWeaponVisualFireAttach

// FCsBeamWeaponVisualFireParams
#pragma region

// NCsWeapon::NBeam::NData::NVisual::NFire::NParams::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NBeam, NData, NVisual, NFire, NParams, FProxy)

USTRUCT(BlueprintType)
struct CSWP_API FCsBeamWeaponVisualFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamWeaponVisualFireAttach Attach;

	FCsBeamWeaponVisualFireParams() :
		FX(),
		Attach(ECsBeamWeaponVisualFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NBeam::NData::NVisual::NFire::NParams::FProxy
	void CopyToParams(ParamsType* Params);
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsBeamWeaponVisualFireParams