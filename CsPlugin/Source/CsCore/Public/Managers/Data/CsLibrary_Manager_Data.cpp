// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Data/CsManager_Data.h"

#if WITH_EDITOR
// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsData
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsData::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Data* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Data)
			return Manager_Data;
		}

		UCsManager_Data* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlayback::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Data* Manager_Data = UCsManager_Data::Get(ContextRoot);

			if (!Manager_Data)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Data."), *Context));
			}
			return Manager_Data;
		}

		UCsManager_Data* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsData::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get
	}
}