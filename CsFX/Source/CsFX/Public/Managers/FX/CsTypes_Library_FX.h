// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Proxy.h"
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

struct CSFX_API EMCsFXSpawnFrequency : public TCsEnumMap<ECsFXSpawnFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsFXSpawnFrequency, ECsFXSpawnFrequency)
};

namespace NCsFXSpawnFrequency
{
	typedef ECsFXSpawnFrequency Type;

	namespace Ref
	{
		extern CSFX_API const Type Once;
		extern CSFX_API const Type Count;
		extern CSFX_API const Type TimeCount;
		extern CSFX_API const Type TimeInterval;
		extern CSFX_API const Type Infinite;
		extern CSFX_API const Type ECsFXSpawnFrequency_MAX;
	}

	extern CSFX_API const uint8 MAX;
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

		struct CSFX_API EMFrequency : public TCsEnumMap<EFrequency>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMFrequency, EFrequency)
		};

		namespace NFrequency
		{
			namespace Ref
			{
				typedef EFrequency Type;

				extern CSFX_API const Type Once;
				extern CSFX_API const Type Count;
				extern CSFX_API const Type TimeCount;
				extern CSFX_API const Type TimeInterval;
				extern CSFX_API const Type Infinite;
				extern CSFX_API const Type EFrequency_MAX;
			}

			extern CSFX_API const uint8 MAX;
		}
	}
}

#pragma endregion FXSpawnFrequency

// FCsFX_Spawn_FrequencyParams
#pragma region

struct FCsFX_Spawn_FrequencyParams;

// ParamsType (NCsFX::NSpawn::NParams::FFrequency)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FFrequency)

namespace NCsFX_Spawn_FrequenceParams
{
	using ThisType = FCsFX_Spawn_FrequencyParams;
	using ParamsType = NCsFX::NSpawn::NParams::FFrequency;
	using FrequencyType = NCsFX::NSpawn::EFrequency;

	// Separate implementation to allow for clearer use of aliases
	struct CSFX_API FImpl
	{
		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsFX::NSpawn::NParams::FFrequency)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FFrequency)

/**
* Parameters describing the frequency at which Spawn is called after calling Start.
*/
USTRUCT(BlueprintType)
struct CSFX_API FCsFX_Spawn_FrequencyParams
{
	GENERATED_USTRUCT_BODY()

private:

	CS_DECLARE_STATIC_LOG_WARNING

	using FrequencyType = ECsFXSpawnFrequency;

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

	using ParamsType = NCsFX::NSpawn::NParams::FFrequency;
	using _Impl = NCsFX_Spawn_FrequenceParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;

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
			struct CSFX_API FFrequency
			{
			private:

				CS_DECLARE_STATIC_LOG_WARNING

				using FrequencyType = NCsFX::NSpawn::EFrequency;

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
				bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;

				float CalculateTotalTime() const;

				void Reset();

				void Update();
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
			struct CSFX_API FParams
			{
			private:
		
				CS_DECLARE_STATIC_LOG_WARNING

				using FrequencyParamsType = NCsFX::NSpawn::NParams::FFrequency;

			public:

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
				bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;

				AActor* GetActor() const;

				void Update();

				void Reset();
			};

			struct CSFX_API FResource : public TCsResourceContainer<FParams>
			{
			};

			const int32 CS_PARAMS_PAYLOAD_SIZE = 256;

			struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};
		}
	}
}

using CsFXSpawnParamsType = NCsFX::NSpawn::NParams::FParams;

struct FCsFX_Spawn_Params;

// ParameterType (NCsFX::NSpawn::NParams::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FParams)

namespace NCsFX_Spawn_Params
{
	using ThisType = FCsFX_Spawn_Params;
	using ParamsType = NCsFX::NSpawn::NParams::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSFX_API FImpl
	{
	public:

		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// NCsFX::NSpawn::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsFX, NSpawn, NParams, FParams)

USTRUCT(BlueprintType)
struct CSFX_API FCsFX_Spawn_Params
{
	GENERATED_USTRUCT_BODY()

private:

	CS_DECLARE_STATIC_LOG_WARNING

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

	using ParamsType = NCsFX::NSpawn::NParams::FParams;
	using _Impl = NCsFX_Spawn_Params::FImpl;

	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const { _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;
	void Update();
	//void OnPostEditChange();
};

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NSetArrayFloatChecked
		{
			struct CSFX_API FPayload
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