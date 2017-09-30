// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Common/CsCommon_Asset.h"
#include "CsCore.h"

#include "Engine.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

#if WITH_EDITOR

// Level Sequence
#include "../LevelSequence/Public/LevelSequence.h"

#include "../Classes/Factories/AnimSequenceFactory.h"

#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"

#endif // #if WITH_EDITOR

UCsCommon_Asset::UCsCommon_Asset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Asset Registry
#pragma region

#if WITH_EDITOR

UFactory* UCsCommon_Asset::GetFactory(UClass* ClassToSpawn)
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* CurrentClass = *It;

		if (CurrentClass->IsChildOf(UFactory::StaticClass()) && !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UFactory* Factory = Cast<UFactory>(CurrentClass->GetDefaultObject());

			if (Factory->CanCreateNew() && Factory->ImportPriority >= 0 && Factory->SupportedClass == ClassToSpawn)
			{
				return Factory;
			}
		}
	}
	return nullptr;
}

UObject* UCsCommon_Asset::CreateAsset(UClass* ClassToSpawn, const FString& Name, const FString &PackagePath)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	UFactory* Factory					= GetFactory(ClassToSpawn);
	UObject* NewAsset					= Cast<ULevelSequence>(AssetToolsModule.Get().CreateAsset(Name, PackagePath, ClassToSpawn, Factory));;

	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(NewAsset);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);

	return NewAsset;
}

ULevelSequence* UCsCommon_Asset::CreateLevelSequence(const FString &Name, const FString &PackagePath)
{
	return Cast<ULevelSequence>(CreateAsset(ULevelSequence::StaticClass(), Name, PackagePath));
}

UAnimSequence* UCsCommon_Asset::CreateAnimSequence(USkeletalMesh* Mesh, const FString &Name, const FString &PackagePath)
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	UAnimSequenceFactory* Factory		= NewObject<UAnimSequenceFactory>();

	Factory->TargetSkeleton = Mesh->Skeleton;
	Factory->PreviewSkeletalMesh = Mesh;

	UAnimSequence* NewAsset = Cast<UAnimSequence>(AssetToolsModule.Get().CreateAsset(Name, PackagePath, UAnimSequence::StaticClass(), Factory));;

	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(NewAsset);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);
	
	return NewAsset;
}

void UCsCommon_Asset::InitAnimSequence(class UAnimSequence* Anim, class USkeletalMeshComponent* Mesh)
{
	USkeleton* AnimSkeleton     = Anim->GetSkeleton();
	USkeletalMesh* SkeletalMesh = Mesh->SkeletalMesh;

	const int32 BoneCount = Mesh->GetComponentSpaceTransforms().Num();

	for (int32 BoneIndex = 0; BoneIndex < BoneCount; ++BoneIndex)
	{
		// verify if this bone exists in skeleton
		const int32 BoneTreeIndex = AnimSkeleton->GetSkeletonBoneIndexFromMeshBoneIndex(SkeletalMesh, BoneIndex);
		if (BoneTreeIndex != INDEX_NONE)
		{
			// add tracks for the bone existing
			FName BoneTreeName = AnimSkeleton->GetReferenceSkeleton().GetBoneName(BoneTreeIndex);
			Anim->AddNewRawTrack(BoneTreeName);
		}
	}

	// Setup notifies
	Anim->InitializeNotifyTrack();
}

void UCsCommon_Asset::InitAnimSequence(class UAnimSequence* Anim, class UPoseableMeshComponent* Mesh)
{
	USkeleton* AnimSkeleton     = Anim->GetSkeleton();
	USkeletalMesh* SkeletalMesh = Mesh->SkeletalMesh;

	const int32 BoneCount = Mesh->GetComponentSpaceTransforms().Num();

	for (int32 BoneIndex = 0; BoneIndex < BoneCount; ++BoneIndex)
	{
		// verify if this bone exists in skeleton
		const int32 BoneTreeIndex = AnimSkeleton->GetSkeletonBoneIndexFromMeshBoneIndex(SkeletalMesh, BoneIndex);
		if (BoneTreeIndex != INDEX_NONE)
		{
			// add tracks for the bone existing
			FName BoneTreeName = AnimSkeleton->GetReferenceSkeleton().GetBoneName(BoneTreeIndex);
			Anim->AddNewRawTrack(BoneTreeName);
		}
	}

	// Setup notifies
	Anim->InitializeNotifyTrack();
}


#endif // #if WITH_EDITOR

#pragma endregion Asset Registry