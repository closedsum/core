// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "World/CsWorld_Delegates_Internal.h"

// Types
#include "World/CsWorld_Delegates.h"

namespace NCsWorld
{
	namespace NDelegates
	{
		void FInternal::Init()
		{
			FWorldDelegates::OnPostWorldInitialization.Remove(OnPostWorldInitializationHandle);
			OnPostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddStatic(&NCsWorld::NDelegates::FInternal::OnPostWorldInitialization);
		}

		void FInternal::OnPostWorldInitialization(UWorld* World, const UWorld::InitializationValues IVS)
		{
			typedef NCsWorld::InitializationValues IVSType;

			IVSType OtherIVS;
			OtherIVS.bInitializeScenes = IVS.bInitializeScenes;
			OtherIVS.bAllowAudioPlayback = IVS.bAllowAudioPlayback;
			OtherIVS.bRequiresHitProxies = IVS.bRequiresHitProxies;
			OtherIVS.bCreatePhysicsScene = IVS.bCreatePhysicsScene;
			OtherIVS.bCreateNavigation = IVS.bCreateNavigation;
			OtherIVS.bCreateAISystem = IVS.bCreateAISystem;
			OtherIVS.bShouldSimulatePhysics = IVS.bShouldSimulatePhysics;
			OtherIVS.bEnableTraceCollision = IVS.bEnableTraceCollision;
			OtherIVS.bForceUseMovementComponentInNonGameWorld = IVS.bForceUseMovementComponentInNonGameWorld;
			OtherIVS.bTransactional = IVS.bTransactional;
			OtherIVS.bCreateFXSystem = IVS.bCreateFXSystem;
			OtherIVS.bCreateWorldPartition = IVS.bCreateWorldPartition;

			NCsWorld::FDelegates::OnPostWorldInitialization_Event.Broadcast(World, OtherIVS);
			NCsWorld::FDelegates::OnPostWorldInitialization_Simple_Event.Broadcast(World);
		}
	}
}