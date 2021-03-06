// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Anim2D.h"

// Library
#include "Library/CsLibrary_Valid.h"

// Anim2DPlayRate
#pragma region

namespace NCsAnim2DPlayRate
{
	namespace Ref
	{
		typedef EMCsAnim2DPlayRate EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_001, "0.001s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_01, "0.01s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_1, "0.1s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_1, "1s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_10, "10s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_100, "100s");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_15Fps, "15 fps");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_24Fps, "24 fps (film)");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_25Fps, "25 fps (PAL/25)");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_29_97Fps, "29.97 fps (NTSC/30)");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_30Fps, "30 fps");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_48Fps, "48 fps");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_50Fps, "50 fps (PAL/50)");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_59_94Fps, "59.94 fps (NTSC/60)");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_60Fps, "60 fps");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_120Fps, "120 fps");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom Delta Time");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom Total Time");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimeAndTotalTime, "Custom Delta Time and Total Time");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnim2DPlayRate_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAnim2DPlayRate_MAX;
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NPlayRate
		{
			namespace Ref
			{
				typedef EMPlayRate EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_001, "0.001s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_01, "0.01s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_0_1, "0.1s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_1, "1s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_10, "10s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_100, "100s");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_15Fps, "15 fps");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_24Fps, "24 fps (film)");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_25Fps, "25 fps (PAL/25)");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_29_97Fps, "29.97 fps (NTSC/30)");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_30Fps, "30 fps");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_48Fps, "48 fps");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_50Fps, "50 fps (PAL/50)");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_59_94Fps, "59.94 fps (NTSC/60)");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_60Fps, "60 fps");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_120Fps, "120 fps");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom Delta Time");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom Total Time");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTimeAndTotalTime, "Custom Delta Time and Total Time");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayRate_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)Type::EPlayRate_MAX;

			float GetDeltaTime(const EPlayRate& PlayRate)
			{
				if (PlayRate == EPlayRate::PR_0_001){ return 0.001f; }
				if (PlayRate == EPlayRate::PR_0_01){ return 0.01f; }
				if (PlayRate == EPlayRate::PR_0_1){ return 0.1f; }
				if (PlayRate == EPlayRate::PR_1){ return 1.0f; }
				if (PlayRate == EPlayRate::PR_10){ return 10.0f; }
				if (PlayRate == EPlayRate::PR_100){ return 100.0f; }
				if (PlayRate == EPlayRate::PR_15Fps){ return 0.066667f; }
				if (PlayRate == EPlayRate::PR_24Fps){ return 0.041667f; }
				if (PlayRate == EPlayRate::PR_25Fps){ return 0.04f; }
				if (PlayRate == EPlayRate::PR_29_97Fps){ return 0.0333667f; }
				if (PlayRate == EPlayRate::PR_30Fps){ return 0.033333f; }
				if (PlayRate == EPlayRate::PR_48Fps){ return 0.020833f; }
				if (PlayRate == EPlayRate::PR_50Fps){ return 0.02f; }
				if (PlayRate == EPlayRate::PR_59_94Fps){ return 0.01668335f; }
				if (PlayRate == EPlayRate::PR_60Fps){ return 0.0166667f; }
				if (PlayRate == EPlayRate::PR_120Fps){ return 0.008333f; }
				return 0.0f;
			}
		}
	}
}

#pragma endregion Anim2DPlayRate

// Anim2DPlayback
#pragma region

namespace NCsAnim2DPlayback
{
	namespace Ref
	{
		typedef EMCsAnim2DPlayback EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Forward);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Reverse);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Loop);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAnim2DPlayback_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAnim2DPlayback_MAX;
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NPlayback
		{
			namespace Ref
			{
				typedef EMPlayback EnumMapType;

				CSCORE_API CS_ADD_TO_ENUM_MAP(Forward);
				CSCORE_API CS_ADD_TO_ENUM_MAP(Reverse);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PingPong, "Ping Pong");
				CSCORE_API CS_ADD_TO_ENUM_MAP(Loop);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopReverse, "Loop Reverse");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(LoopPingPong, "Loop Ping Pong");
				CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EPlayback_MAX, "MAX");
			}

			CSCORE_API const uint8 MAX = (uint8)Type::EPlayback_MAX;
		}
	}
}

