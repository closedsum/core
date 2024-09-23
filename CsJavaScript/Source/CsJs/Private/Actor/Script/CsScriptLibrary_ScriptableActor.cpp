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

UCsScriptLibrary_ScriptableActor::UCsScriptLibrary_ScriptableActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryScriptableActor::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryScriptableActor::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Interface
#pragma region

bool UCsScriptLibrary_ScriptableActor::GetScriptableActorInfo(const FString& Context, const AActor* Actor, FCsScriptableActorInfo& OutInfo)
{
	CONDITIONAL_SET_CTXT(GetScriptableActorInfo);

	bool IsScript = false;

	if (!CsScriptableActorLibrary::SafeImplements(Ctxt, Actor, IsScript))
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
	CONDITIONAL_SET_CTXT(GetAll);

	return CsScriptableActorLibrary::GetSafe(Ctxt, WorldContextObject, OutActors);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag)
{
	CONDITIONAL_SET_CTXT(GetByTag);

	return CsScriptableActorLibrary::GetSafeByTag(Ctxt, WorldContextObject, Tag);
}

bool UCsScriptLibrary_ScriptableActor::GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors)
{
	CONDITIONAL_SET_CTXT(GetAnyByTags);

	return CsScriptableActorLibrary::GetSafeByTags(Ctxt, WorldContextObject, Tags, OutActors);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name)
{
	CONDITIONAL_SET_CTXT(GetByName);

	return CsScriptableActorLibrary::GetSafeByName(Ctxt, WorldContextObject, Name);
}

AActor* UCsScriptLibrary_ScriptableActor::GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label)
{
	CONDITIONAL_SET_CTXT(GetByLabel);

	return CsScriptableActorLibrary::GetSafeByLabel(Ctxt, WorldContextObject, Label);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT