// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"

// Managers
#include "Managers/SkeletalMesh/CsManager_SkeletalMeshActor.h"
// Library
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

#if WITH_EDITOR
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
// Game
#include "GameFramework/GameStateBase.h"
// World
#include "Engine/World.h"
#endif // #if WITH_EDITOR

namespace NCsSkeletalMeshActor
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NManager::FLibrary, SafeSpawn);
				}
			}
		}

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
				return nullptr;
			return GameState;
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* WorldContext)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

	#endif // #if WITH_EDITOR

		// Spawn
		#pragma region

		#define PooledPooledType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot)
		{
			// Get Context for Manager_SkeletalMeshActor
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = UCsManager_SkeletalMeshActor::Get(ContextRoot);
			// Allocate Payload
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());
			// Set Payload
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;

			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			return SpawnChecked(Context, WorldContext, PooledPayload, Shot);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, nullptr);
		}

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot)
		{
			// Get Context for Manager_SkeletalMeshActor
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = UCsManager_SkeletalMeshActor::Get(ContextRoot);
			// Allocate Payload
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());
			// Set Payload
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;

			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			return SpawnChecked(Context, WorldContext, PooledPayload, Shot);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(UObject* WorldContext, const PooledPooledType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, nullptr);
		}

		#undef ShotType

		#undef PooledPooledType

		#pragma endregion Spawn
	}
}