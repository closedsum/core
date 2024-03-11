// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_AnimSequence.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_AnimSequence.h"
#include "Library/CsLibrary_Property.h"
// Animation
#include "Animation/AnimSequence.h"

// Cached
#pragma region

namespace NCsScriptLibraryAnimSequence
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, LoadByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, GetByPath);
			//Set
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, SetProperty);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimSequence::UCsScriptLibrary_AnimSequence(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define AnimSequenceLibrary NCsAnimSequence::FLibrary

// Load
#pragma region

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return AnimSequenceLibrary::SafeLoad(Context, Path);
}

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return AnimSequenceLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UAnimSequence* UCsScriptLibrary_AnimSequence::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByPath : Context;

	return AnimSequenceLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

#pragma endregion Get

// Property
#pragma region

bool UCsScriptLibrary_AnimSequence::SetProperty(const FString& Context, UObject* Object, const FName& PropertyName, UAnimSequence* Anim)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsProperty::FLibrary PropertyLibrary;

	return PropertyLibrary::SetObjectPropertyByName<UAnimSequence>(Ctxt, Object, Object->GetClass(), PropertyName, Anim);
}

#pragma endregion Property

#undef AnimSequenceLibrary