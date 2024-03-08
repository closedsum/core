// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Gesture/CsGesture.h"
#include "CsCore.h"

UCsGesture::UCsGesture(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsGesture::SetCurrentWorld(UWorld* InWorld) { CurrentWorld = InWorld; }
UWorld* UCsGesture::GetCurrentWorld() { return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr; }

bool UCsGesture::CanProcessInputs() { return true; }
void UCsGesture::ProcessInputs(FCsInputFrame* InputFrame){}