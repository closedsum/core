// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_SpawnerParams.generated.h"

// FCsSpawner_CountParams
#pragma region

// NCsSpawner::NParams::FCount
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FCount)

/**
* Parameters describing number (count) of objects "created" when Spawn is called.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawner_CountParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of objects to "create" per Spawn call. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "1", UIMin = "1"))
	int32 CountPerSpawn;

	/** The amount of time between "creating" each object (if CountPerSpawn > 1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float TimeBetweenCountPerSpawn;

	FCsSpawner_CountParams() :
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
			CS_DECLARE_MEMBER_WITH_PROXY(CountPerSpawn, int32)
			/** The amount of time between "creating" each object (if CountPerSpawn > 1). */
			CS_DECLARE_MEMBER_WITH_PROXY(TimeBetweenCountPerSpawn, float)

		public:

			FCount() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(CountPerSpawn, 1),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeBetweenCountPerSpawn, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(CountPerSpawn);
				CS_CTOR_SET_MEMBER_PROXY(TimeBetweenCountPerSpawn);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(CountPerSpawn, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeBetweenCountPerSpawn, float)

			void Copy(const FCount& From)
			{
				SetCountPerSpawn(From.GetCountPerSpawn());
				SetTimeBetweenCountPerSpawn(From.GetTimeBetweenCountPerSpawn());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
		};
	}
}

#pragma endregion FCsSpawner_CountParams

// SpawnerFrequency
#pragma region

/**
* The frequency at which a spawner (ICsSpawner) calls Spawn.
*/
UENUM(BlueprintType)
enum class ECsSpawnerFrequency : uint8
{
	/** The spawner only calls Spawn ONE time. */
	Once						UMETA(DisplayName = "Once"),
	/** The spawner calls Spawn 'COUNT' number of times at a specified
		Interval. */
	Count						UMETA(DisplayName = "Count"),
	/** The spawner calls Spawn 'COUNT' number of times over Time.
		The Interval of each Spawn is Time / COUNT. */
	TimeCount					UMETA(DisplayName = "Time Count"),
	/** The spawner call Spawn a number of times equal to Time / Interval. */
	TimeInterval				UMETA(DisplayName = "Time Interval"),
	/** The spawner keeps calling Spawn every Interval. */
	Infinite					UMETA(DisplayName = "Infinite"),
	/** The spawner keeps calling Spawn every Interval as long as the number of 
		objects active (persistent from being spawned via the spawner) is LESS THAN
		'COUNT' */
	InfiniteFillToCount			UMETA(DisplayName = "Infinite Fill to Count"),
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
		extern CSCORE_API const Type InfiniteFillToCount;
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
		/** The spawner only calls Spawn ONE time. */
		Once,
		/** The spawner calls Spawn 'COUNT' number of times at a specified
			Interval. */
		Count,
		/** The spawner calls Spawn 'COUNT' number of times over Time.
			The Interval of each Spawn is Time / COUNT. */
		TimeCount,
		/** The spawner call Spawn a number of times equal to Time / Interval. */
		TimeInterval,
		/** The spawner keeps calling Spawn every Interval. */
		Infinite,
		/** The spawner keeps calling Spawn every Interval as long as the number of
			objects active (persistent from being spawned via the spawner) is LESS THAN
			'COUNT' */
		InfiniteFillToCount,
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
			extern CSCORE_API const Type InfiniteFillToCount;
			extern CSCORE_API const Type EFrequency_MAX;
		}

		extern CSCORE_API const uint8 MAX;
	}
}

#pragma endregion SpawnerFrequency

// FCsSpawner_FrequencyParams
#pragma region

// NCsSpawner::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FFrequency)

