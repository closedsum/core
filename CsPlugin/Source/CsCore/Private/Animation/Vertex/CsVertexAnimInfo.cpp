// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Vertex/CsVertexAnimInfo.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsVertexAnimInfo)

using InfoType = NCsAnim::NVertex::FInfo;
using NotifyType = NCsAnim::NVertex::FNotify;

void FCsVertexAnimInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_TO_PROXY(Info, NumFrames);
	CS_COPY_TO_PROXY(Info, AnimStartGenerated);
	CS_COPY_TO_PROXY(Info, SpeedGenerated);
	CS_COPY_TO_PROXY(Info, bLooping);
	CS_COPY_TO_PROXY(Info, Length);
	CS_COPY_TO_PROXY(Info, PlayRate);
	CS_COPY_TO_PROXY(Info, BlendInTime);
	CS_COPY_TO_PROXY(Info, BlendOutTime);

	const int32 Count = Info->Notifies.Num();

	Info->Notifies.Reset(Count);

	for (FCsVertexAnimNotify& N : Notifies)
	{
		NotifyType& Notify = Info->Notifies.AddDefaulted_GetRef();

		N.CopyToNotify(&Notify);
	}
}

void FCsVertexAnimInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Info, NumFrames);
	CS_COPY_TO_PROXY_AS_VALUE(Info, AnimStartGenerated);
	CS_COPY_TO_PROXY_AS_VALUE(Info, SpeedGenerated);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bLooping);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Length);
	CS_COPY_TO_PROXY_AS_VALUE(Info, PlayRate);
	CS_COPY_TO_PROXY_AS_VALUE(Info, BlendInTime);
	CS_COPY_TO_PROXY_AS_VALUE(Info, BlendOutTime);

	const int32 Count = Info->Notifies.Num();

	Info->Notifies.Reset(Count);

	for (const FCsVertexAnimNotify& N : Notifies)
	{
		NotifyType& Notify = Info->Notifies.AddDefaulted_GetRef();

		N.CopyToNotifyAsValue(&Notify);
	}
}

bool FCsVertexAnimInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_INT_GREATER_THAN_CHECKED(NumFrames, 0)
	CS_IS_INT_GREATER_THAN_CHECKED(AnimStartGenerated, 0)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(SpeedGenerated, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Length, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(PlayRate, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(BlendInTime, 0.0f)
	CS_IS_FLOAT_LESS_THAN_CHECKED(BlendInTime, Length)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(BlendOutTime, 0.0f)
	CS_IS_FLOAT_LESS_THAN_CHECKED(BlendOutTime, Length)

	for (const FCsVertexAnimNotify& Notify : Notifies)
	{
		CS_IS_VALID_CHECKED(Notify);
	}
	return true;
}

bool FCsVertexAnimInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_INT_GREATER_THAN(NumFrames, 0)
	CS_IS_INT_GREATER_THAN(AnimStartGenerated, 0)
	CS_IS_FLOAT_GREATER_THAN(SpeedGenerated, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(Length, 0.0f)
	CS_IS_FLOAT_GREATER_THAN(PlayRate, 0.0f)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(BlendInTime, 0.0f)
	CS_IS_FLOAT_LESS_THAN(BlendInTime, Length)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(BlendOutTime, 0.0f)
	CS_IS_FLOAT_LESS_THAN(BlendOutTime, Length)

	for (const FCsVertexAnimNotify& Notify : Notifies)
	{
		CS_IS_VALID(Notify)
	}
	return true;
}

const NCsAnim::NVertex::FInfo NCsAnim::NVertex::FInfo::Invalid = NCsAnim::NVertex::FInfo(-1, -1, -1.0f, false, -1.0f, -1.0f, -1.0f, -1.0f);

namespace NCsAnim
{
	namespace NVertex
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_INT_GREATER_THAN_CHECKED(GetNumFrames(), 0)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetAnimStartGenerated(), 0)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetSpeedGenerated(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetLength(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetPlayRate(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetBlendInTime(), 0.0f)
			CS_IS_FLOAT_LESS_THAN_CHECKED(GetBlendInTime(), GetLength())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetBlendOutTime(), 0.0f)
			CS_IS_FLOAT_LESS_THAN_CHECKED(GetBlendOutTime(), GetLength())

			for (const NotifyType& Notify : Notifies)
			{
				CS_IS_VALID_CHECKED(Notify);
			}
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			CS_IS_INT_GREATER_THAN(GetNumFrames(), 0)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetAnimStartGenerated(), 0)
			CS_IS_FLOAT_GREATER_THAN(GetSpeedGenerated(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN(GetLength(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN(GetPlayRate(), 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetBlendInTime(), 0.0f)
			CS_IS_FLOAT_LESS_THAN(GetBlendInTime(), GetLength())
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetBlendOutTime(), 0.0f)
			CS_IS_FLOAT_LESS_THAN(GetBlendOutTime(), GetLength())

			for (const NotifyType& Notify : Notifies)
			{
				CS_IS_VALID(Notify);
			}
			return true;
		}

		float FInfo::GetAlpha_BlendIn(const float& ElapsedTime) const
		{	
			const float Percent = FMath::Clamp(ElapsedTime / GetBlendInTime(), 0.0f, 1.0f);
				
			//return CsMathLibrary::Ease(ECsEasingType::Linear, Percent, 0.0, 1.0f, 1.0f);
			return Percent;
		}

		float FInfo::GetAlpha_BlendOut(const float& ElapsedTime) const
		{
			const float Percent = FMath::Clamp((GetLength() - ElapsedTime) / GetBlendOutTime(), 0.0f, 1.0f);

			//return CsMathLibrary::Ease(ECsEasingType::Linear, Percent, 0.0, 1.0f, 1.0f);
			return Percent;
		}
	}
}