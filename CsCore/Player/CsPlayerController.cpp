// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerController.h"
#include "CsCore.h"
#include "Managers/Input/CsManager_Input.h"

ACsPlayerController::ACsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsPlayerController::OnTickActor_CheckCVars()
{

}

void ACsPlayerController::BuildInputStack(TArray<UInputComponent*>& InputStack)
{
	Super::BuildInputStack(InputStack);

	if (Manager_Input &&
		Manager_Input->InputComponent)
	{
		InputStack.Push(Manager_Input->InputComponent);
	}
}

void ACsPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (Manager_Input &&
		Manager_Input->InputComponent)
	{
		Manager_Input->PreProcessInput(DeltaTime, bGamePaused);
	}
}

void ACsPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
}