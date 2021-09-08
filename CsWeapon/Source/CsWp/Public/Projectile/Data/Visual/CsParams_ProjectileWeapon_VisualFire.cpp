// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Visual/CsParams_ProjectileWeapon_VisualFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

// ProjectileWeaponVisualFireAttach
#pragma region

namespace NCsProjectileWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponVisualFireAttach_MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
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

#pragma endregion ProjectileWeaponVisualFireAttach


#define ParamsType NCsWeapon::NProjectile::NData::NVisual::NFire::FParams

void FCsProjectileWeapon_VisualFire_Params::CopyToParams(ParamsType* Params)
{
	Params->SetFX(&FX);
	Params->SetAttach(&Attach);
}

void FCsProjectileWeapon_VisualFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetFX(FX);
	Params->SetAttach(Attach);
}

#undef ParamsType

bool FCsProjectileWeapon_VisualFire_Params::IsValidChecked(const FString& Context) const
{
	check(FX.IsValidChecked(Context))

	EMCsProjectileWeaponVisualFireAttach::Get().IsValidEnumChecked(Context, Attach);
	return true;
}

bool FCsProjectileWeapon_VisualFire_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!FX.IsValid(Context, Log))
		return false;

	CS_IS_ENUM_VALID(EMCsProjectileWeaponVisualFireAttach, ECsProjectileWeaponVisualFireAttach, Attach)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						check(GetFX().IsValidChecked(Context))

						typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EMAttach AttachMapType;

						AttachMapType::Get().IsValidEnumChecked(Context, GetAttach());
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						if (!GetFX().IsValid(Context, Log))
							return false;

						typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EMAttach AttachMapType;
						typedef NCsWeapon::NProjectile::NData::NVisual::NFire::EAttach AttachType;

						CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
						return true;
					}
				}
			}
		}
	}
}