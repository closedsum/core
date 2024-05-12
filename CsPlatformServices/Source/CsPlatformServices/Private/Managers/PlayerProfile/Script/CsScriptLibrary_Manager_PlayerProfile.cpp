// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/PlayerProfile/Script/CsScriptLibrary_Manager_PlayerProfile.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/PlayerProfile/CsLibrary_Manager_PlayerProfile.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_PlayerProfile)

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

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerPlayerProfile::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerPlayerProfile::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define PlayerProfileManagerLibrary NCsPlayer::NProfile::NManager::FLibrary

bool UCsScriptLibrary_Manager_PlayerProfile::SetCurrentActiveProfile(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& ProfileType)
{
	CONDITIONAL_SET_CTXT(SetCurrentActiveProfile);

	return PlayerProfileManagerLibrary::SetSafeCurrentActiveProfile(Ctxt, WorldContextObject, ProfileType);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef PlayerProfileManagerLibrary