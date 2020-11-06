// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_Texture.h"

#include "CsTypes_Anim2D.generated.h"
#pragma once

// Anim2DPlayRate
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsAnim2DPlayRate : uint8
{
	PR_0_001				UMETA(DisplayName = "0.001s"),
	PR_0_01					UMETA(DisplayName = "0.01s"),
	PR_0_1					UMETA(DisplayName = "0.1s"),
	PR_1					UMETA(DisplayName = "1s"),
	PR_10					UMETA(DisplayName = "10s"),
	PR_100					UMETA(DisplayName = "100s"),
	PR_15Fps				UMETA(DisplayName = "15 fps"),
	PR_24Fps				UMETA(DisplayName = "24 fps (film)"),
	PR_25Fps				UMETA(DisplayName = "25 fps (PAL/25)"),
	PR_29_97Fps				UMETA(DisplayName = "29.97 fps (NTSC/30)"),
	PR_30Fps				UMETA(DisplayName = "30 fps"),
	PR_48Fps				UMETA(DisplayName = "48 fps"),
	PR_50Fps				UMETA(DisplayName = "50 fps (PAL/50)"),
	PR_59_94Fps				UMETA(DisplayName = "59.94 fps (NTSC/60)"),
	PR_60Fps				UMETA(DisplayName = "60 fps"),
	PR_120Fps				UMETA(DisplayName = "120 fps"),
	PR_CustomDeltaTime		UMETA(DisplayName = "Custom DeltaTime"),
	PR_CustomTotalTime		UMETA(DisplayName = "Custom Total Time"),
	PR_Custom				UMETA(DisplayName = "Custom"),
	ECsAnim2DPlayRate_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAnim2DPlayRate : public TCsEnumMap<ECsAnim2DPlayRate>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnim2DPlayRate, ECsAnim2DPlayRate)
};

namespace NCsAnim2DPlayRate
{
	typedef ECsAnim2DPlayRate Type;

	namespace Ref
	{
		extern CSCORE_API const Type PR_0_001;
		extern CSCORE_API const Type PR_0_01;
		extern CSCORE_API const Type PR_0_1;
		extern CSCORE_API const Type PR_1;
		extern CSCORE_API const Type PR_10;
		extern CSCORE_API const Type PR_100;
		extern CSCORE_API const Type PR_15Fps;
		extern CSCORE_API const Type PR_24Fps;
		extern CSCORE_API const Type PR_25Fps;
		extern CSCORE_API const Type PR_29_97Fps;
		extern CSCORE_API const Type PR_30Fps;
		extern CSCORE_API const Type PR_48Fps;
		extern CSCORE_API const Type PR_50Fps;
		extern CSCORE_API const Type PR_59_94Fps;
		extern CSCORE_API const Type PR_60Fps;
		extern CSCORE_API const Type PR_120Fps;
		extern CSCORE_API const Type PR_CustomDeltaTime;
		extern CSCORE_API const Type PR_CustomTotalTime;
		extern CSCORE_API const Type PR_Custom;
		extern CSCORE_API const Type ECsAnim2DPlayRate_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsAnim
{
	namespace N2D
	{
		/**
		*/
		enum class EPlayRate : uint8
		{
			PR_0_001,
			PR_0_01,
			PR_0_1,
			PR_1,
			PR_10,
			PR_100,
			PR_15Fps,
			PR_24Fps,
			PR_25Fps,
			PR_29_97Fps,
			PR_30Fps,
			PR_48Fps,
			PR_50Fps,
			PR_59_94Fps	,
			PR_60Fps,
			PR_120Fps,
			PR_Custom,
			ECsAnim2DPlayRate_MAX
		};

		namespace NPlayRate
		{
			float GetDeltaTime(const EPlayRate& PlayRate);
		}
	}
}

#pragma endregion Anim2DPlayRate

// Anim2DPlayback
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsAnim2DPlayback : uint8
{
	Forward					UMETA(DisplayName = "Forward"),
	Reverse					UMETA(DisplayName = "Reverse"),
	PingPong				UMETA(DisplayName = "Ping Pong"),
	Loop					UMETA(DisplayName = "Loop"),
	LoopReverse				UMETA(DisplayName = "Loop Reverse"),
	LoopPingPong			UMETA(DisplayName = "Loop Ping Pong"),
	Custom					UMETA(DisplayName = "Custom"),
	ECsAnim2DPlayback_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAnim2DPlayback : public TCsEnumMap<ECsAnim2DPlayback>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnim2DPlayback, ECsAnim2DPlayback)
};

namespace NCsAnim2DPlayback
{
	typedef ECsAnim2DPlayback Type;

	namespace Ref
	{
		extern CSCORE_API const Type Forward;
		extern CSCORE_API const Type Reverse;
		extern CSCORE_API const Type PingPong;
		extern CSCORE_API const Type Loop;
		extern CSCORE_API const Type LoopReverse;
		extern CSCORE_API const Type LoopPingPong;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsAnim2DPlayback_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsAnim
{
	namespace N2D
	{
		/**
		*/
		enum class EPlayback : uint8
		{
			Forward,
			Reverse,
			PingPong,
			Loop,
			LoopReverse,
			LoopPingPong,
			Custom,
			ECsAnim2DPlayback_MAX
		};
	}
}

#pragma endregion Anim2DPlayback

// FCsAnim2DFlipbookTextureFrame
#pragma region

// NCsAnim::N2D::NFlipbook::NTexture::FFrame
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NFlipbook, NTexture, FFrame)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DFlipbookTextureFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsTexture Texture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ParameterName;

