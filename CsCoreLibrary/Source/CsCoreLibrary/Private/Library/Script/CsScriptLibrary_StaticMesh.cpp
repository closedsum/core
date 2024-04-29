// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_StaticMesh.h"

// Types
#include "CsMacro_Misc.h"
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

#define USING_NS_CACHED using namespace NCsScriptLibraryStaticMesh::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryStaticMesh::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define StaticMeshLibrary NCsStaticMesh::FLibrary

// Load
#pragma region

UStaticMesh* UCsScriptLibrary_StaticMesh::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return StaticMeshLibrary::SafeLoad(Ctxt, Path);
}

UStaticMesh* UCsScriptLibrary_StaticMesh::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return StaticMeshLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef StaticMeshLibrary