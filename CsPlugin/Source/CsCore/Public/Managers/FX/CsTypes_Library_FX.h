// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsTypes_Library_FX.generated.h"

// FXSpawnFrequency
#pragma region

/**
* The frequency at which a FX spawns.
*/
UENUM(BlueprintType)
enum class ECsFXSpawnFrequency : uint8
{
	/** The FX only spawned ONE time. */
	Once						UMETA(DisplayName = "Once"),
	/** The FX spawn a 'COUNT' number of times at a specified
		Interval. */
	Count						UMETA(DisplayName = "Count"),
	/** The FX spawns a 'COUNT' number of times over Time.
		The Interval of each Spawn is Time / COUNT. */
	TimeCount					UMETA(DisplayName = "Time Count"),
	/** The FX spawns a number of times equal to Time / Interval. */
	TimeInterval				UMETA(DisplayName = "Time Interval"),
	/** The FX spawns every Interval. */
	Infinite					UMETA(DisplayName = "Infinite"),
	ECsFXSpawnFrequency_MAX		UMETA(Hidden),
};

struct CSCORE_API EMCsFXSpawnFrequency : public TCsEnumMap<ECsFXSpawnFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXSpawnFrequency, ECsFXSpawnFrequency)
};

namespace NCsFXSpawnFrequency
{
	typedef ECsFXSpawnFrequency Type;

	namespace Ref
	{
		extern CSCORE_API const Type Once;
		extern CSCORE_API const Type Count;
		extern CSCORE_API const Type TimeCount;
		extern CSCORE_API const Type TimeInterval;
		extern CSCORE_API const Type Infinite;
		extern CSCORE_API const Type ECsFXSpawnFrequency_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsFX
{
	namespace NSpawn
	{
		/**
		* The frequency at which a FX spawns.
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
}

#pragma endregion FXSpawnFrequency

// FCsFX_Spawn_FrequencyParams
#pragma region

// NCsFX::NSpawn::NParams::FFrequency
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FFrequency)

/**
* Parameters describing the frequency at which Spawn is called after calling Start.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Spawn_FrequencyParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Trigger Frequency
		If Type == ECsFXSpawnFrequency::Once,
	     Ignore Count and Interval.
		If Type == ECsFXSpawnFrequency::Count,
	     Count should be > 0, if NOT, it will be treated
	     as ECsFXSpawnFrequency::Once.
		if Type == ECsFXSpawnFrequency::TimeCount,
		if Type == ECsFXSpawnFrequency::TimeInterval,
		If Type == ECsFXSpawnFrequency::Infinite,
	     Ignore Count and Interval should be > 0.0f. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params")
	ECsFXSpawnFrequency Type;

	/** The delay before calling Start.
		If Delay == 0.0f, Spawn will be called at a given interval.
		If Delay == 0.0f and Interval == 0.0f, Spawn will be called immediately. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Delay;

	/** The number of times to call Spawn after Start is called.
		Only valid if 
		 Type == ECsFXSpawnFrequency::Count
		 Type == ECsFXSpawnFrequency::TimeCount
		Should be > 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0", UIMin = "0"))
	int32 Count;

	/** The time between each Spawn call after Start is called.
		Only valid if,
		Type == ECsFXSpawnFrequency::Count
		Type == ECsFXSpawnFrequency::TimeInterval
		Type == ECsFXSpawnFrequency::Infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Interval;

	/** The total time for Spawning. 
		Only valid if,
		Type == ECsFXSpawnFrequency::Count
		Type == ECsFXSpawnFrequency::TimeCount
		Type == ECsFXSpawnFrequency::TimeInterval */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Spawner|Params", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Time;

	FCsFX_Spawn_FrequencyParams() :
		Type(ECsFXSpawnFrequency::Once),
		Delay(0.0f),
		Count(0),
		Interval(0.0f),
		Time(0.0f)
	{
	}

#define ParamsType NCsFX::NSpawn::NParams::FFrequency
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
 
namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			struct CSCORE_API FFrequency
			{
			#define FrequencyType NCsFX::NSpawn::EFrequency

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
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				float CalculateTotalTime() const;

				void Reset();

				void Update();

			#undef FrequencyType
			};
		}
	}
}

#pragma endregion FCsFX_Spawn_FrequencyParams

class AActor;

namespace NCsFX
{
	namespace NSpawn
	{
		namespace NParams
		{
			// TODO: Later make an interface?
			struct CSCORE_API FParams
			{
			public:
		
			#define FrequencyParamsType NCsFX::NSpawn::NParams::FFrequency

				/** FX information */
				FCsFX FX;

				/** Actor for the FX to spawn at or be attached to. */
				TWeakObjectPtr<AActor> Actor;

				/** Delay before starting spawn. */
				float Delay;

				/** Parameters describing how often to spawn the FX. */
				FrequencyParamsType FrequencyParams;

				/** The time group for which any coroutine spawning the FX is associated with. */
				FECsUpdateGroup Group;

				FParams() :
					FX(),
					Actor(nullptr),
					Delay(0.0f),
					FrequencyParams(),
					Group()
				{
				}

				FORCEINLINE FrequencyParamsType* GetFrequencyParamsPtr() { return &FrequencyParams; }

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				AActor* GetActor() const;

				void Update();

				void Reset();

			#undef FrequencyParamsType
			};

			struct CSCORE_API FResource : public TCsResourceContainer<FParams>
			{
			};

			#define CS_PARAMS_PAYLOAD_SIZE 256

			struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};

			#undef CS_PARAMS_PAYLOAD_SIZE
		}
	}
}

// NCsFX::NSpawn::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsFX_Spawn_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FCsFX FX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	float Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FCsFX_Spawn_FrequencyParams FrequencyParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FECsUpdateGroup Group;

	FCsFX_Spawn_Params() :
		FX(),
		Actor(nullptr),
		Delay(0.0f),
		FrequencyParams(),
		Group()
	{
	}

#define ParamsType NCsFX::NSpawn::NParams::FParams
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	void Update();
	//void OnPostEditChange();
};

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NSetArrayFloatChecked
		{
			struct CSCORE_API FPayload
			{
			public:

				bool bComplete;

				int32 Count;

				int32 Stride;

				TArray<int32> Indices;

				TArray<float> Values;

				FPayload() :
					bComplete(false),
					Count(0),
					Stride(0),
					Indices(),
					Values()
				{
				}

				void SetSize(const int32& InSize, const int32& InStride)
				{
					check(InSize > 0);
					check(InStride > 0);

					Indices.Reset(InSize);

					for (int32 I = 0; I < InSize; ++I)
					{
						Indices.Add(INDEX_NONE);
					}

					Stride = InStride;

					const int32 ValuesSize = Stride * InSize;

					Values.Reset(ValuesSize);

					for (int32 I = 0; I < ValuesSize; ++I)
					{
						Values.Add(0.0f);
					}
				}

				FORCEINLINE void Start() { bComplete = false; }
				FORCEINLINE bool IsComplete() const { return bComplete; }
				FORCEINLINE void Complete() { bComplete = true; }

				FORCEINLINE void Clear() 
				{ 
					Count = 0;
				}

				bool IsValidChecked(const FString& Context) const;
			};
		}
	}
}