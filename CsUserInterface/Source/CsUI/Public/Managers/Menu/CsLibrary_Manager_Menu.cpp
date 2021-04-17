// Copyright 2019 Respawn Entertainment, Inc. All rights reserved.
#include "Managers/Menu/CsLibrary_Manager_Menu.h"
#include "CsUI.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
// Game
#include "Engine/GameInstance.h"
#endif // #if WITH_EDITOR

namespace NCsMenu
{
	namespace NManager
	{
	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetChecked(Context, ContextObject);
		}

	#endif // #if WITH_EDITOR
	}
}