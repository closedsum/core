// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/Visual/CsParams_PointWeapon_VisualFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

// PointWeaponVisualFireAttach
#pragma region

namespace NCsPointWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsPointWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsPointWeaponVisualFireAttach_MAX;
}

namespace NCsWeapon
{
	namespace NPoint
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

#pragma endregion PointWeaponVisualFireAttach


#define ParamsType NCsWeapon::NPoint::NFire::NVisual::FParams

void FCsPointWeapon_VisualFire_Params::CopyToParams(ParamsType* Params)
{
	Params->SetFX(&FX);
	Params->SetAttach(&Attach);
}

void FCsPointWeapon_VisualFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetFX(FX);
	Params->SetAttach(Attach);
}

#undef ParamsType

bool FCsPointWeapon_VisualFire_Params::IsValidChecked(const FString& Context) const
{
	check(FX.IsValidChecked(Context))

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsPointWeaponVisualFireAttach, Attach)
	return true;
}

bool FCsPointWeapon_VisualFire_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!FX.IsValid(Context, Log))
		return false;

	CS_IS_ENUM_VALID(EMCsPointWeaponVisualFireAttach, ECsPointWeaponVisualFireAttach, Attach)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NFire
		{
			namespace NVisual
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					check(GetFX().IsValidChecked(Context))

					typedef NCsWeapon::NPoint::NFire::NVisual::EMAttach AttachMapType;

					AttachMapType::Get().IsValidEnumChecked(Context, GetAttach());
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					if (!GetFX().IsValid(Context, Log))
						return false;

					typedef NCsWeapon::NPoint::NFire::NVisual::EMAttach AttachMapType;
					typedef NCsWeapon::NPoint::NFire::NVisual::EAttach AttachType;

					CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
					return true;
				}
			}
		}
	}
}