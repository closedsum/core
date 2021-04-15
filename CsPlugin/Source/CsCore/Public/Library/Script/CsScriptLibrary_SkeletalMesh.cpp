// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_SkeletalMesh.h"
#include "CsCore.h"

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMesh, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_SkeletalMesh, LoadByStringPath);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_SkeletalMesh::UCsScriptLibrary_SkeletalMesh(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibrarySkeletalMesh::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

	return SkeletalMeshLibrary::SafeLoad(Context, Path);
}

USkeletalMesh* UCsScriptLibrary_SkeletalMesh::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryMaterial::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsSkeletalMesh::FLibrary SkeletalMeshLibrary;

	return SkeletalMeshLibrary::SafeLoad(Ctxt, Path);
}

#pragma endregion Load