#pragma endregion Anim2DPlayback

// FCsAnim2DFlipbookTextureFrame
#pragma region

#define FrameType NCsAnim::N2D::NTexture::NFlipbook::FFrame

void FCsAnim2DFlipbookTextureFrame::CopyToFrame(FrameType* Frame)
{
	Frame->SetTexture(Texture.GetPtr());
	Frame->SetParameterName(&ParameterName);
}

void FCsAnim2DFlipbookTextureFrame::CopyToFrameAsValue(FrameType* Frame) const
{
	Frame->SetTexture(Texture.Get());
	Frame->SetParameterName(ParameterName);
}

#undef FrameType

bool FCsAnim2DFlipbookTextureFrame::IsValidChecked(const FString& Context) const
{
	// Check Texture is Valid
	check(Texture.IsValidChecked(Context));
	// Check ParameterName is Valid
	CS_IS_NAME_NONE_CHECKED(ParameterName)
	return true;
}

bool FCsAnim2DFlipbookTextureFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Texture is Valid
	if (!Texture.IsValid(Context, Log))
		return false;
	// Check ParameterName is Valid
	CS_IS_NAME_NONE(ParameterName)
	return true;
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NFlipbook
			{
				bool FFrame::IsValidChecked(const FString& Context) const
				{
					// Check GetTexture() is Valid
					CS_IS_PTR_NULL_CHECKED(GetTexture())
					// Check GetParameterName() is Valid
					CS_IS_NAME_NONE_CHECKED(GetParameterName())
					return true;
				}

				bool FFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					// Check GetTexture() is Valid
					CS_IS_PTR_NULL(GetTexture())
					// Check GetParameterName() is Valid
					CS_IS_NAME_NONE(GetParameterName())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DFlipbookTextureFrame

// FCsAnim2DFlipbookTexture
#pragma region

void FCsAnim2DFlipbookTexture::Resolve()
{
	using namespace NCsAnim::N2D;

	// CustomDeltaTime
	if (PlayRate == ECsAnim2DPlayRate::PR_CustomDeltaTime)
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
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
	if (PlayRate == ECsAnim2DPlayRate::PR_CustomTotalTime)
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
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
	if  (PlayRate == ECsAnim2DPlayRate::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime > 0.0f &&
			TotalTime > 0.0f &&
			!IsLoopingForever())
		{
			TotalCount = FMath::FloorToInt(TotalTime / DeltaTime);
		}
	}
	else
	if (PlayRate == ECsAnim2DPlayRate::PR_Custom)
	{
		// Do Nothing
	}
	else
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
		{
			DeltaTime = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime = (2 * Frames.Num() - 1) * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			DeltaTime = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime = Frames.Num() * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}
}

#define FlipbookType NCsAnim::N2D::NTexture::NFlipbook::FFlipbook

void FCsAnim2DFlipbookTexture::CopyToFlipbook(FlipbookType* Flipbook)
{
	typedef NCsAnim::N2D::EPlayback PlaybackType;
	typedef NCsAnim::N2D::EPlayRate PlayRateType;

	Flipbook->SetPlayback((PlaybackType*)&Playback);
	Flipbook->SetPlayRate((PlayRateType*)&PlayRate);
	Flipbook->SetDeltaTime(&DeltaTime);
	Flipbook->SetTotalTime(&TotalTime);

	Flipbook->Frames.Reset(Frames.Num());

	for (FCsAnim2DFlipbookTextureFrame& Frame : Frames)
	{
		Flipbook->Frames.AddDefaulted();
		
		typedef NCsAnim::N2D::NTexture::NFlipbook::FFrame FrameType;

		FrameType& F = Flipbook->Frames.Last();

		Frame.CopyToFrame(&F);
	}
	Flipbook->SetTotalCount(&TotalCount);
}

