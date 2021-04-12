// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Spawner/Params/CsTypes_SpawnerParams.h"
#include "Managers/Time/CsTypes_Update.h"
// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

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
				bool IsValid(const FString& Context) const;

				AActor* GetActor() const;

				void Update();

				void Reset();
			};

			struct CSCORE_API FResource : public TCsResourceContainer<FParams>
			{
			};

			#define CS_PARAMS_PAYLOAD_SIZE 256

			struct CSCORE_API FManager : public TCsManager_ResourceValueType_Fixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
			{
			};

			#undef CS_PARAMS_PAYLOAD_SIZE
		}
	}
}