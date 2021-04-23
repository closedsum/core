// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsLibrary_Manager_Sound.h"

// Library
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

namespace NCsSound
{
	namespace NManager
	{
		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			UWorld* World = WorldContext->GetWorld();

			checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

			/*
#if WITH_EDITOR
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditor(WorldContext->GetWorld()) ||
				WorldLibrary::IsPlayInEditorPreview(WorldContext->GetWorld()))
			{
				return WorldContext;
			}
			else
#endif // #if WITH_EDITOR
			{	
				return World->GetGameInstance();
			}
			*/
			AGameStateBase* GameState = World->GetGameState();

			checkf(GameState, TEXT("%s: Failed to get GameState from World: %s."), *Context, *(World->GetName()));

			return GameState;
		}

		const FCsSoundPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, const FCsSound& Sound)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			check(Sound.IsValidChecked(Context));

			typedef NCsSound::NPayload::FLibrary PayloadLibrary;
			typedef NCsSound::NPayload::IPayload PayloadType;

			UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(ContextRoot);
			// Allocate Payload
			PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set Payload
			PayloadLibrary::Set(Context, Payload, Sound);
			// Spawn
			return Manager_Sound->Spawn(Sound.Type, Payload);
		}
		
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		const FCsSoundPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsSound& Sound)
		{
		#undef PooledPayloadType

			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			check(Sound.IsValidChecked(Context));

			typedef NCsSound::NPayload::FLibrary PayloadLibrary;
			typedef NCsSound::NPayload::IPayload PayloadType;

			UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(ContextRoot);
			// Allocate Payload
			PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set Payload
			PayloadLibrary::Set(Context, Payload, PooledPayload, Sound);
			// Spawn
			return Manager_Sound->Spawn(Sound.Type, Payload);
		}
	}
}