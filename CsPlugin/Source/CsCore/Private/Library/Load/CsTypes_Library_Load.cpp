// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/Load/CsTypes_Library_Load.h"
#include "CsCore.h"

// Types
#include "CsMacro_Misc.h"
#include "Load/CsObjectPathDependencyGroup.h"
// Movie
#include "MovieSceneSequencePlayer.h"
#include "IMovieScenePlaybackClient.h"
#include "MovieSceneBindingOwnerInterface.h"
#include "MovieSceneSignedObject.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/BlueprintCore.h"
// Animation
#include "Animation/AnimSequence.h"
#include "Animation/AnimCompositeBase.h"
#include "Animation/BlendSpace.h"
#include "Animation/AnimData/AnimDataModel.h"
// Font
#include "Engine/Font.h"
// Material
#include "Materials/Material.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialFunction.h"
#include "Materials/MaterialInstance.h"
// Texture
#include "Engine/Texture.h"
// FX
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
// Sound
#include "Sound/SoundBase.h"
// Mesh
#include "Engine/StaticMesh.h"
// DataTable
#include "Engine/DataTable.h"
// Physics
#include "PhysicsEngine/PhysicsAsset.h"

// GetObjectPaths
#pragma region

namespace NCsLoad
{
	FGetObjectPaths::FGetObjectPaths() :
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

	void FGetObjectPaths::AddPath(const FSoftObjectPath& SoftPath)
	{
		UObject* O	  = SoftPath.TryLoad();
		UClass* Class = O->GetClass();

		typedef ECsObjectPathDependencyGroup GroupType;

		// DataTable
		if (Class->IsChildOf<UDataTable>())
		{
			PathSets[(uint8)GroupType::DataTable].Add(SoftPath);
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
			#if WITH_EDITOR
				if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
				{
					if (O == BpC->SkeletonGeneratedClass)
					{
						return;
					}
				}
			#endif // #if WITH_EDITOR
			}

			if (UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(Class))
			{
			#if WITH_EDITOR
				if (UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy))
				{
					if (Class == BpC->SkeletonGeneratedClass)
					{
						return;
					}
				}
			#endif // #if WITH_EDITOR
			}

			PathSets[(uint8)GroupType::Blueprint].Add(SoftPath);
		}
		// AnimComposite
		else
		if (Class->IsChildOf<UAnimCompositeBase>())
		{
			PathSets[(uint8)GroupType::AnimComposite].Add(SoftPath);
		}
		// BlendSpace
		else
		if (Class->IsChildOf<UBlendSpace>())
		{
			PathSets[(uint8)GroupType::BlendSpace].Add(SoftPath);
		}
		// AnimationAsset
		else
		if (Class->IsChildOf<UAnimSequence>())
		{
			PathSets[(uint8)GroupType::AnimationAsset].Add(SoftPath);
		}
		// AnimData - SKIP
		else
		if (Class->IsChildOf<UAnimDataModel>())
		{
			return;
		}
		// FX
		else
		if (Class->IsChildOf<UNiagaraSystem>())
		{
			PathSets[(uint8)GroupType::FX].Add(SoftPath);
		}
		// FX - SKIP - IGNORE. NOTE: 4.26. Niagara Emitter no longer get cooked
		else
		if (Class->IsChildOf<UNiagaraEmitter>())
		{
			return;
		}
		// Sound
		else
		if (Class->IsChildOf<USoundBase>())
		{
			PathSets[(uint8)GroupType::Sound].Add(SoftPath);
		}
		// Skeletal
		else
		if (Class->IsChildOf<USkeletalMesh>() ||
			Class->IsChildOf<UPhysicsAsset>() ||
			Class->IsChildOf<USkeleton>())
		{
			PathSets[(uint8)GroupType::Skeletal].Add(SoftPath);
		}
		// StaticMesh
		else
		if (Class->IsChildOf<UStaticMesh>())
		{
			PathSets[(uint8)GroupType::StaticMesh].Add(SoftPath);
		}
		// Material Function - SKIP
		else
		if (Class->IsChildOf<UMaterialFunction>())
		{
			return;
		}
		// Material Parameter Collection
		else
		if (Class->IsChildOf<UMaterialParameterCollection>())
		{
			PathSets[(uint8)GroupType::MaterialParameterCollection].Add(SoftPath);
		}
		// Material
		else
		if (Class->IsChildOf<UMaterial>())
		{
			PathSets[(uint8)GroupType::Material].Add(SoftPath);
		}
		// Material Instance
		else
		if (Class->IsChildOf<UMaterialInstance>())
		{
			PathSets[(uint8)GroupType::MaterialInstance].Add(SoftPath);
		}
		// Font
		else
		if (Class->IsChildOf<UFont>())
		{
			PathSets[(uint8)GroupType::Font].Add(SoftPath);
		}
		// Texture
		else
		if (Class->IsChildOf<UTexture>())
		{
			PathSets[(uint8)GroupType::Texture].Add(SoftPath);
		}
		// Other
		else
		{
			PathSets[(uint8)GroupType::Other].Add(SoftPath);
		}
	}

	void FGetObjectPaths::Resolve()
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

	void FGetObjectPaths::Print()
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
}

#pragma endregion GetObjectPaths