// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsGameMode.h"
#include "CsCore.h"

ACsGameMode::ACsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if !WITH_EDITOR
	bUseSeamlessTravel = true;
#endif // #if !WITH_EDITOR
}