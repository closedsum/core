// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_SpawnerParams.generated.h"
#pragma once

// FCsSpawnerCountParams
#pragma region

// NCsSpawner::NParams::FCount
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FCount)

/**
* Parameters describing number (count) of objects "created" when Spawn is called.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerCountParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of objects to "create" per Spawn call. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", UIMin = "1"))
	int32 CountPerSpawn;

	/** The amount of time between "creating" each object (if CountPerSpawn > 1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeBetweenCountPerSpawn;

	FCsSpawnerCountParams() :
		CountPerSpawn(1),
		TimeBetweenCountPerSpawn(0.0f)
	{
	}

#define ParamsType NCsSpawner::NParams::FCount
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsSpawner
{
	namespace NParams
	{
		/**
		* Parameters describing number (count) of objects "created" when Spawn is called.
		*/
		struct CSCORE_API FCount
		{
		private:

			/** The number of objects to "create" per Spawn call. */
			CS_DECLARE_MEMBER_WITH_EMU(CountPerSpawn, int32)
			/** The amount of time between "creating" each object (if CountPerSpawn > 1). */
			CS_DECLARE_MEMBER_WITH_EMU(TimeBetweenCountPerSpawn, float)

		public:

			FCount() :
				CS_CTOR_INIT_MEMBER_WITH_EMU(CountPerSpawn, 1),
				CS_CTOR_INIT_MEMBER_WITH_EMU(TimeBetweenCountPerSpawn, 0.0f)
			{
				CS_CTOR_SET_MEMBER_EMU(CountPerSpawn);
				CS_CTOR_SET_MEMBER_EMU(TimeBetweenCountPerSpawn);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(CountPerSpawn, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenCountPerSpawn, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
		};
	}
}

#pragma endregion FCsSpawnerCountParams

// SpawnerFrequency
#pragma region

/**
* The frequency at which a spawner (ICsSpawner) calls Spawn.
*/
UENUM(BlueprintType)
enum class ECsSpawnerFrequency : uint8
{
	/** */
	Once						UMETA(DisplayName = "Once"),
	/** */
	Count						UMETA(DisplayName = "Count"),
	/** */
	TimeCount					UMETA(DisplayName = "Time Count"),
	/** */
	TimeInterval				UMETA(DisplayName = "Time Interval"),
	/** */
	Infinite					UMETA(DisplayName = "Infinite"),
	ECsSpawnerFrequency_MAX		UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerFrequency : public TCsEnumMap<ECsSpawnerFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerFrequency, ECsSpawnerFrequency)
};

namespace NCsSpawnerFrequency
{
	typedef ECsSpawnerFrequency Type;

	namespace Ref
	{
		extern CSCORE_API const Type Once;
		extern CSCORE_API const Type Count;
		extern CSCORE_API const Type TimeCount;
		extern CSCORE_API const Type TimeInterval;
		extern CSCORE_API const Type Infinite;
		extern CSCORE_API const Type ECsSpawnerFrequency_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	/**
	* The frequency at which a spawner (ICsSpawner) calls Spawn.
	*/
	enum class EFrequency : uint8
	{
		/** */
		Once,
		/** */
		Count,
		/** */
		TimeCount,
		/** */
		TimeInterval,
		/** */
		Infinite,
		EFrequency_MAX
	};

	struct CSCORE_API EMFrequency : public TCsEnumMap<EFrequency>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
	};

	namespace NFrequency
	{
		namespace Ref
		{
			typedef EFrequency Type;

