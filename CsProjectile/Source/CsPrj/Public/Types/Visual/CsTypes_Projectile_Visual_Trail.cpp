// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Visual/CsTypes_Projectile_Visual_Trail.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsProjectile_Visual_TrailInfo
#pragma region

#define InfoType NCsProjectile::NVisual::NTrail::FInfo

void FCsProjectile_Visual_TrailInfo::CopyToInfo(InfoType* Info)
{
	Info->SetFX(&FX);
	Info->SetbScaleParameterName(&bScaleParameterName);
	Info->SetScaleParameterName(&ScaleParameterName);
	Info->SetbSpeedParameterName(&bSpeedParameterName);
	Info->SetSpeedParameterName(&SpeedParameterName);
}

void FCsProjectile_Visual_TrailInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetFX(FX);
	Info->SetbScaleParameterName(bScaleParameterName);
	Info->SetScaleParameterName(ScaleParameterName);
	Info->SetbSpeedParameterName(bSpeedParameterName);
	Info->SetSpeedParameterName(SpeedParameterName);
}

#undef InfoType

bool FCsProjectile_Visual_TrailInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);

	if (bScaleParameterName)
	{
		CS_IS_NAME_NONE_CHECKED(ScaleParameterName)
	}

	if (bSpeedParameterName)
	{
		CS_IS_NAME_NONE_CHECKED(SpeedParameterName)
	}
	return true;
}

bool FCsProjectile_Visual_TrailInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(FX);

	if (bScaleParameterName)
	{
		CS_IS_NAME_NONE(ScaleParameterName)
	}

	if (bSpeedParameterName)
	{
		CS_IS_NAME_NONE(SpeedParameterName)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NTrail
		{
			bool FInfo::IsValidChecked(const FString& Context) const
			{
				CS_IS_VALID_CHECKED(GetFX());

				if (GetbScaleParameterName())
				{
					CS_IS_NAME_NONE_CHECKED(GetScaleParameterName())
				}

				if (GetbSpeedParameterName())
				{
					CS_IS_NAME_NONE_CHECKED(GetSpeedParameterName())
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_VALID(GetFX())

				if (GetbScaleParameterName())
				{
					CS_IS_NAME_NONE(GetScaleParameterName())
				}

				if (GetbSpeedParameterName())
				{
					CS_IS_NAME_NONE(GetSpeedParameterName())
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_TrailInfo