/**
* Parameters describing the frequency at which Spawn is called after calling Start.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawner_FrequencyParams
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params")
	ECsSpawnerFrequency Type;

	/** The delay before calling Start.
		If Delay == 0.0f, Spawn will be called at a given interval.
		If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** The number of times to call Spawn after Start is called.
		Only valid if 
		 Type == ECsSpawnerFrequency::Count
		 Type == ECsSpawnerFrequency::TimeCount
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each Spawn call after Start is called.
		Only valid if,
		Type == ECsSpawnerFrequency::Count
		Type == ECsSpawnerFrequency::TimeInterval
		Type == ECsSpawnerFrequency::Infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	/** The total time for Spawning. 
		Only valid if,
		Type == ECsSpawnerFrequency::Count
		Type == ECsSpawnerFrequency::TimeCount
		Type == ECsSpawnerFrequency::TimeInterval */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsSpawner_FrequencyParams() :
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
			CS_DECLARE_MEMBER_WITH_PROXY(Type, FrequencyType)

			/** The delay before calling Start.
				If Delay == 0.0f, Spawn will be called at a given interval.
				If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
			CS_DECLARE_MEMBER_WITH_PROXY(Delay, float)

			/** The number of times to call Spawn after Start is called.
				Only valid if 
				 Type == FrequencyType::Count
				 Type == FrequencyType::TimeCount
				Should be > 0. */
			CS_DECLARE_MEMBER_WITH_PROXY(Count, int32)

			/** The time between each Spawn call after Start is called.
				Only valid if,
				Type == FrequencyType::Count
				Type == FrequencyType::TimeInterval
				Type == FrequencyType::Infinite */
			CS_DECLARE_MEMBER_WITH_PROXY(Interval, float)

			CS_DECLARE_MEMBER_WITH_PROXY(Time, float)

		public:

			FFrequency() :
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

			void Copy(const FFrequency& From)
			{
				SetType(From.GetType());
				SetDelay(From.GetDelay());
				SetCount(From.GetCount());
				SetInterval(From.GetInterval());
				SetTime(From.GetTime());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

			float CalculateTotalTime() const;

			void Reset();

			void Update();

		#undef FrequencyType
		};
	}
}

#pragma endregion FCsSpawner_FrequencyParams

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
	enum class EPoint : uint8
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

