// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerController.h"
#include "CsCore.h"
#include "../Engine/Classes/Engine/LocalPlayer.h"
#include "Managers/Input/CsManager_Input.h"

ACsPlayerController::ACsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsPlayerController::OnTickActor_CheckCVars(){}

void ACsPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	if (!Manager_Input)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;

		Manager_Input = GetWorld()->SpawnActor<ACsManager_Input>(ManagerInputClass, SpawnInfo);
		Manager_Input->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Manager_Input);

		Manager_Input->InputOwner = this;

		Manager_Input->SetupInputComponent();
		BindDelegatesToInputManager();

		ULocalPlayer* LocalPlayer   = Cast<ULocalPlayer>(Player);
		Manager_Input->ControllerId = LocalPlayer->GetControllerId();

		Manager_Input->LoadInputProfile();
	}
}

void ACsPlayerController::BindDelegatesToInputManager(){}
void ACsPlayerController::UnBindPawnDelegatesFromInputManager(){}

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

bool ACsPlayerController::CanPostProcessInput() { return true; }

void ACsPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused){}