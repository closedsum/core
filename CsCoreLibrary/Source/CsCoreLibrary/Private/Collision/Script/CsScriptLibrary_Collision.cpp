// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Collision/Script/CsScriptLibrary_Collision.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Collision)

// Cached
#pragma region

namespace NCsScriptLibraryCollision
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Collision, Set_CollisionPreset);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Collision, SetFromObject_CollisionPreset);
		}

		namespace Name
		{
			const FName CollisionPreset = FName("CollisionPreset");
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Collision::UCsScriptLibrary_Collision(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UCsScriptLibrary_Collision::Set_CollisionPreset(const FString& Context, UPrimitiveComponent* Component, const FCsCollisionPreset& Preset)
{
	using namespace NCsScriptLibraryCollision::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Set_CollisionPreset : Context;

	return Preset.SetSafe(Ctxt, Component);
}

bool UCsScriptLibrary_Collision::SetFromObject_CollisionPreset(const FString& Context, UObject* Object, UPrimitiveComponent* Component)
{
	using namespace NCsScriptLibraryCollision::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetFromObject_CollisionPreset : Context;

	// Check for properties of type: FCsCollisionPreset
	typedef NCsProperty::FLibrary PropertyLibrary;

	bool Success = false;

	typedef FCsCollisionPreset StructType;

	if (StructType* ImplAsStruct = PropertyLibrary::GetStructPropertyValuePtr<StructType>(Ctxt, Object, Object->GetClass(), Name::CollisionPreset))
	{
		return ImplAsStruct->SetSafe(Ctxt, Component);
	}

	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to find any properties from %s for CollisionPreset."), *Ctxt, *(CsObjectLibrary::PrintObjectAndClass(Object)));
	UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: - Failed to get struct property of type: FCsCollisionPreset with name: CollisionPreset."), *Context);
	return false;
}

FCollisionResponseContainer UCsScriptLibrary_Collision::SetCollisionResponse(const FCollisionResponseContainer& Container, const ECollisionChannel& Channel, const ECollisionResponse& NewResponse)
{
	FCollisionResponseContainer Copy = Container;
	Copy.SetResponse(Channel, NewResponse);
	return Copy;
}