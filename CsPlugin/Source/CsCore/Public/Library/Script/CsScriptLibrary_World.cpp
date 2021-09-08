// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_World.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
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

void UCsScriptLibrary_World::RemoveNetworkActor(const FString& Context, AActor* Actor)
{
	using namespace NCsScriptLibraryWorld::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::RemoveNetworkActor : Context;

	if (!Actor)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Actor is NULL."), *Ctxt);
		return;
	}

	UWorld* World = Actor->GetWorld();

	if (!World)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Failed to get World from Actor: %s."), *Ctxt, *(Actor->GetName()));
		return;
	}
	World->RemoveNetworkActor(Actor);
}