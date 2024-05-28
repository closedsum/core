// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsTypes_AnimMontage.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Anim
#include "Animation/AnimMontage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_AnimMontage)

// FCsAnimMontage_PlayParams
#pragma region

#define ParamsType NCsAnimMontage::NPlay::FParams

void FCsAnimMontage_PlayParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TO_PROXY(Params, Anim);
	CS_COPY_TO_PROXY(Params, bPlayOverExisting);
	CS_COPY_TO_PROXY(Params, PlayRate);
	CS_COPY_TO_PROXY(Params, TimeToStartAt);
	CS_COPY_TO_PROXY(Params, bStopAll);
}

void FCsAnimMontage_PlayParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, Anim);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bPlayOverExisting);
	CS_COPY_TO_PROXY_AS_VALUE(Params, PlayRate);
	CS_COPY_TO_PROXY_AS_VALUE(Params, TimeToStartAt);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bStopAll);
}

#undef ParamsType

bool FCsAnimMontage_PlayParams::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(Anim)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeToStartAt, 0.0f)
	return true;
}

bool FCsAnimMontage_PlayParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_PENDING_KILL(Anim)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TimeToStartAt, 0.0f)
	return true;
}

namespace NCsAnimMontage
{
	namespace NPlay
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_PENDING_KILL_CHECKED(GetAnim())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTimeToStartAt(), 0.0f)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_PENDING_KILL(GetAnim())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTimeToStartAt(), 0.0f)
			return true;
		}
	}
}

#pragma endregion FCsAnimMontage_PlayParams

// FCsAnimMontage_PlayByPathParams
#pragma region

bool FCsAnimMontage_PlayByPathParams::IsValidChecked(const FString& Context) const
{
	CS_IS_STRING_EMPTY_CHECKED(Path)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeToStartAt, 0.0f)
	return true;
}

bool FCsAnimMontage_PlayByPathParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_STRING_EMPTY(Path)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TimeToStartAt, 0.0f)
	return true;
}

#pragma endregion FCsAnimMontage_PlayByPathParams