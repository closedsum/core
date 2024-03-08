// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_AnimMontage.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_AnimMontage.h"

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
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimMontage::UCsScriptLibrary_AnimMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define AnimMontageLibrary NCsAnimMontage::FLibrary

// Load
#pragma region

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryAnimMontage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return AnimMontageLibrary::SafeLoad(Context, Path);
}

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimMontage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return AnimMontageLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UAnimMontage* UCsScriptLibrary_AnimMontage::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAnimMontage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return AnimMontageLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef AnimMontageLibrary