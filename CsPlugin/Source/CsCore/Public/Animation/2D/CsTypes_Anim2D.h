// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_Texture.h"
#include "Material/CsTypes_Material.h"

#include "CsTypes_Anim2D.generated.h"
#pragma once

// Anim2DPlayRate
#pragma region

/**
*/
UENUM(BlueprintType)
enum class ECsAnim2DPlayRate : uint8
{
	PR_0_001						UMETA(DisplayName = "0.001s"),
	PR_0_01							UMETA(DisplayName = "0.01s"),
	PR_0_1							UMETA(DisplayName = "0.1s"),
	PR_1							UMETA(DisplayName = "1s"),
	PR_10							UMETA(DisplayName = "10s"),
	PR_100							UMETA(DisplayName = "100s"),
	PR_15Fps						UMETA(DisplayName = "15 fps"),
	PR_24Fps						UMETA(DisplayName = "24 fps (film)"),
	PR_25Fps						UMETA(DisplayName = "25 fps (PAL/25)"),
	PR_29_97Fps						UMETA(DisplayName = "29.97 fps (NTSC/30)"),
	PR_30Fps						UMETA(DisplayName = "30 fps"),
	PR_48Fps						UMETA(DisplayName = "48 fps"),
	PR_50Fps						UMETA(DisplayName = "50 fps (PAL/50)"),
	PR_59_94Fps						UMETA(DisplayName = "59.94 fps (NTSC/60)"),
	PR_60Fps						UMETA(DisplayName = "60 fps"),
	PR_120Fps						UMETA(DisplayName = "120 fps"),
	PR_CustomDeltaTime				UMETA(DisplayName = "Custom Delta Time"),
	PR_CustomTotalTime				UMETA(DisplayName = "Custom Total Time"),
	PR_CustomDeltaTimeAndTotalTime	UMETA(DisplayName = "Custom Delta Time and Total Time"),
	PR_Custom						UMETA(DisplayName = "Custom"),
	ECsAnim2DPlayRate_MAX			UMETA(Hidden),
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
		extern CSCORE_API const Type PR_CustomDeltaTimeAndTotalTime;
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
			PR_CustomDeltaTime,
			PR_CustomTotalTime,
			PR_CustomDeltaTimeAndTotalTime,
			PR_Custom,
			EPlayRate_MAX
		};

		struct CSCORE_API EMPlayRate : public TCsEnumMap<EPlayRate>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayRate, EPlayRate)
		};

		namespace NPlayRate
		{
			typedef EPlayRate Type;

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
				extern CSCORE_API const Type PR_CustomDeltaTimeAndTotalTime;
				extern CSCORE_API const Type PR_Custom;
				extern CSCORE_API const Type EPlayRate_MAX;
			}

			extern CSCORE_API const uint8 MAX;

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
			EPlayback_MAX
		};

		struct CSCORE_API EMPlayback : public TCsEnumMap<EPlayback>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPlayback, EPlayback)
		};

		namespace NPlayback
		{
			typedef EPlayback Type;

			namespace Ref
			{
				extern CSCORE_API const Type Forward;
				extern CSCORE_API const Type Reverse;
				extern CSCORE_API const Type PingPong;
				extern CSCORE_API const Type Loop;
				extern CSCORE_API const Type LoopReverse;
				extern CSCORE_API const Type LoopPingPong;
				extern CSCORE_API const Type Custom;
				extern CSCORE_API const Type EPlayback_MAX;
			}

			extern CSCORE_API const uint8 MAX;
		}
	}
}

#pragma endregion Anim2DPlayback

// FCsAnim2DFlipbookTextureFrame
#pragma region

// NCsAnim::N2D::NTexture::NFlipbook::FFrame
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NTexture, NFlipbook, FFrame)

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

#define FrameType NCsAnim::N2D::NTexture::NFlipbook::FFrame
	void CopyToFrame(FrameType* Frame);
#undef FrameType

private:

	FORCEINLINE void __Nothing() const {}
};

