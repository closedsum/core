// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Asset.h"
#include "CsCore.h"

// Enum
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"

#include "Engine.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

// Data
#include "Data/CsDataMapping.h"

#if WITH_EDITOR

// Level Sequence
#include "../LevelSequence/Public/LevelSequence.h"

#include "../Classes/Factories/AnimSequenceFactory.h"

#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"

#endif // #if WITH_EDITOR

// Cache
#pragma region

namespace NCsCommonAssetCached
{
	namespace Str
	{
		const FString bp_data_mapping = TEXT("bp_data_mapping");
	}
}

#pragma endregion // Cache

UCsLibrary_Asset::UCsLibrary_Asset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Asset Registry
#pragma region

#if WITH_EDITOR

IAssetRegistry& UCsLibrary_Asset::GetAssetRegistry()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	return AssetRegistryModule.Get();
}

UCsDataMapping* UCsLibrary_Asset::GetDataMapping()
{
	return GetBlueprintDefaultObject<UCsDataMapping>(NCsCommonAssetCached::Str::bp_data_mapping, ECsStringCompare::Equals, UCsDataMapping::StaticClass());
}

UCsEnumStructUserDefinedEnumMap* UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap()
{
	// TODO: Make Name a Config variable for UCsEdEngine
	const FString Name					= TEXT("EnumStructUserDefinedEnumMap");
	const ECsStringCompare& CompareType = ECsStringCompare::Contains;
	TArray<UCsEnumStructUserDefinedEnumMap*> OutDefaultObjects;
	TArray<FString> OutPackagePaths;

	GetBlueprintDefaultObjects<UCsEnumStructUserDefinedEnumMap>(Name, CompareType, UCsEnumStructUserDefinedEnumMap::StaticClass(), OutDefaultObjects, OutPackagePaths);
	
	if (OutDefaultObjects.Num() == CS_EMPTY)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap: No class found of type: UCsEnumStructUserDefinedEnumMap."));
		return nullptr;
	}

	if (OutDefaultObjects.Num() > CS_SINGLETON)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap: More than ONE class found of type: UCsEnumStructUserDefinedEnumMap. Choosing the FIRST one. There should only be ONE."));

		for (const FString& Path : OutPackagePaths)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap: Asset of type: UCsEnumStructUserDefinedEnumMap found at: %s."), *Path);
		}
	}
	return OutDefaultObjects[CS_EMPTY];
}

void UCsLibrary_Asset::SyncBrowserToAsset(UObject* InObject)
{
	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(InObject);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);
}

void UCsLibrary_Asset::SyncBrowserToAssets(TArray<UObject*> Objects)
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(Objects);
}

UFactory* UCsLibrary_Asset::GetFactory(UClass* ClassToSpawn)
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

UObject* UCsLibrary_Asset::CreateAsset(UClass* ClassToSpawn, const FString& Name, const FString &PackagePath)
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

ULevelSequence* UCsLibrary_Asset::CreateLevelSequence(const FString &Name, const FString &PackagePath)
{
	return Cast<ULevelSequence>(CreateAsset(ULevelSequence::StaticClass(), Name, PackagePath));
}

UAnimSequence* UCsLibrary_Asset::CreateAnimSequence(USkeletalMesh* Mesh, const FString &Name, const FString &PackagePath)
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

void UCsLibrary_Asset::InitAnimSequence(class UAnimSequence* Anim, class USkeletalMeshComponent* Mesh)
{
	Anim->RecycleAnimSequence();

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

void UCsLibrary_Asset::InitAnimSequence(class UAnimSequence* Anim, class UPoseableMeshComponent* Mesh)
{
	Anim->RecycleAnimSequence();

	USkeleton* AnimSkeleton     = Anim->GetSkeleton();
	USkeletalMesh* SkeletalMesh = Mesh->SkeletalMesh;

	const int32 BoneCount = Mesh->BoneSpaceTransforms.Num();

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