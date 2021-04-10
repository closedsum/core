// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_SpawnerParams.generated.h"
#pragma once

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

#pragma endregion SpawnerFrequency

// FCsSpawnerCountParams
#pragma region

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

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSpawnerCountParams

// FCsSpawnerFrequencyParams
#pragma region

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

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context) const;

	float CalculateTotalTime() const;

	void Reset();

	void Update();
	void OnPostEditChange();
};
 
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