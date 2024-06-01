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
	CS_COPY_TO_PROXY(Params, bBlendIn);
	CS_COPY_TO_PROXY(Params, BlendIn);
	CS_COPY_TO_PROXY(Params, PlayRate);
	CS_COPY_TO_PROXY(Params, TimeToStartAt);
	CS_COPY_TO_PROXY(Params, bStopAll);
}

void FCsAnimMontage_PlayParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, Anim);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bPlayOverExisting);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bBlendIn);
	CS_COPY_TO_PROXY_AS_VALUE(Params, BlendIn);
	CS_COPY_TO_PROXY_AS_VALUE(Params, PlayRate);
	CS_COPY_TO_PROXY_AS_VALUE(Params, TimeToStartAt);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bStopAll);
}

#undef ParamsType

bool FCsAnimMontage_PlayParams::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(Anim)

	if (bBlendIn)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(BlendIn.BlendTime, 0.0f)
	}
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeToStartAt, 0.0f)
	return true;
}

bool FCsAnimMontage_PlayParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_PENDING_KILL(Anim)

	if (bBlendIn)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(BlendIn.BlendTime, 0.0f)
	}
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

			if (GetbBlendIn())
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetBlendIn().BlendTime, 0.0f)
			}
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTimeToStartAt(), 0.0f)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_PENDING_KILL(GetAnim())

			if (GetbBlendIn())
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetBlendIn().BlendTime, 0.0f)
			}
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

// AnimMontageSetPosition
#pragma region

namespace NCsAnimMontageSetPosition
{
	typedef EMCsAnimMontageSetPosition EnumMapType;

	namespace Ref
	{
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Time);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Percent);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnimMontageSetPosition_MAX, "MAX");
	}
}

namespace NCsAnimMontage
{
	namespace NSetPosition
	{
		namespace Ref
		{
			typedef EMSetPosition EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Time);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Percent);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ESetPosition_MAX, "MAX");
		}
	}
}

#pragma endregion AnimMontageSetPosition

// FCsAnimMontage_SetPositionParams
#pragma region

#define ParamsType NCsAnimMontage::NSetPosition::FParams

void FCsAnimMontage_SetPositionParams::CopyToParams(ParamsType* Params)
{
	CS_COPY_TO_PROXY(Params, Anim);
	CS_COPY_TYPE_TO_PROXY(Params, PositionType, NCsAnimMontage::ESetPosition);
	CS_COPY_TO_PROXY(Params, NewPosition);
	CS_COPY_TO_PROXY(Params, NewPositionAsPercent);
	CS_COPY_TO_PROXY(Params, bPlay);
	CS_COPY_TO_PROXY(Params, bPause);
	CS_COPY_TO_PROXY(Params, bPlayOverExisting);
	CS_COPY_TO_PROXY(Params, PlayRate);
	CS_COPY_TO_PROXY(Params, TimeToStartAt);
	CS_COPY_TO_PROXY(Params, bStopAll);
}

void FCsAnimMontage_SetPositionParams::CopyToParamsAsValue(ParamsType* Params) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Params, Anim);
	CS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, PositionType, NCsAnimMontage::ESetPosition);
	CS_COPY_TO_PROXY_AS_VALUE(Params, NewPosition);
	CS_COPY_TO_PROXY_AS_VALUE(Params, NewPositionAsPercent);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bPlay);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bPause);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bPlayOverExisting);
	CS_COPY_TO_PROXY_AS_VALUE(Params, PlayRate);
	CS_COPY_TO_PROXY_AS_VALUE(Params, TimeToStartAt);
	CS_COPY_TO_PROXY_AS_VALUE(Params, bStopAll);
}

#undef ParamsType

bool FCsAnimMontage_SetPositionParams::IsValidChecked(const FString& Context) const
{
	CS_IS_PENDING_KILL_CHECKED(Anim)

	// Time
	if (PositionType == ECsAnimMontageSetPosition::Time)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(NewPosition, 0.0f)
	}
	// Percent
	if (PositionType == ECsAnimMontageSetPosition::Percent)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(NewPositionAsPercent, 0.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(NewPositionAsPercent, 1.0f)
	}

	if (bPlay)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TimeToStartAt, 0.0f)
	}
	return true;
}

bool FCsAnimMontage_SetPositionParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
{
	CS_IS_PENDING_KILL(Anim)

	// Time
	if (PositionType == ECsAnimMontageSetPosition::Time)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(NewPosition, 0.0f)
	}
	// Percent
	if (PositionType == ECsAnimMontageSetPosition::Percent)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(NewPositionAsPercent, 0.0f)
		CS_IS_FLOAT_LESS_THAN_OR_EQUAL(NewPositionAsPercent, 1.0f)
	}

	if (bPlay)
	{
		CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TimeToStartAt, 0.0f)
	}
	return true;
}

namespace NCsAnimMontage
{
	namespace NSetPosition
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_PENDING_KILL_CHECKED(GetAnim())

			// Time
			if (GetPositionType() == NCsAnimMontage::ESetPosition::Time)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetNewPosition(), 0.0f)
			}
			// Percent
			if (GetPositionType() == NCsAnimMontage::ESetPosition::Percent)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetNewPositionAsPercent(), 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(GetNewPositionAsPercent(), 1.0f)
			}

			if (GetbPlay())
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTimeToStartAt(), 0.0f)
			}
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsTypes::FLog::Warning*/) const
		{
			CS_IS_PENDING_KILL(GetAnim())

			// Time
			if (GetPositionType() == NCsAnimMontage::ESetPosition::Time)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetNewPosition(), 0.0f)
			}
			// Percent
			if (GetPositionType() == NCsAnimMontage::ESetPosition::Percent)
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetNewPositionAsPercent(), 0.0f)
				CS_IS_FLOAT_LESS_THAN_OR_EQUAL(GetNewPositionAsPercent(), 1.0f)
			}

			if (GetbPlay())
			{
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTimeToStartAt(), 0.0f)
			}
			return true;
		}
	}
}

#pragma endregion FCsAnimMontage_SetPositionParams