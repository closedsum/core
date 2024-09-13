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

// FCsProjectileWeapon_Fire_Visual_StartParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::NStart::FParams

void FCsProjectileWeapon_Fire_Visual_StartParams::CopyToParams(ParamsType* Params)
{
	Params->SetFX(&FX);

	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType*)(&Attach));
}

void FCsProjectileWeapon_Fire_Visual_StartParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetFX(FX);

	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType)Attach);
}

#undef ParamsType

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

						typedef NCsWeapon::NProjectile::NFire::NVisual::EMAttach AttachMapType;

						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetFX())

						typedef NCsWeapon::NProjectile::NFire::NVisual::EMAttach AttachMapType;
						typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

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

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::NShot::FParams

void FCsProjectileWeapon_Fire_Visual_ShotParams::CopyToParams(ParamsType* Params)
{
	Params->SetbSkipFirst(&bSkipFirst);
	Params->SetFX(&FX);

	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType*)(&Attach));
}

void FCsProjectileWeapon_Fire_Visual_ShotParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbSkipFirst(bSkipFirst);
	Params->SetFX(FX);

	typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType)Attach);
}

#undef ParamsType

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

						typedef NCsWeapon::NProjectile::NFire::NVisual::EMAttach AttachMapType;

						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetFX())

						typedef NCsWeapon::NProjectile::NFire::NVisual::EMAttach AttachMapType;
						typedef NCsWeapon::NProjectile::NFire::NVisual::EAttach AttachType;

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

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::FParams

void FCsProjectileWeapon_Fire_VisualParams::CopyToParams(ParamsType* Params)
{
	Params->SetbStartParams(&bStartParams);
	StartParams.CopyToParams(Params->GetStartParamsPtr());
	Params->SetbShotParams(&bShotParams);
	ShotParams.CopyToParams(Params->GetShotParamsPtr());
}

void FCsProjectileWeapon_Fire_VisualParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbStartParams(bStartParams);
	StartParams.CopyToParamsAsValue(Params->GetStartParamsPtr());
	Params->SetbShotParams(bShotParams);
	ShotParams.CopyToParamsAsValue(Params->GetShotParamsPtr());
}

#undef ParamsType

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