class UTexture;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NFlipbook
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

					FORCEINLINE FFrame& operator=(const FFrame& B)
					{
						Texture = B.Texture;
						ParameterName = B.ParameterName;
						return *this;
					}

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Texture, UTexture)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(ParameterName, FName)

					bool IsValidChecked(const FString& Context) const;
				};
			}
		}
	}
}

#pragma endregion FCsAnim2DFlipbookTextureFrame

// FCsAnim2DFlipbookTexture
#pragma region

// NCsAnim::N2D::NTexture::NFlipbook::FFlipbook
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NTexture, NFlipbook, FFlipbook)

/**
* Describes a 2D Animation "flipbook" made up of Textures.
* The textures are meant to swapped on a Material (i.e. UMaterialInstanceDynamic) 
* or UI object (i.e. UImage).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DFlipbookTexture
{
	GENERATED_USTRUCT_BODY()

	/** Describes how the Frames will be played. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAnim2DPlayback Playback;

	/** Describes the time between each Frame. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAnim2DPlayRate PlayRate;

	/** Time between each Frame.
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomDeltaTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeltaTime;

	/** Total time to play all Frames. The time between each Frame will be
		TotalTime / Number of Frames. 
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomTotalTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TotalTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCsAnim2DFlipbookTextureFrame> Frames;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCount;

	FCsAnim2DFlipbookTexture() :
		Playback(ECsAnim2DPlayback::Forward),
		PlayRate(ECsAnim2DPlayRate::PR_60Fps),
		DeltaTime(0.0f),
		TotalTime(0.0f),
		Frames(),
		TotalCount(0)
	{
	}

	FORCEINLINE bool IsLooping() const
	{
		return Playback == ECsAnim2DPlayback::Loop ||
			   Playback == ECsAnim2DPlayback::LoopReverse ||
			   Playback == ECsAnim2DPlayback::LoopPingPong;
	}

	FORCEINLINE bool IsLoopingForever() const { return IsLooping() && TotalTime == 0.0f; }

#define FlipbookType NCsAnim::N2D::NTexture::NFlipbook::FFlipbook
	void CopyFlipbook(FlipbookType* Flipbook);
#undef FlipbookType

	void OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName);
};

namespace NCsAnim
{
	namespace N2D
	{
		namespace NTexture
		{
			namespace NFlipbook
			{
				struct CSCORE_API FFlipbook
				{
				#define PlaybackType NCsAnim::N2D::EPlayback
				#define PlayRateType NCsAnim::N2D::EPlayRate
				#define FrameType NCsAnim::N2D::NTexture::NFlipbook::FFrame

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

					int32 TotalCount;
					int32* TotalCount_Emu;

					FFlipbook() :
						Playback(PlaybackType::Forward),
						Playback_Emu(nullptr),
						PlayRate(PlayRateType::PR_60Fps),
						PlayRate_Emu(nullptr),
						DeltaTime(0.0f),
						DeltaTime_Emu(nullptr),
						TotalTime(0.0f),
						TotalTime_Emu(nullptr),
						TotalCount(0),
						TotalCount_Emu(nullptr)
					{
						Playback_Emu = &Playback;
						PlayRate_Emu = &PlayRate;
						DeltaTime_Emu = &DeltaTime;
						TotalTime_Emu = &TotalTime;
						TotalCount_Emu = &TotalCount;
					}

					FORCEINLINE FFlipbook& operator=(const FFlipbook& B)
					{
						Playback = B.GetPlayback();
						SetPlayback(&Playback);
						PlayRate = B.GetPlayRate();
						SetPlayRate(&PlayRate);
						DeltaTime = B.GetDeltaTime();
						SetDeltaTime(&DeltaTime);
						TotalTime = B.GetTotalTime();
						SetTotalTime(&TotalTime);

						Frames.Reset(FMath::Max(Frames.Max(), B.Frames.Max()));

						for (const FrameType& F : B.Frames)
						{
							Frames.Add(F);
						}

						TotalCount = B.GetTotalCount();
						SetTotalCount(&TotalCount);
						return *this;
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Playback, PlaybackType)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(PlayRate, PlayRateType)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(DeltaTime, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalTime, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalCount, int32)

					FORCEINLINE bool IsLooping() const
					{
						return GetPlayback() == EPlayback::Loop ||
							   GetPlayback() == EPlayback::LoopReverse ||
							   GetPlayback() == EPlayback::LoopPingPong;
					}

					FORCEINLINE bool IsLoopingForever() const { return IsLooping() && GetTotalTime() == 0.0f; }

					FORCEINLINE bool ShouldStartReverse() const
					{
						return GetPlayback() == EPlayback::Reverse ||
							   GetPlayback() == EPlayback::LoopReverse;
					}

					bool IsValidChecked(const FString& Context) const;

					void Reset()
					{
						Playback = PlaybackType::Forward;
						SetPlayback(&Playback);
						PlayRate = PlayRateType::PR_60Fps;
						SetPlayRate(&PlayRate);
						DeltaTime = 0.0f;
						SetDeltaTime(&DeltaTime);
						TotalTime = 0.0f;
						SetTotalTime(&TotalTime);

						Frames.Reset(Frames.Max());

						TotalCount = 0;
						SetTotalCount(&TotalCount);
					}

				#undef PlaybackType
				#undef PlayRateType
				#undef FrameType
				};
			}
		}
	}
}
#pragma endregion FCsAnim2DFlipbookTexture

// FCsAnim2DMaterialFlipbookFrame
#pragma region

// NCsAnim::N2D::NMaterial::NFlipbook::FFrame
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NMaterial, NFlipbook, FFrame)

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DMaterialFlipbookFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsMaterialInterface Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (UIMin = "0", ClampMin= "0"))
	int32 Index;

	FCsAnim2DMaterialFlipbookFrame() :
		Material(),
		Index(0)
	{
	}

#define FrameType NCsAnim::N2D::NMaterial::NFlipbook::FFrame
	void CopyToFrame(FrameType* Frame);
#undef FrameType

private:

	FORCEINLINE void __Nothing() const {}
};

class UMaterialInterface;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			namespace NFlipbook
			{
				struct CSCORE_API FFrame
				{
				public:

					UMaterialInterface* Material;
					UMaterialInterface** Material_Emu;

					int32 Index;
					int32* Index_Emu;

					FFrame() :
						Material(nullptr),
						Material_Emu(nullptr),
						Index(NAME_None),
						Index_Emu(nullptr)
					{
						Material_Emu = &Material;
						Index_Emu = &Index;
					}

					FORCEINLINE FFrame& operator=(const FFrame& B)
					{
						Material = B.Material;
						Index = B.Index;
						return *this;
					}

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_EMU(Material, UMaterialInterface)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Index, int32)

					bool IsValidChecked(const FString& Context) const;
				};
			}
		}
	}
}

#pragma endregion FCsAnim2DMaterialFlipbookFrame

// FCsAnim2DMaterialFlipbook
#pragma region

// NCsAnim::N2D::NMaterial::NFlipbook::FFlipbook
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsAnim, N2D, NMaterial, NFlipbook, FFlipbook)

/**
* Describes a 2D Animation "flipbook" made up of Materials.
* The materials are meant to swapped on a StaticMesh or SkeletalMesh.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAnim2DMaterialFlipbook
{
	GENERATED_USTRUCT_BODY()

	/** Describes how the Frames will be played. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAnim2DPlayback Playback;

	/** Describes the time between each Frame. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAnim2DPlayRate PlayRate;

	/** Time between each Frame.
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomDeltaTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeltaTime;

	/** Total time to play all Frames. The time between each Frame will be
		TotalTime / Number of Frames. 
		Only Valid if PlayRate == ECsAnim2DPlayRate::CustomTotalTime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TotalTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCsAnim2DMaterialFlipbookFrame> Frames;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCount;

	FCsAnim2DMaterialFlipbook() :
		Playback(ECsAnim2DPlayback::Forward),
		PlayRate(ECsAnim2DPlayRate::PR_60Fps),
		DeltaTime(0.0f),
		TotalTime(0.0f),
		Frames(),
		TotalCount(0)
	{
	}

	FORCEINLINE bool IsLooping() const
	{
		return Playback == ECsAnim2DPlayback::Loop ||
			   Playback == ECsAnim2DPlayback::LoopReverse ||
			   Playback == ECsAnim2DPlayback::LoopPingPong;
	}

	FORCEINLINE bool IsLoopingForever() const { return IsLooping() && TotalTime == 0.0f; }

#define FlipbookType NCsAnim::N2D::NMaterial::NFlipbook::FFlipbook
	void CopyFlipbook(FlipbookType* Flipbook);
#undef FlipbookType

	void OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName);
};

namespace NCsAnim
{
	namespace N2D
	{
		namespace NMaterial
		{
			namespace NFlipbook
			{
				struct CSCORE_API FFlipbook
				{
				#define PlaybackType NCsAnim::N2D::EPlayback
				#define PlayRateType NCsAnim::N2D::EPlayRate
				#define FrameType NCsAnim::N2D::NMaterial::NFlipbook::FFrame

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

					int32 TotalCount;
					int32* TotalCount_Emu;

					FFlipbook() :
						Playback(PlaybackType::Forward),
						Playback_Emu(nullptr),
						PlayRate(PlayRateType::PR_60Fps),
						PlayRate_Emu(nullptr),
						DeltaTime(0.0f),
						DeltaTime_Emu(nullptr),
						TotalTime(0.0f),
						TotalTime_Emu(nullptr),
						TotalCount(0),
						TotalCount_Emu(nullptr)
					{
						Playback_Emu = &Playback;
						PlayRate_Emu = &PlayRate;
						DeltaTime_Emu = &DeltaTime;
						TotalTime_Emu = &TotalTime;
						TotalCount_Emu = &TotalCount;
					}

					FORCEINLINE FFlipbook& operator=(const FFlipbook& B)
					{
						Playback = B.GetPlayback();
						SetPlayback(&Playback);
						PlayRate = B.GetPlayRate();
						SetPlayRate(&PlayRate);
						DeltaTime = B.GetDeltaTime();
						SetDeltaTime(&DeltaTime);
						TotalTime = B.GetTotalTime();
						SetTotalTime(&TotalTime);

						Frames.Reset(FMath::Max(Frames.Max(), B.Frames.Max()));

						for (const FrameType& F : B.Frames)
						{
							Frames.Add(F);
						}

						TotalCount = B.GetTotalCount();
						SetTotalCount(&TotalCount);
						return *this;
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Playback, PlaybackType)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(PlayRate, PlayRateType)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(DeltaTime, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalTime, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalCount, int32)

					FORCEINLINE bool IsLooping() const
					{
						return GetPlayback() == EPlayback::Loop ||
							   GetPlayback() == EPlayback::LoopReverse ||
							   GetPlayback() == EPlayback::LoopPingPong;
					}

					FORCEINLINE bool IsLoopingForever() const { return IsLooping() && GetTotalTime() == 0.0f; }

					FORCEINLINE bool ShouldStartReverse() const
					{
						return GetPlayback() == EPlayback::Reverse ||
							   GetPlayback() == EPlayback::LoopReverse;
					}

					bool IsValidChecked(const FString& Context) const;

					void Reset()
					{
						Playback = PlaybackType::Forward;
						SetPlayback(&Playback);
						PlayRate = PlayRateType::PR_60Fps;
						SetPlayRate(&PlayRate);
						DeltaTime = 0.0f;
						SetDeltaTime(&DeltaTime);
						TotalTime = 0.0f;
						SetTotalTime(&TotalTime);

						Frames.Reset(Frames.Max());

						TotalCount = 0;
						SetTotalCount(&TotalCount);
					}

				#undef PlaybackType
				#undef PlayRateType
				#undef FrameType
				};
			}
		}
	}
}
#pragma endregion FCsAnim2DMaterialFlipbook