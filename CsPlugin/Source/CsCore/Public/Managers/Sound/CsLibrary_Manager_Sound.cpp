// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsLibrary_Manager_Sound.h"

// Library
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsSound
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::NManager::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::NManager::FLibrary, SafeSpawn);
				}
			}
		}

		// Print
		#pragma region

		FString FLibrary::PrintObjectWithClass(const UCsManager_Sound* Manager)
		{
			return FString::Printf(TEXT("%s: with Class: %s"), *(Manager->GetName()), *(Manager->GetClass()->GetName()));
		}

		#pragma endregion Print

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
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
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsSound::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Sound* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		    = GetContextRootChecked(Context, ContextObject);
			UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Sound)
			return Manager_Sound;
		}

		UCsManager_Sound* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(ContextRoot);

			if (!Manager_Sound)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Sound."), *Context));
			}
			return Manager_Sound;
		}

		UCsManager_Sound* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsSound::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get
		
		// Pool
		#pragma region

			// Find
		#pragma region

		const FCsSoundPooled* FLibrary::FindSafeObject(const FString& Context, const UObject* WorldContext, const FECsSound& Type, const int32& Index, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Sound* Manager_Sound = GetSafe(Context, WorldContext, Log))
			{
				CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsSound, FECsSound, Type)

				if (Index < 0 || Index >= Manager_Sound->GetPoolSize(Type))
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Index: %d is NOT [0, %d] Inclusive."), *Context, Index, Manager_Sound->GetPoolSize(Type)));
					return nullptr;
				}
				return Manager_Sound->FindSafeObject(Type, Index);
			}
			return nullptr;
		}

		#pragma endregion Find

		#pragma endregion Pool

		// Spawn
		#pragma region

		const FCsSoundPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FCsSound& Sound)
		{
			CS_IS_VALID_CHECKED(Sound);

			UCsManager_Sound* Manager_Sound = GetChecked(Context, WorldContext);

			typedef NCsSound::NPayload::FLibrary PayloadLibrary;
			typedef NCsSound::NPayload::IPayload PayloadType;

			// Allocate Payload
			PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set Payload
			PayloadLibrary::SetChecked(Context, Payload, Sound);
			// Spawn
			return Manager_Sound->Spawn(Sound.Type, Payload);
		}
		
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		const FCsSoundPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/)
		{
			CS_IS_VALID_CHECKED(Sound);

			UCsManager_Sound* Manager_Sound = GetChecked(Context, WorldContext);

			typedef NCsSound::NPayload::FLibrary PayloadLibrary;
			typedef NCsSound::NPayload::IPayload PayloadType;

			// Allocate Payload
			PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
			// Set Payload
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Sound, Transform);
			// Spawn
			return Manager_Sound->Spawn(Sound.Type, Payload);
		}

		const FCsSoundPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const FCsSound& Sound, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_VALID_RET_NULL(Sound)

			if (UCsManager_Sound* Manager_Sound = GetSafe(Context, WorldContext, Log))
			{
				typedef NCsSound::NPayload::FLibrary PayloadLibrary;
				typedef NCsSound::NPayload::IPayload PayloadType;

				// Allocate Payload
				PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
				// Set Payload
				if (!PayloadLibrary::SetSafe(Context, Payload, Sound))
					return nullptr;
				// Spawn
				return Manager_Sound->Spawn(Sound.Type, Payload);
			}
			return nullptr;
		}

		#undef PooledPayloadType

		#pragma endregion Spawn
	}
}