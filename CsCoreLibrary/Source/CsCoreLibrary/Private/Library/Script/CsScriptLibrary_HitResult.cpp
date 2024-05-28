// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_HitResult.h"

// CVar
#include "Script/CsCVars_Script.h"
// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_HitResult.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_HitResult)

// Cached
#pragma region

namespace NCScriptLibraryHitResult
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_HitResult, GetActor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_HitResult, GetActorChecked);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_HitResult::UCsScriptLibrary_HitResult(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCScriptLibraryHitResult::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCScriptLibraryHitResult::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogError &NCsCore::NLibrary::FLog::Error
#define HitResultLibrary NCsHitResult::FLibrary

AActor* UCsScriptLibrary_HitResult::GetActor(const FString& Context, const FHitResult& Hit)
{
	CONDITIONAL_SET_CTXT(GetActor);

	return HitResultLibrary::GetSafeActor(Context, Hit);
}

AActor* UCsScriptLibrary_HitResult::GetActor2(const FHitResult& Hit)
{
	return HitResultLibrary::GetSafeActor(Hit);
}

AActor* UCsScriptLibrary_HitResult::GetActorChecked(const FString& Context, const FHitResult& Hit, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetActorChecked);

	OutSuccess = true;
	return CS_SCRIPT_GET_CHECKED(HitResultLibrary::GetActorChecked(Ctxt, Hit), HitResultLibrary::GetSafeActor(Ctxt, Hit, OutSuccess, LogError));
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogError
#undef HitResultLibrary