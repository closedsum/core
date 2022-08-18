// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsTypes_Material_Anim.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
#include "Material/CsLibrary_Material.h"
// Material
#include "Materials/MaterialInstanceDynamic.h"
 
// FCsMaterialAnimParameterVector
#pragma region

#define ValueType NCsMaterial::NAnim::NParameter::FVectorType

void FCsMaterialAnimParameterVector::CopyToValue(ValueType* Value)
{
	Value->SetName(&Name);
	Value->SetEasing(&Easing);
	Value->SetFrom(&From);
	Value->SetTo(&To);
}

void FCsMaterialAnimParameterVector::CopyToValueAsValue(ValueType* Value) const
{
	Value->SetName(Name);
	Value->SetEasing(Easing);
	Value->SetFrom(From);
	Value->SetTo(To);
}

#undef ValueType

bool FCsMaterialAnimParameterVector::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}

bool FCsMaterialAnimParameterVector::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialAnimParameterVector

// FCsMaterialAnimParameterScalar
#pragma region

#define ValueType NCsMaterial::NAnim::NParameter::FScalarType

void FCsMaterialAnimParameterScalar::CopyToValue(ValueType* Value)
{
	Value->SetName(&Name);
	Value->SetEasing(&Easing);
	Value->SetFrom(&From);
	Value->SetTo(&To);
}

void FCsMaterialAnimParameterScalar::CopyToValueAsValue(ValueType* Value) const
{
	Value->SetName(Name);
	Value->SetEasing(Easing);
	Value->SetFrom(From);
	Value->SetTo(To);
}

#undef ValueType

bool FCsMaterialAnimParameterScalar::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}

bool FCsMaterialAnimParameterScalar::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialAnimParameterScalar

// FCsMaterialAnimFrame
#pragma region

#define FrameType NCsMaterial::NAnim::FFrame

void FCsMaterialAnimFrame::CopyToFrame(FrameType* Frame)
{
	Frame->SetDuration(&Duration);

	// Vector
	typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

	Frame->VectorParameters.Reset(FMath::Max(Frame->VectorParameters.Max(), VectorParameters.Num()));

	for (FCsMaterialAnimParameterVector& FromParam : VectorParameters)
	{
		VectorType& ToParam = Frame->VectorParameters.AddDefaulted_GetRef();

		FromParam.CopyToValue(&ToParam);
	}
	// Scalar
	typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

	Frame->ScalarParameters.Reset(FMath::Max(Frame->ScalarParameters.Max(), ScalarParameters.Num()));

	for (FCsMaterialAnimParameterScalar& FromParam : ScalarParameters)
	{
		ScalarType& ToParam = Frame->ScalarParameters.AddDefaulted_GetRef();

		FromParam.CopyToValue(&ToParam);
	}
}

void FCsMaterialAnimFrame::CopyToFrameAsValue(FrameType* Frame) const
{
	Frame->SetDuration(Duration);

	// Vector
	typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

	Frame->VectorParameters.Reset(FMath::Max(Frame->VectorParameters.Max(), VectorParameters.Num()));

	for (const FCsMaterialAnimParameterVector& FromParam : VectorParameters)
	{
		VectorType& ToParam = Frame->VectorParameters.AddDefaulted_GetRef();

		FromParam.CopyToValueAsValue(&ToParam);
	}
	// Scalar
	typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

	Frame->ScalarParameters.Reset(FMath::Max(Frame->ScalarParameters.Max(), ScalarParameters.Num()));

	for (const FCsMaterialAnimParameterScalar& FromParam : ScalarParameters)
	{
		ScalarType& ToParam = Frame->ScalarParameters.AddDefaulted_GetRef();

		FromParam.CopyToValueAsValue(&ToParam);
	}
}

#undef FrameType

bool FCsMaterialAnimFrame::IsValidChecked(const FString& Context) const
{
	// Check Duration is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Duration, 0.0f)
	// Check VectorParameters is Valid
	for (const FCsMaterialAnimParameterVector& Param : VectorParameters)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	// Check ScalarParameters is Valid
	for (const FCsMaterialAnimParameterScalar& Param : ScalarParameters)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	return true;
}

bool FCsMaterialAnimFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Duration is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Duration, 0.0f)
	// Check VectorParameters is Valid
	for (const FCsMaterialAnimParameterVector& Param : VectorParameters)
	{
		if (!Param.IsValid(Context, Log))
			return false;
	}
	// Check ScalarParameters is Valid
	for (const FCsMaterialAnimParameterScalar& Param : ScalarParameters)
	{
		if (!Param.IsValid(Context, Log))
			return false;
	}
	return true;
}

bool FCsMaterialAnimFrame::IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	// Check VectorParameters is Valid
	for (const FCsMaterialAnimParameterVector& Param : VectorParameters)
	{
		if (!MIDLibrary::IsVectorParameterValid(Context, MID, Param.Name, Log))
			return false;
	}
	// Check ScalarParameters is Valid
	for (const FCsMaterialAnimParameterScalar& Param : ScalarParameters)
	{
		if (!MIDLibrary::IsScalarParameterValid(Context, MID, Param.Name, Log))
			return false;
	}
	return true;
}

bool FCsMaterialAnimFrame::IsValid(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	// Check VectorParameters is Valid
	for (const FCsMaterialAnimParameterVector& Param : VectorParameters)
	{
		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			if (!MIDLibrary::IsVectorParameterValid(Context, MID, Param.Name, Log))
				return false;
		}
	}
	// Check ScalarParameters is Valid
	for (const FCsMaterialAnimParameterScalar& Param : ScalarParameters)
	{
		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			if (!MIDLibrary::IsScalarParameterValid(Context, MID, Param.Name, Log))
				return false;
		}
	}
	return true;
}

bool FCsMaterialAnimFrame::IsValid(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	typedef NCsMaterial::NMID::FLibrary MIDLibrary;

	// Check VectorParameters is Valid
	for (const FCsMaterialAnimParameterVector& Param : VectorParameters)
	{
		for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
		{
			if (!MIDLibrary::IsVectorParameterValid(Context, MID.IsValid() ? MID.Get() : nullptr, Param.Name, Log))
				return false;
		}
	}
	// Check ScalarParameters is Valid
	for (const FCsMaterialAnimParameterScalar& Param : ScalarParameters)
	{
		for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
		{
			if (!MIDLibrary::IsScalarParameterValid(Context, MID.IsValid() ? MID.Get() : nullptr, Param.Name, Log))
				return false;
		}
	}
	return true;
}