//// FCsSpawnerPointParams
//#pragma region
//
//class AActor;
//
///**
//* Parameters describing where and how to apply the transform to the object spawned.
//*/
//USTRUCT(BlueprintType)
//struct CSCORE_API FCsSpawnerPointParams
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ECsSpawnerPoint Type;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	ECsSpawnerPointOrder Order;
//
//	/** Which of the components of Transform to apply to the spawned object. */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
//	int32 TransformRules;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FTransform3f> Transforms;
//
//	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
//	TArray<AActor*> Actors;
//
//	FCsSpawnerPointParams() :
//		Type(ECsSpawnerPoint::Self),
//		Order(ECsSpawnerPointOrder::FirstToLast),
//		TransformRules(7), // ALL
//		Transforms(),
//		Actors()
//	{
//	}
//};
//
//namespace NCsSpawner
//{
//	namespace NParams
//	{
//		struct CSCORE_API FPoint
//		{
//		#define PointType NCsSpawner::EPoint
//		#define PointOrderType NCsSpawner::EPointOrder
//
//		private:
//
//			CS_DECLARE_MEMBER_WITH_PROXY(Type, PointType)
//			CS_DECLARE_MEMBER_WITH_PROXY(Order, PointOrderType)
//			CS_DECLARE_MEMBER_WITH_PROXY(TransformRules, int32)
//			CS_DECLARE_MEMBER_WITH_PROXY(Transforms, TArray<FTransform3f>)
//			CS_DECLARE_MEMBER_WITH_PROXY(Actors, TArray<AActor*>)
//
//		public:
//
//			FPoint() :
//				CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, PointType::Self),
//				CS_CTOR_INIT_MEMBER_WITH_PROXY(Order, PointOrderType::FirstToLast),
//				CS_CTOR_INIT_MEMBER_WITH_PROXY(TransformRules, 7),
//				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Transforms),
//				CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(Actors)
//			{
//				CS_CTOR_SET_MEMBER_PROXY(Type);
//				CS_CTOR_SET_MEMBER_PROXY(Order);
//				CS_CTOR_SET_MEMBER_PROXY(TransformRules);
//				CS_CTOR_SET_MEMBER_PROXY(Transforms);
//				CS_CTOR_SET_MEMBER_PROXY(Actors);
//			}
//
//			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, PointType)
//			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Order, PointOrderType)
//			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TransformRules, int32)
//			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Transforms, TArray<FTransform3f>)
//			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Actors, TArray<AActor*>)
//
//		#undef PointType
//		#undef PointOrderType
//		};
//	}
//}
//
//#pragma endregion FCsSpawnerPointParams
//
//// FCsSpawnerPointHelper
//#pragma region
//
//class ICsSpawner;
//class AActor;
//
//struct CSCORE_API FCsSpawnerPointHelper
//{
//public:
//
//	ICsSpawner* Spawner;
//
//	AActor* SpawnerAsActor;
//
//	FCsSpawnerPointParams* Params;
//
//	int32 Index;
//
//	TArray<AActor*> Actors;
//
//	TArray<FTransform3f> Transforms;
//
//	// Delegates
//
//	DECLARE_DELEGATE(FPrepareSpawns);
//
//	FPrepareSpawns PrepareSpawns_Impl;
//
//	DECLARE_DELEGATE(FAdvanceIndex);
//
//	FAdvanceIndex AdvanceIndex_Impl;
//
//	DECLARE_DELEGATE_RetVal(FTransform3f, FGetSpawnTransform);
//
//	FGetSpawnTransform GetSpawnTransform_Impl;
//
//	DECLARE_DELEGATE_RetVal(FVector3f, FGetSpawnLocation);
//
//	FGetSpawnLocation GetSpawnLocation_Impl;
//
//	FCsSpawnerPointHelper() :
//		Spawner(nullptr),
//		SpawnerAsActor(nullptr),
//		Params(nullptr),
//		Index(0),
//		Actors(),
//		Transforms(),
//		PrepareSpawns_Impl(),
//		AdvanceIndex_Impl(),
//		GetSpawnLocation_Impl()
//	{
//		PrepareSpawns_Impl.BindRaw(this, &FCsSpawnerPointHelper::PrepareSpawns);
//		AdvanceIndex_Impl.BindRaw(this, &FCsSpawnerPointHelper::AdvanceIndex);
//		GetSpawnTransform_Impl.BindRaw(this, &FCsSpawnerPointHelper::GetSpawnTransform);
//		GetSpawnLocation_Impl.BindRaw(this, &FCsSpawnerPointHelper::GetSpawnLocation);
//	}
//
//	void PrepareSpawns();
//
//	FORCEINLINE void PrepareSpawnsChecked(const FString& Context)
//	{
//		checkf(PrepareSpawns_Impl.IsBound(), TEXT("%s: PrepareSpawns_Impl is NOT bound to any function."));
//
//		PrepareSpawns_Impl.Execute();
//	}
//
//	void AdvanceIndex();
//
//	FORCEINLINE void AdvanceIndexChecked(const FString& Context)
//	{
//		checkf(AdvanceIndex_Impl.IsBound(), TEXT("%s: AdvanceIndex_Impl is NOT bound to any function."));
//
//		AdvanceIndex_Impl.Execute();
//	}
//
//	FTransform3f GetSpawnTransform() const;
//
//	FORCEINLINE FTransform3f GetSpawnTransformChecked(const FString& Context) const
//	{
//		checkf(GetSpawnTransform_Impl.IsBound(), TEXT("%s: GetSpawnTransform_Impl is NOT bound to any function."));
//
//		return GetSpawnTransform_Impl.Execute();
//	}
//
//	FVector3f GetSpawnLocation() const;
//
//	FORCEINLINE FVector3f GetSpawnLocationChecked(const FString& Context) const
//	{
//		checkf(GetSpawnLocation_Impl.IsBound(), TEXT("%s: GetSpawnLocation_Impl is NOT bound to any function."));
//
//		return GetSpawnLocation_Impl.Execute();
//	}
//};
//
//#pragma endregion FCsSpawnerPointHelper

// SpawnerShape
#pragma region

/**
* The shape / area of the spawner from which objects are spawned.
*/
UENUM(BlueprintType)
enum class ECsSpawnerShape : uint8
{
	Circle				UMETA(DisplayName = "Circle"),
	Rectangle			UMETA(DisplayName = "Rectangle"),
	Sphere				UMETA(DisplayName = "Sphere"),
	Box					UMETA(DisplayName = "Box"),
	Custom				UMETA(DisplayName = "Custom"),
	ECsSpawnerShape_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerShape : public TCsEnumMap<ECsSpawnerShape>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerShape, ECsSpawnerShape)
};

