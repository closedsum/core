// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile_Visual_Impact.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsProjectile_FX_ImpactInfo
#pragma region

#define InfoType NCsProjectile::NImpact::NVisual::NFX::FInfo

void FCsProjectile_FX_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetFX(&FX);
	Info->SetbScaleByDamageRange(&bScaleByDamageRange);
}

void FCsProjectile_FX_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetFX(FX);
	Info->SetbScaleByDamageRange(bScaleByDamageRange);
}

#undef InfoType

bool FCsProjectile_FX_ImpactInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);
	return true;
}

bool FCsProjectile_FX_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(FX)
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
					CS_IS_VALID_CHECKED(GetFX());
					return true;
				}

				bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_VALID(GetFX())
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
	Info->SetSurface((EPhysicalSurface*)(&Surface));
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