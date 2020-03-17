// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/CsAIController.h"
#include "CsCoreDEPRECATED.h"

#include "AI/CsAIPlayerState.h"
#include "GameFramework/GameStateBase.h"

#include "Perception/AIPerceptionComponent.h"

ACsAIController::ACsAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsPlayerState = true;
	PlayerStateClass = ACsAIPlayerState::StaticClass();
}

void ACsAIController::OnConstructor(const FObjectInitializer& ObjectInitializer)
{
	if (UseAIPerceptionComponent)
		PerceptionComponent = ObjectInitializer.CreateDefaultSubobject<UAIPerceptionComponent>(this, TEXT("PerceptionComponent"));
}

// Copied from AController::InitPlayerState. Only change is PlayerStateClass.
void ACsAIController::InitPlayerState()
{
	if (GetNetMode() != NM_Client)
	{
		UWorld* const World = GetWorld();
		const AGameModeBase* GameMode = World ? World->GetAuthGameMode() : NULL;

		// If the GameMode is null, this might be a network client that's trying to
		// record a replay. Try to use the default game mode in this case so that
		// we can still spawn a PlayerState.
		if (GameMode == NULL)
		{
			const AGameStateBase* const GameState = World ? World->GetGameState() : NULL;
			GameMode = GameState ? GameState->GetDefaultGameMode() : NULL;
		}

		if (GameMode != NULL)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Owner = this;
			SpawnInfo.Instigator = GetInstigator();
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnInfo.ObjectFlags |= RF_Transient;	// We never want player states to save into a map
			PlayerState = World->SpawnActor<APlayerState>(PlayerStateClass, SpawnInfo);

			// force a default player name if necessary
			if (PlayerState && PlayerState->GetPlayerName().IsEmpty())
			{
				// don't call SetPlayerName() as that will broadcast entry messages but the GameMode hasn't had a chance
				// to potentially apply a player/bot name yet
				PlayerState->SetPlayerName(GameMode->DefaultPlayerName.ToString());
			}
		}
	}
}