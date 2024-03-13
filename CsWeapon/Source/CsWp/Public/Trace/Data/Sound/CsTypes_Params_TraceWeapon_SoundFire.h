// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Sound/CsTypes_SoundPooled.h"

#include "CsTypes_Params_TraceWeapon_SoundFire.generated.h"

// TraceWeaponSoundFireAttach
#pragma region

/**
* Describes where the Fire Sound should be played from on the weapon.
*/
UENUM(BlueprintType)
enum class ECsTraceWeaponSoundFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsTraceWeaponSoundFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsTraceWeaponSoundFireAttach : public TCsEnumMap<ECsTraceWeaponSoundFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceWeaponSoundFireAttach, ECsTraceWeaponSoundFireAttach)
};

namespace NCsTraceWeaponSoundFireAttach
{
	typedef ECsTraceWeaponSoundFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsTraceWeaponSoundFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion TraceWeaponSoundFireAttach

// FCsTraceWeaponSoundFireParams
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NTrace, NData, NSound, NFire, NParams, FProxy)

USTRUCT(BlueprintType)
struct CSWP_API FCsTraceWeaponSoundFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsTraceWeaponSoundFireAttach Attach;

	FCsTraceWeaponSoundFireParams() :
		Sound(),
		Attach(ECsTraceWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NTrace::NData::NSound::NFire::NParams::FProxy

	void CopyParams(ParamsType* Params);

#undef ParamsType
	
	// NOTE: Added to get around compiler error when using #undef
private:
	FORCEINLINE void _Nothing(){}
};

#pragma endregion FCsTraceWeaponSoundFireParams