namespace NCsMaterial
{
	namespace NAnim
	{
		bool FFrame::IsValidChecked(const FString& Context) const
		{
			// Check Duration is Valid
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetDuration(), 0.0f)
			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				check(Param.IsValidChecked(Context));
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				check(Param.IsValidChecked(Context));
			}
			return true;
		}

		bool FFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Duration is Valid
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetDuration(), 0.0f)
			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				if (!Param.IsValid(Context, Log))
					return false;
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				if (!Param.IsValidChecked(Context))
					return false;
			}
			return true;
		}

		bool FFrame::IsValidChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				check(MIDLibrary::IsVectorParameterValidChecked(Context, MID, Param.GetName()));
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				check(MIDLibrary::IsScalarParameterValidChecked(Context, MID, Param.GetName()));
			}
			return true;
		}
		
		bool FFrame::IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				if (!MIDLibrary::IsVectorParameterValid(Context, MID, Param.GetName(), Log))
					return false;
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				if (!MIDLibrary::IsScalarParameterValid(Context, MID, Param.GetName(), Log))
					return false;
			}
			return true;
		}

		bool FFrame::IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				for (UMaterialInstanceDynamic* MID : MIDs)
				{
					check(MIDLibrary::IsVectorParameterValidChecked(Context, MID, Param.GetName()));
				}
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				for (UMaterialInstanceDynamic* MID : MIDs)
				{
					check(MIDLibrary::IsScalarParameterValidChecked(Context, MID, Param.GetName()));
				}
			}
			return true;
		}

		bool FFrame::IsValid(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				for (UMaterialInstanceDynamic* MID : MIDs)
				{
					if (!MIDLibrary::IsVectorParameterValid(Context, MID, Param.GetName(), Log))
						return false;
				}
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				for (UMaterialInstanceDynamic* MID : MIDs)
				{
					if (!MIDLibrary::IsScalarParameterValid(Context, MID, Param.GetName(), Log))
						return false;
				}
			}
			return true;
		}

		bool FFrame::IsValidChecked(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs) const
		{
			check(IsValidChecked(Context));

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
				{
					check(MIDLibrary::IsVectorParameterValidChecked(Context, MID.IsValid() ? MID.Get() : nullptr, Param.GetName()));
				}
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
				{
					check(MIDLibrary::IsScalarParameterValidChecked(Context, MID.IsValid() ? MID.Get() : nullptr, Param.GetName()));
				}
			}
			return true;
		}

		bool FFrame::IsValid(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			typedef NCsMaterial::NMID::FLibrary MIDLibrary;

			// Check VectorParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FVectorType VectorType;

			for (const VectorType& Param : VectorParameters)
			{
				for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
				{
					if (!MIDLibrary::IsVectorParameterValid(Context, MID.IsValid() ? MID.Get() : nullptr, Param.GetName(), Log))
						return false;
				}
			}
			// Check ScalarParameters is Valid
			typedef NCsMaterial::NAnim::NParameter::FScalarType ScalarType;

			for (const ScalarType& Param : ScalarParameters)
			{
				for (const TWeakObjectPtr<UMaterialInstanceDynamic>& MID : MIDs)
				{
					if (!MIDLibrary::IsScalarParameterValid(Context, MID.IsValid() ? MID.Get() : nullptr, Param.GetName(), Log))
						return false;
				}
			}
			return true;
		}
	}
}

#pragma endregion FCsMaterialAnimFrame

// FCsMaterialAnim
#pragma region

