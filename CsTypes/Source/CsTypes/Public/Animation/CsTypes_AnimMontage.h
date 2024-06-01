// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Types/Enum/CsEnumMap.h"
#include "AlphaBlend.h"
// Log
#include "Utility/CsTypesLog.h"

#include "CsTypes_AnimMontage.generated.h"

// FCsAnimMontage_PlayParams
#pragma region

class UAnimMontage;

// NCsAnimMontage::NPlay::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnimMontage, NPlay, FParams)

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontage_PlayParams
{
	GENERATED_USTRUCT_BODY()

	/** The AnimMontage to Play. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	UAnimMontage* Anim;

	/** Whether it is okay to Play over an existing (i.e. SAME) animatiom that is playing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	bool bPlayOverExisting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (ScriptName = "m_bBlendIn", InlineEditConditionToggle))
	bool bBlendIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (ScriptName = "m_BlendIn", EditCondition = "bBlendIn"))
	FAlphaBlendArgs BlendIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	float PlayRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float TimeToStartAt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	bool bStopAll;

public:

	FCsAnimMontage_PlayParams() :
		Anim(nullptr),
		bPlayOverExisting(true),
		bBlendIn(false),
		BlendIn(),
		PlayRate(1.0f),
		TimeToStartAt(0.0f),
		bStopAll(true)
	{
	}

#define ParamsType NCsAnimMontage::NPlay::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

class UAnimMontage;

namespace NCsAnimMontage
{
	namespace NPlay
	{
		struct CSTYPES_API FParams
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimMontage*)
			CS_DECLARE_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(bBlendIn, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(BlendIn, FAlphaBlendArgs)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DECLARE_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DECLARE_MEMBER_WITH_PROXY(bStopAll, bool)

		public:
		
			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bPlayOverExisting, true),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bBlendIn, false),
				CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(BlendIn),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeToStartAt, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bStopAll, false)
			{
				CS_CTOR_SET_MEMBER_PROXY(Anim);
				CS_CTOR_SET_MEMBER_PROXY(bPlayOverExisting);
				CS_CTOR_SET_MEMBER_PROXY(bBlendIn);
				CS_CTOR_SET_MEMBER_PROXY(BlendIn);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(TimeToStartAt);
				CS_CTOR_SET_MEMBER_PROXY(bStopAll);
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			FParams(FParams& B)
			{
				Copy(B);
			}

			void Copy(const FParams& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Anim);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bPlayOverExisting);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bBlendIn);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, BlendIn);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, PlayRate);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, TimeToStartAt);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bStopAll);
			}

			static FParams Make(const FCsAnimMontage_PlayParams& B)
			{
				FParams P;
				P.SetAnim(B.Anim);
				P.SetbPlayOverExisting(B.bPlayOverExisting);
				P.SetbBlendIn(B.bBlendIn);
				P.SetBlendIn(B.BlendIn);
				P.SetPlayRate(B.PlayRate);
				P.SetTimeToStartAt(B.TimeToStartAt);
				P.SetbStopAll(B.bStopAll);
				return P;
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimMontage)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			FORCEINLINE const bool& ShouldPlayOverExisting() const { return GetbPlayOverExisting(); }
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bBlendIn, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BlendIn, FAlphaBlendArgs)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bStopAll, bool)
			FORCEINLINE const bool& ShouldStopAll() const { return GetbStopAll(); }

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsAnimMontage_PlayParams

// FCsAnimMontage_PlayByPathParams
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontage_PlayByPathParams
{
	GENERATED_USTRUCT_BODY()

	/** Path to the AnimMontage to Play. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	FString Path;

	/** Whether it is okay to Play over an existing (i.e. SAME) animation that is playing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	bool bPlayOverExisting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (ScriptName = "m_bBlendIn", InlineEditConditionToggle))
	bool bBlendIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (ScriptName = "m_BlendIn", EditCondition = "bBlendIn"))
	FAlphaBlendArgs BlendIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	float PlayRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float TimeToStartAt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	bool bStopAll;

public:

	FCsAnimMontage_PlayByPathParams() :
		Path(),
		bPlayOverExisting(true),
		bBlendIn(false),
		BlendIn(),
		PlayRate(1.0f),
		TimeToStartAt(0.0f),
		bStopAll(true)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

#pragma endregion FCsAnimMontage_PlayByPathParams

// AnimMontageSetPosition
#pragma region

UENUM(BlueprintType)
enum class ECsAnimMontageSetPosition : uint8
{
	Time							UMETA(DisplayName = "Time"),
	Percent							UMETA(DisplayName = "Percent"),
	ECsAnimMontageSetPosition_MAX	UMETA(Hidden),
};

struct CSTYPES_API EMCsAnimMontageSetPosition : public TCsEnumMap<ECsAnimMontageSetPosition>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAnimMontageSetPosition, ECsAnimMontageSetPosition)
};

namespace NCsAnimMontageSetPosition
{
	typedef ECsAnimMontageSetPosition Type;

	namespace Ref
	{
		extern CSTYPES_API const Type Time;
		extern CSTYPES_API const Type Percent;
		extern CSTYPES_API const Type ECsAnimMontageSetPosition_MAX;
	}
}

namespace NCsAnimMontage
{
	enum class ESetPosition : uint8 
	{
		Time,
		Percent,
		ESetPosition_MAX
	};

	struct CSTYPES_API EMSetPosition : public TCsEnumMap<ESetPosition>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMSetPosition, ESetPosition)
	};

	namespace NSetPosition
	{
		namespace Ref
		{
			typedef ESetPosition Type;

			extern CSTYPES_API const Type Time;
			extern CSTYPES_API const Type Percent;
			extern CSTYPES_API const Type ESetPosition_MAX;
		}
	}
}

#pragma endregion AnimMontageSetPosition

// FCsAnimMontage_SetPositionParams
#pragma region

class UAnimMontage;

// NCsAnimMontage::NSetPosition::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsAnimMontage, NSetPosition, FParams)

USTRUCT(BlueprintType)
struct CSTYPES_API FCsAnimMontage_SetPositionParams
{
	GENERATED_USTRUCT_BODY()

	/** The AnimMontage to SetPosition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim")
	UAnimMontage* Anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (InlineEditConditionToggle))
	ECsAnimMontageSetPosition PositionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditConditionHides, EditCondition= "PositionType==ECsAnimMontageSetPosition::Time", UIMin = "0.0", ClampMin = "0.0"))
	float NewPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditConditionHides, EditCondition= "PositionType==ECsAnimMontageSetPosition::Percent", UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))
	float NewPositionAsPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (InlineEditConditionToggle))
	bool bPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditCondition = "bPlay"))
	bool bPause;

	/** Whether it is okay to Play over an existing (i.e. SAME) animation that is playing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditCondition = "bPlay"))
	bool bPlayOverExisting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditCondition = "bPlay"))
	float PlayRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditCondition = "bPlay", UIMin = "0.0", ClampMin = "0.0"))
	float TimeToStartAt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Anim", meta = (EditCondition = "bPlay"))
	bool bStopAll;

public:

	FCsAnimMontage_SetPositionParams() :
		Anim(nullptr),
		PositionType(ECsAnimMontageSetPosition::Time),
		NewPosition(0.0f),
		NewPositionAsPercent(0.0f),
		bPlay(false),
		bPause(false),
		bPlayOverExisting(true),
		PlayRate(1.0f),
		TimeToStartAt(0.0f),
		bStopAll(true)
	{
	}

#define ParamsType NCsAnimMontage::NSetPosition::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

class UAnimMontage;

namespace NCsAnimMontage
{
	namespace NSetPosition
	{
		struct CSTYPES_API FParams
		{
		private:

			/** The AnimMontage to SetPosition. */
			CS_DECLARE_MEMBER_WITH_PROXY(Anim, UAnimMontage*)
			CS_DECLARE_MEMBER_WITH_PROXY(PositionType, NCsAnimMontage::ESetPosition)
			CS_DECLARE_MEMBER_WITH_PROXY(NewPosition, float)
			CS_DECLARE_MEMBER_WITH_PROXY(NewPositionAsPercent, float)
			CS_DECLARE_MEMBER_WITH_PROXY(bPlay, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(bPause, bool)
			/** Whether it is okay to Play over an existing (i.e. SAME) animation that is playing. */
			CS_DECLARE_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			CS_DECLARE_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DECLARE_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DECLARE_MEMBER_WITH_PROXY(bStopAll, bool)

		public:
		
			FParams() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Anim, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PositionType, NCsAnimMontage::ESetPosition::Time),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(NewPosition, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(NewPositionAsPercent, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bPlay, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bPause, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bPlayOverExisting, true),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(PlayRate, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeToStartAt, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bStopAll, false)
			{
				CS_CTOR_SET_MEMBER_PROXY(Anim);
				CS_CTOR_SET_MEMBER_PROXY(PositionType);
				CS_CTOR_SET_MEMBER_PROXY(NewPosition);
				CS_CTOR_SET_MEMBER_PROXY(NewPositionAsPercent);
				CS_CTOR_SET_MEMBER_PROXY(bPlay);
				CS_CTOR_SET_MEMBER_PROXY(bPause);
				CS_CTOR_SET_MEMBER_PROXY(bPlayOverExisting);
				CS_CTOR_SET_MEMBER_PROXY(PlayRate);
				CS_CTOR_SET_MEMBER_PROXY(TimeToStartAt);
				CS_CTOR_SET_MEMBER_PROXY(bStopAll);
			}

			FParams(const FParams& B)
			{
				Copy(B);
			}

			FParams(FParams& B)
			{
				Copy(B);
			}

			void Copy(const FParams& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Anim);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, PositionType);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, NewPosition);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, NewPositionAsPercent);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bPlay);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bPause);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bPlayOverExisting);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, PlayRate);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, TimeToStartAt);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bStopAll);
			}

			static FParams Make(const FCsAnimMontage_SetPositionParams& B)
			{
				FParams P;
				P.SetAnim(B.Anim);
				P.SetPositionType((NCsAnimMontage::ESetPosition)B.PositionType);
				P.SetNewPosition(B.NewPosition);
				P.SetNewPositionAsPercent(B.NewPositionAsPercent);
				P.SetbPlay(B.bPlay);
				P.SetbPause(B.bPause);
				P.SetbPlayOverExisting(B.bPlayOverExisting);
				P.SetPlayRate(B.PlayRate);
				P.SetTimeToStartAt(B.TimeToStartAt);
				P.SetbStopAll(B.bStopAll);
				return P;
			}

		#define PlayParamsType NCsAnimMontage::NPlay::FParams
			static PlayParamsType MakePlayParams(const FParams& B)
			{
				PlayParamsType P;
				P.SetAnim(B.GetAnim());
				P.SetbPlayOverExisting(B.GetbPlayOverExisting());
				P.SetbBlendIn(true);
				FAlphaBlendArgs BlendIn;
				BlendIn.BlendTime = 0.0f;
				BlendIn.BlendOption = EAlphaBlendOption::Linear;
				P.SetBlendIn(BlendIn);
				P.SetPlayRate(B.GetPlayRate());
				P.SetTimeToStartAt(B.GetTimeToStartAt());
				P.SetbStopAll(B.GetbStopAll());
				return P;
			}
		#undef PlayParamsType

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Anim, UAnimMontage)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PositionType, NCsAnimMontage::ESetPosition)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(NewPosition, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(NewPositionAsPercent, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPlay, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPause, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPlayOverExisting, bool)
			FORCEINLINE const bool& ShouldPlayOverExisting() const { return GetbPlayOverExisting(); }
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(PlayRate, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeToStartAt, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bStopAll, bool)
			FORCEINLINE const bool& ShouldStopAll() const { return GetbStopAll(); }

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;

		#undef SetPositionType
		};
	}
}

#pragma endregion FCsAnimMontage_SetPositionParams