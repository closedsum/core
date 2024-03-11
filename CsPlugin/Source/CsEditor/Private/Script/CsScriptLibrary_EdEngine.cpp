// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Script/CsScriptLibrary_EdEngine.h"
#include "CsEditor.h"

// Engine
#include "CsEdEngine.h"

// Cached
#pragma region

namespace NCsScriptLibraryEdEngine
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_EdEngine, AddCreatedObject);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_EdEngine::UCsScriptLibrary_EdEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsScriptLibrary_EdEngine::AddCreatedObject(const FString& Context, UObject* Object, UObject* Owner)
{
	using namespace NCsScriptLibraryEdEngine::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::AddCreatedObject : Context;

	UCsEdEngine* EdEngine = Cast<UCsEdEngine>(GEngine);

	if (!EdEngine)
	{
		UE_LOG(LogCsEditor, Warning, TEXT("%s: GEngine: %s with Class: %s is NOT of type: UCsEdEngine."), *Ctxt, *(GEngine->GetName()), *(GEngine->GetClass()->GetName()));
		return;
	}

	typedef NCsObject::NCreate::FCreated CreatedObjectsType;

	CreatedObjectsType* CreatedObjects = EdEngine->GetCreatedObjects();

	CreatedObjects->Add(Object, Owner);
}