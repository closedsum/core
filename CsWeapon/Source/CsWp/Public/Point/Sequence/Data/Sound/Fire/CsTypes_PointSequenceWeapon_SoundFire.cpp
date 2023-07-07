// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Data/Sound/Fire/CsTypes_PointSequenceWeapon_SoundFire.h"

// PointSequenceWeaponSoundFireAttach
#pragma region

namespace NCsPointSequenceWeaponSoundFireAttach
{
	namespace Ref
	{
		typedef EMCsPointSequenceWeaponSoundFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointSequenceWeaponSoundFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsPointSequenceWeaponSoundFireAttach_MAX;
}

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
}

#pragma endregion PointSequenceWeaponSoundFireAttach