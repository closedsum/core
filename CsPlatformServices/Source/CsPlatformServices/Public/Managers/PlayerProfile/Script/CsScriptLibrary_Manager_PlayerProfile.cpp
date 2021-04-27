// Copyright 2018 Respawn Entertainment, Inc. All rights reserved.

#include "Managers/PlayerProfile/Script/CsScriptLibrary_Manager_PlayerProfile.h"
#include "CsPlatformServices.h"

// Library
#include "Managers/PlayerProfile/CsLibrary_Manager_PlayerProfile.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerPlayerProfile
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_PlayerProfile, SetCurrentActiveProfile);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_PlayerProfile::UCsScriptLibrary_Manager_PlayerProfile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UCsScriptLibrary_Manager_PlayerProfile::SetCurrentActiveProfile(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& ProfileType)
{
	using namespace NCsScriptLibraryManagerPlayerProfile::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetCurrentActiveProfile : Context;

	typedef NCsPlayer::NProfile::NManager::FLibrary PlayerProfileManagerLibrary;

	PlayerProfileManagerLibrary::SetSafeCurrentActiveProfile(Ctxt, WorldContextObject, ProfileType);
}