			extern CSCORE_API const Type Once;
			extern CSCORE_API const Type Count;
			extern CSCORE_API const Type TimeCount;
			extern CSCORE_API const Type TimeInterval;
			extern CSCORE_API const Type Infinite;
			extern CSCORE_API const Type EFrequency_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}
}

#pragma endregion SpawnerFrequency

// FCsSpawnerFrequencyParams
#pragma region

// NCsSpawner::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FFrequency)

/**
* Parameters describing the frequency at which Spawn is called after calling Start.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerFrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Trigger Frequency
		If Type == ECsSpawnerFrequency::Once,
	     Ignore Count and Interval.
		If Type == ECsSpawnerFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsSpawnerFrequency::Once.
		if Type == ECsSpawnerFrequency::TimeCount,
		if Type == ECsSpawnerFrequency::TimeInterval,
		If Type == ECsSpawnerFrequency::Infinite,
	     Ignore Count and Interval should be > 0.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsSpawnerFrequency Type;

	/** The delay before calling Start.
		If Delay == 0.0f, Spawn will be called at a given interval.
		If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** The number of times to call Spawn after Start is called.
		Only valid if 
		 Type == ECsSpawnerFrequency::Count
		 Type == ECsSpawnerFrequency::TimeCount
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each Spawn call after Start is called.
		Only valid if,
		Type == ECsSpawnerFrequency::Count
		Type == ECsSpawnerFrequency::TimeInterval
		Type == ECsSpawnerFrequency::Infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsSpawnerFrequencyParams() :
		Type(ECsSpawnerFrequency::Once),
		Delay(0.0f),
		Count(0),
		Interval(0.0f),
		Time(0.0f)
	{
	}

#define ParamsType NCsSpawner::NParams::FFrequency
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	float CalculateTotalTime() const;

	void Reset();

	void Update();
	void OnPostEditChange();
};
 
namespace NCsSpawner
{
	namespace NParams
	{
		struct CSCORE_API FFrequency
		{
		#define FrequencyType NCsSpawner::EFrequency

		private:

			/** Trigger Frequency
				If Type == FrequencyType::Once,
				 Ignore Count and Interval.
				If Type == FrequencyType::Count,
				 Count should be > 0, if NOT, it will be treated
				 as ECsSpawnerFrequency::Once.
				if Type == FrequencyType::TimeCount,
				if Type == FrequencyType::TimeInterval,
				If Type == FrequencyType::Infinite,
				 Ignore Count and Interval should be > 0.0f. */
			CS_DECLARE_MEMBER_WITH_EMU(Type, FrequencyType)

			/** The delay before calling Start.
				If Delay == 0.0f, Spawn will be called at a given interval.
				If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
			CS_DECLARE_MEMBER_WITH_EMU(Delay, float)

			/** The number of times to call Spawn after Start is called.
				Only valid if 
				 Type == FrequencyType::Count
				 Type == FrequencyType::TimeCount
				Should be > 0. */
			CS_DECLARE_MEMBER_WITH_EMU(Count, int32)

			/** The time between each Spawn call after Start is called.
				Only valid if,
				Type == FrequencyType::Count
				Type == FrequencyType::TimeInterval
				Type == FrequencyType::Infinite */
			CS_DECLARE_MEMBER_WITH_EMU(Interval, float)

			CS_DECLARE_MEMBER_WITH_EMU(Time, float)

		public:

			FFrequency() :
				CS_CTOR_INIT_MEMBER_WITH_EMU(Type, FrequencyType::Once),
				CS_CTOR_INIT_MEMBER_WITH_EMU(Delay, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_EMU(Count, 0),
				CS_CTOR_INIT_MEMBER_WITH_EMU(Interval, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_EMU(Time, 0.0f)
			{
				CS_CTOR_SET_MEMBER_EMU(Type);
				CS_CTOR_SET_MEMBER_EMU(Delay);
				CS_CTOR_SET_MEMBER_EMU(Count);
				CS_CTOR_SET_MEMBER_EMU(Interval);
				CS_CTOR_SET_MEMBER_EMU(Time);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Type, FrequencyType)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Delay, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Count, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Interval, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Time, float)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			float CalculateTotalTime() const;

			void Reset();

		#undef FrequencyType
		};
	}
}

#pragma endregion FCsSpawnerFrequencyParams

// SpawnerPoint
#pragma region

/**
* The where to get the Transform to apply to the spawned object.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPoint : uint8
{
	/** Spawn using the Spawner's Transform */
	Self				UMETA(DisplayName = "Self"),
	/** Spawn from a predefined list of Transforms */
	Transform			UMETA(DisplayName = "Transform"),
	/** Spawn using the an Actor's Transform */
	Actor				UMETA(DisplayName = "Actor"),
	/** Spawn using a custom method */
	Custom				UMETA(DisplayName = "Custom"),
	ECsSpawnerPoint_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPoint : public TCsEnumMap<ECsSpawnerPoint>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPoint, ECsSpawnerPoint)
};