void FCsMaterialAnim::UpdateFromPlaybackAndPlayRate()
{
	// CustomDeltaTime
	if (PlayRate == ECsAnimPlayRate::PR_CustomDeltaTime)
	{
		if (Playback == ECsAnimPlayback::PingPong)
		{
			TotalTime = (2 * Frames.Num() - 1) * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			TotalTime = Frames.Num() * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}
	// CustomTotalTime
	else
	if (PlayRate == ECsAnimPlayRate::PR_CustomTotalTime)
	{
		if (Playback == ECsAnimPlayback::PingPong)
		{
			DeltaTime = TotalTime > 0.0f && (2 * Frames.Num() - 1) > 0 ? TotalTime / (2 * Frames.Num() - 1) : 0.0f;
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			DeltaTime = TotalTime > 0.0f && Frames.Num() > 0 ? TotalTime / Frames.Num() : 0.0f;
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}
	// CustomDeltaTimeAndTotalTime | Custom
	else
	if  (PlayRate == ECsAnimPlayRate::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime > 0.0f &&
			TotalTime > 0.0f &&
			!IsLoopingForever())
		{
			TotalCount = FMath::FloorToInt(TotalTime / DeltaTime);
		}
	}
	else
	if (PlayRate == ECsAnimPlayRate::PR_Custom)
	{
		const int32 Count = Frames.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FCsMaterialAnimFrame& Frame = Frames[I];

			if (Playback == ECsAnimPlayback::PingPong)
			{
				TotalTime += I == Count - 1 ? Frame.Duration : 2.0f * Frame.Duration;
			}
			else
			{
				TotalTime += Frame.Duration;
			}
		}

		if (Playback == ECsAnimPlayback::PingPong)
		{
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}
	else
	{
		using namespace NCsAnim;

		if (Playback == ECsAnimPlayback::PingPong)
		{
			DeltaTime  = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime  = (2 * Frames.Num() - 1) * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			DeltaTime  = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime  = Frames.Num() * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}

	// Update Frame Duration
	if (PlayRate != ECsAnimPlayRate::PR_Custom)
	{
		for (FCsMaterialAnimFrame& Frame : Frames)
		{
			Frame.Duration = DeltaTime;
		}
	}
}

#define AnimType NCsMaterial::NAnim::FAnim

void FCsMaterialAnim::CopyToAnim(AnimType* Anim)
{
	typedef NCsAnim::EPlayback PlaybackType;

	Anim->SetPlayback((PlaybackType*)&Playback);

	typedef NCsAnim::EPlayRate PlayRateType;

	Anim->SetPlayRate((PlayRateType*)&PlayRate);

	Anim->SetDeltaTime(&DeltaTime);	
	Anim->SetTotalTime(&TotalTime);

	typedef NCsMaterial::NAnim::FFrame FrameType;

	Anim->Frames.Reset(FMath::Max(Anim->Frames.Max(), Frames.Num()));

	for (FCsMaterialAnimFrame& FromFrame : Frames)
	{
		FrameType& ToFrame = Anim->Frames.AddDefaulted_GetRef();

		FromFrame.CopyToFrame(&ToFrame);
	}
	Anim->FrameCount = Frames.Num();

	Anim->SetTotalCount(&TotalCount);
}

void FCsMaterialAnim::CopyToAnimAsValue(AnimType* Anim) const
{
	typedef NCsAnim::EPlayback PlaybackType;

	Anim->SetPlayback((PlaybackType)Playback);

	typedef NCsAnim::EPlayRate PlayRateType;

	Anim->SetPlayRate((PlayRateType)PlayRate);

	Anim->SetDeltaTime(DeltaTime);
	Anim->SetTotalTime(TotalTime);

	typedef NCsMaterial::NAnim::FFrame FrameType;

	Anim->Frames.Reset(FMath::Max(Anim->Frames.Max(), Frames.Num()));

	for (const FCsMaterialAnimFrame& FromFrame : Frames)
	{
		FrameType& ToFrame = Anim->Frames.AddDefaulted_GetRef();

		FromFrame.CopyToFrameAsValue(&ToFrame);
	}
	Anim->FrameCount = Frames.Num();

	Anim->SetTotalCount(TotalCount);
}

#undef AnimType

bool FCsMaterialAnim::IsValidChecked(const FString& Context) const
{
	// Check Playback is Valid.
	CS_IS_ENUM_VALID_CHECKED(EMCsAnimPlayback, Playback)
	// Check PlayRate is Valid.
	CS_IS_ENUM_VALID_CHECKED(EMCsAnimPlayRate, PlayRate)

	// Check DeltaTime or TotalTime

	using namespace NCsAnim;

	if (PlayRate != ECsAnimPlayRate::PR_CustomDeltaTime &&
		PlayRate != ECsAnimPlayRate::PR_CustomTotalTime &&
		PlayRate != ECsAnimPlayRate::PR_CustomDeltaTimeAndTotalTime &&
		PlayRate != ECsAnimPlayRate::PR_Custom)
	{
		const float DT = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);

		checkf(FMath::Abs(DeltaTime - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));

		checkf(DeltaTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));

		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));
		}
	}
	if (PlayRate == ECsAnimPlayRate::PR_CustomDeltaTime ||
		PlayRate == ECsAnimPlayRate::PR_CustomTotalTime ||
		PlayRate == ECsAnimPlayRate::PR_CustomDeltaTimeAndTotalTime)
	{
		checkf(DeltaTime > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));

		checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));
				
		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate));
		}
	}

	// Check Frames
	CS_IS_ARRAY_EMPTY_CHECKED(Frames, FCsMaterialAnimFrame)

	for (const FCsMaterialAnimFrame& Frame : Frames)
	{
		CS_IS_VALID_CHECKED(Frame);
	}
	return true;
}

