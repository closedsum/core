// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Script/CsScriptLibrary_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/CsLibrary_FX.h"

// Cached
#pragma region

namespace NCsScriptLibraryFX
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_FX, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_FX::UCsScriptLibrary_FX(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UNiagaraSystem* UCsScriptLibrary_FX::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	return nullptr;
}

UNiagaraSystem* UCsScriptLibrary_FX::LoadByStringPath(const FString& Context, const FString& Path)
{
	return nullptr;
}

FCsRoutineHandle UCsScriptLibrary_FX::Spawn(const FString& Context, UObject* WorldContextObject, const FCsScriptLibrary_FX_Spawn_Params& Params)
{
	using namespace NCsScriptLibraryFX::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;

	return FCsRoutineHandle::Invalid;
}