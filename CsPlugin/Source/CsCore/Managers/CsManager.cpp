// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsManager.h"
#include "CsCore.h"

ACsManager::ACsManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	SetReplicatingMovement(false);
}