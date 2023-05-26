// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/Script/CsScriptLibrary_GameInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"

// Cached
#pragma region

namespace NCsScriptLibraryGameInstance
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_GameInstance, IsMobilePreviewEditor);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_GameInstance::UCsScriptLibrary_GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_GameInstance::IsMobilePreviewEditor(const FString& Context, const UObject* WorldContextObject)
{
	using namespace NCsScriptLibraryGameInstance::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::IsMobilePreviewEditor : Context;

	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	return GameInstanceLibrary::SafeIsMobilePreviewEditor(Ctxt, WorldContextObject);
}