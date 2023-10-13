// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_SkeletalMesh.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_SkeletalMesh.h"

// Cached
#pragma region

namespace NCsScriptLibrarySkeletalMesh
{
	namespace NCached
	{
		namespace Str
		{
			// Load
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMesh, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMesh, LoadByStringPath);
			// Get
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMesh, GetByPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_SkeletalMesh::UCsScriptLibrary_SkeletalMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define SkeletalMeshLibrary NCsSkeletalMesh::FLibrary

// Load
#pragma region

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibrarySkeletalMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	return SkeletalMeshLibrary::SafeLoad(Ctxt, Path);
}

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibrarySkeletalMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	return SkeletalMeshLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	using namespace NCsScriptLibrarySkeletalMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetByPath : Context;

	return SkeletalMeshLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef SkeletalMeshLibrary