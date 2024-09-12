// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Visual/CsTypes_Projectile_Visual_Death.h"

// Library
#include "Managers/FX/CsLibrary_FX.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Projectile_Visual_Death)

// FCsProjectile_Visual_Death_FX_ScaleInfo
#pragma region

#define InfoType NCsProjectile::NVisual::NDeath::NFX::NScale::FInfo

void FCsProjectile_Visual_Death_FX_ScaleInfo::CopyToInfo(InfoType* Info)
{
	Info->SetParameterName(&ParameterName);
	Info->SetbCollisionRadius(&bCollisionRadius);
	Info->SetCollisionRadiusMultiplier(&CollisionRadiusMultiplier);
}

void FCsProjectile_Visual_Death_FX_ScaleInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetParameterName(ParameterName);
	Info->SetbCollisionRadius(bCollisionRadius);
	Info->SetCollisionRadiusMultiplier(CollisionRadiusMultiplier);
}

#undef InfoType

bool FCsProjectile_Visual_Death_FX_ScaleInfo::IsValidChecked(const FString& Context) const
{
	typedef NCsFX::FLibrary FXLibrary;

	check(FXLibrary::IsValidUserVariableNameChecked(Context, ParameterName));

	if (bCollisionRadius)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(CollisionRadiusMultiplier, 0.0f)
	}
	return true;
}

