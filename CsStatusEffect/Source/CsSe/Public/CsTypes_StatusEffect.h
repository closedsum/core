// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_StatusEffect.generated.h"
#pragma once

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
* The frequency the status effect will occur once triggered.
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

#pragma endregion StatusEffectTriggerFrequency

// FCsStatusEffectTriggerFrequencyParams
#pragma region

/**
* Parameters describing the trigger frequency.
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsStatusEffectTriggerFrequencyParams
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

	FCsStatusEffectTriggerFrequencyParams() :
		Type(ECsStatusEffectTriggerFrequency::Once),
		Delay(0.0f),
		Count(0),
		Interval(0.0f),
		Time(0.0f)
	{
	}
};
 
#pragma endregion FCsStatusEffectTriggerFrequencyParams

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


#pragma endregion StatusEffectTransferFrequency

// FCsStatusEffectTransferFrequencyParams
#pragma region

/**
* Parameters describing the transfer frequency.
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsStatusEffectTransferFrequencyParams
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

	FCsStatusEffectTransferFrequencyParams() :
		Type(ECsStatusEffectTransferFrequency::Once),
		Count(0),
		Time(0.0f)
	{
	}
};
 
#pragma endregion FCsStatusEffectTriggerFrequencyParams

namespace NCsStatusEffect
{
	namespace NTrigger
	{
		// Frequency
		#pragma region

		/**
		* The frequency the status effect will occur once triggered.
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
				extern CSSE_API const Type None;
				extern CSSE_API const Type Once;
				extern CSSE_API const Type Count;
				extern CSSE_API const Type Time;
				extern CSSE_API const Type Infinite;
				extern CSSE_API const Type EFrequency_MAX;
			}

			extern CSSE_API const uint8 MAX;
		}

		#pragma endregion Frequency

		struct CSSE_API FFrequencyParams
		{
		public:

			/** Trigger Frequency
				If Type == EFrequency::Once,
				 Ignore Count and Interval.
				If Type == EFrequency::Count,
				 Count should be > 0, if NOT, it will be treated
				 as EFrequency::Once.
				if Type == EFrequency::Time, 
				If Type == EFrequency::Infinite,
				 Ignore Count and Interval should be > 0.0f. */
			EFrequency Type;

			/** The delay before applying the status effect when triggered.
				If Delay == 0.0f, the status effect will be applied at a given interval.
				If Delay == 0.0f and Interval == 0.0f, the status will be applied immediately. */
			float Delay;

			/** The number of times to apply the status effect when triggered.
				Only valid if Type == EFrequency::Count.
				Should be > 0. */
			int32 Count;

			/** The time between each status effect being applied when triggered.
				Only valid if,
				Type == EFrequency::Count
				 or
				Type == EFrequency::Infinite */
			float Interval;

			float Time;

			FFrequencyParams() :
				Type(EFrequency::Once),
				Delay(0.0f),
				Count(0),
				Interval(0.0f),
				Time(0.0f)
			{
			}
		};
	}

	namespace NTransfer
	{
		// Frequency
		#pragma region

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

			extern CSSE_API const uint8 MAX;
		}

		#pragma endregion Frequency

		/**
		* Parameters describing the transfer frequency.
		*/
		struct CSSE_API FFrequencyParams
		{
		public:

			/** */
			EFrequency Type;

			/** */
			int32 Count;

			/** */
			float Time;

			FFrequencyParams() :
				Type(EFrequency::Once),
				Count(0),
				Time(0.0f)
			{
			}
		};
	}
}

// StatusEffectEvent
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FECsStatusEffectEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStatusEffectEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStatusEffectEvent)

struct CSSE_API EMCsStatusEffectEvent : public TCsEnumStructMap<FECsStatusEffectEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStatusEffectEvent, FECsStatusEffectEvent, uint8)
};

namespace NCsStatusEffectEvent
{
	typedef FECsStatusEffectEvent Type;
	typedef EMCsStatusEffectEvent EnumMapType;

	extern CSSE_API const Type Default;
	extern CSSE_API const Type Damage;
}

#pragma endregion StatusEffectEvent

// FCsData_StatusEffectPtr
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSSE_API FCsData_StatusEffectPtr
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "CsData_StatusEffect"))
	TSoftClassPtr<UObject> Data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly)
	UObject* Data_Internal;

	UPROPERTY(Transient, BlueprintReadOnly)
	UClass* Data_Class;

	FCsData_StatusEffectPtr() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr),
		Data_Class(nullptr)
	{
	}

	FORCEINLINE UObject* Get() const { return Data_Internal; }

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE UObject* GetChecked(const FString& Context) const
	{
		checkf(Data_Internal, TEXT("%s: Data_Internal is NULL."), *Context);

		return Data_Internal;
	}

	template<typename T>
	FORCEINLINE T* GetChecked(const FString& Context) const
	{
		return Cast<T>(GetChecked(Context));
	}

	FORCEINLINE UClass* GetClass() const { return Data_Class; }
};

#pragma endregion FCsData_StatusEffectPtr