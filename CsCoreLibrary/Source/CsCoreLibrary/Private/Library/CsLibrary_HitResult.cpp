// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_HitResult.h"

// Types
#include "CsMacro_Misc.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsHitResult
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsHitResult::FLibrary, GetSafeActor);
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsHitResult::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsHitResult::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName
	#define LogLevel void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/

	AActor* FLibrary::GetActorChecked(const FString& Context, const FHitResult& Hit)
	{
		checkf(Hit.HasValidHitObjectHandle(), TEXT("%s: Hit does NOT have a Valid HitObjectHandle."), *Context);
		
		AActor* Actor = Hit.GetActor();

		checkf(IsValid(Actor), TEXT("%s: Hit.HitObjectHandle resolves to NULL or is no longer Valid."), *Context);
		return Actor;
	}

	AActor* FLibrary::GetSafeActor(const FString& Context, const FHitResult& Hit, LogLevel)
	{
		if (!Hit.HasValidHitObjectHandle())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Hit does NOT have a Valid HitObjectHandle."), *Context));
			return nullptr;
		}
		
		AActor* Actor = Hit.GetActor();

		if (!IsValid(Actor))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Hit.HitObjectHandle resolves to NULL or is no longer Valid."), *Context));
			return nullptr;
		}
		return Actor;
	}

	AActor* FLibrary::GetSafeActor(const FHitResult& Hit)
	{
		SET_CONTEXT(GetSafeActor);

		return GetSafeActor(Context, Hit, nullptr);
	}

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	#undef LogLevel
}