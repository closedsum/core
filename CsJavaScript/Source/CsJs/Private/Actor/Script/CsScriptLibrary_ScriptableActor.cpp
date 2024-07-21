// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Actor/Script/CsScriptLibrary_ScriptableActor.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Actor/CsLibrary_ScriptableActor.h"
// Actor
#include "Actor/CsScriptScriptableActor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_ScriptableActor)

// Cached
#pragma region

namespace NCsScriptLibraryScriptableActor
{
	namespace NCached
	{
		namespace Str
		{
			// Interface
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetScriptableActorInfo);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetAll);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetByTag);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetAnyByTags);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetByName);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_ScriptableActor, GetByLabel);
		}
	}
}

#pragma endregion Cached

#define ActorLibrary NCsActor::NScriptable::FLibrary

UCsScriptLibrary_ScriptableActor::UCsScriptLibrary_ScriptableActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Interface
#pragma region

bool UCsScriptLibrary_ScriptableActor::GetScriptableActorInfo(const FString& Context, const AActor* Actor, FCsScriptableActorInfo& OutInfo)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetScriptableActorInfo : Context;

	bool IsScript = false;

	if (!ActorLibrary::SafeImplements(Ctxt, Actor, IsScript))
		return false;

	if (IsScript)
	{
		ICsScriptScriptableActor::Execute_Script_GetScriptableActorInfo(Actor, OutInfo);
	}
	else
	{
		const ICsScriptableActor* ScriptableActor = Cast<ICsScriptableActor>(Actor);

		OutInfo = ScriptableActor->GetScriptableActorInfo();
	}
	return true;
}

#pragma endregion Interface

// Get
#pragma region

bool UCsScriptLibrary_ScriptableActor::GetAll(const FString& Context, const UObject* WorldContextObject, TArray<AActor*>& OutActors)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAll : Context;

	return ActorLibrary::GetSafe(Ctxt, WorldContextObject, OutActors);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByTag : Context;

	return ActorLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

bool UCsScriptLibrary_ScriptableActor::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetAnyByTags : Context;

	return ActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutActors);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByName : Context;

	return ActorLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	using namespace NCsScriptLibraryScriptableActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByLabel : Context;

	return ActorLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef ActorLibrary