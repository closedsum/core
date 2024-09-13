// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Data/Visual/Fire/CsParams_PointSequenceWeapon_VisualFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_PointSequenceWeapon_VisualFire)

// PointSequenceWeaponVisualFireAttach
#pragma region

namespace NCsPointSequenceWeaponVisualFireAttach
{
	namespace Ref
	{
		typedef EMCsPointSequenceWeaponVisualFireAttach EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointSequenceWeaponVisualFireAttach_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsPointSequenceWeaponVisualFireAttach_MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
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
}

#pragma endregion PointSequenceWeaponVisualFireAttach

// FCsPointSequenceWeapon_Visual_FireParams
#pragma region

#define ParamsType NCsWeapon::NPoint::NSequence::NFire::NVisual::FParams

void FCsPointSequenceWeapon_Visual_FireParams::CopyToParams(ParamsType* Params)
{
	Params->SetFX(&FX);

	typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType*)(&Attach));
	Params->SetbDestinationAsStart(&bDestinationAsStart);
	Params->SetbDistanceParameter(&bDistanceParameter);
	Params->SetDistanceParameter(&DistanceParameter);
	Params->SetbOrientationParameter(&bOrientationParameter);
	Params->SetOrientationParameter(&OrientationParameter);
}

void FCsPointSequenceWeapon_Visual_FireParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetFX(FX);

	typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EAttach AttachType;

	Params->SetAttach((AttachType)Attach);
	Params->SetbDestinationAsStart(bDestinationAsStart);
	Params->SetbDistanceParameter(bDistanceParameter);
	Params->SetDistanceParameter(DistanceParameter);
	Params->SetbOrientationParameter(bOrientationParameter);
	Params->SetOrientationParameter(OrientationParameter);
}

#undef ParamsType

bool FCsPointSequenceWeapon_Visual_FireParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);

	typedef EMCsPointSequenceWeaponVisualFireAttach AttachMapType;

	CS_IS_ENUM_VALID_CHECKED(AttachMapType, Attach)

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

bool FCsPointSequenceWeapon_Visual_FireParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(FX)

	typedef EMCsPointSequenceWeaponVisualFireAttach AttachMapType;
	typedef ECsPointSequenceWeaponVisualFireAttach AttachType;

	CS_IS_ENUM_VALID(AttachMapType, AttachType, Attach)

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
		namespace NSequence
		{
			namespace NFire
			{
				namespace NVisual
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetFX());

						typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EMAttach AttachMapType;

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

						typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EMAttach AttachMapType;
						typedef NCsWeapon::NPoint::NSequence::NFire::NVisual::EAttach AttachType;

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
}

#pragma endregion FCsPointSequenceWeapon_Visual_FireParams