bool FCsProjectile_Visual_Death_FX_ScaleInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	typedef NCsFX::FLibrary FXLibrary;

	if (!FXLibrary::IsValidUserVariableName(Context, ParameterName, Log))
		return false;

	if (bCollisionRadius)
	{
		CS_IS_FLOAT_GREATER_THAN(CollisionRadiusMultiplier, 0.0f)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NDeath
		{
			namespace NFX
			{
				namespace NScale
				{
					bool FInfo::IsValidChecked(const FString& Context) const
					{
						typedef NCsFX::FLibrary FXLibrary;

						check(FXLibrary::IsValidUserVariableNameChecked(Context, GetParameterName()));

						if (GetbCollisionRadius())
						{
							CS_IS_FLOAT_GREATER_THAN_CHECKED(GetCollisionRadiusMultiplier(), 0.0f)
						}
						return true;
					}

					bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						typedef NCsFX::FLibrary FXLibrary;

						if (!FXLibrary::IsValidUserVariableNameChecked(Context, GetParameterName()))
							return false;

						if (GetbCollisionRadius())
						{
							CS_IS_FLOAT_GREATER_THAN(GetCollisionRadiusMultiplier(), 0.0f)
						}
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FX_ScaleInfo

// FCsProjectile_Visual_Death_FX_SpeedInfo
#pragma region

#define InfoType NCsProjectile::NVisual::NDeath::NFX::NSpeed::FInfo

void FCsProjectile_Visual_Death_FX_SpeedInfo::CopyToInfo(InfoType* Info)
{
	Info->SetParameterName(&ParameterName);
}

void FCsProjectile_Visual_Death_FX_SpeedInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetParameterName(ParameterName);
}

#undef InfoType

bool FCsProjectile_Visual_Death_FX_SpeedInfo::IsValidChecked(const FString& Context) const
{
	typedef NCsFX::FLibrary FXLibrary;

	check(FXLibrary::IsValidUserVariableNameChecked(Context, ParameterName));
	return true;
}

bool FCsProjectile_Visual_Death_FX_SpeedInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	typedef NCsFX::FLibrary FXLibrary;

	if (!FXLibrary::IsValidUserVariableName(Context, ParameterName, Log))
		return false;
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NDeath
		{
			namespace NFX
			{
				namespace NSpeed
				{
					bool FInfo::IsValidChecked(const FString& Context) const
					{
						typedef NCsFX::FLibrary FXLibrary;

						check(FXLibrary::IsValidUserVariableNameChecked(Context, GetParameterName()));
						return true;
					}

					bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
					{
						typedef NCsFX::FLibrary FXLibrary;

						if (!FXLibrary::IsValidUserVariableNameChecked(Context, GetParameterName()))
							return false;
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FX_SpeedInfo

// FCsProjectile_Visual_Death_FXInfo
#pragma region

#define InfoType NCsProjectile::NVisual::NDeath::NFX::FInfo

void FCsProjectile_Visual_Death_FXInfo::CopyToInfo(InfoType* Info)
{
	Info->SetFX(&FX);
	Info->SetbScaleInfo(&bScaleInfo);
	ScaleInfo.CopyToInfo(Info->GetScaleInfoPtr());
	Info->SetbSpeedInfo(&bSpeedInfo);
	SpeedInfo.CopyToInfo(Info->GetSpeedInfoPtr());
}

void FCsProjectile_Visual_Death_FXInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetFX(FX);
	Info->SetbScaleInfo(bScaleInfo);
	ScaleInfo.CopyToInfoAsValue(Info->GetScaleInfoPtr());
	Info->SetbSpeedInfo(bSpeedInfo);
	SpeedInfo.CopyToInfoAsValue(Info->GetSpeedInfoPtr());
}

#undef InfoType

bool FCsProjectile_Visual_Death_FXInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);

	if (bScaleInfo)
	{
		CS_IS_VALID_CHECKED(ScaleInfo);
	}

	if (bSpeedInfo)
	{
		CS_IS_VALID_CHECKED(SpeedInfo);
	}
	return true;
}

bool FCsProjectile_Visual_Death_FXInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(FX)

	if (bScaleInfo)
	{
		CS_IS_VALID(ScaleInfo)
	}

	if (bSpeedInfo)
	{
		CS_IS_VALID(SpeedInfo)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NDeath
		{
			namespace NFX
			{
				bool FInfo::IsValidChecked(const FString& Context) const
				{
					CS_IS_VALID_CHECKED(GetFX());

					if (GetbScaleInfo())
					{
						CS_IS_VALID_CHECKED(GetScaleInfo());
					}

					if (GetbSpeedInfo())
					{
						CS_IS_VALID_CHECKED(GetSpeedInfo());
					}
					return true;
				}

				bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_VALID(GetFX())

					if (GetbScaleInfo())
					{
						CS_IS_VALID(GetScaleInfo());
					}

					if (GetbSpeedInfo())
					{
						CS_IS_VALID(GetSpeedInfo());
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_Death_FXInfo

// FCsProjectile_Visual_DeathInfo
#pragma region

#define InfoType NCsProjectile::NVisual::NDeath::FInfo

void FCsProjectile_Visual_DeathInfo::CopyToInfo(InfoType* Info)
{
	Info->SetbFXInfos(&bFXInfos);

	typedef NCsProjectile::NVisual::NDeath::NFX::FInfo FXInfoType;

	const int32 Count = FXInfos.Num();

	Info->GetFXInfosPtr()->Reset(Count);

	for (FCsProjectile_Visual_Death_FXInfo& _Info : FXInfos)
	{
		FXInfoType& FXInfo = Info->GetFXInfosPtr()->AddDefaulted_GetRef();

		_Info.CopyToInfo(&FXInfo);
	}
}

void FCsProjectile_Visual_DeathInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetbFXInfos(bFXInfos);

	typedef NCsProjectile::NVisual::NDeath::NFX::FInfo FXInfoType;

	const int32 Count = FXInfos.Num();

	Info->GetFXInfosPtr()->Reset(Count);

	for (const FCsProjectile_Visual_Death_FXInfo& _Info : FXInfos)
	{
		FXInfoType& FXInfo = Info->GetFXInfosPtr()->AddDefaulted_GetRef();

		_Info.CopyToInfoAsValue(&FXInfo);
	}
}

#undef InfoType

bool FCsProjectile_Visual_DeathInfo::IsValidChecked(const FString& Context) const
{
	if (bFXInfos)
	{
		typedef FCsProjectile_Visual_Death_FXInfo FXInfoType;

		for (const FXInfoType& Info : FXInfos)
		{
			CS_IS_VALID_CHECKED(Info);
		}
	}
	return true;
}

bool FCsProjectile_Visual_DeathInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (bFXInfos)
	{
		typedef FCsProjectile_Visual_Death_FXInfo FXInfoType;

		for (const FXInfoType& Info : FXInfos)
		{
			CS_IS_VALID(Info);
		}
	}
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NDeath
		{
			bool FInfo::IsValidChecked(const FString& Context) const
			{
				if (GetbFXInfos())
				{
					typedef NCsProjectile::NVisual::NDeath::NFX::FInfo FXInfoType;

					for (const FXInfoType& Info : GetFXInfos())
					{
						CS_IS_VALID_CHECKED(Info);
					}
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				if (GetbFXInfos())
				{
					typedef NCsProjectile::NVisual::NDeath::NFX::FInfo FXInfoType;

					for (const FXInfoType& Info : GetFXInfos())
					{
						CS_IS_VALID(Info)
					}
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_Visual_DeathInfo