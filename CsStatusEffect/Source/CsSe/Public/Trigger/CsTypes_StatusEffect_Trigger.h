// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Types/CsTypes_Macro.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsSeLog.h"

#include "CsTypes_StatusEffect_Trigger.generated.h"

// StatusEffectTriggerCondition
#pragma region

/**
* How the status effect will get triggered.
*/
USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectTriggerCondition : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectTriggerCondition)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectTriggerCondition)

struct CSSE_API EMCsStatusEffectTriggerCondition : public TCsEnumStructMap<FECsStatusEffectTriggerCondition, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition, uint8)
};

namespace NCsStatusEffectTriggerCondition
{
	typedef FECsStatusEffectTriggerCondition Type;
	typedef EMCsStatusEffectTriggerCondition EnumMapType;

	extern CSSE_API const Type OnParentTrigger;
	extern CSSE_API const Type OnHit;
}

#pragma endregion StatusEffectTriggerCondition

// StatusEffectTriggerFrequency
#pragma region

/**
* The frequency the Status Effect will occur once triggered.
*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
*/
UENUM(BlueprintType)
enum class ECsStatusEffectTriggerFrequency : uint8
{
	Once								 UMETA(DisplayName = "Once"),
	Count								 UMETA(DisplayName = "Count"),
	Time								 UMETA(DisplayName = "Time"),
	Infinite							 UMETA(DisplayName = "Infinite"),
	ECsStatusEffectTriggerFrequency_MAX  UMETA(Hidden),
};

struct CSSE_API EMCsStatusEffectTriggerFrequency : public TCsEnumMap<ECsStatusEffectTriggerFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStatusEffectTriggerFrequency, ECsStatusEffectTriggerFrequency)
};

namespace NCsStatusEffectTriggerFrequency
{
	typedef ECsStatusEffectTriggerFrequency Type;

	namespace Ref
	{
		extern CSSE_API const Type Once;
		extern CSSE_API const Type Count;
		extern CSSE_API const Type Time;
		extern CSSE_API const Type Infinite;
		extern CSSE_API const Type ECsStatusEffectTriggerFrequency_MAX;
	}

	extern CSSE_API const uint8 MAX;
}

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		/**
		* The frequency the Status Effect will occur once triggered.
		*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
		*/
		enum class EFrequency : uint8
		{
			Once,
			Count,
			Time,
			Infinite,
			EFrequency_MAX
		};

		struct CSSE_API EMFrequency : public TCsEnumMap<EFrequency>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
		};

		namespace NFrequency
		{
			typedef EFrequency Type;

			namespace Ref
			{
				extern CSSE_API const Type Once;
				extern CSSE_API const Type Count;
				extern CSSE_API const Type Time;
				extern CSSE_API const Type Infinite;
				extern CSSE_API const Type EFrequency_MAX;
			}
		}
	}
}

#pragma endregion StatusEffectTriggerFrequency

// FCsStatusEffect_TriggerFrequencyParams
#pragma region

// NCsStatusEffect::NTrigger::NFrequency::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStatusEffect, NTrigger, NFrequency, FParams)

/**
* Parameters describing the trigger frequency of a Status Effect.
*  Status Effect is an object that implements the interface: NCsStatusEffect::IStatusEffect
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsStatusEffect_TriggerFrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Trigger Frequency
		If Type == ECsStatusEffectTriggerFrequency::Once,
	     Ignore Count and Interval.
		If Type == ECsStatusEffectTriggerFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsStatusEffectTriggerFrequency::Once.
		if Type == ECsStatusEffectTriggerFrequency::Time, 
		If Type == ECsStatusEffectTriggerFrequency::Infinite,
	     Ignore Count and Interval should be > 0.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsStatusEffectTriggerFrequency Type;

	/** The delay before applying the status effect when triggered.
		If Delay == 0.0f, the status effect will be applied at a given interval.
		If Delay == 0.0f and Interval == 0.0f, the status will be applied immediately. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** The number of times to apply the status effect when triggered.
		Only valid if Type == ECsStatusEffectTriggerFrequency::Count.
		Should be > 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each status effect being applied when triggered.
		Only valid if,
		Type == ECsStatusEffectTriggerFrequency::Count
		 or
		Type == ECsStatusEffectTriggerFrequency::Infinite */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsStatusEffect_TriggerFrequencyParams() :
		Type(ECsStatusEffectTriggerFrequency::Once),
		Delay(0.0f),
		Count(0),
		Interval(0.0f),
		Time(0.0f)
	{
	}

#define ParamsType NCsStatusEffect::NTrigger::NFrequency::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;
};
 
namespace NCsStatusEffect
{
	namespace NTrigger
	{
		namespace NFrequency
		{
			struct CSSE_API FParams
			{
			#define FrequencyType NCsStatusEffect::NTrigger::EFrequency

			private:

