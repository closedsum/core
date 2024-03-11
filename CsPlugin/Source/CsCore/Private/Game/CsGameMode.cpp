// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Game/CsGameMode.h"
#include "CsCore.h"

ACsGameMode::ACsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if !WITH_EDITOR
	bUseSeamlessTravel = true;
#endif // #if !WITH_EDITOR
}