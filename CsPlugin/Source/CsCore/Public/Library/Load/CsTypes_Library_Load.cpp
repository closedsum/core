// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/Load/CsTypes_Library_Load.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Load.h"
// Movie
#include "MovieSceneSequencePlayer.h"
#include "IMovieScenePlaybackClient.h"
#include "MovieSceneBindingOwnerInterface.h"
#include "MovieSceneSignedObject.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/BlueprintCore.h"
// Animation
#include "Animation/AnimCompositeBase.h"
#include "Animation/BlendSpaceBase.h"
// Font
#include "Engine/Font.h"
// Material
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialFunction.h"
// FX
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
// Sound
#include "Sound/SoundBase.h"

// LoadCodes
#pragma region

namespace NCsLibraryLoad_GetSoftObjectPaths_Code
{
	/*
	namespace Ref
	{
	}
	*/
	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 1;
}

#pragma endregion LoadCodes

// FCsLibraryLoad_GetObjectPaths
#pragma region

FCsLibraryLoad_GetObjectPaths::FCsLibraryLoad_GetObjectPaths() :
	RootName(),
	RootDefaultName(),
	Paths(),
	PathGroups(),
	PathSets(),
	VisitedFunctions(),
	VisitedPointers(),
	TotalCount(0)
{
	const int32& Count = EMCsObjectPathDependencyGroup::Get().Num();

	PathSets.Reset(Count);

	for (const ECsObjectPathDependencyGroup& Group : EMCsObjectPathDependencyGroup::Get())
	{
		PathSets.AddDefaulted();
	}
}

void FCsLibraryLoad_GetObjectPaths::AddPath(const FSoftObjectPath& SoftPath)
{
	UObject* O	  = SoftPath.TryLoad();
	UClass* Class = O->GetClass();

	// DataTable
	if (Class->IsChildOf<UDataTable>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::DataTable].Add(SoftPath);
	}
	// Sequencer
	/*
	else
	if (Class->IsChildOf<UMovieSceneSequencePlayer>() ||
		Class->ImplementsInterface(UMovieScenePlaybackClient::StaticClass()) ||
		Class->ImplementsInterface(UMovieSceneBindingOwnerInterface::StaticClass()) ||
		Class->IsChildOf<UMovieSceneSignedObject>())
	{
		DependencySetList[(uint8)ECsObjectPathDependencyGroup::Sequencer].Add(SoftPath);
	}
	*/
	// Blueprint
	else
	if (Class->HasAnyClassFlags(EClassFlags::CLASS_CompiledFromBlueprint) ||
		Class->IsChildOf<UBlueprintGeneratedClass>())
	{
		// Check for SkeletonGeneratedClasses. Skip adding the path.
		if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O))
		{
			if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
			{
				if (O == BpC->SkeletonGeneratedClass)
				{
					return;
				}
			}
		}

		if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(Class))
		{
			if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
			{
				if (Class == BpC->SkeletonGeneratedClass)
				{
					return;
				}
			}
		}

		PathSets[(uint8)ECsObjectPathDependencyGroup::Blueprint].Add(SoftPath);
	}
	// AnimComposite
	else
	if (Class->IsChildOf<UAnimCompositeBase>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::AnimComposite].Add(SoftPath);
	}
	// AnimationAsset
	else
	if (Class->IsChildOf<UAnimSequence>() ||
		Class->IsChildOf<UBlendSpaceBase>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::AnimationAsset].Add(SoftPath);
	}
	// FX
	else
	if (Class->IsChildOf<UNiagaraSystem>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::FX].Add(SoftPath);
	}
	// FX - IGNORE. NOTE: 4.26. Niagara Emitter no longer get cooked
	else
	if (Class->IsChildOf<UNiagaraEmitter>())
	{
		return;
	}
	// Sound
	else
	if (Class->IsChildOf<USoundBase>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::Sound].Add(SoftPath);
	}
	// Skeletal
	else
	if (Class->IsChildOf<USkeletalMesh>() ||
		Class->IsChildOf<UPhysicsAsset>() ||
		Class->IsChildOf<USkeleton>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::Skeletal].Add(SoftPath);
	}
	// StaticMesh
	else
	if (Class->IsChildOf<UStaticMesh>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::StaticMesh].Add(SoftPath);
	}
	// Material
	else
	if (Class->IsChildOf<UMaterial>() ||
		Class->IsChildOf<UMaterialInstance>() ||
		Class->IsChildOf<UMaterialFunction>())
	{
		if (Class->IsChildOf<UMaterialFunction>())
			return;

		PathSets[(uint8)ECsObjectPathDependencyGroup::Material].Add(SoftPath);
	}
	// Texture
	else
	if (Class->IsChildOf<UTexture>() ||
		Class->IsChildOf<UFont>())
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::Texture].Add(SoftPath);
	}
	// Other
	else
	{
		PathSets[(uint8)ECsObjectPathDependencyGroup::Other].Add(SoftPath);
	}
}

void FCsLibraryLoad_GetObjectPaths::Resolve()
{
	PathGroups.Reset(PathSets.Num());

	for (TSet<FSoftObjectPath>& Set : PathSets)
	{
		if (Set.Num() > CS_EMPTY)
		{
			PathGroups.AddDefaulted();
			TArray<FSoftObjectPath>& L = PathGroups.Last();

			L.Reset(Set.Num());

			for (FSoftObjectPath& SoftPath : Set)
			{
				L.Add(SoftPath);
			}

			TotalCount += Set.Num();
		}
	}

	Paths.Reset(TotalCount);

	for (TSet<FSoftObjectPath>& Set : PathSets)
	{
		for (FSoftObjectPath& Path : Set)
		{
			Paths.Add(Path);
		}
	}
}

void FCsLibraryLoad_GetObjectPaths::Print()
{
	//UE_LOG(LogRs, Warning, TEXT("GetObjectPaths: %s @ %s"), *Name, *Path);
	UE_LOG(LogCs, Warning, TEXT("GetObjectPaths"));
	UE_LOG(LogCs, Warning, TEXT("- Depth List - %d Paths"), TotalCount);

	const int32 Count = PathGroups.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		TArray<FSoftObjectPath>& L = PathGroups[I];

		UE_LOG(LogCs, Warning, TEXT("-- %d - %d Paths"), I, L.Num());

		for (FSoftObjectPath& SoftPath : L)
		{
			const FString AssetName = SoftPath.GetAssetName();
			const FString AssetPath = SoftPath.GetAssetPathString();

			UE_LOG(LogCs, Warning, TEXT("--- %s @ %s"), *AssetName, *AssetPath);
		}
	}
}

#pragma endregion FCsLibraryLoad_GetObjectPaths

// FCsLibraryLoad_GetReferencesReport_Category
#pragma region

void FCsLibraryLoad_GetReferencesReport_Category::Add(const FCsLibraryLoad_MemberInfo& MemberInfo, const FSoftObjectPath& ObjectPath)
{
	MemberInfos.Add(MemberInfo);

	FString& SubPathString = const_cast<FString&>(ObjectPath.GetSubPathString());
	SubPathString.Empty();

	ObjectPaths.Add(ObjectPath);

	if (int32* CountPtr = CountByObjectPath.Find(ObjectPath))
	{
		++(*CountPtr);
	}
	else
	{
		CountByObjectPath.Add(ObjectPath, 1);
	}

	if (TArray<FCsLibraryLoad_MemberInfo>* PathsPtr = MemberInfosByObjectPath.Find(ObjectPath))
	{
		PathsPtr->Add(MemberInfo);
	}
	else
	{
		TArray<FCsLibraryLoad_MemberInfo> Paths;
		Paths.Add(MemberInfo);
		MemberInfosByObjectPath.Add(ObjectPath, Paths);
	}
}

void FCsLibraryLoad_GetReferencesReport_Category::AddUnused(const FCsLibraryLoad_MemberInfo& MemberInfo)
{
	UnusedMemberInfos.Add(MemberInfo);
}

void FCsLibraryLoad_GetReferencesReport_Category::Print()
{
	// "Category Name"
	UE_LOG(LogCs, Warning, TEXT("- %s"), *Name);
		// Used
	UE_LOG(LogCs, Warning, TEXT("--"));
	UE_LOG(LogCs, Warning, TEXT("-- Used: %d Members %d Paths (%d Unique)"), MemberInfos.Num(), ObjectPaths.Num(), CountByObjectPath.Num());
	{
		const int32 Count = MemberInfos.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FCsLibraryLoad_MemberInfo& MemberInfo	= MemberInfos[I];
			const FString Info							= MemberInfo.ToString();

			const FSoftObjectPath& ObjectPath = ObjectPaths[I];
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			UE_LOG(LogCs, Warning, TEXT("--- %s"), *Info);
			UE_LOG(LogCs, Warning, TEXT("     = %s @ %s"), *ObjectName, *Path);
		}

		// Count
		UE_LOG(LogCs, Warning, TEXT("---"));
		UE_LOG(LogCs, Warning, TEXT("--- Count: %d Unique Paths"), CountByObjectPath.Num());

		for (TPair<FSoftObjectPath, int32>& Pair : CountByObjectPath)
		{
			const FSoftObjectPath& ObjectPath = Pair.Key;
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			UE_LOG(LogCs, Warning, TEXT("---- %d for %s @ %s"), Pair.Value, *ObjectName, *Path);
		}

		// Members
		UE_LOG(LogCs, Warning, TEXT("---"));
		UE_LOG(LogCs, Warning, TEXT("--- Member: %d Unique Paths"), CountByObjectPath.Num());

		for (TPair<FSoftObjectPath, TArray<FCsLibraryLoad_MemberInfo>>& Pair : MemberInfosByObjectPath)
		{
			const FSoftObjectPath& ObjectPath = Pair.Key;
			const FString& ObjectName		  = ObjectPath.GetAssetName();
			const FString& Path				  = ObjectPath.GetAssetPathString();

			const TArray<FCsLibraryLoad_MemberInfo>& Infos = Pair.Value;

			UE_LOG(LogCs, Warning, TEXT("---- %s @ %s"), *ObjectName, *Path);

			UE_LOG(LogCs, Warning, TEXT("----- %d Members"), Infos.Num());

			for (const FCsLibraryLoad_MemberInfo& Info : Infos)
			{
				UE_LOG(LogCs, Warning, TEXT("------ %s"), *(Info.ToString()));
			}
		}
	}
		// Unused
	UE_LOG(LogCs, Warning, TEXT("--"));
	UE_LOG(LogCs, Warning, TEXT("-- Unused: %d Members"), UnusedMemberInfos.Num());
	{
		for (const FCsLibraryLoad_MemberInfo& Info : UnusedMemberInfos)
		{
			UE_LOG(LogCs, Warning, TEXT("--- %s"), *(Info.ToString()));
		}
	}
}

#pragma endregion FCsLibraryLoad_GetReferencesReport_Category

// FCsLibraryLoad_GetReferencesReport
#pragma region

void FCsLibraryLoad_GetReferencesReport::AddToDepthList(const FSoftObjectPath& InPath, const int32& Depth)
{
	if (Depth >= ReferenceDepthList.Num())
	{
		const int32 Count = ReferenceDepthList.Num();

		for (int32 I = Count; I < Depth + 1; ++I)
		{
			ReferenceDepthList.AddDefaulted();
		}
	}

	ReferenceDepthList[Depth].Add(InPath);
}

void FCsLibraryLoad_GetReferencesReport::ResolveDepthList()
{
	int32 Count = ReferenceDepthList.Num();

	for (int32 I = 0; I < Count - 1; ++I)
	{
		TSet<FSoftObjectPath>& Set = ReferenceDepthList[I];

		for (FSoftObjectPath& SoftPath : Set)
		{
			for (int32 J = I + 1; J < Count; ++J)
			{
				ReferenceDepthList[J].Remove(SoftPath);
			}
		}
	}

	// Remove empty entries
	Count = ReferenceDepthList.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (ReferenceDepthList[I].Num() == 0)
		{
			ReferenceDepthList.RemoveAt(I, 1, false);
		}
		else
		{
			TotalCount += ReferenceDepthList[I].Num();
		}
	}
}

void FCsLibraryLoad_GetReferencesReport::Print()
{
	UE_LOG(LogCs, Warning, TEXT("GetReferencesReport: %s @ %s"), *Name, *Path);

	Hard.Print();

	UE_LOG(LogCs, Warning, TEXT("-"));

	Soft.Print();
}

#pragma endregion FCsLibraryLoad_GetReferencesReport