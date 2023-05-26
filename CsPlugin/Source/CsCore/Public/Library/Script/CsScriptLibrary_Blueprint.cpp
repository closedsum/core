// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Script/CsScriptLibrary_Blueprint.h"

// Library
#include "Library/CsLibrary_Blueprint.h"

// Cached
#pragma region

namespace NCsScriptLibraryBlueprint
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, LoadBySoftObjectPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, LoadByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, LoadAndGetGeneratedClassByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, LoadAndGetDefaultObjectByStringPath);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, GetGeneratedClass);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Blueprint, GetDefaultObject);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Blueprint::UCsScriptLibrary_Blueprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Load
#pragma region

UBlueprint* UCsScriptLibrary_Blueprint::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadBySoftObjectPath : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	return BlueprintLibrary::SafeLoad(Ctxt, Path);
}

UBlueprint* UCsScriptLibrary_Blueprint::LoadByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadByStringPath : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	return BlueprintLibrary::SafeLoad(Ctxt, Path);
}

UBlueprintGeneratedClass* UCsScriptLibrary_Blueprint::LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadAndGetGeneratedClassByStringPath : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	if (UBlueprint* Blueprint = BlueprintLibrary::SafeLoad(Ctxt, Path))
	{
		return BlueprintLibrary::GetSafeClass(Ctxt, Blueprint);
	}
	return nullptr;
}

UObject* UCsScriptLibrary_Blueprint::LoadAndGetDefaultObjectByStringPath(const FString& Context, const FString& Path)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::LoadAndGetDefaultObjectByStringPath : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	if (UBlueprint* Blueprint = BlueprintLibrary::SafeLoad(Ctxt, Path))
	{
		return BlueprintLibrary::GetSafeDefaultObject(Ctxt, Blueprint);
	}
	return nullptr;
}

#pragma endregion Load

// Get
#pragma region

UBlueprintGeneratedClass* UCsScriptLibrary_Blueprint::GetGeneratedClass(const FString& Context, UBlueprint* Blueprint)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetGeneratedClass : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	return BlueprintLibrary::GetSafeClass(Ctxt, Blueprint);
}

UObject* UCsScriptLibrary_Blueprint::GetDefaultObject(const FString& Context, UBlueprint* Blueprint)
{
	using namespace NCsScriptLibraryBlueprint::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::GetDefaultObject : Context;

	typedef NCsBlueprint::FLibrary BlueprintLibrary;

	return BlueprintLibrary::GetSafeDefaultObject(Ctxt, Blueprint);
}

#pragma endregion Get

// TSoftObjectPtr
#pragma region

FString UCsScriptLibrary_Blueprint::GetName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject)
{
	return SoftObject.GetAssetName();
}

FName UCsScriptLibrary_Blueprint::GetFName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject)
{
	return FName(*(SoftObject.GetAssetName()));
}

	// Container
#pragma region

USoundCue* UCsScriptLibrary_Blueprint::Conv_CsSoundCueToInternal(const FCsSoundCue& Container)
{
	return Container.Get();
}

UParticleSystem* UCsScriptLibrary_Blueprint::Conv_CsParticleSystemToInternal(const FCsParticleSystem& Container)
{
	return Container.Get();
}

UDataTable* UCsScriptLibrary_Blueprint::Conv_CsDataTableToInternal(const FCsDataTable& Container)
{
	return Container.Get();
}

AActor* UCsScriptLibrary_Blueprint::Conv_CsActorToInternal(const FCsActor& Container)
{
	return Container.Get();
}

UClass* UCsScriptLibrary_Blueprint::Conv_CsActorToClass(const FCsActor& Container)
{
	return Container.GetClass();
}

TSubclassOf<AActor> UCsScriptLibrary_Blueprint::Conv_CsActorToSubclassOf(const FCsActor& Container)
{
	return Container.GetSubclassOf();
}

USkeletalMesh* UCsScriptLibrary_Blueprint::Conv_CsSkeletalMeshToInternal(const FCsSkeletalMesh& Container)
{
	return Container.Get();
}

UTexture* UCsScriptLibrary_Blueprint::Conv_CsTextureToInternal(const FCsTexture& Container)
{
	return Container.Get();
}

#pragma endregion Container

#pragma endregion TSoftObjectPtr

// TSoftClassPtr
#pragma region

FString UCsScriptLibrary_Blueprint::GetName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass)
{
	return SoftClass.GetAssetName();
}

FName UCsScriptLibrary_Blueprint::GetFName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass)
{
	return FName(*(SoftClass.GetAssetName()));
}

#pragma endregion TSoftClassPtr