namespace NCsSpawnerPoint
{
	typedef ECsSpawnerPoint Type;

	namespace Ref
	{
		extern CSCORE_API const Type Self;
		extern CSCORE_API const Type Transform;
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSpawnerPoint_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	enum class EPoint
	{
		/** Spawn using the Spawner's Transform */
		Self,
		/** Spawn from a predefined list of Transforms */
		Transform,
		/** Spawn using the an Actor's Transform */
		Actor	,
		/** Spawn using a custom method */
		Custom,
		EPoint_MAX
	};

	struct CSCORE_API EMPoint : public TCsEnumMap<EPoint>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPoint, EPoint)
	};

	namespace NPoint
	{
		namespace Ref
		{
			typedef EPoint Type;

			extern CSCORE_API const Type Self;
			extern CSCORE_API const Type Transform;
			extern CSCORE_API const Type Actor;
			extern CSCORE_API const Type Custom;
			extern CSCORE_API const Type EPoint_MAX;
		}
	}
}

#pragma endregion SpawnerPoint

// SpawnerPointOrder
#pragma region

/**
* The order in which to use spawn points.
*/
UENUM(BlueprintType)
enum class ECsSpawnerPointOrder : uint8
{
	FirstToLast					UMETA(DisplayName = "First to Last"),
	RandomShuffle				UMETA(DisplayName = "Random Shuffle"),
	Random						UMETA(DisplayName = "Random"),
	Custom						UMETA(DisplayName = "Custom"),
	ECsSpawnerPointOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerPointOrder : public TCsEnumMap<ECsSpawnerPointOrder>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerPointOrder, ECsSpawnerPointOrder)
};

namespace NCsSpawnerPointOrder
{
	typedef ECsSpawnerPointOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type FirstToLast;
		extern CSCORE_API const Type RandomShuffle;
		extern CSCORE_API const Type Random;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSpawnerPointOrder_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	/**
	* The order in which to use spawn points.
	*/
	enum class EPointOrder : uint8
	{
		FirstToLast,
		RandomShuffle,
		Random,
		Custom,
		EPointOrder_MAX
	};

	struct CSCORE_API EMPointOrder : public TCsEnumMap<EPointOrder>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMPointOrder, EPointOrder)
	};

	namespace NPointOrder
	{
		namespace Ref
		{
			typedef EPointOrder Type;

			extern CSCORE_API const Type FirstToLast;
			extern CSCORE_API const Type RandomShuffle;
			extern CSCORE_API const Type Random;
			extern CSCORE_API const Type Custom;
			extern CSCORE_API const Type EPointOrder_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}
}

#pragma endregion SpawnerPointOrder

// FCsSpawnerPointParams
#pragma region

class AActor;

