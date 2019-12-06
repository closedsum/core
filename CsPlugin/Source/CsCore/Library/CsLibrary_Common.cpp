// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Common.h"
#include "CsCore.h"

#include "Classes/Engine/World.h"

#include "Classes/Engine/GameInstance.h"

#include "Classes/Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"

UCsLibrary_Common::UCsLibrary_Common(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Player
#pragma region

void UCsLibrary_Common::GetAllLocalPlayerControllers(UWorld* World, TArray<APlayerController*>& OutControllers)
{
	UGameInstance* GameInstance = World->GetGameInstance();

	if (!GameInstance)
		return;

	for (auto It = GameInstance->GetLocalPlayerIterator(); It; ++It)
	{
		ULocalPlayer *Player = *It;

		if (Player->PlayerController)
			OutControllers.Add(Player->PlayerController);
	}
}

#pragma endregion Player