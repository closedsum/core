// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Visual/Impact/CsTypes_Projectile_Visual_Impact.h"

// Library
#include "Library/CsLibrary_Valid.h"

// ProjectileVisualImpactDirection
#pragma region

namespace NCsProjectileVisualImpactDirection
{
	namespace Ref
	{
		typedef EMCsProjectileVisualImpactDirection EnumMapType;

		CSPRJ_API CS_ADD_TO_ENUM_MAP(None);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Normal);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseNormal, "Inverse Normal");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(Velocity);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseVelocity, "Inverse Velocity");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileVisualImpactDirection_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileVisualImpactDirection_MAX;
}

namespace NCsProjectile
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

					CSPRJ_API CS_ADD_TO_ENUM_MAP(None);
					CSPRJ_API CS_ADD_TO_ENUM_MAP(Normal);
					CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseNormal, "Inverse Normal");
					CSPRJ_API CS_ADD_TO_ENUM_MAP(Velocity);
					CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(InverseVelocity, "Inverse Velocity");
					CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion ProjectileVisualImpactDirection

// FCsProjectile_FX_ImpactInfo
#pragma region

#define InfoType NCsProjectile::NImpact::NVisual::NFX::FInfo

void FCsProjectile_FX_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetbFX(&bFX);
	Info->SetFX(&FX);

	typedef NCsProjectile::NImpact::NVisual::EDirection DirectionType;

	Info->SetDirection((DirectionType*)(&Direction));
	Info->SetbScaleByDamageRange(&bScaleByDamageRange);
}

void FCsProjectile_FX_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetbFX(bFX);
	Info->SetFX(FX);

	typedef NCsProjectile::NImpact::NVisual::EDirection DirectionType;

	Info->SetDirection((DirectionType*)(&Direction));
	Info->SetbScaleByDamageRange(bScaleByDamageRange);
}

#undef InfoType

bool FCsProjectile_FX_ImpactInfo::IsValidChecked(const FString& Context) const
{
	if (bFX)
	{
		CS_IS_VALID_CHECKED(FX);
		CS_IS_ENUM_VALID_CHECKED(EMCsProjectileVisualImpactDirection, Direction)
	}
	return true;
}

bool FCsProjectile_FX_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bFX)
	{
		CS_IS_VALID(FX)
		CS_IS_ENUM_VALID(EMCsProjectileVisualImpactDirection, ECsProjectileVisualImpactDirection, Direction)
	}
	return true;
}

namespace NCsProjectile
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

						typedef NCsProjectile::NImpact::NVisual::EMDirection DirectionMapType;

						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetDirection())
					}
					return true;
				}

				bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					if (GetbFX())
					{
						CS_IS_VALID(GetFX())

						typedef NCsProjectile::NImpact::NVisual::EMDirection DirectionMapType;
						typedef NCsProjectile::NImpact::NVisual::EDirection DirectionType;

						CS_IS_ENUM_VALID(DirectionMapType, DirectionType, GetDirection())
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_FX_ImpactInfo

// FCsProjectile_Visual_ImpactInfo
#pragma region

#define InfoType NCsProjectile::NImpact::NVisual::FInfo

void FCsProjectile_Visual_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetSurface((EPhysicalSurface)Surface);
	FXInfo.CopyToInfo(Info->GetFXInfoPtr());
}

void FCsProjectile_Visual_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetSurface((EPhysicalSurface)Surface);
	FXInfo.CopyToInfoAsValue(Info->GetFXInfoPtr());
}

#undef InfoType

bool FCsProjectile_Visual_ImpactInfo::IsValidChecked(const FString& Context) const
{
	checkf(Surface != EPhysicalSurface::SurfaceType_Max, TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);
	CS_IS_VALID_CHECKED(FXInfo);
	return true;
}

bool FCsProjectile_Visual_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (Surface == EPhysicalSurface::SurfaceType_Max)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
		return false;
	}
	CS_IS_VALID(FXInfo)
	return true;
}

namespace NCsProjectile
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

#pragma endregion FCsProjectile_Visual_ImpactInfo