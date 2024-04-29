// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Material/CsLibrary_Manager_Material.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Material/CsManager_Material.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameState.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsMaterial
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NManager::FLibrary, GetContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NManager::FLibrary, GetSafeContextRoot);
					CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsMaterial::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(ContextObject, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(ContextObject))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(ContextObject, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsMaterial::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Material* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot				  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Material* Manager_Material = UCsManager_Material::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Material)
			return Manager_Material;
		}

		UCsManager_Material* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Material* Manager_Material = UCsManager_Material::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Material)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Material."), *Context));
			}
			return Manager_Material;
		}

		UCsManager_Material* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsMaterial::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get
	}
}