	FCsAnim2DFlipbookTextureFrame() :
		Texture(),
		ParameterName(NAME_None)
	{
	}

#define FrameType NCsAnim::N2D::NFlipbook::NTexture::FFrame
	void CopyFrame(FrameType* Frame);
#undef FrameType

private:

	FORCEINLINE void __Nothing() const {}
};

class UTexture;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NFlipbook
		{
			namespace NTexture
			{
				struct CSCORE_API FFrame
				{
				public:

					UTexture* Texture;
					UTexture** Texture_Emu;

					FName ParameterName;
					FName* ParameterName_Emu;

					FFrame() :
						Texture(nullptr),
						Texture_Emu(nullptr),
						ParameterName(NAME_None),
						ParameterName_Emu(nullptr)
					{
						Texture_Emu = &Texture;
						ParameterName_Emu = &ParameterName;
					}

					FORCEINLINE void SetTexture(UTexture** Value) { Texture_Emu = Value; }
					FORCEINLINE UTexture* GetTexture() const { return *Texture_Emu; }

					FORCEINLINE void SetParameterName(FName* Value) { ParameterName_Emu = Value; }
					FORCEINLINE const FName& GetParameterName() const { return *ParameterName_Emu; }
				};
			}
		}
	}
}

#pragma endregion FCsAnim2DFlipbookTextureFrame

// FCsAnim2DFlipbookTexture
#pragma region

// NCsAnim::N2D::NFlipbook::NTexture::FFlipbook
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NFlipbook, NTexture, FFlipbook)

/**
* Describes a 2D Animation "flipbook" made up of Textures.
* The texture are meant to swapped on a Material.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DFlipbookTexture
{
	GENERATED_USTRUCT_BODY()

	/** Describes how the Frames will be played. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECsAnim2DPlayback Playback;

	/** Describes the time between each Frame. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECsAnim2DPlayRate PlayRate;

	/** Time between each Frame.
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomDeltaTime. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DeltaTime;

	/** Total time to play all Frames. The time between each Frame will be
		TotalTime / Number of Frames. 
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomTotalTime. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TotalTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCsAnim2DFlipbookTextureFrame> Frames;

	FCsAnim2DFlipbookTexture() :
		Playback(ECsAnim2DPlayback::Forward),
		PlayRate(ECsAnim2DPlayRate::PR_60Fps),
		DeltaTime(0.0f),
		TotalTime(0.0f),
		Frames()
	{
	}

#define FlipbookType NCsAnim::N2D::NFlipbook::NTexture::FFlipbook
	void CopyFlipbook(FlipbookType* Flipbook);
#undef FlipbookType

private:

	FORCEINLINE void __Nothing() const {}
};

namespace NCsAnim
{
	namespace N2D
	{
		namespace NFlipbook
		{
			namespace NTexture
			{
				struct CSCORE_API FFlipbook
				{
				#define PlaybackType NCsAnim::N2D::EPlayback
				#define PlayRateType NCsAnim::N2D::EPlayRate
				#define FrameType NCsAnim::N2D::NFlipbook::NTexture::FFrame

				public:

					PlaybackType Playback;
					PlaybackType* Playback_Emu;

					PlayRateType PlayRate;
					PlayRateType* PlayRate_Emu;

					float DeltaTime;
					float* DeltaTime_Emu;

					float TotalTime;
					float* TotalTime_Emu;

					TArray<FrameType> Frames;

					FFlipbook() :
						Playback(PlaybackType::Forward),
						Playback_Emu(nullptr),
						PlayRate(PlayRateType::PR_60Fps),
						PlayRate_Emu(nullptr),
						DeltaTime(0.0f),
						DeltaTime_Emu(nullptr),
						TotalTime(0.0f),
						TotalTime_Emu(nullptr)
					{
						Playback_Emu = &Playback;
						PlayRate_Emu = &PlayRate;
						DeltaTime_Emu = &DeltaTime;
						TotalTime_Emu = &TotalTime;
					}

					FORCEINLINE void SetPlayback(PlaybackType* Value) { Playback_Emu = Value; }
					FORCEINLINE const PlaybackType& GetPlayback() const { return *Playback_Emu; }

					FORCEINLINE void SetPlayRate(PlayRateType* Value) { PlayRate_Emu = Value; }
					FORCEINLINE const PlayRateType& GetPlayRate() const { return *PlayRate_Emu; }

					FORCEINLINE void SetDeltaTime(float* Value) { DeltaTime_Emu = Value; }
					FORCEINLINE const float& GetDeltaTime() const { return *DeltaTime_Emu; }

					FORCEINLINE void SetTotalTime(float* Value) { TotalTime_Emu = Value; }
					FORCEINLINE const float& GetTotalTime() const { return *TotalTime_Emu; }

				#undef PlaybackType
				#undef PlayRateType
				#undef FrameType
				};
			}
		}
	}
}
#pragma endregion FCsAnim2DFlipbookTexture

class UStaticMeshComponent;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NPlay
		{
			namespace NStaticMesh
			{
				struct CSCORE_API FParams
				{
				#define PlayRateType NCsAnim::N2D::EPlayRate

					UObject* Owner;

					UStaticMeshComponent* Component;
					
					PlayRateType PlayRate;

					float DeltaTime;

					FParams() :
						Owner(nullptr),
						Component(nullptr),
						PlayRate(PlayRateType::PR_60Fps),
						DeltaTime(0.0f)
					{
					}

				#undef PlayRateType
				};
			}
		}
	}
}