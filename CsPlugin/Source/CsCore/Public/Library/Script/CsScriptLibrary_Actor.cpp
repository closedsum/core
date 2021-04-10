// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Actor.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Actor.h"

// Cached
#pragma region

namespace NCsScriptLibraryActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetRootComponent);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, SetRole);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetActorByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Actor, GetActorByLabel);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Actor::UCsScriptLibrary_Actor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_Actor::SetRootComponent(const FString& Context, AActor* Actor, USceneComponent* Component)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetRootComponent : Context;

	if (!Actor)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Actor is NULL."), *Ctxt);
		return;
	}

	if (!Component)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Component is NULL. Use ClearRootComponent."), *Ctxt);
		return;
	}
	Actor->SetRootComponent(Component);
}

void UCsScriptLibrary_Actor::SetRole(const FString& Context, AActor* Actor, const ENetRole& Role)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetRole : Context;

	if (!Actor)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Actor is NULL."), *Ctxt);
		return;
	}
	Actor->SetRole(Role);
}

AActor* UCsScriptLibrary_Actor::GetActorByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetActorByName : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeActorByName(Ctxt, WorldContextObject, Name);
}

AActor* UCsScriptLibrary_Actor::GetActorByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetActorByLabel : Context;

	typedef NCsActor::FLibrary ActorLibrary;

	return ActorLibrary::GetSafeActorByLabel(Ctxt, WorldContextObject, Label);
}