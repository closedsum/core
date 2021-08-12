// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsLibrary_Manager_Damage.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsDamage
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NManager::FLibrary, GetSafe);
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

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsDamage::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Damage* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Damage)
			return Manager_Damage;
		}

		UCsManager_Damage* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

			if (!Manager_Damage)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Damage."), *Context));
			}
			return Manager_Damage;
		}

		UCsManager_Damage* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsDamage::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get
		
		// Modifier
		#pragma region

		#define ModifierResourceType NCsDamage::NModifier::FResource
		#define ModifierType NCsDamage::NModifier::IModifier
		void FLibrary::CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To)
		{
		#undef ModifierResourceType
		#undef ModifierType

			GetChecked(Context, WorldContext)->CreateCopyOfModifiers(Context, From, To);
		}

		

		#pragma endregion Modifier

		// Data
		#pragma region

		#define DataType NCsDamage::NData::IData
		#define ModifierResourceType NCsDamage::NModifier::FResource
		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers)
		{
		#undef DataType
		#undef ModifierResourceType

			GetChecked(Context, WorldContext)->ProcessData(Context, Data, Instigator, Causer, HitResult, Modifiers);
		}

		#pragma endregion Data
	}
}