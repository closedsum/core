// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Anim2D.h"

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
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom DeltaTime");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom TotalTime");
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
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_Custom, "Custom");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomDeltaTime, "Custom DeltaTime");
				CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(PR_CustomTotalTime, "Custom TotalTime");
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

#define FrameType NCsAnim::N2D::NFlipbook::NTexture::FFrame
void FCsAnim2DFlipbookTextureFrame::CopyFrame(FrameType* Frame)
{
#undef FrameType

	Frame->SetTexture(&(Texture.Texture_Internal));
	Frame->SetParameterName(&ParameterName);
}

#pragma endregion FCsAnim2DFlipbookTextureFrame

// FCsAnim2DFlipbookTexture
#pragma region

#define FlipbookType NCsAnim::N2D::NFlipbook::NTexture::FFlipbook
void FCsAnim2DFlipbookTexture::CopyFlipbook(FlipbookType* Flipbook)
{
#undef FlipbookType

	typedef NCsAnim::N2D::EPlayback PlaybackType;
	typedef NCsAnim::N2D::EPlayRate PlayRateType;

	Flipbook->SetPlayback((PlaybackType*)&Playback);
	Flipbook->SetPlayRate((PlayRateType*)&PlayRate);
	Flipbook->SetDeltaTime(&DeltaTime);
	Flipbook->SetTotalTime(&TotalTime);
}

namespace NCsAnim
{
	namespace N2D
	{
		namespace NFlipbook
		{
			namespace NTexture
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
						PR != PlayRateType::PR_Custom)
					{
						const float DT = NCsAnim::N2D::NPlayRate::GetDeltaTime(PR);

						checkf(FMath::Abs(DeltaTime - DT) > KINDA_SMALL_NUMBER, TEXT("%s: DeltaTime: %f is NOT correct (%f != %f) for PlayRate: %s."), *Context, DeltaTime, DeltaTime, DT, PlayRateMapType::Get().ToDisplayNameChar(PR));
					}
					if (PR == PlayRateType::PR_CustomDeltaTime)
					{
						checkf(DeltaTime > 0.0f, TEXT("%s: DeltaTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR));
					}
					if (PR == PlayRateType::PR_CustomTotalTime)
					{
						checkf(TotalTime > 0.0f, TEXT("%s: TotalTime: %f is NOT > 0.0f for PlayRate: %s."), *Context, DeltaTime, PlayRateMapType::Get().ToDisplayNameChar(PR))
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsAnim2DFlipbookTexture