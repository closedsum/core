// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerController.h"
#include "CsCore.h"
#include "../Engine/Classes/Engine/LocalPlayer.h"

// Managers
#include "Managers/Input/CsManager_Input.h"
// Game
#include "Game/CsGameInstance.h"

ACsPlayerController::ACsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor	   = false;
	bEnableClickEvents	   = true;
	bEnableMouseOverEvents = true;
}

void ACsPlayerController::Destroyed()
{
	Super::Destroyed();

	if (!Manager_Input && !Manager_Input->IsPendingKill())
		Manager_Input->Destroy();
}

void ACsPlayerController::OnTickActor_HandleCVars(){}

// Input
#pragma region

int32 ACsPlayerController::GetCurrentInputActionMap()
{
	return Manager_Input->CurrentInputActionMap;
}

void ACsPlayerController::SetCurrentInputActionMap(const TCsInputActionMap &ActionMap)
{
	Manager_Input->SetCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::SetCurrentInputActionMap(const int32 &ActionMap)
{
	Manager_Input->SetCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::ClearCurrentInputActionMap(const TCsInputActionMap &ActionMap)
{
	Manager_Input->ClearCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::ClearCurrentInputActionMap(const int32 &ActionMap)
{
	Manager_Input->ClearCurrentInputActionMap(ActionMap);
}

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

		Manager_Input->Init();
		Manager_Input->SetupInputComponent();
		BindDelegatesToInputManager();

		ULocalPlayer* LocalPlayer   = Cast<ULocalPlayer>(Player);
		Manager_Input->ControllerId = LocalPlayer->GetControllerId();

		Manager_Input->LoadInputProfile();

		Cast<UCsGameInstance>(GetGameInstance())->OnServerTravel_Event.AddUObject(Manager_Input, &ACsManager_Input::OnServerTravel);
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

#pragma endregion Input