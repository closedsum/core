// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Common.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
// Engine
#include "Engine/World.h"
#include "Engine/GameInstance.h"

// Cached
#pragma region

namespace NCsScriptLibraryCommon
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Common, GetGameInstanceFromContext);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Common::UCsScriptLibrary_Common(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryCommon::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryCommon::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define GameInstanceLibrary NCsGameInstance::FLibrary

UGameInstance* UCsScriptLibrary_Common::GetGameInstanceFromContext(const FString& Context, const UObject* WorldContextObject)
{
	CONDITIONAL_SET_CTXT(GetGameInstanceFromContext);

	return GameInstanceLibrary::GetSafe(Ctxt, WorldContextObject);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef GameInstanceLibrary
