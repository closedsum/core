// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

namespace NCsFX
{
	namespace NManager
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext)
		{
			if (!WorldContext)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: WorldContext is NULL."), *Context);
				return nullptr;
			}

			UWorld* World = WorldContext->GetWorld();

			if (!World)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));
				return nullptr;
			}

			AGameStateBase* GameState = World->GetGameState();

			if (!GameState)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));
			}
			return GameState;
		}

	#endif // #if WITH_EDITOR

		#define PayloadImplType NCsFX::NPayload::FImpl
		PayloadImplType* FLibrary::AllocatePayloadChecked(const FString& Context, UObject* WorldContext, const FECsFX& Type, const FCsFX& FX)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

			PayloadImplType* Payload = Manager_FX->AllocatePayload<PayloadImplType>(Type);

			typedef NCsFX::NPayload::FLibrary PayloadLibrary;

			PayloadLibrary::SetChecked(Context, Payload, FX);

			//for ()

			return Payload;
		}
		#undef PayloadImplType
	}
}