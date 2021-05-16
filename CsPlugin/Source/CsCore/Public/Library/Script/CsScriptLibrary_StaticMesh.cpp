// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_StaticMesh.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_StaticMesh.h"

// Cached
#pragma region

namespace NCsScriptLibraryStaticMesh
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_StaticMesh, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_StaticMesh, LoadByStringPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_StaticMesh::UCsScriptLibrary_StaticMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UStaticMesh* UCsScriptLibrary_StaticMesh::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryStaticMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsStaticMesh::FLibrary StaticMeshLibrary;

	return StaticMeshLibrary::SafeLoad(Context, Path);
}

UStaticMesh* UCsScriptLibrary_StaticMesh::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryStaticMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsStaticMesh::FLibrary StaticMeshLibrary;

	return StaticMeshLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load