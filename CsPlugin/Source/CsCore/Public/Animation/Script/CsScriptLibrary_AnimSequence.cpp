// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Script/CsScriptLibrary_AnimSequence.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Animation/CsLibrary_AnimSequence.h"

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