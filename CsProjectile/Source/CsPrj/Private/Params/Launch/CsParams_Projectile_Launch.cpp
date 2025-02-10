// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/Launch/CsParams_Projectile_Launch.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_Projectile_Launch)

// FCsProjectile_Launch_DelayParams
#pragma region

namespace NCsProjectile_Launch_DelayParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bCollision);
		CS_THIS_COPY_TO_PROXY(Params, bTracking);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bCollision);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bTracking);
	}
}

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

namespace NCsProjectile_LaunchParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Delay);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, DelayParams);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Delay);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, DelayParams);
	}
}

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