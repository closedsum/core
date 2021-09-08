// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"

#include "CsTypes_Params_BeamWeapon_SoundFire.generated.h"
#pragma once

// BeamWeaponSoundFireAttach
#pragma region

/**
* Describes where the Fire Sound should be played from on the weapon.
*/
UENUM(BlueprintType)
enum class ECsBeamWeaponSoundFireAttach : uint8
{
	None								UMETA(DisplayName = "None"),
	Owner								UMETA(DisplayName = "Owner"),
	Component							UMETA(DisplayName = "Component"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsBeamWeaponSoundFireAttach_MAX	UMETA(Hidden),
};


struct CSWP_API EMCsBeamWeaponSoundFireAttach : public TCsEnumMap<ECsBeamWeaponSoundFireAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamWeaponSoundFireAttach, ECsBeamWeaponSoundFireAttach)
};

namespace NCsBeamWeaponSoundFireAttach
{
	typedef ECsBeamWeaponSoundFireAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsBeamWeaponSoundFireAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

#pragma endregion BeamWeaponSoundFireAttach

// FCsBeamWeaponSoundFireParams
#pragma region

CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NBeam, NData, NSound, NFire, NParams, FProxy)

USTRUCT(BlueprintType)
struct CSWP_API FCsBeamWeaponSoundFireParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsBeamWeaponSoundFireAttach Attach;

	FCsBeamWeaponSoundFireParams() :
		Sound(),
		Attach(ECsBeamWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NBeam::NData::NSound::NFire::NParams::FProxy
	void CopyToParams(ParamsType* Params);
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsBeamWeaponSoundFireParams