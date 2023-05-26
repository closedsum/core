// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Asset.h"
#include "CsCore.h"

// Enum
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
// Engine
#include "Engine.h"
// Components
#include "Components/SkeletalMeshComponent.h"
#include "Components/PoseableMeshComponent.h"

#if WITH_EDITOR

// Level Sequence

#include "../Classes/Factories/AnimSequenceFactory.h"

#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Editor/ContentBrowser/Public/IContentBrowserSingleton.h"

#endif // #if WITH_EDITOR

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
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::GetEnumStructUserDefinedEnumMap: More than ONE class found of type: UCsEnumStructUserDefinedEnumMap. Choosing the FICST one. There should only be ONE."));

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
	UObject* NewAsset					= AssetToolsModule.Get().CreateAsset(Name, PackagePath, ClassToSpawn, Factory);

	TArray<UObject*> ObjectsToSync;
	ObjectsToSync.Add(NewAsset);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().SyncBrowserToAssets(ObjectsToSync);

	return NewAsset;
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

// Find
#pragma region
#if WITH_EDITOR

void UCsLibrary_Asset::FindObjectsByClass(const FName& ClassName, const FName& ObjectName, TArray<UObject*>& OutObjects)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();
	TArray<FAssetData> AssetDatas;

	AssetRegistry.GetAssetsByClass(ClassName, AssetDatas);

	for (FAssetData& Data : AssetDatas)
	{
		if (Data.AssetName == ObjectName)
		{
			OutObjects.Add(Data.GetAsset());
		}
	}
}

UObject* UCsLibrary_Asset::FindObjectByClass(const FName& ClassName, const FName& ObjectName, const ECsFindObjectByClassRule& Rule /*= ECsFindObjectByClassRule::None*/)
{
	// None | First
	if (Rule == ECsFindObjectByClassRule::None ||
		Rule == ECsFindObjectByClassRule::First)
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
		IAssetRegistry& AssetRegistry			  = AssetRegistryModule.Get();
		TArray<FAssetData> AssetDatas;

		AssetRegistry.GetAssetsByClass(ClassName, AssetDatas);

		UObject* Object = nullptr;

		for (FAssetData& Data : AssetDatas)
		{
			if (Data.AssetName == ObjectName)
			{
				Object = Data.GetAsset();
			}
		}

		if (Rule == ECsFindObjectByClassRule::First)
		{
			if (!Object)
			{
				UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::FindObjectByClass: Failed to find %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
			}
		}
		return Object;
	}
	// Exact
	if (Rule == ECsFindObjectByClassRule::Exact)
	{
		TArray<UObject*> Objects;
		FindObjectsByClass(ClassName, ObjectName, Objects);

		// Check if NO Objects were found
		if (Objects.Num() == CS_EMPTY)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::FindObjectByClass: Failed to find %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
			return nullptr;
		}
		// Check if only ONE Object was found
		if (Objects.Num() != CS_SINGLETON)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Asset::FindObjectByClass: Found more than one %s with name: %s."), *(ClassName.ToString()), *(ObjectName.ToString()));
			return nullptr;
		}
		return Objects[CS_FIRST];
	}
	return nullptr;
}

#endif // #if WITH_EDITOR
#pragma endregion Find