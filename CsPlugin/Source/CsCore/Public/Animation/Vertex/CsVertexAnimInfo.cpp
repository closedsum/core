// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Vertex/CsVertexAnimInfo.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"

#define InfoType NCsAnim::NVertex::FInfo

void FCsVertexAnimInfo::CopyToInfo(InfoType* Info)
{
	Info->SetNumFrames(&NumFrames);
	Info->SetAnimStartGenerated(&AnimStartGenerated);
	Info->SetSpeedGenerated(&SpeedGenerated);
	Info->SetbLooping(&bLooping);
	Info->SetLength(&Length);
	Info->SetPlayRate(&PlayRate);
	Info->SetBlendInTime(&BlendInTime);
	Info->SetBlendOutTime(&BlendOutTime);

	typedef NCsAnim::NVertex::FNotify NotifyType;

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
	Info->SetNumFrames(NumFrames);
	Info->SetAnimStartGenerated(AnimStartGenerated);
	Info->SetSpeedGenerated(SpeedGenerated);
	Info->SetbLooping(bLooping);
	Info->SetLength(Length);
	Info->SetPlayRate(PlayRate);
	Info->SetBlendInTime(BlendInTime);
	Info->SetBlendOutTime(BlendOutTime);

	typedef NCsAnim::NVertex::FNotify NotifyType;

	const int32 Count = Info->Notifies.Num();

	Info->Notifies.Reset(Count);

	for (const FCsVertexAnimNotify& N : Notifies)
	{
		NotifyType& Notify = Info->Notifies.AddDefaulted_GetRef();

		N.CopyToNotifyAsValue(&Notify);
	}
}

#undef InfoType

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

			typedef NCsAnim::NVertex::FNotify NotifyType;

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

			typedef NCsAnim::NVertex::FNotify NotifyType;

			for (const NotifyType& Notify : Notifies)
			{
				CS_IS_VALID(Notify);
			}
			return true;
		}

		float FInfo::GetAlpha_BlendIn(const float& ElapsedTime) const
		{	
			const float Percent = FMath::Clamp(ElapsedTime / GetBlendInTime(), 0.0f, 1.0f);
				
			//typedef NCsMath::FLibrary MathLibrary;

			//return MathLibrary::Ease(ECsEasingType::Linear, Percent, 0.0, 1.0f, 1.0f);
			return Percent;
		}

		float FInfo::GetAlpha_BlendOut(const float& ElapsedTime) const
		{
			const float Percent = FMath::Clamp((GetLength() - ElapsedTime) / GetBlendOutTime(), 0.0f, 1.0f);

			//typedef NCsMath::FLibrary MathLibrary;

			//return MathLibrary::Ease(ECsEasingType::Linear, Percent, 0.0, 1.0f, 1.0f);
			return Percent;
		}
	}
}