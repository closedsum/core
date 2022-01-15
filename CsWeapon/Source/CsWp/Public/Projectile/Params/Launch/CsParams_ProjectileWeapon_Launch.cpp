// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"

const FName NCsWeapon::NProjectile::NParams::NLaunch::ILaunch::Name = FName("NCsWeapon::NProjectile::NParams::NLaunch::ILaunch");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
			// Location
			#pragma region

				namespace NLocation
				{
					namespace Ref
					{
						typedef EMLocation EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
						CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
						CSWP_API CS_ADD_TO_ENUM_MAP(Component);
						CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
					}
				}

			#pragma endregion Location

			// Direction
			#pragma region

				namespace NDirection
				{
					namespace Ref
					{
						typedef EMDirection EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
						CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
						CSWP_API CS_ADD_TO_ENUM_MAP(Component);
						CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
						CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
						CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
					}
				}

			#pragma endregion Direction
			}
		}
	}
}
