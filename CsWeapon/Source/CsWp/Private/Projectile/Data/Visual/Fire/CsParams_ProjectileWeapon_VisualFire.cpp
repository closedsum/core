// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Visual/Fire/CsParams_ProjectileWeapon_VisualFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_ProjectileWeapon_VisualFire)

// ProjectileWeaponFireVisualAttach
#pragma region

namespace NCsProjectileWeaponFireVisualAttach
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponFireVisualAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponFireVisualAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponFireVisualAttach_MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
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

#pragma endregion ProjectileWeaponFireVisualAttach

using AttachType = NCsWeapon::NProjectile::NFire::NVisual::EAttach;
using AttachMapType = NCsWeapon::NProjectile::NFire::NVisual::EMAttach;

// FCsProjectileWeapon_Fire_Visual_StartParams
#pragma region

namespace NCsProjectileWeapon_Fire_Visual_StartParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, FX);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Attach, AttachType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, FX);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Attach, AttachType);
	}
}

bool FCsProjectileWeapon_Fire_Visual_StartParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponFireVisualAttach, Attach)
	return true;
}

bool FCsProjectileWeapon_Fire_Visual_StartParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(FX)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponFireVisualAttach, ECsProjectileWeaponFireVisualAttach, Attach)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				namespace NStart
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetFX());
						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetFX())
						CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Visual_StartParams

// FCsProjectileWeapon_Fire_Visual_ShotParams
#pragma region

namespace NCsProjectileWeapon_Fire_Visual_ShotParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bSkipFirst);
		CS_THIS_COPY_TO_PROXY(Params, FX);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Attach, AttachType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bSkipFirst);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, FX);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Attach, AttachType);
	}
}

bool FCsProjectileWeapon_Fire_Visual_ShotParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponFireVisualAttach, Attach)
	return true;
}

bool FCsProjectileWeapon_Fire_Visual_ShotParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(FX)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponFireVisualAttach, ECsProjectileWeaponFireVisualAttach, Attach)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				namespace NShot
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetFX());
						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetFX())
						CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Visual_ShotParams

// FCsProjectileWeapon_Fire_VisualParams
#pragma region

namespace NCsProjectileWeapon_Fire_VisualParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bStartParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, StartParams);
		CS_THIS_COPY_TO_PROXY(Params, bShotParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, ShotParams);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bStartParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, StartParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bShotParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, ShotParams);
	}
}

bool FCsProjectileWeapon_Fire_VisualParams::IsValidChecked(const FString& Context) const
{
	if (bStartParams)
	{
		CS_IS_VALID_CHECKED(StartParams);
	}

	if (bShotParams)
	{
		CS_IS_VALID_CHECKED(ShotParams);
	}
	return true;
}

bool FCsProjectileWeapon_Fire_VisualParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (bStartParams)
	{
		CS_IS_VALID(StartParams)
	}
	
	if (bShotParams)
	{
		CS_IS_VALID(ShotParams)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					if (GetbStartParams())
					{
						CS_IS_VALID_CHECKED(GetStartParams());
					}

					if (GetbShotParams())
					{
						CS_IS_VALID_CHECKED(GetShotParams());
					}
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					if (GetbStartParams())
					{
						CS_IS_VALID(GetStartParams())
					}

					if (GetbShotParams())
					{
						CS_IS_VALID(GetShotParams())
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_SoundParams