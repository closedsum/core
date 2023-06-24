// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsTypes_Library_FX.generated.h"

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
		
			#define FrequencyParamsType NCsSpawner::NParams::FFrequency

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
	FCsSpawner_FrequencyParams FrequencyParams;

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