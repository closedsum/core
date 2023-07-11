// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Sound/CsTypes_Sound.h"
#include "Point/Sequence/Data/Sound/Fire/CsTypes_PointSequenceWeapon_SoundFire.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointSequenceWeapon_SoundFire.generated.h"

// FCsPointSequenceWeapon_Sound_FireParams
#pragma region

// NCsWeapon::NPoint::NSequence::NFire::NSound::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NPoint, NSequence, NFire, NSound, FParams)

/**
* Describes any Sound information related to the Fire action for a Point Sequence Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointSequenceWeapon_Sound_FireParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which Sound to play when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FCsSound Sound;

	/** How the Sound should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointSequenceWeaponSoundFireAttach Attach;

	FCsPointSequenceWeapon_Sound_FireParams() :
		Sound(),
		Attach(ECsPointSequenceWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NPoint::NSequence::NFire::NSound::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NFire
			{
				namespace NSound
				{
					/**
						* Describes any Sound information related to the Fire action for a Point Sequence Weapon.
						*  Weapon is an object that implements the interface: ICsWeapon.
						*  Point Sequence Weapon is an object that implements the interface: ICsPointSequenceWeapon.
						*/
						struct CSWP_API FParams
						{
						#define AttachType NCsWeapon::NPoint::NSequence::NFire::NSound::EAttach

						private:

							/** Which Sound to play when the Fire action is executed. */
							CS_DECLARE_MEMBER_WITH_PROXY(Sound, FCsSound)
							/** How the Sound should be attached. */
							CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

						public:

							FParams() :
								CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Sound),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::Component)
							{

							}

							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Sound, FCsSound)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)

						public:

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

						#undef AttachType
						};
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Sound_FireParams