// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_AnimInstance.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Animation/CsLibrary_AnimInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AnimInstance)

// Cached
#pragma region

namespace NCsScriptLibraryAnimInstance
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadAndGetGeneratedClassByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, GetGeneratedClass);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, GetClassByPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimInstance::UCsScriptLibrary_AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryAnimInstance::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryAnimInstance::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Load
#pragma region

UAnimBlueprint* UCsScriptLibrary_AnimInstance::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return CsAnimInstanceLibrary::SafeLoad(Ctxt, Path);
}

UAnimBlueprint* UCsScriptLibrary_AnimInstance::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return CsAnimInstanceLibrary::SafeLoad(Ctxt, Path);
}

UAnimBlueprintGeneratedClass* UCsScriptLibrary_AnimInstance::LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadAndGetGeneratedClassByStringPath);

#if WITH_EDITOR
	if (UAnimBlueprint* AnimBlueprint = CsAnimInstanceLibrary::SafeLoad(Ctxt, Path))
		return CsAnimInstanceLibrary::GetSafeClass(Ctxt, AnimBlueprint);
	return nullptr;
#else
	return CsAnimInstanceLibrary::GetSafeClass(Ctxt, Path);
#endif // #if WITH_EDITOR
}

#pragma endregion Load

// Get
#pragma region

UAnimBlueprintGeneratedClass* UCsScriptLibrary_AnimInstance::GetGeneratedClass(const FString& Context, UAnimBlueprint* Blueprint)
{
	CONDITIONAL_SET_CTXT(GetGeneratedClass);

	return CsAnimInstanceLibrary::GetSafeClass(Ctxt, Blueprint);
}

UAnimBlueprintGeneratedClass* UCsScriptLibrary_AnimInstance::GetClassByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetClassByPath);

	return CsAnimInstanceLibrary::GetSafeClass(Context, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT