// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Spawner
#include "Params/CsSpawnerParams.h"

#include "CsSpawnerParamsImpl.generated.h"

// NCsSpawner::NParams::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FImpl)

USTRUCT(BlueprintType)
struct CSSPAWNER_API FCsSpawnerParamsImpl
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the number of objects "created" when Spawn is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	FCsSpawner_CountParams CountParams;

	/** Describes how often objects are "created" whens Spawn is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	FCsSpawner_FrequencyParams FrequencyParams;

	/** The total time the objects are being spawned for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Spawner|Params")
	float TotalTime;

	FCsSpawnerParamsImpl() :
		CountParams(),
		FrequencyParams(),
		TotalTime(0.0f)
	{
	}

	void Update()
	{
		FrequencyParams.Update();
	}

#define ParamsType NCsSpawner::NParams::FImpl
	ParamsType* ConstructParamsImpl() const;
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsSpawner
{
	namespace NParams
	{
	#define ParamsType NCsSpawner::NParams::IParams

		/**
		* Implements the interface ParamsType (NCsSpawner::NParams::IParmas)
		* and describes any information regarding the act of spawning an object.
		* i.e. Count, Frequency, Time, ... etc.
		*/
		struct CSSPAWNER_API FImpl final : public ParamsType
		{
		public:

			static const FName Name;

		#define CountParamsType NCsSpawner::NParams::FCount
		#define FrequencyParamsType NCsSpawner::NParams::FFrequency

		private:

			FCsInterfaceMap* InterfaceMap;

		public:

			// ParamsType (NCsSpawner::NParams::IParams)

			CountParamsType CountParams;

			FrequencyParamsType FrequencyParams;

			float TotalTime;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			FORCEINLINE CountParamsType* GetCountParamsPtr() { return &CountParams; }
			FORCEINLINE FrequencyParamsType* GetFrequencyParamsPtr() { return &FrequencyParams; }
			FORCEINLINE float* GetTotalTimePtr() { return &TotalTime; }

		// ParamsType (NCsSpawner::NParams::IParams)
		#pragma region
		public:

			FORCEINLINE const CountParamsType& GetCountParams() const { return CountParams; }
			FORCEINLINE const FrequencyParamsType& GetFrequencyParams() const { return FrequencyParams; }
			FORCEINLINE const float& GetTotalTime() const { return TotalTime; }

		#pragma endregion ParamsType (NCsSpawner::NParams::IParams)

		public:

			static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsSpawner::NParams::FImpl*>(Ptr);
			}

			bool IsValidChecked(const FString& Context) const;
			static bool IsValidChecked(const FString& Context, ParamsType* Params);
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#undef CountParamsType
		#undef FrequencyParamsType
		};

	#undef ParamsType
	}
}