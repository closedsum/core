// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Input.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"
#include "Managers/Input/CsGetManagerInput.h"
// Player
#include "GameFramework/PlayerController.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"
#include "Engine/Engine.h"

UCsScriptLibrary_Input::UCsScriptLibrary_Input(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Input::SetFirstLocalPlayerInputActionMap(const UObject* WorldContextObject, const FECsInputActionMap& Map)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (APlayerController* PlayerController = GEngine->GetFirstLocalPlayerController(World))
		{
			if (ICsGetManagerInput* GetManagerInput = Cast<ICsGetManagerInput>(PlayerController))
			{
				if (UCsManager_Input* Manager_Input = GetManagerInput->GetManager_Input())
				{
					Manager_Input->SetCurrentInputActionMap(Map);
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Input::SetFirstLocalPlayerInputActionMap: PlayerController: %s does NOT contain a reference a Manager_Input of type: UCsManager_Input."), *(PlayerController->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Input::SetFirstLocalPlayerInputActionMap: PlayerController: %s fails to implement interface: ICsGetManagerInput."), *(PlayerController->GetName()));
			}
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Input::SetFirstLocalPlayerInputActionMap: Failed to get PlayerController from World."))
		}
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Input::SetFirstLocalPlayerInputActionMap: Failed to get World from WorldContextObject."));
	}
}
