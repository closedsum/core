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

// FCsProjectileWeapon_Launch_LocationParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams

void FCsProjectileWeapon_Launch_LocationParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LocationType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace OffsetSpaceType;

	Params->SetType((LocationType*)(&Type));
	Params->SetOffsetSpace((OffsetSpaceType*)(&OffsetSpace));
	Params->SetOffsetSpaceRules(&OffsetSpaceRules),
	Params->SetOffsetSpaceOffset(&OffsetSpaceOffset);
	Params->SetOffset(&Offset);
}

void FCsProjectileWeapon_Launch_LocationParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::ELocation LocationType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace OffsetSpaceType;

	Params->SetType((LocationType)Type);
	Params->SetOffsetSpace((OffsetSpaceType)OffsetSpace);
	Params->SetOffsetSpaceRules(OffsetSpaceRules),
	Params->SetOffsetSpaceOffset(OffsetSpaceOffset);
	Params->SetOffset(Offset);
}

#undef ParamsType

bool FCsProjectileWeapon_Launch_LocationParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsProjectileWeaponLaunchLocation LocationMapType;
	typedef EMCsProjectileWeaponLaunchLocationOffsetSpace LocationOffsetSpaceMap;
	typedef ECsProjectileWeaponLaunchLocationOffsetSpace LocationOffsetSpace;

	CS_IS_ENUM_VALID_CHECKED(LocationMapType, Type)
	CS_IS_ENUM_VALID_CHECKED(LocationOffsetSpaceMap, OffsetSpace)

	if (OffsetSpace != LocationOffsetSpace::None)
	{
		checkf(OffsetSpaceRules != NCsRotationRules::None, TEXT("%s: No Rules set for OffsetSpace, OffsetSpaceRules == 0."), *Context);
	}
	return true;
}

bool FCsProjectileWeapon_Launch_LocationParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsProjectileWeaponLaunchLocation LocationMapType;
	typedef ECsProjectileWeaponLaunchLocation LocationType;
	typedef EMCsProjectileWeaponLaunchLocationOffsetSpace LocationOffsetSpaceMap;
	typedef ECsProjectileWeaponLaunchLocationOffsetSpace LocationOffsetSpace;

	CS_IS_ENUM_VALID(LocationMapType, LocationType, Type)
	CS_IS_ENUM_VALID(LocationOffsetSpaceMap, LocationOffsetSpace, OffsetSpace)

	if (OffsetSpace == LocationOffsetSpace::None)
	{
		if (OffsetSpaceRules == NCsRotationRules::None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Rules set for OffsetSpace, OffsetSpaceRules == 0."), *Context));
			return false;
		}
	}
	return true;
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

#pragma endregion FCsProjectileWeapon_Launch_LocationParams

// FCsProjectileWeapon_Launch_DirectionParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams

void FCsProjectileWeapon_Launch_DirectionParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection DirectionType;

	Params->SetType((DirectionType*)(&Type));
	Params->SetbInvert(&bInvert);
	Params->SetOffset(&Offset);
	Params->SetRules(&Rules);
}

void FCsProjectileWeapon_Launch_DirectionParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection DirectionType;

	Params->SetType((DirectionType)Type);
	Params->SetbInvert(bInvert);
	Params->SetOffset(Offset);
	Params->SetRules(Rules);
}

#undef ParamsType

bool FCsProjectileWeapon_Launch_DirectionParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsProjectileWeaponLaunchDirection DirectionMapType;

	CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Type)

	checkf(Rules != NCsRotationRules::None, TEXT("%s: No Rules set for Type, Rules == 0."), *Context);
	return true;
}

bool FCsProjectileWeapon_Launch_DirectionParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsProjectileWeaponLaunchDirection DirectionMapType;
	typedef ECsProjectileWeaponLaunchDirection DirectionType;

	CS_IS_ENUM_VALID(DirectionMapType, DirectionType, Type)

	if (Rules == NCsRotationRules::None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Rules set for Type, Rules == 0."), *Context));
		return false;
	}
	return true;
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
					bool FParams::IsValidChecked(const FString& Context) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::EMDirection DirectionMapType;

						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetType())

						checkf(GetRules() != NCsRotationRules::None, TEXT("%s: No Rules set for GetType(), GetRules() == 0."), *Context);
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::EMDirection DirectionMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection DirectionType;

						CS_IS_ENUM_VALID(DirectionMapType, DirectionType, GetType())

						if (GetRules() == NCsRotationRules::None)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Rules set for GetType(), GetRules() == 0."), *Context));
							return false;
						}
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_LocationParams