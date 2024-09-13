// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/Fire/CsTypes_ProjectileWeapon_SoundFire.h"

#include "Projectile/Data/Sound/Fire/CsParams_ProjectileWeapon_SoundFire.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_ProjectileWeapon_SoundFire)

// ProjectileWeaponFireSoundAttach
#pragma region

namespace NCsProjectileWeaponFireSoundAttach
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponFireSoundAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponFireSoundAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponFireSoundAttach_MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
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

#pragma endregion ProjectileWeaponFireSoundAttach