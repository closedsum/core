// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Log
#include "Utility/CsSoundLog.h"

#include "CsTypes_Library_Sound.generated.h"

// SoundSpawnFrequency
#pragma region

/**
* The frequency at which a Sound spawns.
*/
UENUM(BlueprintType)
enum class ECsSoundSpawnFrequency : uint8
{
	/** The Sound only spawned ONE time. */
	Once						UMETA(DisplayName = "Once"),
	/** The Sound spawn a 'COUNT' number of times at a specified
		Interval. */
	Count						UMETA(DisplayName = "Count"),
	/** The Sound spawns a 'COUNT' number of times over Time.
		The Interval of each Spawn is Time / COUNT. */
	TimeCount					UMETA(DisplayName = "Time Count"),
	/** The Sound spawns a number of times equal to Time / Interval. */
	TimeInterval				UMETA(DisplayName = "Time Interval"),
	/** The Sound spawns every Interval. */
	Infinite					UMETA(DisplayName = "Infinite"),
	ECsSoundSpawnFrequency_MAX		UMETA(Hidden),
};

struct CSSOUND_API EMCsSoundSpawnFrequency : public TCsEnumMap<ECsSoundSpawnFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSoundSpawnFrequency, ECsSoundSpawnFrequency)
};

namespace NCsSoundSpawnFrequency
{
	typedef ECsSoundSpawnFrequency Type;

	namespace Ref
	{
		extern CSSOUND_API const Type Once;
		extern CSSOUND_API const Type Count;
		extern CSSOUND_API const Type TimeCount;
		extern CSSOUND_API const Type TimeInterval;
		extern CSSOUND_API const Type Infinite;
		extern CSSOUND_API const Type ECsSoundSpawnFrequency_MAX;
	}

	extern CSSOUND_API const uint8 MAX;
}

namespace NCsSound
{
	namespace NSpawn
	{
		/**
		* The frequency at which a Sound spawns.
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
			EFrequency_MAX
		};

		struct CSSOUND_API EMFrequency : public TCsEnumMap<EFrequency>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
		};

		namespace NFrequency
		{
			namespace Ref
			{
				typedef EFrequency Type;

				extern CSSOUND_API const Type Once;
				extern CSSOUND_API const Type Count;
				extern CSSOUND_API const Type TimeCount;
				extern CSSOUND_API const Type TimeInterval;
				extern CSSOUND_API const Type Infinite;
				extern CSSOUND_API const Type EFrequency_MAX;
			}

			extern CSSOUND_API const uint8 MAX;
		}
	}
}

#pragma endregion SoundSpawnFrequency

// FCsSound_Spawn_FrequencyParams
#pragma region

// NCsSound::NSpawn::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSound, NSpawn, NParams, FFrequency)

/**
* Parameters describing the frequency at which Spawn is called after calling Start.
*/
USTRUCT(BlueprintType)
struct CSSOUND_API FCsSound_Spawn_FrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Trigger Frequency
		If Type == ECsSoundSpawnFrequency::Once,
	     Ignore Count and Interval.
		If Type == ECsSoundSpawnFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsSoundSpawnFrequency::Once.
		if Type == ECsSoundSpawnFrequency::TimeCount,
		if Type == ECsSoundSpawnFrequency::TimeInterval,
		If Type == ECsSoundSpawnFrequency::Infinite,
	     Ignore Count and Interval should be > 0.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params")
	ECsSoundSpawnFrequency Type;

	/** The delay before calling Start.
		If Delay == 0.0f, Spawn will be called at a given interval.
		If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** The number of times to call Spawn after Start is called.
		Only valid if 
		 Type == ECsSoundSpawnFrequency::Count
		 Type == ECsSoundSpawnFrequency::TimeCount
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each Spawn call after Start is called.
		Only valid if,
		Type == ECsSoundSpawnFrequency::Count
		Type == ECsSoundSpawnFrequency::TimeInterval
		Type == ECsSoundSpawnFrequency::Infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	/** The total time for Spawning. 
		Only valid if,
		Type == ECsSoundSpawnFrequency::Count
		Type == ECsSoundSpawnFrequency::TimeCount
		Type == ECsSoundSpawnFrequency::TimeInterval */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsSound_Spawn_FrequencyParams() :
		Type(ECsSoundSpawnFrequency::Once),
		Delay(0.0f),
		Count(0),
		Interval(0.0f),
		Time(0.0f)
	{
	}

#define ParamsType NCsSound::NSpawn::NParams::FFrequency
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSound::FLog::Warning) const;

	float CalculateTotalTime() const;

	void Reset();

	void Update();
	void OnPostEditChange();
};
 
namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			struct CSSOUND_API FFrequency
			{
			#define FrequencyType NCsSound::NSpawn::EFrequency

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

				FORCEINLINE FFrequency(FFrequency& B)
				{
					Copy(B);
				}

				FORCEINLINE FFrequency(const FFrequency& B)
				{
					Copy(B);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FrequencyType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Delay, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Count, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Interval, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Time, float)

				FORCEINLINE void Copy(const FFrequency& B)
				{
					CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Type);
					CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Delay);
					CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Count);
					CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Interval);
					CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Time);
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSound::FLog::Warning) const;

				float CalculateTotalTime() const;

				void Reset();

				void Update();

			#undef FrequencyType
			};
		}
	}
}

#pragma endregion FCsSound_Spawn_FrequencyParams

class UObject;

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			// TODO: Later make an interface?
			struct CSSOUND_API FParams
			{
			public:
		
			#define FrequencyParamsType NCsSound::NSpawn::NParams::FFrequency

				/** Sound information */
				FCsSound Sound;

				float VolumeMultiplier;

				float PitchMultiplier;

				/** Object for the Sound to spawn at or be attached to. */
				TWeakObjectPtr<UObject> Object;

				/** Parameters describing how often to spawn the Sound. */
				FrequencyParamsType FrequencyParams;

				/** The time group for which any coroutine spawning the Sound is associated with. */
				FECsUpdateGroup Group;

				FParams() :
					Sound(),
					VolumeMultiplier(1.0f),
					PitchMultiplier(1.0f),
					Object(nullptr),
					FrequencyParams(),
					Group()
				{
				}

				FORCEINLINE FrequencyParamsType* GetFrequencyParamsPtr() { return &FrequencyParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSound::FLog::Warning) const;

				UObject* GetObject() const;

				void Update();

				void Reset();

			#undef FrequencyParamsType
			};

			struct CSSOUND_API FResource : public TCsResourceContainer<FParams>
			{
			};

			#define CS_PARAMS_PAYLOAD_SIZE 32

			struct CSSOUND_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};

			#undef CS_PARAMS_PAYLOAD_SIZE
		}
	}
}

// NCsSound::NSpawn::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSound, NSpawn, NParams, FParams)

USTRUCT(BlueprintType)
struct CSSOUND_API FCsSound_Spawn_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound", meta = (UIMin = "0.001", ClampMin = "0.001"))
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound", meta = (UIMin = "0.001", ClampMin = "0.001"))
	float PitchMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	UObject* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FCsSound_Spawn_FrequencyParams FrequencyParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FECsUpdateGroup Group;

	FCsSound_Spawn_Params() :
		Sound(),
		VolumeMultiplier(1.0f),
		PitchMultiplier(1.0f),
		Object(nullptr),
		FrequencyParams(),
		Group()
	{
	}

#define ParamsType NCsSound::NSpawn::NParams::FParams
	void CopyToParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSound::FLog::Warning) const;
	void Update();
};