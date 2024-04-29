// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/Script/CsScriptLibrary_AnimSequence.h"

// Types
#include "CsMacro_Misc.h"
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

#define USING_NS_CACHED using namespace NCsScriptLibraryAnimSequence::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryAnimSequence::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define AnimSequenceLibrary NCsAnimSequence::FLibrary

// Load
#pragma region

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return AnimSequenceLibrary::SafeLoad(Context, Path);
}

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return AnimSequenceLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

UAnimSequence* UCsScriptLibrary_AnimSequence::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return AnimSequenceLibrary::GetSafe(Context, Object, Path, OutSuccess);
}

#pragma endregion Get

// Property
#pragma region

bool UCsScriptLibrary_AnimSequence::SetProperty(const FString& Context, UObject* Object, const FName& PropertyName, UAnimSequence* Anim)
{
	CONDITIONAL_SET_CTXT(SetProperty);

	typedef NCsProperty::FLibrary PropertyLibrary;

	return PropertyLibrary::SetObjectPropertyByName<UAnimSequence>(Ctxt, Object, Object->GetClass(), PropertyName, Anim);
}

#pragma endregion Property

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef AnimSequenceLibrary