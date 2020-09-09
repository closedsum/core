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
	Once								 UMETA(DisplayName = "Once"),
	Count								 UMETA(DisplayName = "Count"),
	Time								 UMETA(DisplayName = "Time"),
	Infinite							 UMETA(DisplayName = "Infinite"),
	ECsSpawnerFrequency_MAX  UMETA(Hidden),
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
		extern CSCORE_API const Type Time;
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
		If Type == ECsStatusEffectTriggerFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsStatusEffectTriggerFrequency::Once.
		if Type == ECsSpawnerFrequency::Time, 
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
		Only valid if Type == ECsSpawnerFrequency::Count.
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each Spawn call after Start is called.
		Only valid if,
		Type == ECsSpawnerFrequency::Count
		 or
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

	/** Which of the components of Transform to apply to the spawned object. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> Transforms;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AActor*> Actors;

	FCsSpawnerPointParams() :
		Type(ECsSpawnerPoint::Self),
		TransformRules(7), // ALL
		Transforms(),
		Actors()
	{
	}
};

#pragma endregion FCsSpawnerPointParams