bool FCsMaterialAnim::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Playback is Valid.
	CS_IS_ENUM_VALID(EMCsAnimPlayback, ECsAnimPlayback, Playback)
	// Check PlayRate is Valid.
	CS_IS_ENUM_VALID(EMCsAnimPlayRate, ECsAnimPlayRate, PlayRate)

	// Check DeltaTime or TotalTime

	using namespace NCsAnim;

	if (PlayRate != ECsAnimPlayRate::PR_CustomDeltaTime &&
		PlayRate != ECsAnimPlayRate::PR_CustomTotalTime &&
		PlayRate != ECsAnimPlayRate::PR_CustomDeltaTimeAndTotalTime &&
		PlayRate != ECsAnimPlayRate::PR_Custom)
	{
		const float DT = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);

		if (FMath::Abs(DeltaTime - DT) > KINDA_SMALL_NUMBER)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
			return false;
		}

		if (DeltaTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
			return false;
		}

		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
				return false;
			}
		}
	}
	if (PlayRate == ECsAnimPlayRate::PR_CustomDeltaTime ||
		PlayRate == ECsAnimPlayRate::PR_CustomTotalTime ||
		PlayRate == ECsAnimPlayRate::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
			return false;
		}

		if (TotalTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
			return false;
		}
				
		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, EMCsAnimPlayRate::Get().ToDisplayNameChar(PlayRate)));
				return false;
			}
		}
	}

	// Check Frames
	CS_IS_ARRAY_EMPTY(Frames, FCsMaterialAnimFrame)

	for (const FCsMaterialAnimFrame& Frame : Frames)
	{
		if (!Frame.IsValid(Context, Log))
			return false;
	}
	return true;
}

bool FCsMaterialAnim::IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	// Check Frames
	CS_IS_ARRAY_EMPTY(Frames, FCsMaterialAnimFrame)

	for (const FCsMaterialAnimFrame& Frame : Frames)
	{
		if (!Frame.IsValid(Context, MID, Log))
			return false;
	}
	return true;
}

bool FCsMaterialAnim::IsValid(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	// Check Frames
	CS_IS_ARRAY_EMPTY(Frames, FCsMaterialAnimFrame)

	for (const FCsMaterialAnimFrame& Frame : Frames)
	{
		if (!Frame.IsValid(Context, MIDs, Log))
			return false;
	}
	return true;
}

bool FCsMaterialAnim::IsValid(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	// Check Frames
	CS_IS_ARRAY_EMPTY(Frames, FCsMaterialAnimFrame)

	for (const FCsMaterialAnimFrame& Frame : Frames)
	{
		if (!Frame.IsValid(Context, MIDs, Log))
			return false;
	}
	return true;
}

