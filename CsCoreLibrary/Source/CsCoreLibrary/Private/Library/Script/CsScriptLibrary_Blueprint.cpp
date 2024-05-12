// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Script/CsScriptLibrary_Blueprint.h"

// Library
#include "Library/CsLibrary_Blueprint.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Blueprint)

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

#define USING_NS_CACHED using namespace NCsScriptLibraryBlueprint::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryBlueprint::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define BlueprintLibrary NCsBlueprint::FLibrary

// Load
#pragma region

UBlueprint* UCsScriptLibrary_Blueprint::LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path)
{
	CONDITIONAL_SET_CTXT(LoadBySoftObjectPath);

	return BlueprintLibrary::SafeLoad(Ctxt, Path);
}

UBlueprint* UCsScriptLibrary_Blueprint::LoadByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadByStringPath);

	return BlueprintLibrary::SafeLoad(Ctxt, Path);
}

UBlueprintGeneratedClass* UCsScriptLibrary_Blueprint::LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadAndGetGeneratedClassByStringPath);

#if WITH_EDITOR
	if (UBlueprint* Blueprint = BlueprintLibrary::SafeLoad(Ctxt, Path))
		return BlueprintLibrary::GetSafeClass(Ctxt, Blueprint);
	return nullptr;
#else
	return BlueprintLibrary::GetSafeClass(Ctxt, Path);
#endif //  #if WITH_EDITOR
}

UObject* UCsScriptLibrary_Blueprint::LoadAndGetDefaultObjectByStringPath(const FString& Context, const FString& Path)
{
	CONDITIONAL_SET_CTXT(LoadAndGetDefaultObjectByStringPath);

#if WITH_EDITOR
	if (UBlueprint* Blueprint = BlueprintLibrary::SafeLoad(Ctxt, Path))
		return BlueprintLibrary::GetSafeDefaultObject(Ctxt, Blueprint);
	return nullptr;
#else
	return BlueprintLibrary::GetSafeDefaultObject(Ctxt, Path);
#endif // #if WITH_EDITOR
}

#pragma endregion Load

// Get
#pragma region

UBlueprintGeneratedClass* UCsScriptLibrary_Blueprint::GetGeneratedClass(const FString& Context, UBlueprint* Blueprint)
{
	CONDITIONAL_SET_CTXT(GetGeneratedClass);

	return BlueprintLibrary::GetSafeClass(Ctxt, Blueprint);
}

UObject* UCsScriptLibrary_Blueprint::GetDefaultObject(const FString& Context, UBlueprint* Blueprint)
{
	CONDITIONAL_SET_CTXT(GetDefaultObject);

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

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef BlueprintLibrary