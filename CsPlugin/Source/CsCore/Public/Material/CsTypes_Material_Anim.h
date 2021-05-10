// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Interpolation.h"
#include "Animation/CsTypes_Anim_PlayRate.h"
#include "Animation/CsTypes_Anim_Playback.h"
#include "Managers/Time/CsTypes_Update.h"
// Log
#include "Utility/CsLog.h"
// Library
#include "Library/CsLibrary_Array.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsTypes_Material_Anim.generated.h"
#pragma once

// FCsMaterialAnimParameterVector
#pragma region

// NCsMaterial::NAnim::NParameter::FVectorType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NAnim, NParameter, FVectorType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialAnimParameterVector
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsEasingType Easing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor To;

	FCsMaterialAnimParameterVector() :
		Name(NAME_None),
		Easing(ECsEasingType::Linear),
		From(0.0f, 0.0f, 0.0f, 0.0f),
		To(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

#define ValueType NCsMaterial::NAnim::NParameter::FVectorType
	void CopyToValue(ValueType* Value);
	void CopyToValueAsValue(ValueType* Value) const;
#undef ValueType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsMaterialAnimParameterVector

// FCsMaterialAnimParameterScalar
#pragma region

// NCsMaterial::NAnim::NParameter::FScalarType
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NAnim, NParameter, FScalarType)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialAnimParameterScalar
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsEasingType Easing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float To;

	FCsMaterialAnimParameterScalar() :
		Name(NAME_None),
		Easing(ECsEasingType::Linear),
		From(0.0f),
		To(0.0f)
	{
	}

#define ValueType NCsMaterial::NAnim::NParameter::FScalarType
	void CopyToValue(ValueType* Value);
	void CopyToValueAsValue(ValueType* Value) const;
#undef ValueType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsMaterialAnimParameterScalar

class UMaterialInstanceDynamic;

namespace NCsMaterial
{
	namespace NAnim
	{
		namespace NParameter
		{
			template<typename ValueType>
			struct CSCORE_API TValueType
			{
			private:

				FName Name;
				FName* Name_Emu;

				ECsEasingType Easing;
				ECsEasingType* Easing_Emu;

			protected:

				ValueType From;
				ValueType* From_Emu;

				ValueType To;
				ValueType* To_Emu;

			public:

				TValueType() :
					Name(NAME_None),
					Name_Emu(nullptr),
					Easing(ECsEasingType::Linear),
					Easing_Emu(nullptr),
					From_Emu(nullptr),
					To_Emu(nullptr)
				{
					Name_Emu = &Name;
					Easing_Emu = &Easing;
					From_Emu = &From;
					To_Emu = &To;
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Easing, ECsEasingType)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(From, ValueType)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(To, ValueType)

				CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(Name)
				CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(Easing)
				CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(From)
				CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(To)

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					checkf(Name != NAME_None, TEXT("%s: Name: None is NOT Valid."), *Context);
					return true;
				}

				FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
				{
					if (Name == NAME_None)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
						return false;
					}
					return true;
				}

				FORCEINLINE bool AreEmuPtrsDefaultChecked(const FString& Context) const
				{
					CS_IS_EMU_PTR_DEFAULT_CHECKED(Name);
					CS_IS_EMU_PTR_DEFAULT_CHECKED(Easing);
					CS_IS_EMU_PTR_DEFAULT_CHECKED(From);
					CS_IS_EMU_PTR_DEFAULT_CHECKED(To);
					return true;
				}
			};

			struct CSCORE_API FVectorType final : TValueType<FLinearColor>
			{
			private:

				typedef TValueType<FLinearColor> Super;

			public:

				FVectorType() :
					Super()
				{
					From = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
					To = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
				}
			};

			struct CSCORE_API FScalarType final : TValueType<float>
			{
			private:

				typedef TValueType<float> Super;

			public:

				FScalarType() :
					Super()
				{
					From = 0.0f;
					To = 0.0f;
				}
			};
		}
	}
}

// FCsMaterialAnimFrame
#pragma region

// NCsMaterial::NAnim::FFrame
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsMaterial, NAnim, FFrame)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialAnimFrame
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsMaterialAnimParameterVector> VectorParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsMaterialAnimParameterScalar> ScalarParameters;

	FCsMaterialAnimFrame() :
		Duration(0.0f),
		VectorParameters(),
		ScalarParameters()
	{
	}

#define FrameType NCsMaterial::NAnim::FFrame
	void CopyToFrame(FrameType* Frame);
	void CopyToFrameAsValue(FrameType* Frame) const;
#undef FrameType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	bool IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class UMaterialInstanceDynamic;

