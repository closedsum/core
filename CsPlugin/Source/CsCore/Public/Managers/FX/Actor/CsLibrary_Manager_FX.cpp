// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"
#endif // #if WITH_EDITOR

namespace NCsFX
{
	namespace NManager
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);

			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			AGameStateBase* GameState = World->GetGameState();

			if (!GameState)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName())));
			}
			return GameState;
		}

	#endif // #if WITH_EDITOR

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		const FCsFXActorPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
		#undef PooledPayloadType

			// Get Context for Manager_FX
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);
			// Allocate Payload
			typedef NCsFX::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_FX->AllocatePayload<PayloadImplType>(FX.Type);
			// Set Payload
			typedef NCsFX::NPayload::FLibrary PayloadLibrary;

			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, FX);

			// Int
			for (const FCsFXParameterInt& Param : FX.IntParameters)
			{
				typedef NCsFX::NParameter::NInt::FIntType ParameterIntType;

				ParameterIntType* IntType = Manager_FX->AllocateValue<ParameterIntType>();

				Payload->Parameters.Add(IntType);
			}
			// Float

			// Vector

			return Manager_FX->Spawn(FX.Type, Payload);
		}
	}
}