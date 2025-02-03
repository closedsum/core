// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Params_ProjectileWeapon_Launch)

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

namespace NCsProjectileWeapon_Launch_LocationParams
{
	using LocationType = NCsWeapon::NProjectile::NParams::NLaunch::ELocation;
	using OffsetSpaceType = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EOffsetSpace;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Type, LocationType);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, OffsetSpace, OffsetSpaceType);
		CS_THIS_COPY_TO_PROXY(Params, OffsetSpaceRules);
		CS_THIS_COPY_TO_PROXY(Params, OffsetSpaceOffset);
		CS_THIS_COPY_TO_PROXY(Params, Offset);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Type, LocationType);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, OffsetSpace, OffsetSpaceType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, OffsetSpaceRules);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, OffsetSpaceOffset);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Offset);
	}
}

bool FCsProjectileWeapon_Launch_LocationParams::IsValidChecked(const FString& Context) const
{
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
					using LocationMapType = NCsWeapon::NProjectile::NParams::NLaunch::EMLocation;
					using LocationOffsetSpaceMap = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::EMOffsetSpace;

					bool FParams::IsValidChecked(const FString& Context) const
					{
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

namespace NCsProjectileWeapon_Launch_DirectionParams
{
	using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::EDirection;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Type, DirectionType);
		CS_THIS_COPY_TO_PROXY(Params, bInvert);
		CS_THIS_COPY_TO_PROXY(Params, Offset);
		CS_THIS_COPY_TO_PROXY(Params, Rules);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Type, DirectionType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bInvert);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Offset);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Rules);
	}
}

bool FCsProjectileWeapon_Launch_DirectionParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Type)

	checkf(Rules != NCsRotationRules::None, TEXT("%s: No Rules set for Type, Rules == 0."), *Context);
	return true;
}

bool FCsProjectileWeapon_Launch_DirectionParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
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
					using DirectionMapType = NCsWeapon::NProjectile::NParams::NLaunch::EMDirection;

					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetType())

						checkf(GetRules() != NCsRotationRules::None, TEXT("%s: No Rules set for GetType(), GetRules() == 0."), *Context);
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
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