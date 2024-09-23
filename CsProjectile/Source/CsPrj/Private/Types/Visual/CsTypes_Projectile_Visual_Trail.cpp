// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Visual/CsTypes_Projectile_Visual_Trail.h"

// Library
#include "Managers/FX/CsLibrary_FX.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Projectile_Visual_Trail)

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
		check(CsFXLibrary::IsValidUserVariableNameChecked(Context, ScaleParameterName));
	}

	if (bSpeedParameterName)
	{
		check(CsFXLibrary::IsValidUserVariableNameChecked(Context, SpeedParameterName));
	}
	return true;
}

bool FCsProjectile_Visual_TrailInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(FX);

	if (bScaleParameterName)
	{
		if (!CsFXLibrary::IsValidUserVariableName(Context, ScaleParameterName))
			return false;
	}

	if (bSpeedParameterName)
	{
		if (!CsFXLibrary::IsValidUserVariableName(Context, SpeedParameterName))
			return false;
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
					check(CsFXLibrary::IsValidUserVariableNameChecked(Context, GetScaleParameterName()));
				}

				if (GetbSpeedParameterName())
				{
					check(CsFXLibrary::IsValidUserVariableNameChecked(Context, GetSpeedParameterName()));
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_VALID(GetFX())

				if (GetbScaleParameterName())
				{
					if (!CsFXLibrary::IsValidUserVariableName(Context, GetScaleParameterName()))
						return false;
				}

				if (GetbSpeedParameterName())
				{
					if (!CsFXLibrary::IsValidUserVariableName(Context, GetSpeedParameterName()))
						return false;
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_TrailInfo