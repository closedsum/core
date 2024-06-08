// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

#include "CsWorld_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsWorld_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsWorld_Delegates_STUB()
	{
	}
};

class UWorld;
class AGameModeBase;

namespace NCsWorld
{
	/** 
	* NOTE: This mimics UWorld::InitializationValues.
	*		The intent is NOT have to include World.h
	* Struct containing a collection of optional parameters for initialization of a World. 
	*/
	struct InitializationValues
	{
		InitializationValues()
			: bInitializeScenes(true)
			, bAllowAudioPlayback(true)
			, bRequiresHitProxies(true)
			, bCreatePhysicsScene(true)
			, bCreateNavigation(true)
			, bCreateAISystem(true)
			, bShouldSimulatePhysics(true)
			, bEnableTraceCollision(false)
			, bForceUseMovementComponentInNonGameWorld(false)
			, bTransactional(true)
			, bCreateFXSystem(true)
			, bCreateWorldPartition(false)
		{
		}

		/** Should the scenes (physics, rendering) be created. */
		uint32 bInitializeScenes:1;

		/** Are sounds allowed to be generated from this world. */
		uint32 bAllowAudioPlayback:1;

		/** Should the render scene create hit proxies. */
		uint32 bRequiresHitProxies:1;

		/** Should the physics scene be created. bInitializeScenes must be true for this to be considered. */
		uint32 bCreatePhysicsScene:1;

		/** Should the navigation system be created for this world. */
		uint32 bCreateNavigation:1;

		/** Should the AI system be created for this world. */
		uint32 bCreateAISystem:1;

		/** Should physics be simulated in this world. */
		uint32 bShouldSimulatePhysics:1;

		/** Are collision trace calls valid within this world. */
		uint32 bEnableTraceCollision:1;

		/** Special flag to enable movement component in non game worlds (see UMovementComponent::OnRegister) */
		uint32 bForceUseMovementComponentInNonGameWorld:1;

		/** Should actions performed to objects in this world be saved to the transaction buffer. */
		uint32 bTransactional:1;

		/** Should the FX system be created for this world. */
		uint32 bCreateFXSystem:1;

		/** Should the world be partitioned */
		uint32 bCreateWorldPartition:1;

		/** The default game mode for this world (if any) */
		TSubclassOf<AGameModeBase> DefaultGameMode;
	};

	struct CSCORE_API FDelegates
	{
	public:

		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostWorldInitialization, UWorld* /*World*/, const NCsWorld::InitializationValues& /*IVS*/);
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnPostWorldInitialization_Simple, UWorld* /*World*/);

		static FOnPostWorldInitialization OnPostWorldInitialization_Event;
		static FOnPostWorldInitialization_Simple OnPostWorldInitialization_Simple_Event;
	};
}