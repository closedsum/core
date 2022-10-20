// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Script/CsScriptLibrary_AnimInstance.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_AnimInstance.h"

// Cached
#pragma region

namespace NCsScriptLibraryAnimInstance
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, LoadAndGetGeneratedClassByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimInstance, GetGeneratedClass);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimInstance::UCsScriptLibrary_AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UAnimBlueprint* UCsScriptLibrary_AnimInstance::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryAnimInstance::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

	return AnimInstanceLibrary::SafeLoad(Ctxt, Path);
}

UAnimBlueprint* UCsScriptLibrary_AnimInstance::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimInstance::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

	return AnimInstanceLibrary::SafeLoad(Ctxt, Path);
}

UAnimBlueprintGeneratedClass* UCsScriptLibrary_AnimInstance::LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimInstance::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadAndGetGeneratedClassByStringPath : Context;

	typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

	if (UAnimBlueprint* AnimBlueprint = AnimInstanceLibrary::SafeLoad(Ctxt, Path))
	{
		return AnimInstanceLibrary::GetSafeClass(Ctxt, AnimBlueprint);
	}
	return nullptr;
}

#pragma endregion Load

// Get
#pragma region

UAnimBlueprintGeneratedClass* UCsScriptLibrary_AnimInstance::GetGeneratedClass(const FString& Context, UAnimBlueprint* Blueprint)
{
	using namespace NCsScriptLibraryAnimInstance::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetGeneratedClass : Context;

	typedef NCsAnimInstance::FLibrary AnimInstanceLibrary;

	return AnimInstanceLibrary::GetSafeClass(Ctxt, Blueprint);
}

#pragma endregion Get