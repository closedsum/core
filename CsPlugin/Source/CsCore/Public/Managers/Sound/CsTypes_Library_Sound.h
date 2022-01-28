// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Sound/CsTypes_Sound.h"
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

#include "CsTypes_Library_Sound.generated.h"

class UObject;

namespace NCsSound
{
	namespace NSpawn
	{
		namespace NParams
		{
			// TODO: Later make an interface?
			struct CSCORE_API FParams
			{
			public:
		
				/** Sound information */
				FCsSound Sound;

				/** Object for the Sound to spawn at or be attached to. */
				TWeakObjectPtr<UObject> Object;

				/** Parameters describing how often to spawn the Sound. */
				FCsSpawnerFrequencyParams FrequencyParams;

				/** The time group for which any coroutine spawning the Sound is associated with. */
				FECsUpdateGroup Group;

				FParams() :
					Sound(),
					Object(nullptr),
					FrequencyParams(),
					Group()
				{
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				UObject* GetObject() const;

				void Update();

				void Reset();
			};

			struct CSCORE_API FResource : public TCsResourceContainer<FParams>
			{
			};

			#define CS_PARAMS_PAYLOAD_SIZE 32

			struct CSCORE_API FManager : public NCsResource::NManager::NValue::TFixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};

			#undef CS_PARAMS_PAYLOAD_SIZE
		}
	}
}

// NCsSound::NSpawn::NParams::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSound, NSpawn, NParams, FParams)

USTRUCT(BlueprintType)
struct CSCORE_API FCsSound_Spawn_Params
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FCsSound Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	UObject* Object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FCsSpawnerFrequencyParams FrequencyParams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Sound")
	FECsUpdateGroup Group;

	FCsSound_Spawn_Params() :
		Sound(),
		Object(nullptr),
		FrequencyParams(),
		Group()
	{
	}

#define ParamsType NCsSound::NSpawn::NParams::FParams
	void CopyToParams(ParamsType* Params) const;
#undef ParamsType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
	void Update();
};