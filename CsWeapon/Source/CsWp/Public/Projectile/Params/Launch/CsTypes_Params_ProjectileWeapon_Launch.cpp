// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"

// Library
#include "Library/CsLibrary_Valid.h"

// ProjectileWeaponLaunchLocation
#pragma region

namespace NCsProjectileWeaponLaunchLocation
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchLocation EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchLocation_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchLocation_MAX;
}

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
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ELocation_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchLocation

// ProjectileWeaponLaunchLocationOffsetSpace
#pragma region

namespace NCsProjectileWeaponLaunchLocationOffsetSpace
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchLocationOffsetSpace EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchLocationOffsetSpace_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchLocationOffsetSpace_MAX;
}

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
					namespace NOffsetSpace
					{
						namespace Ref
						{
							typedef EMOffsetSpace EnumMapType;

							CSWP_API CS_ADD_TO_ENUM_MAP(None);
							CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
							CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
							CSWP_API CS_ADD_TO_ENUM_MAP(Component);
							CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
							CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
							CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EOffsetSpace_MAX, "MAX");
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchLocationOffsetSpace

// ProjectileWeaponLaunchDirection
#pragma region

namespace NCsProjectileWeaponLaunchDirection
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchDirection_MAX;
}

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
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchDirection

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
					bool FParams::IsValidChecked(const FString& Context) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::EMLocation LocationMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EMOffsetSpace LocationOffsetSpaceMap;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace LocationOffsetSpace;

						CS_IS_ENUM_VALID_CHECKED(LocationMapType, GetType())
						CS_IS_ENUM_VALID_CHECKED(LocationOffsetSpaceMap, GetOffsetSpace())

						if (GetOffsetSpace() != LocationOffsetSpace::None)
						{
							checkf(GetOffsetSpaceRules() != NCsRotationRules::None, TEXT("%s: No Rules set for GetOffsetSpace(), GetOffsetSpaceRules() == 0."), *Context);
						}
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::EMLocation LocationMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LocationType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EMOffsetSpace LocationOffsetSpaceMap;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace LocationOffsetSpace;

						CS_IS_ENUM_VALID(LocationMapType, LocationType, GetType())
						CS_IS_ENUM_VALID(LocationOffsetSpaceMap, LocationOffsetSpace, GetOffsetSpace())

						if (GetOffsetSpace() == LocationOffsetSpace::None)
						{
							if (GetOffsetSpaceRules() == NCsRotationRules::None)
							{
								CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Rules set for GetOffsetSpace(), GetOffsetSpaceRules() == 0."), *Context));
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}
}