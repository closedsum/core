// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Spread/CsParams_ProjectileWeapon_Spread.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsProjectileWeapon_Spread_AngleParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NSpread::NAngle::FParams

void FCsProjectileWeapon_Spread_AngleParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType*)(&AngleType));
	Params->SetAngle(&Angle);

	typedef NCsWeapon::NProjectile::NSpread::EDistribution DistributionType;

	Params->SetDistribution((DistributionType*)(&Distribution));
}

void FCsProjectileWeapon_Spread_AngleParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

	Params->SetAngleType((SpreadAngleType)AngleType);
	Params->SetAngle(Angle);

	typedef NCsWeapon::NProjectile::NSpread::EDistribution DistributionType;

	Params->SetDistribution((DistributionType)Distribution);
}

#undef ParamsType

bool FCsProjectileWeapon_Spread_AngleParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(Angle, 180.0f)
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponSpreadDistribution, Distribution)
	return true;
}

bool FCsProjectileWeapon_Spread_AngleParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadAngle, ECsProjectileWeaponSpreadAngle, AngleType)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Angle, 0.0f)
	CS_IS_FLOAT_LESS_THAN_OR_EQUAL(Angle, 180.0f)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponSpreadDistribution, ECsProjectileWeaponSpreadDistribution, Distribution)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			namespace NAngle
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;

					CS_IS_ENUM_VALID_CHECKED(SpreadAngleMapType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetAngle(), 180.0f)

					typedef NCsWeapon::NProjectile::NSpread::EMDistribution DistributionMapType;

					CS_IS_ENUM_VALID_CHECKED(DistributionMapType, GetDistribution())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NProjectile::NSpread::EMAngle SpreadAngleMapType;
					typedef NCsWeapon::NProjectile::NSpread::EAngle SpreadAngleType;

					CS_IS_ENUM_VALID(SpreadAngleMapType, SpreadAngleType, GetAngleType())
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetAngle(), 0.0f)
					CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetAngle(), 180.0f)

					typedef NCsWeapon::NProjectile::NSpread::EMDistribution DistributionMapType;
					typedef NCsWeapon::NProjectile::NSpread::EDistribution DistributionType;

					CS_IS_ENUM_VALID(DistributionMapType, DistributionType, GetDistribution())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Spread_AngleParams

// FCsProjectileWeapon_SpreadParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NSpread::FParams

void FCsProjectileWeapon_SpreadParams::CopyToParams(ParamsType* Params)
{
	Params->SetbYaw(&bYaw);
	YawParams.CopyToParams(Params->GetYawParamsPtr());
	Params->SetbPitch(&bPitch);
	PitchParams.CopyToParams(Params->GetPitchParamsPtr());
}

void FCsProjectileWeapon_SpreadParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbYaw(bYaw);
	YawParams.CopyToParamsAsValue(Params->GetYawParamsPtr());
	Params->SetbPitch(bPitch);
	PitchParams.CopyToParamsAsValue(Params->GetPitchParamsPtr());
}

#undef ParamsType

bool FCsProjectileWeapon_SpreadParams::IsValidChecked(const FString& Context) const
{
	if (bYaw)
	{
		CS_IS_VALID_CHECKED(YawParams);
	}

	if (bPitch)
	{
		CS_IS_VALID_CHECKED(PitchParams);
	}
	return true;
}

bool FCsProjectileWeapon_SpreadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (bYaw)
	{
		CS_IS_VALID(YawParams)
	}

	if (bPitch)
	{
		CS_IS_VALID(PitchParams)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NSpread
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				if (GetbYaw())
				{
					CS_IS_VALID_CHECKED(YawParams);
				}

				if (GetbPitch())
				{
					CS_IS_VALID_CHECKED(PitchParams);
				}
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
			{
				if (GetbYaw())
				{
					CS_IS_VALID(YawParams)
				}

				if (GetbPitch())
				{
					CS_IS_VALID(PitchParams)
				}
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_SpreadParams