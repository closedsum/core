// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
}

void ACsPlayerController::OnTickActor_HandleCVars(){}

// Camera
#pragma region

void ACsPlayerController::SetTargetActor(AActor* InActor)
{
	TargetActor = InActor;
}

AActor* ACsPlayerController::GetTargetActor()
{
	return TargetActor.IsValid() ? TargetActor.Get() : nullptr;
}


#pragma endregion Camera

// Input
#pragma region

int32 ACsPlayerController::GetCurrentInputActionMap()
{
	return Manager_Input->CurrentInputActionMap;
}

void ACsPlayerController::SetCurrentInputActionMap(const FECsInputActionMap& ActionMap)
{
	Manager_Input->SetCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::SetCurrentInputActionMap(const int32& ActionMap)
{
	Manager_Input->SetCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::ClearCurrentInputActionMap(const FECsInputActionMap& ActionMap)
{
	Manager_Input->ClearCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::ClearCurrentInputActionMap(const int32& ActionMap)
{
	Manager_Input->ClearCurrentInputActionMap(ActionMap);
}

void ACsPlayerController::InitInputSystem()
{
	Super::InitInputSystem();

	if (!Manager_Input)
	{
		Manager_Input = NewObject<UCsManager_Input>(this, ManagerInputClass.Get(), FName("Manager_Input"));
		Manager_Input->RegisterComponent();

		/*
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;

		Manager_Input = GetWorld()->SpawnActor<UCsManager_Input>(ManagerInputClass, SpawnInfo);
		Manager_Input->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Manager_Input);

		Manager_Input->MyOwner = this;

		Manager_Input->Init();
		Manager_Input->SetupInputComponent();
		BindDelegatesToInputManager();

		ULocalPlayer* LocalPlayer   = Cast<ULocalPlayer>(Player);
		Manager_Input->ControllerId = LocalPlayer->GetControllerId();

		Manager_Input->LoadInputProfile();

		Cast<UCsGameInstance>(GetGameInstance())->OnServerTravel_Event.AddUObject(Manager_Input, &UCsManager_Input::OnServerTravel);
		*/
	}
}

#pragma endregion Input