				/** Trigger Frequency
					If Type == EFrequency::Once,
					 Ignore Count and Interval.
					If Type == EFrequency::Count,
					 Count should be > 0, if NOT, it will be treated
					 as EFrequency::Once.
					if Type == EFrequency::Time, 
					If Type == EFrequency::Infinite,
					 Ignore Count and Interval should be > 0.0f. */
				CS_DECLARE_MEMBER_WITH_PROXY(Type, FrequencyType)

				/** The delay before applying the status effect when triggered.
					If Delay == 0.0f, the status effect will be applied at a given interval.
					If Delay == 0.0f and Interval == 0.0f, the status will be applied immediately. */
				CS_DECLARE_MEMBER_WITH_PROXY(Delay, float)

				/** The number of times to apply the status effect when triggered.
					Only valid if Type == EFrequency::Count.
					Should be > 0. */
				CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)

				/** The time between each status effect being applied when triggered.
					Only valid if,
					Type == EFrequency::Count
					 or
					Type == EFrequency::Infinite */
				CS_DECLARE_MEMBER_WITH_PROXY(Interval, float)

				CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, FrequencyType::Once),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Delay, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Interval, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Delay);
					CS_CTOR_SET_MEMBER_PROXY(Count);
					CS_CTOR_SET_MEMBER_PROXY(Interval);
					CS_CTOR_SET_MEMBER_PROXY(Time);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FrequencyType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Delay, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;

			#undef FrequencyType
			};
		}
	}
}

#pragma endregion FCsStatusEffect_TriggerFrequencyParams

// StatusEffectTransferFrequency
#pragma region

UENUM(BlueprintType)
enum class ECsStatusEffectTransferFrequency : uint8
{
	None								 UMETA(DisplayName = "None"),
	Once								 UMETA(DisplayName = "Once"),
	Count								 UMETA(DisplayName = "Count"),
	Time								 UMETA(DisplayName = "Time"),
	Infinite							 UMETA(DisplayName = "Infinite"),
	ECsStatusEffectTransferFrequency_MAX  UMETA(Hidden),
};

struct CSSE_API EMCsStatusEffectTransferFrequency : public TCsEnumMap<ECsStatusEffectTransferFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStatusEffectTransferFrequency, ECsStatusEffectTransferFrequency)
};

namespace NCsStatusEffectTransferFrequency
{
	typedef ECsStatusEffectTransferFrequency Type;

	namespace Ref
	{
		extern CSSE_API const Type None;
		extern CSSE_API const Type Once;
		extern CSSE_API const Type Count;
		extern CSSE_API const Type Time;
		extern CSSE_API const Type Infinite;
		extern CSSE_API const Type ECsStatusEffectTransferFrequency_MAX;
	}

	extern CSSE_API const uint8 MAX;
}

namespace NCsStatusEffect
{
	namespace NTransfer
	{
		enum class EFrequency : uint8
		{
			None,
			Once,
			Count,
			Time,
			Infinite,
			EFrequency_MAX
		};

		struct CSSE_API EMFrequency : public TCsEnumMap<EFrequency>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
		};

		namespace NFrequency
		{
			typedef EFrequency Type;

			namespace Ref
			{
				extern CSSE_API const Type None;
				extern CSSE_API const Type Once;
				extern CSSE_API const Type Count;
				extern CSSE_API const Type Time;
				extern CSSE_API const Type Infinite;
				extern CSSE_API const Type EFrequency_MAX;
			}
		}
	}
}

#pragma endregion StatusEffectTransferFrequency

// FCsStatusEffect_TransferFrequencyParams
#pragma region

// NCsStatusEffect::NTransfer::NFrequency::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStatusEffect, NTransfer, NFrequency, FParams)

/**
* Parameters describing the transfer frequency.
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsStatusEffect_TransferFrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsStatusEffectTransferFrequency Type;

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsStatusEffect_TransferFrequencyParams() :
		Type(ECsStatusEffectTransferFrequency::Once),
		Count(0),
		Time(0.0f)
	{
	}

#define ParamsType NCsStatusEffect::NTransfer::NFrequency::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;
};
 
namespace NCsStatusEffect
{
	namespace NTransfer
	{
		namespace NFrequency
		{
			/**
			* Parameters describing the transfer frequency.
			*/
			struct CSSE_API FParams
			{
			#define FrequencyType NCsStatusEffect::NTransfer::EFrequency

			private:

				/** */
				CS_DECLARE_MEMBER_WITH_PROXY(Type, FrequencyType)

				/** */
				CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)

				/** */
				CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

			public:

				FParams() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, FrequencyType::Once),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Time, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Count);
					CS_CTOR_SET_MEMBER_PROXY(Time);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FrequencyType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;

			#undef FrequencyType
			};
		}
	}
}

#pragma endregion FCsStatusEffect_TransferFrequencyParams