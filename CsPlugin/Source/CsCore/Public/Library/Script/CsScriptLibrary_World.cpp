// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_World.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
// Engine
#include "Engine/World.h"

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

#define WorldLibrary NCsWorld::FLibrary

bool UCsScriptLibrary_World::IsPlayInEditorPreview(const UObject* WorldContextObject)
{
	return WorldLibrary::IsPlayInEditorPreview(WorldContextObject);
}

void UCsScriptLibrary_World::RemoveNetworkActor(const FString& Context, AActor* Actor)
{
	using namespace NCsScriptLibraryWorld::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RemoveNetworkActor : Context;

	UWorld* World = WorldLibrary::GetSafe(Ctxt, Actor);

	if (!World)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from Actor: %s."), *Ctxt, *(Actor->GetName()));
		return;
	}
	World->RemoveNetworkActor(Actor);
}

#undef WorldLibrary