void FCsAnim2DFlipbookTexture::CopyToFlipbookAsValue(FlipbookType* Flipbook) const
{
	typedef NCsAnim::N2D::EPlayback PlaybackType;
	typedef NCsAnim::N2D::EPlayRate PlayRateType;

	Flipbook->SetPlayback((PlaybackType)Playback);
	Flipbook->SetPlayRate((PlayRateType)PlayRate);
	Flipbook->SetDeltaTime(DeltaTime);
	Flipbook->SetTotalTime(TotalTime);

	Flipbook->Frames.Reset(Frames.Num());

	for (const FCsAnim2DFlipbookTextureFrame& Frame : Frames)
	{
		Flipbook->Frames.AddDefaulted();

		typedef NCsAnim::N2D::NTexture::NFlipbook::FFrame FrameType;

		FrameType& F = Flipbook->Frames.Last();

		Frame.CopyToFrameAsValue(&F);
	}
	Flipbook->SetTotalCount(TotalCount);
}

#undef FlipbookType

bool FCsAnim2DFlipbookTexture::IsValidChecked(const FString& Context) const
{
	// Check Playback is Valid.
	typedef EMCsAnim2DPlayback PlaybackMapType;
	typedef ECsAnim2DPlayback PlaybackType;

	check(EMCsAnim2DPlayback::Get().IsValidEnumChecked(Context, Playback));
	// Check PlayRate is Valid.
	typedef EMCsAnim2DPlayRate PlayRateMapType;
	typedef ECsAnim2DPlayRate PlayRateType;

	const PlayRateType& PR = PlayRate;

	check(EMCsAnim2DPlayRate::Get().IsValidEnumChecked(Context, PlayRate));

	// Check DeltaTime or TotalTime

	if (PR != PlayRateType::PR_CustomDeltaTime &&
		PR != PlayRateType::PR_CustomTotalTime &&
		PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
		PR != PlayRateType::PR_Custom)
	{
		const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime((NCsAnim::N2D::EPlayRate)PR);

		checkf(FMath::Abs(DeltaTime - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, PlayRateMapType::Get().ToDisplayNameChar(PR));

		checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR));
						
		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR));
		}
	}
	if (PR == PlayRateType::PR_CustomDeltaTime ||
		PR == PlayRateType::PR_CustomTotalTime ||
		PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
	{
		checkf(DeltaTime > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR));
		checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR));

		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR));
		}
	}

	// Check Frames
	checkf(Frames.Num() > CS_EMPTY, TEXT("%s: No Frames set."));

	typedef FCsAnim2DFlipbookTextureFrame FrameType;

	for (const FrameType& Frame : Frames)
	{
		check(Frame.IsValidChecked(Context));
	}
	return true;
}

bool FCsAnim2DFlipbookTexture::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Playback is Valid.
	typedef EMCsAnim2DPlayback PlaybackMapType;
	typedef ECsAnim2DPlayback PlaybackType;

	CS_IS_ENUM_VALID(PlaybackMapType, PlaybackType, Playback)

	// Check PlayRate is Valid.
		typedef EMCsAnim2DPlayRate PlayRateMapType;
	typedef ECsAnim2DPlayRate PlayRateType;

	const PlayRateType& PR = PlayRate;

	CS_IS_ENUM_VALID(PlayRateMapType, PlayRateType, PlayRate)

	// Check DeltaTime or TotalTime

	if (PR != PlayRateType::PR_CustomDeltaTime &&
		PR != PlayRateType::PR_CustomTotalTime &&
		PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
		PR != PlayRateType::PR_Custom)
	{
		const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime((NCsAnim::N2D::EPlayRate)PR);

		if (FMath::Abs(DeltaTime - DT) > KINDA_SMALL_NUMBER)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (TotalTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR)));
				return false;
			}
		}
	}

	if (PR == PlayRateType::PR_CustomDeltaTime ||
		PR == PlayRateType::PR_CustomTotalTime ||
		PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (TotalTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR)));
				return false;
			}
		}
	}

	// Check Frames
	if (Frames.Num() == CS_EMPTY)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Frames set.")));
		return false;
	}

	typedef FCsAnim2DFlipbookTextureFrame FrameType;

	for (const FrameType& Frame : Frames)
	{
		if (!Frame.IsValid(Context, Log))
			return false;
	}
	return true;
}

