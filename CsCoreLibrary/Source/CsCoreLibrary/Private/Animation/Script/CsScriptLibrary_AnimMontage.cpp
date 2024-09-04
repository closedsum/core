// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_AnimMontage.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Animation/CsLibrary_AnimMontage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_AnimMontage)

// Cached
#pragma region

namespace NCsScriptLibraryAnimMontage
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, LoadByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, GetByPath);
			// Play
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, PlayByPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimMontage::UCsScriptLibrary_AnimMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryAnimMontage::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryAnimMontage::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context

// Load
#pragma region

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return CsAnimMontageLibrary::SafeLoad(Context, Path);
}

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return CsAnimMontageLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UAnimMontage* UCsScriptLibrary_AnimMontage::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return CsAnimMontageLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

#pragma endregion Get

// Play
#pragma region

float UCsScriptLibrary_AnimMontage::PlayByPath(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayByPathParams& Params)
{
	CONDITIONAL_SET_CTXT(PlayByPath);

	return CsAnimMontageLibrary::SafePlay(Ctxt, Component, Params);
}

#pragma endregion Play

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT