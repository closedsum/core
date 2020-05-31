// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Creep/UnitTest/Game/CsTdGameMode_UnitTest_Manager_Creep.h"
#include "CsTd.h"

// Game
#include "Managers/Creep/UnitTest/Game/CsTdGameState_UnitTest_Manager_Creep.h"

ACsTdGameMode_UnitTest_Manager_Creep::ACsTdGameMode_UnitTest_Manager_Creep(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//DefaultPawnClass = ADefaultPawn::StaticClass();
	//PlayerControllerClass = APlayerController::StaticClass();
	//PlayerStateClass = APlayerState::StaticClass();
	GameStateClass = ACsTdGameState_UnitTest_Manager_Creep::StaticClass();
	//HUDClass = AHUD::StaticClass();
	//GameSessionClass = AGameSession::StaticClass();
	//SpectatorClass = ASpectatorPawn::StaticClass();
	//ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
	//ServerStatReplicatorClass = AServerStatReplicator::StaticClass();
}