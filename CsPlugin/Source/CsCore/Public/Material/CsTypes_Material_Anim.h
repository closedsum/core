// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Interpolation.h"
#include "Animation/CsAnimPlayRate.h"
#include "Animation/CsAnimPlayback.h"
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

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)
				CS_DECLARE_MEMBER_WITH_PROXY(Easing, ECsEasingType)

			protected:

				CS_DECLARE_MEMBER_WITH_PROXY(From, ValueType)
				CS_DECLARE_MEMBER_WITH_PROXY(To, ValueType)

			public:

				TValueType() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear),
					From_Proxy(nullptr),
					To_Proxy(nullptr)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Easing);
					CS_CTOR_SET_MEMBER_PROXY(From);
					CS_CTOR_SET_MEMBER_PROXY(To);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Easing, ECsEasingType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(From, ValueType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(To, ValueType)

				CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(Name)
				CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(Easing)
				CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(From)
				CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(To)

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					return true;
				}

				FORCEINLINE bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
				{
					if (GetName() == NAME_None)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: GetName(): None is NOT Valid."), *Context));
						return false;
					}
					return true;
				}

				FORCEINLINE bool AreProxyPtrsDefaultChecked(const FString& Context) const
				{
					CS_IS_PROXY_PTR_DEFAULT_CHECKED(Name);
					CS_IS_PROXY_PTR_DEFAULT_CHECKED(Easing);
					CS_IS_PROXY_PTR_DEFAULT_CHECKED(From);
					CS_IS_PROXY_PTR_DEFAULT_CHECKED(To);
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

			CS_DECLARE_MEMBER_WITH_PROXY(Duration, float)

		public:

			TArray<VectorType> VectorParameters;

			TArray<ScalarType> ScalarParameters;

		public:

			FFrame() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Duration, 0.0f),
				VectorParameters(),
				ScalarParameters()
			{
				CS_CTOR_SET_MEMBER_PROXY(Duration);
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

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Duration, float)

			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(Duration)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			bool IsValidChecked(const FString& Context, UMaterialInstanceDynamic* MID) const;
			bool IsValid(const FString& Context, UMaterialInstanceDynamic* MID, void(*Log)(const FString&) = &FCsLog::Warning) const;

			FORCEINLINE bool AreProxyPtrsDefaultChecked(const FString& Context) const
			{
				CS_IS_PROXY_PTR_DEFAULT_CHECKED(Duration);

				for (const VectorType& Param : VectorParameters)
				{
					check(Param.AreProxyPtrsDefaultChecked(Context));
				}

				for (const ScalarType& Param : ScalarParameters)
				{
					check(Param.AreProxyPtrsDefaultChecked(Context));
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
			CS_DECLARE_MEMBER_WITH_PROXY(Playback, PlaybackType)

			/** Describes the time between each Frame. */
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, PlayRateType)

			/** Time between each Frame.
				Only Valid if:
				 PlayRate == ECsAnimPlayRate::CustomDeltaTime.
				if PlayRate == EcsAnimPlayRate::Custon,
				 this value is ignored. */
			CS_DECLARE_MEMBER_WITH_PROXY(DeltaTime, float)

			/** Total time to play all Frames.
				If PlayRate == ECsAnimPlayRate::CustomTotalTime:
				 The time between each Frame will be
				 TotalTime / Number of Frames.
				If PlayRate == ECsAnimPlayRate::Custom:
				 Total = Sum of Duration of each Frame (Frame[Index].Duration). */
			CS_DECLARE_MEMBER_WITH_PROXY(TotalTime, float)

		public:

			TArray<FrameType> Frames;

		private:

			CS_DECLARE_MEMBER_WITH_PROXY(TotalCount, int32)

		public:

			FAnim()	:
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Playback, PlaybackType::Forward),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, PlayRateType::PR_60Fps),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(DeltaTime, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TotalTime, 0.0f),
				Frames(),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TotalCount, 0)
			{
				CS_CTOR_SET_MEMBER_PROXY(Playback);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(DeltaTime);
				CS_CTOR_SET_MEMBER_PROXY(TotalTime);
				CS_CTOR_SET_MEMBER_PROXY(TotalCount);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Playback, PlaybackType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, PlayRateType)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(DeltaTime, float)

			FORCEINLINE const float& GetDeltaTime(const int32& Index) const
			{
				return GetDeltaTime();
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TotalTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TotalCount, int32)

			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(Playback)
			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(PlayRate)
			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(DeltaTime)
			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(TotalTime)
			CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(TotalCount)

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

			FORCEINLINE bool AreProxyPtrsDefaultChecked(const FString& Context) const
			{
				CS_IS_PROXY_PTR_DEFAULT_CHECKED(Playback);
				CS_IS_PROXY_PTR_DEFAULT_CHECKED(PlayRate);
				CS_IS_PROXY_PTR_DEFAULT_CHECKED(DeltaTime);
				CS_IS_PROXY_PTR_DEFAULT_CHECKED(TotalTime);

				for (const FrameType& Frame : Frames)
				{
					check(Frame.AreProxyPtrsDefaultChecked(Context));
				}

				CS_IS_PROXY_PTR_DEFAULT_CHECKED(TotalCount);
				return true;
			}

			void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Playback, PlaybackType::Forward)
				CS_RESET_MEMBER_WITH_PROXY(PlayRate, PlayRateType::PR_60Fps)
				CS_RESET_MEMBER_WITH_PROXY(DeltaTime, 0.0f)
				CS_RESET_MEMBER_WITH_PROXY(TotalTime, 0.0f)
				// TODO: Since there are arrays contained in each Frame, look into handling this better in the future.
				Frames.Reset(Frames.Max());

				CS_RESET_MEMBER_WITH_PROXY(TotalCount, 0)
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
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* MID;

	UPROPERTY(BlueprintReadWrite)
	UObject* MIDAsObject;

	/** Owner of the Animation */
	UPROPERTY(BlueprintReadWrite)
	UObject* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsUpdateGroup Group;

	FCsMaterialAnim_Params() :
		Anim(),
		MID(nullptr),
		MIDAsObject(nullptr),
		Owner(nullptr),
		Group()
	{
	}

	void ConditionalSetSafeMID(const FString& Context);

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

				CS_DECLARE_MEMBER_WITH_PROXY(Group, FECsUpdateGroup)

				// TODO: Add Abort and End Callbacks

			public:
			
				FParams() :
					Anim(),
					MID(nullptr),
					Owner(nullptr),
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Group)
				{
					CS_CTOR_SET_MEMBER_PROXY(Group);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Group, FECsUpdateGroup)

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