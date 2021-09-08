// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/CsLibrary_Coordinator_StatusEffect.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsStatusEffect
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NCoordinator::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NCoordinator::FLibrary, GetSafe);
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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsStatusEffect::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsCoordinator_StatusEffect* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot								  = GetContextRootChecked(Context, WorldContext);
			UCsCoordinator_StatusEffect* Coordinator_StatusEffect = UCsCoordinator_StatusEffect::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Coordinator_StatusEffect)
			return Coordinator_StatusEffect;
		}

		UCsCoordinator_StatusEffect* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_StatusEffect* Coordinator_StatusEffect = UCsCoordinator_StatusEffect::Get(ContextRoot);

			if (!Coordinator_StatusEffect)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_StatusEffect."), *Context));
			}
			return Coordinator_StatusEffect;
		}

		UCsCoordinator_StatusEffect* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsStatusEffect::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get
	}
}