void FCsAnim2DFlipbookTexture::OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName)
{
	Resolve();
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NFlipbook
			{
				bool FFlipbook::IsValidChecked(const FString& Context) const
				{
					// Check Playback is Valid.
					typedef NCsAnim::N2D::EMPlayback PlaybackMapType;
					check(PlaybackMapType::Get().IsValidEnumChecked(Context, GetPlayback()));
					// Check PlayRate is Valid.
					typedef NCsAnim::N2D::EPlayRate PlayRateType;
					typedef NCsAnim::N2D::EMPlayRate PlayRateMapType;
					
					const PlayRateType& PR = GetPlayRate();
					
					check(PlayRateMapType::Get().IsValidEnumChecked(Context, PR));

					// Check DeltaTime or TotalTime

					if (PR != PlayRateType::PR_CustomDeltaTime &&
						PR != PlayRateType::PR_CustomTotalTime &&
						PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
						PR != PlayRateType::PR_Custom)
					{
						const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime(PR);

						checkf(FMath::Abs(GetDeltaTime() - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, GetDeltaTime(), GetDeltaTime(), DT, PlayRateMapType::Get().ToDisplayNameChar(PR));

						checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						
						if (!IsLoopingForever())
						{
							checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						}
					}
					if (PR == PlayRateType::PR_CustomDeltaTime ||
						PR == PlayRateType::PR_CustomTotalTime ||
						PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
					{
						checkf(GetDeltaTime() > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetDeltaTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));

						if (!IsLoopingForever())
						{
							checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						}
					}

					// Check Frames
					checkf(Frames.Num() > CS_EMPTY, TEXT("%s: No Frames set."));

					typedef NCsAnim::N2D::NTexture::NFlipbook::FFrame FrameType;

					for (const FrameType& Frame : Frames)
					{
						check(Frame.IsValidChecked(Context));
					}
					return true;
				}

				bool FFlipbook::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					// Check Playback is Valid.
					typedef NCsAnim::N2D::EMPlayback PlaybackMapType;
					typedef NCsAnim::N2D::EPlayback PlaybackType;

					CS_IS_ENUM_VALID(PlaybackMapType, PlaybackType, GetPlayback())

					// Check PlayRate is Valid.
					typedef NCsAnim::N2D::EMPlayRate PlayRateMapType;
					typedef NCsAnim::N2D::EPlayRate PlayRateType;

					const PlayRateType& PR = GetPlayRate();

					CS_IS_ENUM_VALID(PlayRateMapType, PlayRateType, GetPlayRate())

					// Check DeltaTime or TotalTime

					if (PR != PlayRateType::PR_CustomDeltaTime &&
						PR != PlayRateType::PR_CustomTotalTime &&
						PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
						PR != PlayRateType::PR_Custom)
					{
						const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime(PR);

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
					if (Frames.Num() == CS_EMPTY)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Frames set.")));
						return false;
					}

					typedef NCsAnim::N2D::NTexture::NFlipbook::FFrame FrameType;

					for (const FrameType& Frame : Frames)
					{
						if (!Frame.IsValid(Context, Log))
							return false;
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DFlipbookTexture

// FCsAnim2DMaterialFlipbookFrame
#pragma region

#define FrameType NCsAnim::N2D::NMaterial::NFlipbook::FFrame
void FCsAnim2DMaterialFlipbookFrame::CopyToFrame(FrameType* Frame)
{
	Frame->SetMaterial(Material.GetPtr());
	Frame->SetIndex(&Index);
}

void FCsAnim2DMaterialFlipbookFrame::CopyToFrameAsValue(FrameType* Frame) const
{
	Frame->SetMaterial(Material.Get());
	Frame->SetIndex(Index);
}

#undef FrameType

bool FCsAnim2DMaterialFlipbookFrame::IsValidChecked(const FString& Context) const
{
	// Check Material is Valid
	check(Material.IsValidChecked(Context))
	// Check GetIndex() is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)
	return true;
}

bool FCsAnim2DMaterialFlipbookFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Material is Valid
	if (!Material.IsValid(Context, Log))
		return false;
	// Check Index is Valid
	CS_IS_INT_GREATER_THAN_OR_EQUAL(Index, 0)
	return true;
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			namespace NFlipbook
			{
				bool FFrame::IsValidChecked(const FString& Context) const
				{
					// Check GetMaterial() is Valid
					CS_IS_PTR_NULL_CHECKED(GetMaterial())
					// Check GetIndex() is Valid
					CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetIndex(), 0)
					return true;
				}

				bool FFrame::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					// Check GetMaterial() is Valid
					CS_IS_PTR_NULL(GetMaterial())
					// Check GetIndex() is Valid
					CS_IS_INT_GREATER_THAN_OR_EQUAL(GetIndex(), 0)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DMaterialFlipbookFrame

// FCsAnim2DMaterialFlipbook
#pragma region

void FCsAnim2DMaterialFlipbook::Resolve()
{
	using namespace NCsAnim::N2D;

	// CustomDeltaTime
	if (PlayRate == ECsAnim2DPlayRate::PR_CustomDeltaTime)
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
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
	if (PlayRate == ECsAnim2DPlayRate::PR_CustomTotalTime)
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
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
	if  (PlayRate == ECsAnim2DPlayRate::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime > 0.0f &&
			TotalTime > 0.0f &&
			!IsLoopingForever())
		{
			TotalCount = FMath::FloorToInt(TotalTime / DeltaTime);
		}
	}
	else
	if (PlayRate == ECsAnim2DPlayRate::PR_Custom)
	{
		// Do Nothing
	}
	else
	{
		if (Playback == ECsAnim2DPlayback::PingPong)
		{
			DeltaTime = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime = (2 * Frames.Num() - 1) * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : (2 * Frames.Num() - 1);
		}
		else
		{
			DeltaTime = NPlayRate::GetDeltaTime((EPlayRate)PlayRate);
			TotalTime = Frames.Num() * DeltaTime;
			TotalCount = IsLoopingForever() ? 0 : Frames.Num();
		}
	}
}

#define FlipbookType NCsAnim::N2D::NMaterial::NFlipbook::FFlipbook

void FCsAnim2DMaterialFlipbook::CopyToFlipbook(FlipbookType* Flipbook)
{
	typedef NCsAnim::N2D::EPlayback PlaybackType;
	typedef NCsAnim::N2D::EPlayRate PlayRateType;

	Flipbook->SetPlayback((PlaybackType*)&Playback);
	Flipbook->SetPlayRate((PlayRateType*)&PlayRate);
	Flipbook->SetDeltaTime(&DeltaTime);
	Flipbook->SetTotalTime(&TotalTime);

	Flipbook->Frames.Reset(Frames.Num());

	for (FCsAnim2DMaterialFlipbookFrame& Frame : Frames)
	{
		Flipbook->Frames.AddDefaulted();
		
		typedef NCsAnim::N2D::NMaterial::NFlipbook::FFrame FrameType;

		FrameType& F = Flipbook->Frames.Last();

		Frame.CopyToFrame(&F);
	}
	Flipbook->SetTotalCount(&TotalCount);
}

void FCsAnim2DMaterialFlipbook::CopyToFlipbookAsValue(FlipbookType* Flipbook) const
{
	typedef NCsAnim::N2D::EPlayback PlaybackType;
	typedef NCsAnim::N2D::EPlayRate PlayRateType;

	Flipbook->SetPlayback((PlaybackType)Playback);
	Flipbook->SetPlayRate((PlayRateType)PlayRate);
	Flipbook->SetDeltaTime(DeltaTime);
	Flipbook->SetTotalTime(TotalTime);

	Flipbook->Frames.Reset(Frames.Num());

	for (const FCsAnim2DMaterialFlipbookFrame& Frame : Frames)
	{
		Flipbook->Frames.AddDefaulted();

		typedef NCsAnim::N2D::NMaterial::NFlipbook::FFrame FrameType;

		FrameType& F = Flipbook->Frames.Last();

		Frame.CopyToFrameAsValue(&F);
	}
	Flipbook->SetTotalCount(TotalCount);
}

#undef FlipbookType

bool FCsAnim2DMaterialFlipbook::IsValidChecked(const FString& Context) const
{
	// Check Playback is Valid.
	typedef EMCsAnim2DPlayback PlaybackMapType;
	typedef ECsAnim2DPlayback PlaybackType;

	check(EMCsAnim2DPlayback::Get().IsValidEnumChecked(Context, Playback));
	// Check PlayRate is Valid.
	typedef EMCsAnim2DPlayRate PlayRateMapType;
	typedef ECsAnim2DPlayRate PlayRateType;

	const PlayRateType& PR = PlayRate;

	check(EMCsAnim2DPlayRate::Get().IsValidEnumChecked(Context, PlayRate));

	// Check DeltaTime or TotalTime

	if (PR != PlayRateType::PR_CustomDeltaTime &&
		PR != PlayRateType::PR_CustomTotalTime &&
		PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
		PR != PlayRateType::PR_Custom)
	{
		const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime((NCsAnim::N2D::EPlayRate)PR);

		checkf(FMath::Abs(DeltaTime - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, PlayRateMapType::Get().ToDisplayNameChar(PR));

		checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR));
						
		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR));
		}
	}
	if (PR == PlayRateType::PR_CustomDeltaTime ||
		PR == PlayRateType::PR_CustomTotalTime ||
		PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
	{
		checkf(DeltaTime > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR));
		checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR));

		if (!IsLoopingForever())
		{
			checkf(TotalCount > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR));
		}
	}

	// Check Frames
	checkf(Frames.Num() > CS_EMPTY, TEXT("%s: No Frames set."));

	typedef FCsAnim2DMaterialFlipbookFrame FrameType;

	for (const FrameType& Frame : Frames)
	{
		check(Frame.IsValidChecked(Context));
	}
	return true;
}