namespace NCsMaterial
{
	namespace NAnim
	{
		void FAnim::UpdateFromPlaybackAndPlayRateChecked(const FString& Context)
		{
			check(AreProxyPtrsDefaultChecked(Context));

			typedef NCsAnim::EPlayRate PlayRateType;
			typedef NCsAnim::EPlayback PlaybackType;

			// CustomDeltaTime
			if (PlayRate == PlayRateType::PR_CustomDeltaTime)
			{
				if (Playback == PlaybackType::PingPong)
				{
					TotalTime = (2 * FrameCount - 1) * DeltaTime;
					TotalCount = IsLoopingForever() ? 0 : (2 * FrameCount - 1);
				}
				else
				{
					TotalTime = FrameCount * DeltaTime;
					TotalCount = IsLoopingForever() ? 0 : FrameCount;
				}
			}
			// CustomTotalTime
			else
			if (PlayRate == PlayRateType::PR_CustomTotalTime)
			{
				if (Playback == PlaybackType::PingPong)
				{
					DeltaTime = TotalTime > 0.0f && (2 * FrameCount - 1) > 0 ? TotalTime / (2 * FrameCount - 1) : 0.0f;
					TotalCount = IsLoopingForever() ? 0 : (2 * FrameCount - 1);
				}
				else
				{
					DeltaTime = TotalTime > 0.0f && FrameCount > 0 ? TotalTime / FrameCount : 0.0f;
					TotalCount = IsLoopingForever() ? 0 : FrameCount;
				}
			}
			// CustomDeltaTimeAndTotalTime | Custom
			else
			if  (PlayRate == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
			{
				if (DeltaTime > 0.0f &&
					TotalTime > 0.0f &&
					!IsLoopingForever())
				{
					TotalCount = FMath::FloorToInt(TotalTime / DeltaTime);
				}
			}
			else
			if (PlayRate == PlayRateType::PR_Custom)
			{
				// Do Nothing
			}
			else
			{
				using namespace NCsAnim;

				if (Playback == PlaybackType::PingPong)
				{
					DeltaTime  = NPlayRate::GetDeltaTime(PlayRate);
					TotalTime  = (2 * FrameCount - 1) * DeltaTime;
					TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
				}
				else
				{
					DeltaTime  = NPlayRate::GetDeltaTime(PlayRate);
					TotalTime  = FrameCount * DeltaTime;
					TotalCount = IsLoopingForever() ? 0 : FrameCount;
				}
			}

			// Update Frame Duration
			if (PlayRate != PlayRateType::PR_Custom)
			{
				typedef NCsMaterial::NAnim::FFrame FrameType;

				for (FrameType& Frame : Frames)
				{
					Frame.SetDuration(DeltaTime);
				}
			}
		}

		bool FAnim::IsValidChecked(const FString& Context) const
		{
			// Check Playback is Valid.
			typedef NCsAnim::EPlayback PlaybackType;
			typedef NCsAnim::EMPlayback PlaybackMapType;
			check(PlaybackMapType::Get().IsValidEnumChecked(Context, GetPlayback()));
			// Check PlayRate is Valid.
			typedef NCsAnim::EPlayRate PlayRateType;
			typedef NCsAnim::EMPlayRate PlayRateMapType;

			const PlayRateType& PR = GetPlayRate();

			check(PlayRateMapType::Get().IsValidEnumChecked(Context, PR));

			// Check DeltaTime or TotalTime

			if (PR != PlayRateType::PR_CustomDeltaTime &&
				PR != PlayRateType::PR_CustomTotalTime &&
				PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
				PR != PlayRateType::PR_Custom)
			{
				const float DT = NCsAnim::NPlayRate::GetDeltaTime(PR);

				checkf(FMath::Abs(GetDeltaTime() - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, GetDeltaTime(), GetDeltaTime(), DT, PlayRateMapType::Get().ToDisplayNameChar(PR));

				if (IsLoopingForever())
				{

				}
				else
				{
					checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));

					checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0 for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
				}
			}
			if (PR == PlayRateType::PR_CustomDeltaTime ||
				PR == PlayRateType::PR_CustomTotalTime ||
				PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
			{
				checkf(GetDeltaTime() > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetDeltaTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));
				
				if (IsLoopingForever())
				{

				}
				else
				{
					checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));

					checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0 for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
				}
			}

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY_CHECKED(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				check(Frames[I].IsValidChecked(Context));
			}
			return true;
		}

		bool FAnim::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			// Check Playback is Valid.
			typedef NCsAnim::EPlayback PlaybackType;
			typedef NCsAnim::EMPlayback PlaybackMapType;
			CS_IS_ENUM_VALID(PlaybackMapType, PlaybackType, GetPlayback())
			// Check PlayRate is Valid.
			typedef NCsAnim::EPlayRate PlayRateType;
			typedef NCsAnim::EMPlayRate PlayRateMapType;

			const PlayRateType& PR = GetPlayRate();

			CS_IS_ENUM_VALID(PlayRateMapType, PlayRateType, GetPlayRate())

			// Check DeltaTime or TotalTime

			if (PR != PlayRateType::PR_CustomDeltaTime &&
				PR != PlayRateType::PR_CustomTotalTime &&
				PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
				PR != PlayRateType::PR_Custom)
			{
				const float DT = NCsAnim::NPlayRate::GetDeltaTime(PR);

				if (FMath::Abs(GetDeltaTime() - DT) > KINDA_SMALL_NUMBER)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, GetDeltaTime(), GetDeltaTime(), DT, PlayRateMapType::Get().ToDisplayNameChar(PR)));
					return false;
				}

				if (GetTotalTime() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR)));
					return false;
				}

				if (!IsLoopingForever())
				{
					if (GetTotalCount() <= 0)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR)));
						return false;
					}
				}
			}
			if (PR == PlayRateType::PR_CustomDeltaTime ||
				PR == PlayRateType::PR_CustomTotalTime ||
				PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
			{
				if (GetDeltaTime() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetDeltaTime(), PlayRateMapType::Get().ToDisplayNameChar(PR)));
					return false;
				}

				if (GetTotalTime() <= 0.0f)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR)));
					return false;
				}
				
				if (!IsLoopingForever())
				{
					if (GetTotalCount() <= 0)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR)));
						return false;
					}
				}
			}

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				if (!Frames[I].IsValid(Context, Log))
					return false;
			}
			return true;
		}

		bool FAnim::IsValidChecked(const FString& Context, UMaterialInstanceDynamic* MID) const
		{
			check(IsValidChecked(Context));

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY_CHECKED(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				check(Frames[I].IsValidChecked(Context, MID));
			}
			return true;
		}

		bool FAnim::IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				if (!Frames[I].IsValid(Context, MID, Log))
					return false;
			}
			return true;
		}

		bool FAnim::IsValidChecked(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs) const
		{
			check(IsValidChecked(Context));

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY_CHECKED(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				check(Frames[I].IsValidChecked(Context, MIDs));
			}
			return true;
		}

		bool FAnim::IsValid(const FString& Context, const TArray<UMaterialInstanceDynamic*>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				if (!Frames[I].IsValid(Context, MIDs, Log))
					return false;
			}
			return true;
		}

		bool FAnim::IsValidChecked(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs) const
		{
			check(IsValidChecked(Context));

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY_CHECKED(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				check(Frames[I].IsValidChecked(Context, MIDs));
			}
			return true;
		}

		bool FAnim::IsValid(const FString& Context, const TArray<TWeakObjectPtr<UMaterialInstanceDynamic>>& MIDs, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
		{
			if (!IsValid(Context, Log))
				return false;

			// Check Frames
			typedef NCsMaterial::NAnim::FFrame FrameType;

			CS_IS_ARRAY_EMPTY(Frames, FrameType)

			for (int32 I = 0; I < FrameCount; ++I)
			{
				if (!Frames[I].IsValid(Context, MIDs, Log))
					return false;
			}
			return true;
		}
	}
}