namespace NCsMaterial
{
	namespace NAnim
	{
		struct CSCORE_API FFrame final
		{
		#define VectorType NCsMaterial::NAnim::NParameter::FVectorType
		#define ScalarType NCsMaterial::NAnim::NParameter::FScalarType

		private:

			float Duration;
			float* Duration_Emu;

		public:

			TArray<VectorType> VectorParameters;

			TArray<ScalarType> ScalarParameters;

		public:

			FFrame() :
				Duration(0.0f),
				Duration_Emu(nullptr),
				VectorParameters(),
				ScalarParameters()
			{
				Duration_Emu = &Duration;
			}

			FORCEINLINE FFrame& operator=(const FFrame& B)
			{
				Duration = B.GetDuration();
				SetDuration(&Duration);

				typedef NCsArray::FLibrary ArrayLibrary;

				ArrayLibrary::Copy<VectorType>(VectorParameters, B.VectorParameters);
				ArrayLibrary::Copy<ScalarType>(ScalarParameters, B.ScalarParameters);
				return *this;
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Duration, float)

			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(Duration)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			bool IsValidChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
			bool IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE bool AreEmuPtrsDefaultChecked(const FString& Context) const
			{
				CS_IS_EMU_PTR_DEFAULT_CHECKED(Duration);

				for (const VectorType& Param : VectorParameters)
				{
					check(Param.AreEmuPtrsDefaultChecked(Context));
				}

				for (const ScalarType& Param : ScalarParameters)
				{
					check(Param.AreEmuPtrsDefaultChecked(Context));
				}
				return true;
			}

		#undef VectorType
		#undef ScalarType
		};
	}
}

#pragma endregion FCsMaterialAnimFrame

// FCsMaterialAnim
#pragma region

// NCsMaterial::NAnim::FAnim

CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsMaterial, NAnim, FAnim)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialAnim
{
	GENERATED_USTRUCT_BODY()

	/** Describes how the Frames will be played. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsAnimPlayback Playback;

	/** Describes the time between each Frame. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsAnimPlayRate PlayRate;

	/** Time between each Frame.
		Only Valid if:
		 PlayRate == ECsAnimPlayRate::CustomDeltaTime. 
		if PlayRate == EcsAnimPlayRate::Custon, 
		 this value is ignored. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeltaTime;

	/** Total time to play all Frames. 
		If PlayRate == ECsAnimPlayRate::CustomTotalTime:
		 The time between each Frame will be
		 TotalTime / Number of Frames. 
		If PlayRate == ECsAnimPlayRate::Custom: 
		 Total = Sum of Duration of each Frame (Frame[Index].Duration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCsMaterialAnimFrame> Frames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCount;

	FCsMaterialAnim() :
		Playback(ECsAnimPlayback::Forward),
		PlayRate(ECsAnimPlayRate::PR_60Fps),
		DeltaTime(0.0f),
		TotalTime(0.0f),
		Frames(), 
		TotalCount(0)
	{
	}

	FORCEINLINE bool IsLooping() const
	{
		return Playback == ECsAnimPlayback::Loop ||
			   Playback == ECsAnimPlayback::LoopReverse ||
			   Playback == ECsAnimPlayback::LoopPingPong;
	}

	FORCEINLINE bool IsLoopingForever() const { return IsLooping() && TotalTime == 0.0f; }

#define AnimType NCsMaterial::NAnim::FAnim
	void CopyToAnim(AnimType* Anim);
	void CopyToAnimAsValue(AnimType* Anim) const;
#undef AnimType

	void UpdateFromPlaybackAndPlayRate();

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	bool IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

class UMaterialInstanceDynamic;

namespace NCsMaterial
{
	namespace NAnim
	{
		struct CSCORE_API FAnim final
		{
		#define PlaybackType NCsAnim::EPlayback
		#define PlayRateType NCsAnim::EPlayRate
		#define FrameType NCsMaterial::NAnim::FFrame

		private:

			/** Describes how the Frames will be played. */
			PlaybackType Playback;
			PlaybackType* Playback_Emu;

			/** Describes the time between each Frame. */
			PlayRateType PlayRate;
			PlayRateType* PlayRate_Emu;

			/** Time between each Frame.
				Only Valid if:
				 PlayRate == ECsAnimPlayRate::CustomDeltaTime.
				if PlayRate == EcsAnimPlayRate::Custon,
				 this value is ignored. */
			float DeltaTime;
			float* DeltaTime_Emu;

			/** Total time to play all Frames.
				If PlayRate == ECsAnimPlayRate::CustomTotalTime:
				 The time between each Frame will be
				 TotalTime / Number of Frames.
				If PlayRate == ECsAnimPlayRate::Custom:
				 Total = Sum of Duration of each Frame (Frame[Index].Duration). */
			float TotalTime;
			float* TotalTime_Emu;

		public:

			TArray<FrameType> Frames;

		private:

			int32 TotalCount;
			int32* TotalCount_Emu;

		public:

			FAnim()	:
				Playback(PlaybackType::Forward),
				Playback_Emu(nullptr),
				PlayRate(PlayRateType::PR_60Fps),
				PlayRate_Emu(nullptr),
				DeltaTime(0.0f),
				DeltaTime_Emu(nullptr),
				TotalTime(0.0f),
				TotalTime_Emu(nullptr),
				Frames(),
				TotalCount(0),
				TotalCount_Emu(nullptr)
			{
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Playback, PlaybackType)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(PlayRate, PlayRateType)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(DeltaTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TotalCount, int32)

			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(Playback)
			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(PlayRate)
			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(DeltaTime)
			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(TotalTime)
			CS_DEFINE_IS_EMU_PTR_DEFAULT_CHECKED(TotalCount)

			FORCEINLINE bool IsLooping() const
			{
				return Playback == PlaybackType::Loop ||
					   Playback == PlaybackType::LoopReverse ||
					   Playback == PlaybackType::LoopPingPong;
			}

			FORCEINLINE bool IsLoopingForever() const { return IsLooping() && TotalTime == 0.0f; }

			FORCEINLINE bool ShouldStartReverse() const
			{
				return GetPlayback() == PlaybackType::Reverse ||
					   GetPlayback() == PlaybackType::LoopReverse;
			}

			void UpdateFromPlaybackAndPlayRateChecked(const FString& Context);

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			bool IsValidChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
			bool IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE bool AreEmuPtrsDefaultChecked(const FString& Context) const
			{
				CS_IS_EMU_PTR_DEFAULT_CHECKED(Playback);
				CS_IS_EMU_PTR_DEFAULT_CHECKED(PlayRate);
				CS_IS_EMU_PTR_DEFAULT_CHECKED(DeltaTime);
				CS_IS_EMU_PTR_DEFAULT_CHECKED(TotalTime);

				for (const FrameType& Frame : Frames)
				{
					check(Frame.AreEmuPtrsDefaultChecked(Context));
				}

				CS_IS_EMU_PTR_DEFAULT_CHECKED(TotalCount);
				return true;
			}

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
				// TODO: Since there are arrays contained in each Frame, look into handling this better in the future.
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

#pragma endregion FCsMaterialAnim

// FCsMaterialAnim_Params
#pragma region

class UMaterialInstanceDynamic;

// NCsMaterial::NAnim::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsMaterial, NAnim, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsMaterialAnim_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsMaterialAnim Anim;

	/** Material to perform the animation on. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* MID;

	/** Owner of the Animation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsUpdateGroup Group;

	FCsMaterialAnim_Params() :
		Anim(),
		MID(nullptr),
		Owner(nullptr),
		Group()
	{
	}

#define ParamsType NCsMaterial::NAnim::NParams::FParams
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsMaterial
{
	namespace NAnim
	{
		namespace NParams
		{
			struct CSCORE_API FParams final
			{
			#define AnimType NCsMaterial::NAnim::FAnim

			public:

				AnimType Anim;

			private:

				TWeakObjectPtr<UMaterialInstanceDynamic> MID;

				TWeakObjectPtr<UObject> Owner;

				FECsUpdateGroup Group;
				FECsUpdateGroup* Group_Emu;

				// TODO: Add Abort and End Callbacks

			public:
			
				FParams() :
					Anim(),
					MID(nullptr),
					Owner(nullptr),
					Group(),
					Group_Emu(nullptr)
				{
					Group_Emu = &Group;
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Group, FECsUpdateGroup)

				void SetMID(UMaterialInstanceDynamic* Value);
				UMaterialInstanceDynamic* GetMID() const;
				FORCEINLINE UMaterialInstanceDynamic* GetMIDChecked(const FString& Context) const 
				{
					UMaterialInstanceDynamic* Value = GetMID();

					checkf(Value, TEXT("%s: MID is NULL."), *Context);

					return Value;
				}

				FORCEINLINE void SetOwner(UObject* Value) { Owner = Value; }
				UObject* GetOwner() const;

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				void Reset();

			#undef AnimType
			};

			struct CSCORE_API FResource : public TCsResourceContainer<FParams>
			{
			};

			#define CS_PARAMS_PAYLOAD_SIZE 64

			struct CSCORE_API FManager : public TCsManager_ResourceValueType_Fixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};

			#undef CS_PARAMS_PAYLOAD_SIZE
		}
	}
}

#pragma endregion FCsMaterialAnim_Params