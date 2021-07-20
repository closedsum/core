// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Script/CsScriptLibrary_AnimSequence.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_AnimSequence.h"
#include "Library/CsLibrary_Property.h"

// Cached
#pragma region

namespace NCsScriptLibraryAnimSequence
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_AnimSequence, SetProperty);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_AnimSequence::UCsScriptLibrary_AnimSequence(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsAnimSequence::FLibrary AnimSequenceLibrary;

	return AnimSequenceLibrary::SafeLoad(Context, Path);
}

UAnimSequence* UCsScriptLibrary_AnimSequence::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryAnimSequence::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsAnimSequence::FLibrary AnimSequenceLibrary;

	return AnimSequenceLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

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