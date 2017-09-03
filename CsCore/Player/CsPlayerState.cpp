// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerState.h"
#include "CsCore.h"
#include "Game/CsGameState.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "Managers/CsManager_Loading.h"

#include "Player/CsPlayerController.h"

ACsPlayerState::ACsPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick				 = true;
	PrimaryActorTick.bStartWithTickEnabled		 = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}