bool FCsAnim2DMaterialFlipbook::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Playback is Valid.
	typedef EMCsAnim2DPlayback PlaybackMapType;
	typedef ECsAnim2DPlayback PlaybackType;

	CS_IS_ENUM_VALID(PlaybackMapType, PlaybackType, Playback)

	// Check PlayRate is Valid.
		typedef EMCsAnim2DPlayRate PlayRateMapType;
	typedef ECsAnim2DPlayRate PlayRateType;

	const PlayRateType& PR = PlayRate;

	CS_IS_ENUM_VALID(PlayRateMapType, PlayRateType, PlayRate)

	// Check DeltaTime or TotalTime

	if (PR != PlayRateType::PR_CustomDeltaTime &&
		PR != PlayRateType::PR_CustomTotalTime &&
		PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
		PR != PlayRateType::PR_Custom)
	{
		const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime((NCsAnim::N2D::EPlayRate)PR);

		if (FMath::Abs(DeltaTime - DT) > KINDA_SMALL_NUMBER)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (TotalTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR)));
				return false;
			}
		}
	}

	if (PR == PlayRateType::PR_CustomDeltaTime ||
		PR == PlayRateType::PR_CustomTotalTime ||
		PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
	{
		if (DeltaTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (TotalTime <= 0.0f)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, TotalTime, PlayRateMapType::Get().ToDisplayNameChar(PR)));
			return false;
		}

		if (!IsLoopingForever())
		{
			if (TotalCount <= 0)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, TotalCount, PlayRateMapType::Get().ToDisplayNameChar(PR)));
				return false;
			}
		}
	}

	// Check Frames
	if (Frames.Num() == CS_EMPTY)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Frames set.")));
		return false;
	}

	typedef FCsAnim2DMaterialFlipbookFrame FrameType;

	for (const FrameType& Frame : Frames)
	{
		if (!Frame.IsValid(Context, Log))
			return false;
	}
	return true;
}

