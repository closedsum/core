// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsLibrary_Manager_Javascript.h"

// Types
#include "Types/CsTypes_Macro.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
// Game
#include "Engine/GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsJs
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsJs::NManager::FLibrary, GetSafeContextRoot);
				}
			}
		}

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
		{
			using namespace NCsJs::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

	#endif // #if WITH_EDITOR

		UObject* FLibrary::GetEngineContextRoot()
		{
			return GEngine;
		}
	}
}