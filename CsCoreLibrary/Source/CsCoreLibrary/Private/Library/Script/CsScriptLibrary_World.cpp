// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_World.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_World.h"
// Engine
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_World)

// Cached
#pragma region

namespace NCsScriptLibraryWorld
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_World, RemoveNetworkActor);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_World::UCsScriptLibrary_World(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


#define USING_NS_CACHED using namespace NCsScriptLibraryWorld::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryWorld::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

bool UCsScriptLibrary_World::IsPlayInEditorPreview(const UObject* WorldContextObject)
{
	return CsWorldLibrary::IsPlayInEditorPreview(WorldContextObject);
}

void UCsScriptLibrary_World::RemoveNetworkActor(const FString& Context, AActor* Actor)
{
	CONDITIONAL_SET_CTXT(RemoveNetworkActor);

	UWorld* World = CsWorldLibrary::GetSafe(Ctxt, Actor);

	if (!World)
	{
		UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to get World from Actor: %s."), *Ctxt, *(Actor->GetName()));
		return;
	}
	World->RemoveNetworkActor(Actor);
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT