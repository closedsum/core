// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Sound/Impact/CsTypes_Projectile_Sound_Impact.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Projectile_Sound_Impact)

// FCsProjectile_Sound_ImpactInfo
#pragma region

#define InfoType NCsProjectile::NImpact::NSound::FInfo

void FCsProjectile_Sound_ImpactInfo::CopyToInfo(InfoType* Info)
{
	Info->SetSurface((EPhysicalSurface)Surface);
	Info->SetbSound(&bSound);
	Info->SetSound(&Sound);
}

void FCsProjectile_Sound_ImpactInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetSurface((EPhysicalSurface)Surface);
	Info->SetbSound(bSound);
	Info->SetSound(Sound);
}

#undef InfoType

bool FCsProjectile_Sound_ImpactInfo::IsValidChecked(const FString& Context) const
{
	checkf(Surface != EPhysicalSurface::SurfaceType_Max, TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);

	if (bSound)
	{
		CS_IS_VALID_CHECKED(Sound);
	}
	return true;
}

bool FCsProjectile_Sound_ImpactInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (Surface == EPhysicalSurface::SurfaceType_Max)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Surface == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
		return false;
	}

	if (bSound)
	{
		CS_IS_VALID(Sound)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NImpact
	{
		namespace NSound
		{
			bool FInfo::IsValidChecked(const FString& Context) const
			{
				checkf(GetSurface() != EPhysicalSurface::SurfaceType_Max, TEXT("%s: GetSurface() == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context);

				if (GetbSound())
				{
					CS_IS_VALID_CHECKED(GetSound());
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				if (GetSurface() == EPhysicalSurface::SurfaceType_Max)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: GetSurface() == EPhysicalSurface::SurfaceType_Max is NOT Valid."), *Context));
					return false;
				}

				if (GetbSound())
				{
					CS_IS_VALID(GetSound())
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_Sound_ImpactInfo