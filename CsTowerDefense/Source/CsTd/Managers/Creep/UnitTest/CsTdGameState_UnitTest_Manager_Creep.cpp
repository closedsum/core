// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/UnitTest/CsTdGameState_UnitTest_Manager_Creep.h"
#include "CsTd.h"

// Singleton
#include "Managers/Creep/UnitTest/CsTdManager_Singleton_GameState_UnitTest_Manager_Creep.h"
// Managers
#include "Managers/UnitTest/CsManager_UnitTest.h"
#include "Managers/Creep/CsTdManager_Creep.h"
// Game
#include "Engine/GameInstance.h"
// Unit Test
#include "Managers/Creep/UnitTest/CsTdUnitTestPlan_Manager_Creep.h"


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

	// TODO: Add checks for: UCsManager_UnitTest, UCsCoroutineScheduler, UCsManager_Time

	//UCsTdManager_Creep::Init(this, UCsTdManager_Creep::StaticClass(), GetGameInstance());
	//UCsManager_UnitTest::Init(this, GetGameInstance());

	// Setup
	{
		UCsManager_UnitTest::Get(GetGameInstance())->Add<FCsTdUnitTestPlan_Manager_Creep>();
	}

	UCsManager_UnitTest::Get(GetGameInstance())->Start();
}

void ACsTdGameState_UnitTest_Manager_Creep::OnBeginDestroy_ShutdownSingletons()
{
	if (Manager_Singleton)
	{
		if (UCsTdManager_Creep::IsValid(this))
			UCsTdManager_Creep::Shutdown(this);

		Manager_Singleton = nullptr;
	}
}

#pragma endregion Manager Singleton