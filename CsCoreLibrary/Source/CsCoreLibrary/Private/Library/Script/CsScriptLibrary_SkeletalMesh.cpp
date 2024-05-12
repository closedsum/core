// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_SkeletalMesh.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_SkeletalMesh.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_SkeletalMesh)

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

#define USING_NS_CACHED using namespace NCsScriptLibrarySkeletalMesh::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibrarySkeletalMesh::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define SkeletalMeshLibrary NCsSkeletalMesh::FLibrary

// Load
#pragma region

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return SkeletalMeshLibrary::SafeLoad(Ctxt, Path);
}

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return SkeletalMeshLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load

// Get
#pragma region

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::GetByPath(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess)
{
	CONDITIONAL_SET_CTXT(GetByPath);

	return SkeletalMeshLibrary::GetSafe(Ctxt, Object, Path, OutSuccess);
}

#pragma endregion Get

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef SkeletalMeshLibrary