#pragma endregion FCsMaterialAnim

// FCsMaterialAnim_Params
#pragma region

void FCsMaterialAnim_Params::ConditionalSetSafeMIDs(const FString& Context)
{
	if (MIDs.Num() > CS_EMPTY)
	{
		MIDsAsObjects.Reset(FMath::Max(MIDsAsObjects.Max(), MIDs.Num()));

		for (UMaterialInstanceDynamic* MID : MIDs)
		{
			MIDsAsObjects.Add(MID);
		}
	}
	else
	if (MIDsAsObjects.Num() > CS_EMPTY)
	{
		const int32 Count = MIDsAsObjects.Num();

		MIDs.Reset(FMath::Max(MIDs.Max(), Count));

		for (int32 I = 0; I < Count; ++I)
		{
			UObject* MIDAsObject		  = MIDsAsObjects[I];
			UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(MIDsAsObjects[I]);

			if (!MID)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: MIDsAsObjects[%d]: %s with Class: %s is NOT of type: UMaterialInstanceDynamic."), *Context, I, *(MIDAsObject->GetName()), *(MIDAsObject->GetClass()->GetName()));
			}
			MIDs.Add(MID);
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("%s: MIDs is EMPTY and MIDsAsObjects is EMPTY."), *Context);
	}
}

#define ParamsType NCsMaterial::NAnim::NParams::FParams
void FCsMaterialAnim_Params::CopyToParamsAsValue(ParamsType* Params) const
{
#undef ParamsType

	Anim.CopyToAnimAsValue(&(Params->Anim));
	Params->SetMIDs(MIDs);
	Params->SetOwner(Owner);
	Params->SetGroup(Group);
}

bool FCsMaterialAnim_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check MID is Valid
	CS_IS_ARRAY_EMPTY(MIDs, UMaterialInstanceDynamic*)
	CS_IS_ARRAY_ANY_NULL(MIDs, UMaterialInstanceDynamic)
	// Check Anim is Valid
	if (!Anim.IsValid(Context, MIDs, Log))
		return false;
	// Check Owner is Valid
	CS_IS_PTR_NULL(Owner)
	// Check Group is Valid
	CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, Group)
	return true;
}

namespace NCsMaterial
{
	namespace NAnim
	{
		namespace NParams
		{
			void FParams::SetMIDs(const TArray<UMaterialInstanceDynamic*>& Value)
			{
				MIDs.Reset(FMath::Max(MIDs.Max(), Value.Num()));

				for (UMaterialInstanceDynamic* MID : Value)
				{
					MIDs.Add(MID);
				}
			}

			const TArray<UMaterialInstanceDynamic*>& FParams::ResolveAndGetMIDsChecked(const FString& Context)
			{
				MIDs_Internal.Reset(MIDs_Internal.Max());

				const int32 Count = MIDs.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					TWeakObjectPtr<UMaterialInstanceDynamic>& MID = MIDs[I];
					UMaterialInstanceDynamic* M					  = MID.IsValid() ? MID.Get() : nullptr;

					checkf(M, TEXT("%s: MIDs[%d] is NULL."), *Context, I);

					MIDs_Internal.Add(M);
				}
				return MIDs_Internal;
			}

			UObject* FParams::GetOwner() const { return Owner.IsValid() ? Owner.Get() : nullptr; }

			bool FParams::IsValidChecked(const FString& Context) const
			{
				// Check MID is Valid
				CS_IS_ARRAY_EMPTY_CHECKED(GetMIDs(), TWeakObjectPtr<UMaterialInstanceDynamic>)
				CS_IS_ARRAY_ANY_NULL_CHECKED(GetMIDs(), UMaterialInstanceDynamic)
				// Check Anim is Valid
				check(Anim.IsValidChecked(Context, GetMIDs()));
				// Check Owner is Valid
				CS_IS_PTR_NULL_CHECKED(GetOwner())
				// Check Group is Valid
				check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, GetGroup()));
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				// Check MID is Valid
				CS_IS_ARRAY_EMPTY(GetMIDs(), TWeakObjectPtr<UMaterialInstanceDynamic>)
				CS_IS_ARRAY_ANY_NULL(GetMIDs(), UMaterialInstanceDynamic)
				// Check Anim is Valid
				if (!Anim.IsValid(Context, GetMIDs(), Log))
					return false;
				// Check Owner is Valid
				CS_IS_PTR_NULL(GetOwner())
				// Check Group is Valid
				CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, GetGroup())
				return true;
			}

			void FParams::Reset()
			{
				Anim.Reset();
				MIDs.Reset(MIDs.Max());
				MIDs_Internal.Reset(MIDs_Internal.Max());
				Owner = nullptr;
				CS_RESET_MEMBER_WITH_PROXY(Group, EMCsUpdateGroup::Get().GetMAX())
			}
		}
	}
}

#pragma endregion FCsMaterialAnim_Params