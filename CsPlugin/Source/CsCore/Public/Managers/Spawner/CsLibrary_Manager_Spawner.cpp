// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Spawner/CsLibrary_Manager_Spawner.h"
#include "CsCore.h"

// Library
	// Game
#include "Game/CsLibrary_GameState.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Spawner/CsManager_Spawner.h"

namespace NCsSpawner
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Spawner* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			    = GetContextRootChecked(Context, WorldContext);
			UCsManager_Spawner* Manager_Spawner = UCsManager_Spawner::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Spawner)
			return Manager_Spawner;
		}

		UCsManager_Spawner* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Spawner* Manager_Spawner = UCsManager_Spawner::Get(ContextRoot);

			if (!Manager_Spawner)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Spawner."), *Context));
			}
			return Manager_Spawner;
		}

		UCsManager_Spawner* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsSpawner::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		namespace NModifier
		{
			#define ModifierResourceType NCsSpawner::NModifier::FResource
			#define ModifierType NCsSpawner::NModifier::IModifier
		
			ModifierResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsSpawnerModifier& Type)
			{
				typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

				return SpawnerManagerLibrary::GetChecked(Context, WorldContext)->AllocateModifier(Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsSpawnerModifier& Type, ModifierResourceType* Modifier)
			{
				typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

				SpawnerManagerLibrary::GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
			}

			const FECsSpawnerModifier& FLibrary::GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

				return SpawnerManagerLibrary::GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

				return SpawnerManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
			{
				typedef NCsSpawner::NManager::FLibrary SpawnerManagerLibrary;

				return SpawnerManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}

			#undef ModifierResourceType
			#undef ModifierType
		}
	}
}