// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_Launch.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeapon.h"

// Location (NCsWeapon::NProjectile::NParams::NLaunch::ELocation)
#pragma region

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
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
			}
		}
	}
}

#pragma endregion Location (NCsWeapon::NProjectile::NParams::NLaunch::ELocation)

// Direction (NCsWeapon::NProjectile::NParams::NLaunch::EDirection)
#pragma region

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
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
			}
		}
	}
}

#pragma endregion Direction (NCsWeapon::NProjectile::NParams::NLaunch::EDirection)

const FName NCsWeapon::NProjectile::NParams::NLaunch::ILaunch::Name = FName("NCsWeapon::NProjectile::NParams::NLaunch::ILaunch");