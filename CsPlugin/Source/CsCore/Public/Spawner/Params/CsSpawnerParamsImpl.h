// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Spawner
#include "Spawner/Params/CsSpawnerParams.h"

#include "CsSpawnerParamsImpl.generated.h"
#pragma once

// NCsSpawner::NParams::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NParams, FImpl)

USTRUCT(BlueprintType)
struct CSCORE_API FCsSpawnerParamsImpl
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the number of objects "created" when Spawn is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSpawnerCountParams CountParams;

	/** Describes how often objects are "created" whens Spawn is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSpawnerFrequencyParams FrequencyParams;

	/** The total time the objects are being spawned for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
		struct CSCORE_API FImpl final : public ParamsType
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