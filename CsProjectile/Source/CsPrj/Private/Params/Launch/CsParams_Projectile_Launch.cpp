// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/Launch/CsParams_Projectile_Launch.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_Projectile_Launch)

// FCsProjectile_Launch_DelayParams
#pragma region

#define ParamsType NCsProjectile::NLaunch::NDelay::FParams

void FCsProjectile_Launch_DelayParams::CopyToParams(ParamsType* Params)
{
	Params->SetbCollision(&bCollision);
	Params->SetbTracking(&bTracking);
}

void FCsProjectile_Launch_DelayParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbCollision(bCollision);
	Params->SetbTracking(bTracking);
}

#undef ParamsType

bool FCsProjectile_Launch_DelayParams::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsProjectile_Launch_DelayParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	return true;
}

namespace NCsProjectile
{
	namespace NLaunch
	{
		namespace NDelay
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_Launch_DelayParams

// FCsProjectile_LaunchParams
#pragma region

#define ParamsType NCsProjectile::NLaunch::FParams

void FCsProjectile_LaunchParams::CopyToParams(ParamsType* Params)
{
	Params->SetDelay(&Delay);
	DelayParams.CopyToParams(Params->GetDelayParamsPtr());
}

void FCsProjectile_LaunchParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetDelay(Delay);
	DelayParams.CopyToParamsAsValue(Params->GetDelayParamsPtr());
}

#undef ParamsType

bool FCsProjectile_LaunchParams::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Delay, 0.0f)
	
	if (Delay > 0.0f)
	{
		CS_IS_VALID_CHECKED(DelayParams);
	}
	return true;
}

bool FCsProjectile_LaunchParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Delay, 0.0f)
	
	if (Delay > 0.0f)
	{
		CS_IS_VALID(DelayParams)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NLaunch
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDelay(), 0.0f)
	
			if (GetDelay() > 0.0f)
			{
				CS_IS_VALID_CHECKED(DelayParams);
			}
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetDelay(), 0.0f)

			if (GetDelay() > 0.0f)
			{
				CS_IS_VALID(DelayParams)
			}
			return true;
		}
	}
}

#pragma endregion FCsProjectile_OnHit_RicochetParams