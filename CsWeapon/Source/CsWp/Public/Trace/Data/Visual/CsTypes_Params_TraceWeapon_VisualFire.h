// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"

#include "CsTypes_Params_TraceWeapon_VisualFire.generated.h"
#pragma once

// TraceWeaponVisualFireAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the weapon.
*/
UENUM(BlueprintType)
enum class ECsTraceWeaponVisualFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsTraceWeaponVisualFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsTraceWeaponVisualFireAttach : public TCsEnumMap<ECsTraceWeaponVisualFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceWeaponVisualFireAttach, ECsTraceWeaponVisualFireAttach)
};

namespace NCsTraceWeaponVisualFireAttach
{
	typedef ECsTraceWeaponVisualFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsTraceWeaponVisualFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponVisualFireAttach

// FCsTraceWeaponVisualFireParams
#pragma region

// NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FProxy
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NTrace, NData, NVisual, NFire, NParams, FProxy)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponVisualFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponVisualFireAttach Attach;

	FCsTraceWeaponVisualFireParams() :
		FX(),
		Attach(ECsTraceWeaponVisualFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NTrace::NData::NVisual::NFire::NParams::FProxy

	void CopyParams(ParamsType* Params);

#undef ParamsType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponVisualFireParams