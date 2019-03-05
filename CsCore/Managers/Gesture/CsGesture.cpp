// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Gesture/CsGesture.h"
#include "CsCore.h"

UCsGesture::UCsGesture(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsGesture::SetCurrentWorld(UWorld* InWorld) { CurrentWorld = InWorld; }
UWorld* UCsGesture::GetCurrentWorld() { return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr; }

bool UCsGesture::CanProcessInputs() { return true; }
void UCsGesture::ProcessInputs(FCsInputFrame &InputFrame){}