// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/Sound/Fire/CsTypes_PointWeapon_SoundFire.h"

// PointWeaponSoundFireAttach
#pragma region

namespace NCsPointWeaponSoundFireAttach
{
	namespace Ref
	{
		typedef EMCsPointWeaponSoundFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponSoundFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsPointWeaponSoundFireAttach_MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NFire
		{
			namespace NSound
			{
				namespace NAttach
				{
					namespace Ref
					{
						typedef EMAttach EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(None);
						CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
						CSWP_API CS_ADD_TO_ENUM_MAP(Component);
						CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAttach_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion PointWeaponSoundFireAttach