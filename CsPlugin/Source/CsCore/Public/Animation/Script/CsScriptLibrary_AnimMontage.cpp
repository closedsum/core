// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimMontage, LoadByStringPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimMontage::UCsScriptLibrary_AnimMontage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryAnimMontage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsAnimMontage::FLibrary AnimMontageLibrary;

	return AnimMontageLibrary::SafeLoad(Context, Path);
}

UAnimMontage* UCsScriptLibrary_AnimMontage::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimMontage::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsAnimMontage::FLibrary AnimMontageLibrary;

	return AnimMontageLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load