// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Blueprint.h"

UCsLibrary_Blueprint::UCsLibrary_Blueprint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// TSoftObjectPtr
#pragma region

FString UCsLibrary_Blueprint::GetName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject)
{
	return SoftObject.GetAssetName();
}

FName UCsLibrary_Blueprint::GetFName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject)
{
	return FName(*(SoftObject.GetAssetName()));
}

	// Container
#pragma region

USoundCue* UCsLibrary_Blueprint::Conv_CsSoundCueToInternal(const FCsSoundCue& Container)
{
	return Container.Get();
}

UParticleSystem* UCsLibrary_Blueprint::Conv_CsParticleSystemToInternal(const FCsParticleSystem& Container)
{
	return Container.Get();
}

UDataTable* UCsLibrary_Blueprint::Conv_CsDataTableToInternal(const FCsDataTable& Container)
{
	return Container.Get();
}

AActor* UCsLibrary_Blueprint::Conv_CsActorToInternal(const FCsActor& Container)
{
	return Container.Get();
}

UClass* UCsLibrary_Blueprint::Conv_CsActorToClass(const FCsActor& Container)
{
	return Container.GetClass();
}

TSubclassOf<AActor> UCsLibrary_Blueprint::Conv_CsActorToSubclassOf(const FCsActor& Container)
{
	return Container.GetSubclassOf();
}

USkeletalMesh* UCsLibrary_Blueprint::Conv_CsSkeletalMeshToInternal(const FCsSkeletalMesh& Container)
{
	return Container.Get();
}

UTexture* UCsLibrary_Blueprint::Conv_CsTextureToInternal(const FCsTexture& Container)
{
	return Container.Get();
}

#pragma endregion Container

#pragma endregion TSoftObjectPtr

// TSoftClassPtr
#pragma region

FString UCsLibrary_Blueprint::GetName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass)
{
	return SoftClass.GetAssetName();
}

FName UCsLibrary_Blueprint::GetFName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass)
{
	return FName(*(SoftClass.GetAssetName()));
}

#pragma endregion TSoftClassPtr