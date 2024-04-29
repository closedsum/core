// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsTypes_Beam_Collision.generated.h"
// BeamCollisionFrequency
#pragma region

/**
* The frequency at which a beam (ICsBeam) attempts, via a sweep or trace, to collide with objects.
*/
UENUM(BlueprintType)
enum class ECsBeamCollisionFrequency : uint8
{
	/** Collide with objects only 1 time. 
		NOTE: Only ONE collision 'pass' (sweep or trace) will be performed. */
	Once							UMETA(DisplayName = "Once"),
	/** Collide with objects 'Count' number of times. 
		NOTE: Only ONE collision 'pass' (sweep or trace) will be performed. */
	Count							UMETA(DisplayName = "Count"),
	/** Collide with objects 'Count' number of times over the LifeTime of the Beam.
		This results in 'Count' number of collision 'passes' (sweep or trace) 
		at a specified Intervals = LifeTime / Count. */
	TimeCount						UMETA(DisplayName = "Time Count"),
	/** Collide with objects a 'number' of times over the LifeTime of the Beam.
		This results in a 'number' of collision 'passes' (sweep or trace) 
		where 'number' = Floor(LifeTime / Interval). */
	TimeInterval					UMETA(DisplayName = "Time Interval"),
	/** Collide with objects an infinite number of times.
		A collision 'pass' (sweep or trace) is performed each interval. */
	Infinite						UMETA(DisplayName = "Infinite"),
	ECsBeamCollisionFrequency_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamCollisionFrequency : public TCsEnumMap<ECsBeamCollisionFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamCollisionFrequency, ECsBeamCollisionFrequency)
};

namespace NCsBeamCollisionFrequency
{
	typedef ECsBeamCollisionFrequency Type;

	namespace Ref
	{
		extern CSBEAM_API const Type Once;
		extern CSBEAM_API const Type Count;
		extern CSBEAM_API const Type TimeCount;
		extern CSBEAM_API const Type TimeInterval;
		extern CSBEAM_API const Type Infinite;
		extern CSBEAM_API const Type ECsBeamCollisionFrequency_MAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

namespace NCsBeam
{
	namespace NCollision
	{
		/**
		* The frequency at which a beam (ICsBeam) attempts, via a sweep or trace, to collide with objects.
		*/
		enum class EFrequency : uint8
		{
			/** Collide with objects only 1 time. 
				NOTE: Only ONE collision 'pass' (sweep or trace) will be performed. */
			Once,
			/** Collide with objects 'Count' number of times.
				NOTE: Only ONE collision 'pass' (sweep or trace) will be performed. */
			Count,
			/** Collide with objects 'Count' number of times over the LifeTime of the Beam.
				This results in 'Count' number of collision 'passes' (sweep or trace)
				at a specified Intervals = LifeTime / Count. */
			TimeCount,
			/** Collide with objects a 'number' of times over the LifeTime of the Beam.
				This results in a 'number' of collision 'passes' (sweep or trace)
				where 'number' = Floor(LifeTime / Interval). */
			TimeInterval,
			/** Collide with objects an infinite number of times.
				A collision 'pass' (sweep or trace) is performed each frame. */
			Infinite,
			EFrequency_MAX
		};

		struct CSBEAM_API EMFrequency : public TCsEnumMap<EFrequency>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
		};

		namespace NFrequency
		{
			namespace Ref
			{
				typedef EFrequency Type;

				extern CSBEAM_API const Type Once;
				extern CSBEAM_API const Type Count;
				extern CSBEAM_API const Type TimeCount;
				extern CSBEAM_API const Type TimeInterval;
				extern CSBEAM_API const Type Infinite;
				extern CSBEAM_API const Type EFrequency_MAX;
			}
		}
	}
}

#pragma endregion BeamCollisionFrequency

// FCsBeamCollisionFrequencyParams
#pragma region

// NCsBeam::NCollision::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NCollision, NParams, FFrequency)

/**
* Parameters describing the frequency at which a beam (ICsBeam) attempts,
* via sweep or trace, to collide with objects.
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamCollisionFrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Trigger Frequency
		If Type == ECsBeamCollisionFrequency::Once,
	     Ignore Count and Interval.
		If Type == ECsBeamCollisionFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsBeamCollisionFrequency::Once.
		if Type == ECsBeamCollisionFrequency::TimeCount,
		if Type == ECsBeamCollisionFrequency::TimeInterval,
		If Type == ECsBeamCollisionFrequency::Infinite,
	     Ignore Count and Interval should be >= 0.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Collision|Frequency")
	ECsBeamCollisionFrequency Type;

	/** The number of times to perform a collision 'pass' (sweep or trace).
		Only valid if 
		 Type == ECsBeamCollisionFrequency::Count
		 Type == ECsBeamCollisionFrequency::TimeCount
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Collision|Frequency", meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each collision 'pass' (sweep or trace).
		Interval == 0.0f performs a collision 'pass' each frame.
		Only valid if,
		Type == ECsSpawnerFrequency::Count
		Type == ECsSpawnerFrequency::TimeInterval
		Type == ECsSpawnerFrequency::Infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Collision|Frequency", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	FCsBeamCollisionFrequencyParams() :
		Type(ECsBeamCollisionFrequency::Once),
		Count(0),
		Interval(0.0f)
	{
	}

#define ParamsType NCsBeam::NCollision::NParams::FFrequency
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

	void Reset();

	void Update(const float& Time);
	void OnPostEditChange(const float& Time);
};
 
namespace NCsBeam
{
	namespace NCollision
	{
		namespace NParams
		{
			struct CSBEAM_API FFrequency
			{
			#define FrequencyType NCsBeam::NCollision::EFrequency

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

			public:

				FFrequency() :
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, FrequencyType::Once),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Count, 0),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Interval, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Count);
					CS_CTOR_SET_MEMBER_PROXY(Interval);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FrequencyType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

				void Reset();

			#undef FrequencyType
			};
		}
	}
}

#pragma endregion FCsBeamCollisionFrequencyParams