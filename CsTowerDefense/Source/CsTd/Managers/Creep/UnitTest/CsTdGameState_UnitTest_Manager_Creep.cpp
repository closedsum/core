// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/UnitTest/CsTdGameState_UnitTest_Manager_Creep.h"
#include "CsTd.h"

// Singleton
#include "Managers/Creep/UnitTest/CsTdManager_Singleton_GameState_UnitTest_Manager_Creep.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Creep/CsTdManager_Creep.h"
// Game
#include "Engine/GameInstance.h"


ACsTdGameState_UnitTest_Manager_Creep::ACsTdGameState_UnitTest_Manager_Creep(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// UObject Interface
#pragma region

void ACsTdGameState_UnitTest_Manager_Creep::BeginDestroy()
{
	Super::BeginDestroy();

	OnBeginDestroy_ShutdownSingletons();
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsTdGameState_UnitTest_Manager_Creep::BeginPlay()
{
	Super::BeginPlay();

	OnBeginPlay_SetupSingletons();
}

#pragma endregion AActor Interface

// Manager Singleton
#pragma region

void ACsTdGameState_UnitTest_Manager_Creep::ConstructManagerSingleton()
{
	Manager_Singleton = NewObject<UCsTdManager_Singleton_GameState_UnitTest_Manager_Creep>(GetGameInstance(), UCsTdManager_Singleton_GameState_UnitTest_Manager_Creep::StaticClass());
}

void ACsTdGameState_UnitTest_Manager_Creep::OnBeginPlay_SetupSingletons()
{
	ConstructManagerSingleton();

	UCsTdManager_Creep::Init(this, UCsTdManager_Creep::StaticClass(), GetGameInstance());
}

void ACsTdGameState_UnitTest_Manager_Creep::OnBeginDestroy_ShutdownSingletons()
{
	if (Manager_Singleton)
	{
		UCsTdManager_Creep::Shutdown(this);

		Manager_Singleton->MarkPendingKill();
		Manager_Singleton = nullptr;
	}
}

#pragma endregion Manager Singleton