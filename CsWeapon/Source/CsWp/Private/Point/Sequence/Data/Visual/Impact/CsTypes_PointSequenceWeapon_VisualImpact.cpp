// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Point/Sequence/Data/Visual/Impact/CsTypes_PointSequenceWeapon_VisualImpact.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_PointSequenceWeapon_VisualImpact)

// PointSequenceWeaponVisualImpactDirection
#pragma region

namespace NCsPointSequenceWeaponVisualImpactDirection
{
	namespace Ref
	{
		typedef EMCsPointSequenceWeaponVisualImpactDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(None);
		CSWP_API CS_ADD_TO_ENUM_MAP(Normal);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseNormal, "Inverse Normal");
		CSWP_API CS_ADD_TO_ENUM_MAP(Direction);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseDirection, "Inverse Direction");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPointSequenceWeaponVisualImpactDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsPointSequenceWeaponVisualImpactDirection_MAX;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NImpact
		{
			namespace NVisual
			{
				namespace NDirection
				{
					namespace Ref
					{
						typedef EMDirection EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(None);
						CSWP_API CS_ADD_TO_ENUM_MAP(Normal);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseNormal, "Inverse Normal");
						CSWP_API CS_ADD_TO_ENUM_MAP(Direction);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseDirection, "Inverse Direction");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
					}
				}
			}
		}
		}
	}
}

#pragma endregion PointSequenceWeaponVisualImpactDirection

// FCsPointSequenceWeapon_FX_ImpactInfo
#pragma region

#define InfoType NCsWeapon::NPoint::NSequence::NImpact::NVisual::NFX::FInfo

void FCsPointSequenceWeapon_FX_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetbFX(&bFX);
	Info->SetFX(&FX);

	typedef NCsWeapon::NPoint::NSequence::NImpact::NVisual::EDirection DirectionType;

	Info->SetDirection((DirectionType*)(&Direction));
	Info->SetbScaleByDamageRange(&bScaleByDamageRange);
}

void FCsPointSequenceWeapon_FX_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetbFX(bFX);
	Info->SetFX(FX);

	typedef NCsWeapon::NPoint::NSequence::NImpact::NVisual::EDirection DirectionType;

	Info->SetDirection((DirectionType*)(&Direction));
	Info->SetbScaleByDamageRange(bScaleByDamageRange);
}

#undef InfoType

bool FCsPointSequenceWeapon_FX_ImpactInfo::IsValidChecked(const FString& Context) const
{
	if (bFX)
	{
		CS_IS_VALID_CHECKED(FX);

		typedef EMCsPointSequenceWeaponVisualImpactDirection DirectionMapType;

		CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Direction)
	}
	return true;
}

bool FCsPointSequenceWeapon_FX_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (bFX)
	{
		CS_IS_VALID(FX)

		typedef EMCsPointSequenceWeaponVisualImpactDirection DirectionMapType;
		typedef ECsPointSequenceWeaponVisualImpactDirection DirectionType;

		CS_IS_ENUM_VALID(DirectionMapType, DirectionType, Direction)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NImpact
		{
			namespace NVisual
			{
				namespace NFX
				{
					bool FInfo::IsValidChecked(const FString& Context) const
					{
						if (GetbFX())
						{
							CS_IS_VALID_CHECKED(GetFX());

							typedef NCsWeapon::NPoint::NSequence::NImpact::NVisual::EMDirection DirectionMapType;

							CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Direction)
						}
						return true;
					}

					bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						if (GetbFX())
						{
							CS_IS_VALID(GetFX())

							typedef NCsWeapon::NPoint::NSequence::NImpact::NVisual::EMDirection DirectionMapType;
							typedef NCsWeapon::NPoint::NSequence::NImpact::NVisual::EDirection DirectionType;

							CS_IS_ENUM_VALID(DirectionMapType, DirectionType, Direction)
						}
						return true;
					}
				}
			}
		}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_FX_ImpactInfo

// FCsPointSequenceWeapon_Visual_ImpactInfo
#pragma region

#define InfoType NCsWeapon::NPoint::NSequence::NImpact::NVisual::FInfo

void FCsPointSequenceWeapon_Visual_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetSurface((EPhysicalSurface)Surface);
	FXInfo.CopyToInfo(Info->GetFXInfoPtr());
}

void FCsPointSequenceWeapon_Visual_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetSurface((EPhysicalSurface)Surface);
	FXInfo.CopyToInfoAsValue(Info->GetFXInfoPtr());
}

#undef InfoType

bool FCsPointSequenceWeapon_Visual_ImpactInfo::IsValidChecked(const FString& Context) const
{
	checkf(Surface != EPhysicalSurface::SurfaceType_Max, TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);
	CS_IS_VALID_CHECKED(FXInfo);
	return true;
}

bool FCsPointSequenceWeapon_Visual_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (Surface == EPhysicalSurface::SurfaceType_Max)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
		return false;
	}
	CS_IS_VALID(FXInfo)
	return true;
}

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NImpact
			{
				namespace NVisual
				{
					bool FInfo::IsValidChecked(const FString& Context) const
					{
						checkf(GetSurface() != EPhysicalSurface::SurfaceType_Max, TEXT("%s: GetSurface() == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);
						CS_IS_VALID_CHECKED(GetFXInfo());
						return true;
					}

					bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						if (GetSurface() == EPhysicalSurface::SurfaceType_Max)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSurface() == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
							return false;
						}
						CS_IS_VALID(GetFXInfo())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsPointSequenceWeapon_Visual_ImpactInfo