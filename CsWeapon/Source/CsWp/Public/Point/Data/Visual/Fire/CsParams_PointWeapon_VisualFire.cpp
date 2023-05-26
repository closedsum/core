// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Data/Visual/Fire/CsParams_PointWeapon_VisualFire.h"

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
	Params->SetbDestinationAsStart(&bDestinationAsStart);
	Params->SetbDistanceParameter(&bDistanceParameter);
	Params->SetDistanceParameter(&DistanceParameter);
	Params->SetbOrientationParameter(&bOrientationParameter);
	Params->SetOrientationParameter(&OrientationParameter);
}

void FCsPointWeapon_VisualFire_Params::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetFX(FX);
	Params->SetAttach(Attach);
	Params->SetbDestinationAsStart(bDestinationAsStart);
	Params->SetbDistanceParameter(bDistanceParameter);
	Params->SetDistanceParameter(DistanceParameter);
	Params->SetbOrientationParameter(bOrientationParameter);
	Params->SetOrientationParameter(OrientationParameter);
}

#undef ParamsType

bool FCsPointWeapon_VisualFire_Params::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);
	CS_IS_ENUM_VALID_CHECKED(EMCsPointWeaponVisualFireAttach, Attach)

	if (bDistanceParameter)
	{
		CS_IS_NAME_NONE_CHECKED(DistanceParameter)
	}

	if (bOrientationParameter)
	{
		CS_IS_NAME_NONE_CHECKED(OrientationParameter)
	}
	return true;
}

bool FCsPointWeapon_VisualFire_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(FX)
	CS_IS_ENUM_VALID(EMCsPointWeaponVisualFireAttach, ECsPointWeaponVisualFireAttach, Attach)

	if (bDistanceParameter)
	{
		CS_IS_NAME_NONE(DistanceParameter)
	}

	if (bOrientationParameter)
	{
		CS_IS_NAME_NONE(OrientationParameter)
	}
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
					CS_IS_VALID_CHECKED(GetFX());

					typedef NCsWeapon::NPoint::NFire::NVisual::EMAttach AttachMapType;

					CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())

					if (GetbDistanceParameter())
					{
						CS_IS_NAME_NONE_CHECKED(GetDistanceParameter())
					}

					if (GetbOrientationParameter())
					{
						CS_IS_NAME_NONE_CHECKED(GetOrientationParameter())
					}
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					CS_IS_VALID(GetFX())

					typedef NCsWeapon::NPoint::NFire::NVisual::EMAttach AttachMapType;
					typedef NCsWeapon::NPoint::NFire::NVisual::EAttach AttachType;

					CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())

					if (GetbDistanceParameter())
					{
						CS_IS_NAME_NONE(GetDistanceParameter())
					}

					if (GetbOrientationParameter())
					{
						CS_IS_NAME_NONE(GetOrientationParameter())
					}
					return true;
				}
			}
		}
	}
}