namespace NCsSpawnerShape
{
	typedef ECsSpawnerShape Type;

	namespace Ref
	{
		extern CSCORE_API const Type Circle;
		extern CSCORE_API const Type Rectangle;
		extern CSCORE_API const Type Sphere;
		extern CSCORE_API const Type Box;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSpawnerShape_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	enum class EShape : uint8
	{
		Circle,
		Rectangle,
		Sphere,
		Box,
		Custom,
		EShape_MAX
	};

	struct CSCORE_API EMShape : public TCsEnumMap<EShape>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMShape, EShape)
	};

	namespace NShape
	{
		namespace Ref
		{
			typedef EShape Type;

			extern CSCORE_API const Type Circle;
			extern CSCORE_API const Type Rectangle;
			extern CSCORE_API const Type Sphere;
			extern CSCORE_API const Type Box;
			extern CSCORE_API const Type Custom;
			extern CSCORE_API const Type EShape_MAX;
		}
	}
}

#pragma endregion SpawnerShape

// SpawnerShapeCenter
#pragma region

/**
* Describe what is designed as the "center" of the spawner's shape.
*/
UENUM(BlueprintType)
enum class ECsSpawnerShapeCenter : uint8
{
	/** Center of shape using the Spawner's Transform */
	Self						UMETA(DisplayName = "Self"),
	/** Center of shape using a predefined Transform */
	Transform					UMETA(DisplayName = "Transform"),
	/** Center of shape using the an Actor's Transform */
	Actor						UMETA(DisplayName = "Actor"),
	/** Center of shape using a custom method */
	Custom						UMETA(DisplayName = "Custom"),
	ECsSpawnerShapeCenter_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerShapeCenter : public TCsEnumMap<ECsSpawnerShapeCenter>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerShapeCenter, ECsSpawnerShapeCenter)
};

namespace NCsSpawnerShapeCenter
{
	typedef ECsSpawnerShapeCenter Type;

	namespace Ref
	{
		extern CSCORE_API const Type Self;
		extern CSCORE_API const Type Transform;
		extern CSCORE_API const Type Actor;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSpawnerShapeCenter_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	namespace NShape
	{
		enum class ECenter : uint8
		{
			/** Center of shape using the Spawner's Transform */
			Self,
			/** Center of shape using a predefined Transform */
			Transform,
			/** Center of shape using an Actor's Transform */
			Actor,
			/** Center of shape using a custom method */
			Custom,
			ECenter_MAX
		};

		struct CSCORE_API EMCenter : public TCsEnumMap<ECenter>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCenter, ECenter)
		};

		namespace NCenter
		{
			namespace Ref
			{
				typedef ECenter Type;

				extern CSCORE_API const Type Self;
				extern CSCORE_API const Type Transform;
				extern CSCORE_API const Type Actor;
				extern CSCORE_API const Type Custom;
				extern CSCORE_API const Type ECenter_MAX;
			}
		}
	}
}

#pragma endregion SpawnerShapeCenter

// SpawnerDistribution
#pragma region

/**
* How the spawning is distributed over a shape / area.
*/
UENUM(BlueprintType)
enum class ECsSpawnerDistribution : uint8
{
	Uniform						UMETA(DisplayName = "Uniform"),
	ECsSpawnerDistribution_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSpawnerDistribution : public TCsEnumMap<ECsSpawnerDistribution>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSpawnerDistribution, ECsSpawnerDistribution)
};

namespace NCsSpawnerDistribution
{
	typedef ECsSpawnerDistribution Type;

	namespace Ref
	{
		extern CSCORE_API const Type Uniform;
		extern CSCORE_API const Type ECsSpawnerDistribution_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSpawner
{
	enum class EDistribution : uint8
	{
		Uniform,
		EDistribution_MAX
	};

	struct CSCORE_API EMDistribution : public TCsEnumMap<EDistribution>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDistribution, EDistribution)
	};

	namespace NDistribution
	{
		namespace Ref
		{
			typedef EDistribution Type;

			extern CSCORE_API const Type Uniform;
			extern CSCORE_API const Type EDistribution_MAX;
		}
	}
}

#pragma endregion SpawnerDistribution