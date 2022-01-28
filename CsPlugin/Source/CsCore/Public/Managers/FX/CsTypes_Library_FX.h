// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
		
				/** FX information */
				FCsFX FX;

				/** Actor for the FX to spawn at or be attached to. */
				TWeakObjectPtr<AActor> Actor;

				/** Parameters describing how often to spawn the FX. */
				FCsSpawnerFrequencyParams FrequencyParams;

				/** The time group for which any coroutine spawning the FX is associated with. */
				FECsUpdateGroup Group;

				FParams() :
					FX(),
					Actor(nullptr),
					FrequencyParams(),
					Group()
				{
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				AActor* GetActor() const;

				void Update();

				void Reset();
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
	FCsSpawnerFrequencyParams FrequencyParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|FX")
	FECsUpdateGroup Group;

	FCsFX_Spawn_Params() :
		FX(),
		Actor(nullptr),
		FrequencyParams(),
		Group()
	{
	}

#define ParamsType NCsFX::NSpawn::NParams::FParams
	void CopyToParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	void Update();
	//void OnPostEditChange();
};