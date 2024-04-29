// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Point/Data/Sound/Fire/CsTypes_PointWeapon_SoundFire.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_PointWeapon_SoundFire.generated.h"

// FCsPointWeapon_SoundFire_Params
#pragma region

// NCsWeapon::NPoint::NFire::NSound::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NPoint, NFire, NSound, FParams)

/**
* Describes any Sound information related to the Fire action for a Point Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Point Weapon is an object that implements the interface: ICsPointWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsPointWeapon_SoundFire_Params
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which Sound to play when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	FCsSound Sound;

	/** How the Sound should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Point")
	ECsPointWeaponSoundFireAttach Attach;

	FCsPointWeapon_SoundFire_Params() :
		Sound(),
		Attach(ECsPointWeaponSoundFireAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NPoint::NFire::NSound::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsPointWeapon_SoundFire_Params

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NFire
		{
			namespace NSound
			{
				/**
					* Describes any Sound information related to the Fire action for a Point Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Point Weapon is an object that implements the interface: ICsPointWeapon.
					*/
					struct CSWP_API FParams
					{
					#define AttachType NCsWeapon::NPoint::NFire::NSound::EAttach

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