// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Interpolation.h"
// Anim
#include "Animation/Vertex/CsVertexAnimNotify.h"
// Log
#include "Utility/CsLog.h"

#include "CsVertexAnimInfo.generated.h"

// NCsAnim::NVertex::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnim, NVertex, FInfo)

USTRUCT(BlueprintType)
struct CSCORE_API FCsVertexAnimInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0", ClampMin = "0"))
	int32 NumFrames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0", ClampMin = "0"))
	int32 AnimStartGenerated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float SpeedGenerated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	bool bLooping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float PlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float BlendInTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float BlendOutTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim")
	TArray<FCsVertexAnimNotify> Notifies;

public:

	FCsVertexAnimInfo() :
		NumFrames(0),
		AnimStartGenerated(0),
		SpeedGenerated(0.0f),
		bLooping(false),
		Length(0.0f),
		PlayRate(0.0f),
		BlendInTime(0.0f),
		BlendOutTime(0.0f),
		Notifies()
	{
	}

#define InfoType NCsAnim::NVertex::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsAnim
{
	namespace NVertex
	{
		struct CSCORE_API FInfo
		{
		public:

			static const FInfo Invalid;

		private:

		#define NotifyType NCsAnim::NVertex::FNotify

			CS_DECLARE_MEMBER_WITH_PROXY(NumFrames, int32)
			CS_DECLARE_MEMBER_WITH_PROXY(AnimStartGenerated, int32)
			CS_DECLARE_MEMBER_WITH_PROXY(SpeedGenerated, float)
			CS_DECLARE_MEMBER_WITH_PROXY(bLooping, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(Length, float)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DECLARE_MEMBER_WITH_PROXY(BlendInTime, float)
			CS_DECLARE_MEMBER_WITH_PROXY(BlendOutTime, float)

		public:

			TArray<NotifyType> Notifies;

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(NumFrames, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AnimStartGenerated, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(SpeedGenerated, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bLooping, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Length, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(BlendInTime, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(BlendOutTime, 0.0f),
				Notifies()
			{
				CS_CTOR_SET_MEMBER_PROXY(NumFrames);
				CS_CTOR_SET_MEMBER_PROXY(AnimStartGenerated);
				CS_CTOR_SET_MEMBER_PROXY(SpeedGenerated);
				CS_CTOR_SET_MEMBER_PROXY(bLooping);
				CS_CTOR_SET_MEMBER_PROXY(Length);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(BlendInTime);
				CS_CTOR_SET_MEMBER_PROXY(BlendOutTime);
			}

			FInfo(const int32& InNumFrames, 
				  const int32& InAnimStartGenerated,
				  const float& InSpeedGenerated,
				  const bool& InLooping,
				  const float& InLength,
				  const float& InPlayRate,
				  const float& InBlendInTime,
				  const float& InBlendOutTime) :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(NumFrames, InNumFrames),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(AnimStartGenerated, InAnimStartGenerated),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(SpeedGenerated, InSpeedGenerated),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bLooping, InLooping),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Length, InLength),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, InPlayRate),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(BlendInTime, InBlendInTime),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(BlendOutTime, InBlendOutTime)
			{
				CS_CTOR_SET_MEMBER_PROXY(NumFrames);
				CS_CTOR_SET_MEMBER_PROXY(AnimStartGenerated);
				CS_CTOR_SET_MEMBER_PROXY(SpeedGenerated);
				CS_CTOR_SET_MEMBER_PROXY(bLooping);
				CS_CTOR_SET_MEMBER_PROXY(Length);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(BlendInTime);
				CS_CTOR_SET_MEMBER_PROXY(BlendOutTime);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(NumFrames, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AnimStartGenerated, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(SpeedGenerated, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bLooping, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Length, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BlendInTime, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BlendOutTime, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			/**
			* NOTE: This should be called when / if the Blend In is being carried out and
			*		for the duration of the Blend In.
			*/
			float GetAlpha_BlendIn(const float& ElapsedTime) const;

			FORCEINLINE bool CanStartBlendOut(const float& ElapsedTime) const { return GetBlendOutTime() > 0.0f && (GetLength() - ElapsedTime) <= GetBlendOutTime(); }

			/**
			* NOTE: This should be called when / if the Blend Out is being carried out and
			*		for the duration of the Blend Out.
			*/
			float GetAlpha_BlendOut(const float& ElapsedTime) const;

		#undef NotifyType
		};
	}
}