/**
* Parameters describing where and how to apply the transform to the object spawned.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerPointParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsSpawnerPoint Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsSpawnerPointOrder Order;

	/** Which of the components of Transform to apply to the spawned object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> Transforms;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AActor*> Actors;

	FCsSpawnerPointParams() :
		Type(ECsSpawnerPoint::Self),
		Order(ECsSpawnerPointOrder::FirstToLast),
		TransformRules(7), // ALL
		Transforms(),
		Actors()
	{
	}
};

namespace NCsSpawner
{
	namespace NParams
	{
		struct CSCORE_API FPoint
		{
		#define PointType NCsSpawner::EPoint
		#define PointOrderType NCsSpawner::EPointOrder

		private:

			CS_DECLARE_MEMBER_WITH_EMU(Type, PointType)
			CS_DECLARE_MEMBER_WITH_EMU(Order, PointOrderType)
			CS_DECLARE_MEMBER_WITH_EMU(TransformRules, int32)
			CS_DECLARE_MEMBER_WITH_EMU(Transforms, TArray<FTransform>)
			CS_DECLARE_MEMBER_WITH_EMU(Actors, TArray<AActor*>)

		public:

			FPoint() :
				CS_CTOR_INIT_MEMBER_WITH_EMU(Type, PointType::Self),
				CS_CTOR_INIT_MEMBER_WITH_EMU(Order, PointOrderType::FirstToLast),
				CS_CTOR_INIT_MEMBER_WITH_EMU(TransformRules, 7),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_EMU(Transforms),
				CS_CTOR_INIT_MEMBER_ARRAY_WITH_EMU(Actors)
			{
				CS_CTOR_SET_MEMBER_EMU(Type);
				CS_CTOR_SET_MEMBER_EMU(Order);
				CS_CTOR_SET_MEMBER_EMU(TransformRules);
				CS_CTOR_SET_MEMBER_EMU(Transforms);
				CS_CTOR_SET_MEMBER_EMU(Actors);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Type, PointType)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Order, PointOrderType)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TransformRules, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Transforms, TArray<FTransform>)
			CS_DEFINE_SET_GET_MEMBER_WITH_EMU(Actors, TArray<AActor*>)

		#undef PointType
		#undef PointOrderType
		};
	}
}

#pragma endregion FCsSpawnerPointParams

// FCsSpawnerPointHelper
#pragma region

class ICsSpawner;
class AActor;

struct CSCORE_API FCsSpawnerPointHelper
{
public:

	ICsSpawner* Spawner;

	AActor* SpawnerAsActor;

	FCsSpawnerPointParams* Params;

	int32 Index;

	TArray<AActor*> Actors;

	TArray<FTransform> Transforms;

	// Delegates

	DECLARE_DELEGATE(FPrepareSpawns);

	FPrepareSpawns PrepareSpawns_Impl;

	DECLARE_DELEGATE(FAdvanceIndex);

	FAdvanceIndex AdvanceIndex_Impl;

	DECLARE_DELEGATE_RetVal(FTransform, FGetSpawnTransform);

	FGetSpawnTransform GetSpawnTransform_Impl;

	DECLARE_DELEGATE_RetVal(FVector, FGetSpawnLocation);

	FGetSpawnLocation GetSpawnLocation_Impl;

	FCsSpawnerPointHelper() :
		Spawner(nullptr),
		SpawnerAsActor(nullptr),
		Params(nullptr),
		Index(0),
		Actors(),
		Transforms(),
		PrepareSpawns_Impl(),
		AdvanceIndex_Impl(),
		GetSpawnLocation_Impl()
	{
		PrepareSpawns_Impl.BindRaw(this, &FCsSpawnerPointHelper::PrepareSpawns);
		AdvanceIndex_Impl.BindRaw(this, &FCsSpawnerPointHelper::AdvanceIndex);
		GetSpawnTransform_Impl.BindRaw(this, &FCsSpawnerPointHelper::GetSpawnTransform);
		GetSpawnLocation_Impl.BindRaw(this, &FCsSpawnerPointHelper::GetSpawnLocation);
	}

	void PrepareSpawns();

	FORCEINLINE void PrepareSpawnsChecked(const FString& Context)
	{
		checkf(PrepareSpawns_Impl.IsBound(), TEXT("%s: PrepareSpawns_Impl is NOT bound to any function."));

		PrepareSpawns_Impl.Execute();
	}

	void AdvanceIndex();

	FORCEINLINE void AdvanceIndexChecked(const FString& Context)
	{
		checkf(AdvanceIndex_Impl.IsBound(), TEXT("%s: AdvanceIndex_Impl is NOT bound to any function."));

		AdvanceIndex_Impl.Execute();
	}

	FTransform GetSpawnTransform() const;

	FORCEINLINE FTransform GetSpawnTransformChecked(const FString& Context) const
	{
		checkf(GetSpawnTransform_Impl.IsBound(), TEXT("%s: GetSpawnTransform_Impl is NOT bound to any function."));

		return GetSpawnTransform_Impl.Execute();
	}

	FVector GetSpawnLocation() const;

	FORCEINLINE FVector GetSpawnLocationChecked(const FString& Context) const
	{
		checkf(GetSpawnLocation_Impl.IsBound(), TEXT("%s: GetSpawnLocation_Impl is NOT bound to any function."));

		return GetSpawnLocation_Impl.Execute();
	}
};

#pragma endregion FCsSpawnerPointHelper