void FCsAnim2DMaterialFlipbook::OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName)
{
	Resolve();
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			namespace NFlipbook
			{
				bool FFlipbook::IsValidChecked(const FString& Context) const
				{
					// Check Playback is Valid.
					typedef NCsAnim::N2D::EMPlayback PlaybackMapType;
					check(PlaybackMapType::Get().IsValidEnumChecked(Context, GetPlayback()));
					// Check PlayRate is Valid.
					typedef NCsAnim::N2D::EPlayRate PlayRateType;
					typedef NCsAnim::N2D::EMPlayRate PlayRateMapType;
					
					const PlayRateType& PR = GetPlayRate();
					
					check(PlayRateMapType::Get().IsValidEnumChecked(Context, PR));

					// Check DeltaTime or TotalTime

					if (PR != PlayRateType::PR_CustomDeltaTime &&
						PR != PlayRateType::PR_CustomTotalTime &&
						PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
						PR != PlayRateType::PR_Custom)
					{
						const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime(PR);

						checkf(FMath::Abs(GetDeltaTime() - DT) <= KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, GetDeltaTime(), GetDeltaTime(), DT, PlayRateMapType::Get().ToDisplayNameChar(PR));

						checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						
						if (!IsLoopingForever())
						{
							checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						}
					}
					if (PR == PlayRateType::PR_CustomDeltaTime ||
						PR == PlayRateType::PR_CustomTotalTime ||
						PR == PlayRateType::PR_CustomDeltaTimeAndTotalTime)
					{
						checkf(GetDeltaTime() > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetDeltaTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						checkf(GetTotalTime() > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalTime(), PlayRateMapType::Get().ToDisplayNameChar(PR));

						if (!IsLoopingForever())
						{
							checkf(GetTotalCount() > 0, TEXT("%s: TotalCount: %d is NOT > 0.0f for PlayRate: %s."), *Context, GetTotalCount(), PlayRateMapType::Get().ToDisplayNameChar(PR));
						}
					}

					// Check Frames
					checkf(Frames.Num() > CS_EMPTY, TEXT("%s: No Frames set."));

					typedef NCsAnim::N2D::NMaterial::NFlipbook::FFrame FrameType;

					for (const FrameType& Frame : Frames)
					{
						check(Frame.IsValidChecked(Context));
					}
					return true;
				}

				bool FFlipbook::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
				// Check Playback is Valid.
					typedef NCsAnim::N2D::EMPlayback PlaybackMapType;
					typedef NCsAnim::N2D::EPlayback PlaybackType;

					CS_IS_ENUM_VALID(PlaybackMapType, PlaybackType, GetPlayback())

					// Check PlayRate is Valid.
					typedef NCsAnim::N2D::EMPlayRate PlayRateMapType;
					typedef NCsAnim::N2D::EPlayRate PlayRateType;

					const PlayRateType& PR = GetPlayRate();

					CS_IS_ENUM_VALID(PlayRateMapType, PlayRateType, GetPlayRate())

					// Check DeltaTime or TotalTime

					if (PR != PlayRateType::PR_CustomDeltaTime &&
						PR != PlayRateType::PR_CustomTotalTime &&
						PR != PlayRateType::PR_CustomDeltaTimeAndTotalTime &&
						PR != PlayRateType::PR_Custom)
					{
						const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime(PR);

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
					if (Frames.Num() == CS_EMPTY)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Frames set.")));
						return false;
					}

					typedef NCsAnim::N2D::NMaterial::NFlipbook::FFrame FrameType;

					for (const FrameType& Frame : Frames)
					{
						if (!Frame.IsValid(Context, Log))
							return false;
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DMaterialFlipbook