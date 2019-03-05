// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/Poseable/CsPoseableMeshActor.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Common/CsCommon_Asset.h"

#include "Components/CsPoseableMeshComponent.h"

#if WITH_EDITOR
#include "../AnimationCore/Public/TwoBoneIK.h"
#endif // #if WITH_EDITOR

#include "Animation/Poseable/CsAnim_Bone.h"
#include "Animation/Poseable/Controls/CsAnim_Control.h"
#include "Animation/Poseable/Controls/CsAnim_ControlAnchor.h"
#include "Animation/Poseable/Controls/CsAnim_Control_FK.h"
#include "Animation/Poseable/Controls/CsAnim_Control_TwoBoneIK.h"
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_EndEffector.h"
#include "Animation/Poseable/Controls/Helpers/CsAnim_ControlHelper_JointTarget.h"

// Level Sequence
//#include "../LevelSequence/Public/LevelSequence.h"
#include "../LevelSequence/Public/LevelSequenceActor.h"

#if WITH_EDITOR

#include "Editor/Sequencer/Public/ISequencer.h"
/*
#include "../MovieScene/Public/MovieScene.h"
*/

//#include "../MovieScene/Public/MovieSceneSection.h"


//#include "../MovieScene/Public/MovieScenePossessable.h"
#include "../MovieScene/Public/MovieSceneFolder.h"
#include "../MovieSceneTracks/Public/Tracks/MovieSceneCinematicShotTrack.h"
#include "../MovieSceneTracks/Public/Tracks/MovieScene3DTransformTrack.h"
//#include "../MovieSceneTracks/Public/Sections/MovieScene3dTransformSection.h"


#include "../UnrealEd/Public/Toolkits/AssetEditorManager.h"
#include "Private/LevelSequenceEditorToolkit.h"
//#include "../LevelSequence/Public/LevelSequencePlayer.h"

#include "../Engine/Classes/Curves/KeyHandle.h"

#endif // #if WITH_EDITOR

ACsPoseableMeshActor::ACsPoseableMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;

	PoseableMeshComponent = ObjectInitializer.CreateDefaultSubobject<UCsPoseableMeshComponent>(this, TEXT("PoseableMeshComponent"));
	SetRootComponent(PoseableMeshComponent);
}

void ACsPoseableMeshActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Make a Copy of Controls_TwoBoneIK
	Controls_TwoBoneIK_Copy.Reset();

	const int32 Count = Controls_TwoBoneIK.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Controls_TwoBoneIK_Copy.AddDefaulted();
		Controls_TwoBoneIK_Copy[I] = Controls_TwoBoneIK[I];
	}
}

void ACsPoseableMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	// Handle Waypoints placed in Editor
	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		OnTick_Editor(DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR
}

bool ACsPoseableMeshActor::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditor(GetWorld()))
		return true;
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

#if WITH_EDITOR

void ACsPoseableMeshActor::OnTick_Editor(const float &DeltaSeconds)
{
	if (!HasTickedInEditor)
	{
		HasTickedInEditor = true;
	}
	
	OpenShotIndex	    = GetOpenShotIndexInEditor();
	bIsAssetEditorOpen  = OpenShotIndex != INDEX_NONE;
	LevelSequenceEditor = bIsAssetEditorOpen ? GetOpenAssetEditor() : nullptr;

	//if (IsSelected())
	//	return;

	// Controls

		// TwoBoneIK
	{
		const int32 ControlCount = Controls_TwoBoneIK.Num();

		for (int32 I = 0; I < ControlCount; ++I)
		{
			FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[I];
			ACsAnim_Control_TwoBoneIK* Control		= TwoBoneIK.Actor;

			if (!Control)
			{
				DestroyOrphanedControlAnchors();
				DestroyOrphanedControlHelpers();
				Create_Control_TwoBoneIK(I);
			}

			if (!Control->Anchor ||
				!Control->EndEffector || 
				!Control->JointTarget)
			{
				Create_Control_TwoBoneIK(I);
			}

			if (IsSelected())
			{
				Control->ForceUpdateTransform = true;
				Control->EndEffector->ForceUpdateTransform = true;
				Control->JointTarget->ForceUpdateTransform = true;
				continue;
			}

			if (!Control->StartBone || !Control->MiddleBone || !Control->EndBone)
				continue;

			const bool UpdateIK = !bIsAssetEditorOpen || (bIsAssetEditorOpen && (Control->EndEffector->Location.HasChanged() || Control->JointTarget->Location.HasChanged()));

			if (UpdateIK)
			{
				PerformTwoBoneIK(I);
			}

			if (bIsAssetEditorOpen && UpdateIK)
			{
				AnimLevelSequence_Shot_AddKey(OpenShotIndex, Control->StartBone);
				AnimLevelSequence_Shot_AddKey(OpenShotIndex, Control->MiddleBone);
				AnimLevelSequence_Shot_AddKey(OpenShotIndex, Control->EndBone);
			}
		}
	}
		// FK
	{
		const int32 ControlCount = Controls_FK.Num();

		for (int32 I = 0; I < ControlCount; ++I)
		{
			FCsAnimControlInfo_FK& FK = Controls_FK[I];
			ACsAnim_Control_FK* Control = FK.Actor;

			if (!Control)
			{
				DestroyOrphanedControlAnchors();
				Create_Control_FK(I);
			}

			if (!Control->Anchor)
				Create_Control_FK(I);

			if (IsSelected())
			{
				Control->ForceUpdateTransform = true;
				continue;
			}

			PerformFK(I);
		}
	}
	// Bones
	const int32 BoneCount = Bones.Num();

	for (int32 I = 0; I < BoneCount; ++I)
	{
		if (!Bones[I].Actor)
		{
			RecreateBone(I);
		}

		Bones[I].Actor->ForceUpdateTransform |= IsSelected() || bIsAssetEditorOpen;

		// Location
		if (Bones[I].Actor->Location.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneLocationByIndex(Bones[I].BoneIndex, Bones[I].Actor->Location.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Location.Clear();
		}
		// Rotation
		if (Bones[I].Actor->Rotation.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneRotationByIndex(Bones[I].BoneIndex, Bones[I].Actor->Rotation.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Rotation.Clear();
		}
		// Scale
		if (Bones[I].Actor->Scale.HasChanged() ||
			Bones[I].Actor->ForceUpdateTransform)
		{
			PoseableMeshComponent->SetBoneScaleByIndex(Bones[I].BoneIndex, Bones[I].Actor->Scale.Get(), EBoneSpaces::WorldSpace);
			Bones[I].Actor->Scale.Clear();
		}
	}
}

#endif // #if WITH_EDITOR

#if WITH_EDITOR

bool ACsPoseableMeshActor::IsAssetEditorOpen()
{
	if (AnimLevelSequence.Master && FAssetEditorManager::Get().FindEditorForAsset(AnimLevelSequence.Master, false))
		return true;

	const int32 Count = AnimLevelSequence.Shots.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[I];

		if (Shot.Shot && FAssetEditorManager::Get().FindEditorForAsset(Shot.Shot, false))
			return true;
	}
	return false;
}

FLevelSequenceEditorToolkit* ACsPoseableMeshActor::GetOpenAssetEditor()
{
	if (AnimLevelSequence.Master)
	{
		if (FLevelSequenceEditorToolkit* Editor = (FLevelSequenceEditorToolkit*)(FAssetEditorManager::Get().FindEditorForAsset(AnimLevelSequence.Master, false)))
			return Editor;
	}

	const int32 Count = AnimLevelSequence.Shots.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[I];

		if (Shot.Shot)
		{
			if (FLevelSequenceEditorToolkit* Editor = (FLevelSequenceEditorToolkit*)(FAssetEditorManager::Get().FindEditorForAsset(Shot.Shot, false)))
				return Editor;
		}
	}
	return nullptr;
}

int32 ACsPoseableMeshActor::GetOpenShotIndexInEditor()
{
	const int32 Count = AnimLevelSequence.Shots.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[I];

		if (Shot.Shot && FAssetEditorManager::Get().FindEditorForAsset(Shot.Shot, false))
			return I;
	}
	return INDEX_NONE;
}

void ACsPoseableMeshActor::OnControlNameChanged_TwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control		= TwoBoneIK.Actor;

	TwoBoneIK.Control = Control->GetActorLabel();
}

void ACsPoseableMeshActor::OnControlNameChanged_FK(const int32 &Index)
{
	FCsAnimControlInfo_FK& FK   = Controls_FK[Index];
	ACsAnim_Control_FK* Control = FK.Actor;

	FK.Control = Control->GetActorLabel();
}

FString ACsPoseableMeshActor::GetMeshName()
{
	return PoseableMeshComponent->SkeletalMesh->GetName();
}

FString ACsPoseableMeshActor::GetBaseAssetName()
{
	return TEXT("seq_") + GetMeshName();
}

void ACsPoseableMeshActor::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeProperty(e);
		return;
	}

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// SkeletalMesh
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACsPoseableMeshActor, PoseableMeshComponent))
	{
		if (PoseableMeshComponent->SkeletalMesh != Last_SkeletalMesh)
		{
			if (PoseableMeshComponent->SkeletalMesh)
			{
				GenerateBones();
			}
			else
			{
				ClearControlsFK();
				ClearControlsTwoBoneIK();
				ClearBones();
			}
		}
		Last_SkeletalMesh = PoseableMeshComponent->SkeletalMesh;
	}
	// LevelSequence
	PostEditChangeProperty_LevelSequence_Master(e);

	Super::PostEditChangeProperty(e);
}

void ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Open
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimLevelSequenceInfo_Master, Open))
	{
		if (!AnimLevelSequence.Open)
			return;

		AnimLevelSequence.Open = false;

		if (!AnimLevelSequence.Master)
		{
			UCsCommon::DisplayNotificationInfo(TEXT("No Level Sequence created. LevelSequence.Master is NULL."), TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(%s): No Level Sequence created. LevelSequence.Master is NULL."), *GetName());
			return;
		}

		IAssetEditorInstance* AssetEditor = FAssetEditorManager::Get().FindEditorForAsset(AnimLevelSequence.Master, true);

		if (!AssetEditor)
		{
			UCsCommon::DisplayNotificationInfo(TEXT("Failed to Open Level Sequence Editor."), TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(%s): Failed to Open Level Sequence Editor."), *GetName());
			return;
		}

		const bool Success = FAssetEditorManager::Get().OpenEditorForAsset(AnimLevelSequence.Master);

		if (!Success)
		{
			const FString AssetName = AnimLevelSequence.Master->GetName();
			const FString Message   = TEXT("Failed to Open Level Sequence: ") + AssetName + TEXT(".");

			UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(%s): %s"), *GetName(), *Message);
			return;
		}
		return;
	}
	// FindOrCreate
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimLevelSequenceInfo_Master, FindOrCreate))
	{
		if (!AnimLevelSequence.FindOrCreate)
			return;

		AnimLevelSequence.FindOrCreate = false;

		if (AnimLevelSequence.Master)
			return;

		const FString MeshName		= GetMeshName();
		const FString BaseAssetName = GetBaseAssetName();
		const FString AssetName		= AnimLevelSequence.Name != TEXT("") ? BaseAssetName + TEXT("_") + AnimLevelSequence.Name + ("_master") : BaseAssetName + ("_master");

		FString PackageName = AnimLevelSequence.PackagePath != TEXT("") ? AnimLevelSequence.PackagePath : PoseableMeshComponent->SkeletalMesh->GetPathName();
		PackageName			= PackageName.Replace(*MeshName, TEXT(""));
		PackageName			= PackageName.Replace(TEXT("."), TEXT(""));

		if (PackageName.EndsWith(TEXT("/")))
		{
			const int32 Len = PackageName.Len();
			PackageName.RemoveAt(Len - 1);
		}

		TArray<ULevelSequence*> Sequences;
		TArray<FString> PackagePaths;
		UCsCommon_Asset::GetAssets<ULevelSequence>(AssetName, ECsStringCompare::Equals, Sequences, PackagePaths);

		const int32 SeqCount = Sequences.Num();

		if (SeqCount > CS_EMPTY)
		{
			if (SeqCount == 1)
			{
				AnimLevelSequence.Master = Sequences[CS_FIRST];
			}
			else
			{
				FString Message = TEXT("Multiple Level Sequences found with the Name: ") + AssetName;

				UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

				UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(%s): %s"), *GetName(), *Message);

				for (int32 I = 0; I < SeqCount; ++I)
				{
					const FString FullPathName = PackagePaths[I] + TEXT("/") + AssetName;
					Message						= TEXT("Level Sequence already exists at ") + FullPathName;

					UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

					UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeProperty_LevelSequence_Master(%s): %s"), *GetName(), *Message);
				}
				return;
			}
		}
		else
		{
			AnimLevelSequence.Master = UCsCommon_Asset::CreateLevelSequence(AssetName, PackageName);
		}

		ULevelSequence* Seq						 = AnimLevelSequence.Master;
		UMovieSceneCinematicShotTrack* ShotTrack = Cast<UMovieSceneCinematicShotTrack>(Seq->GetMovieScene()->FindMasterTrack(UMovieSceneCinematicShotTrack::StaticClass()));
	
		if (!ShotTrack)
		{
			ShotTrack = Cast<UMovieSceneCinematicShotTrack>(Seq->GetMovieScene()->AddMasterTrack(UMovieSceneCinematicShotTrack::StaticClass()));
		}
	}
}

void ACsPoseableMeshActor::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	if (!UCsCommon::IsPlayInEditor(GetWorld()))
	{
		Super::PostEditChangeChainProperty(e);
		return;
	}

	// Controls_FK
	PostEditChangeChainProperty_Control_FK(e);
	// Controls_FK[Index].Connections
	PostEditChangeChainProperty_Control_FK_Connection(e);
	// Controls_TwoBoneIK
	PostEditChangeChainProperty_TwoBoneIK(e);
	// LevelSequence
	PostEditChangeChainProperty_LevelSequence_Shots(e);

	Super::PostEditChangeChainProperty(e);
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_Control_FK(struct FPropertyChangedChainEvent& e)
{
	// Controls_FK
	const int32 Index = e.GetArrayIndex(TEXT("Controls_FK"));

	if (Index == INDEX_NONE)
		return;

	FCsAnimControlInfo_FK& FK = Controls_FK[Index];

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	const int32 ControlCount = Controls_FK.Num();
	const int32 CopyCount    = Controls_FK_Copy.Num();

	// Check if NEW elements were ADDED
	if (ControlCount > CopyCount)
	{
		const int32 Delta = ControlCount - CopyCount;

		for (int32 I = 0; I < Delta; ++I)
		{
			const int32 CopyIndex = CopyCount + I;

			Create_Control_FK(CopyIndex);

			Controls_FK_Copy.AddDefaulted();
			Controls_FK_Copy[CopyIndex] = Controls_FK[CopyIndex];
		}
	}
	// Check if elements were REMOVED
	if (ControlCount < CopyCount)
	{
		const int32 Delta = CopyCount - ControlCount;

		for (int32 I = CopyCount - 1; I >= CopyCount - Delta; --I)
		{
			ACsAnim_Control_FK* Control = Controls_FK_Copy[I].Actor;

			if (Control && !Control->IsPendingKill())
			{
				if (Control->Anchor && !Control->Anchor->IsPendingKill())
					Control->Anchor->Destroy();
				Control->Destroy();
			}
			Controls_FK_Copy.RemoveAt(I);
		}
	}
	// Controls_FK[Index].Control
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK, Control))
	{
		if (ACsAnim_Control_FK* Control = FK.Actor)
		{
			Control->SetControlName(FK.Control);
		}
	}
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_Control_FK_Connection(struct FPropertyChangedChainEvent& e)
{
	const int32 Index = e.GetArrayIndex(TEXT("Connections"));

	if (Index == INDEX_NONE)
		return;

	// Search through Controls_FK and see if any Connections were ADDED / REMOVED
	int32 ControlIndex		 = INDEX_NONE;
	const int32 ControlCount = Controls_FK.Num();

	for (int32 I = 0; I < ControlCount; ++I)
	{
		if (Controls_FK[I].Connections.Num() != Controls_FK[I].Connections_Copy.Num())
		{
			ControlIndex = I;
			break;
		}
	}

	if (ControlIndex != INDEX_NONE)
	{
		FCsAnimControlInfo_FK& FK   = Controls_FK[ControlIndex];
		ACsAnim_Control_FK* Control = FK.Actor;

		const int32 ConnectionCount = FK.Connections.Num();
		const int32 CopyCount		= FK.Connections_Copy.Num();

		// Check if NEW elements were ADDED
		if (ConnectionCount > CopyCount)
		{
			const int32 Delta = ConnectionCount - CopyCount;

			for (int32 I = 0; I < Delta; ++I)
			{
				const int32 CopyIndex = CopyCount + I;

				FK.Connections_Copy.AddDefaulted();
				FK.Connections_Copy[CopyIndex] = FK.Connections[CopyIndex];
			}
		}
		// Check if elements were REMOVED
		if (ConnectionCount < CopyCount)
		{
			const int32 Delta = CopyCount - ConnectionCount;

			for (int32 I = CopyCount - 1; I >= CopyCount - Delta; --I)
			{
				FK.Connections_Copy.RemoveAt(I);
			}
		}
		return;
	}

	for (int32 I = 0; I < ControlCount; ++I)
	{
		FCsAnimControlInfo_FK& FK = Controls_FK[I];
		FCsAnimControlInfo_FK_Connection& Connection = FK.Connections[Index];

		if (Connection.Bone != Connection.Last_Bone ||
			Connection.SnapToBone != Connection.Last_SnapToBone ||
			Connection.Output.Member != Connection.Output.Last_Member ||
			Connection.Output.Axes != Connection.Output.Last_Axes ||
			Connection.Input.Member != Connection.Input.Last_Member ||
			Connection.Input.Axes != Connection.Input.Last_Axes)
		{
			ControlIndex = I;
			break;
		}
	}

	if (ControlIndex == INDEX_NONE)
		return;

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	FCsAnimControlInfo_FK& FK					 = Controls_FK[ControlIndex];
	ACsAnim_Control_FK* Control					 = FK.Actor;
	FCsAnimControlInfo_FK_Connection& Connection = FK.Connections[Index];

	// Controls_FK[ControlIndex].Connections[Index].Bone
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_Connection, Bone))
	{
		const FName BoneName = Connection.Bone;

		if (BoneName == NAME_None)
		{
			Connection.Last_Bone	  = NAME_None;
			Connection.BoneIndex	  = INDEX_NONE;
			Connection.BoneArrayIndex = INDEX_NONE;
			return;
		}

		const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
		Connection.BoneIndex = BoneIndex;

		if (BoneIndex == INDEX_NONE)
		{
			Connection.Bone			  = NAME_None;
			Connection.Last_Bone	  = NAME_None;
			Connection.BoneArrayIndex = INDEX_NONE;
			return;
		}

		const int32 Count = Bones.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Bones[I].Bone == BoneName)
			{
				Connection.BoneArrayIndex = I;
				break;
			}
		}
		Connection.Last_Bone = Connection.Bone;
	}
	// Controls_FK[ControlIndex].Connections[Index].SnapToBone
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_Connection, SnapToBone))
	{
		if (Connection.SnapToBone)
		{
			const int32 BoneIndex = Connection.BoneIndex;

			if (BoneIndex == INDEX_NONE)
				return;

			const int32 BoneArrayIndex = Connection.BoneArrayIndex;

			if (Control)
			{
				ACsAnim_Bone* Bone = Bones[BoneArrayIndex].Actor;
				Control->Anchor->SetActorTransform(Bone->GetActorTransform());
			}
		}
		Connection.SnapToBone = false;
		Connection.Last_SnapToBone = Connection.SnapToBone;
	}
	// Controls_FK[ControlIndex].Connections[Index].Ouput.Member
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_ConnectionOutput, Member))
	{
		Connection.Output.Last_Member = Connection.Output.Member;
	}
	// Controls_FK[ControlIndex].Connections[Index].Ouput.Axes
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_ConnectionOutput, Axes))
	{
		Connection.Output.Last_Axes = Connection.Output.Axes;
	}
	// Controls_FK[ControlIndex].Connections[Index].Input.Member
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_ConnectionInput, Member))
	{
		Connection.Input.Last_Member = Connection.Input.Member;
	}
	// Controls_FK[ControlIndex].Connections[Index].Input.Axes
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_FK_ConnectionInput, Axes))
	{
		Connection.Input.Last_Axes = Connection.Input.Axes;
	}
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_TwoBoneIK(struct FPropertyChangedChainEvent& e)
{
	const int32 Index = e.GetArrayIndex(TEXT("Controls_TwoBoneIK"));

	if (Index == INDEX_NONE)
		return;

	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];

	// SkeletalMesh is NULL
	if (!PoseableMeshComponent->SkeletalMesh)
	{
		UCsCommon::DisplayNotificationInfo(TEXT("SkeletalMesh is NULL."), TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 5.0f);

		UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_TwoBoneIK(%s): SkeletalMesh is NULL. Can NOT update Controls."), *GetName());
		return;
	}

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	const int32 ControlCount = Controls_TwoBoneIK.Num();
	const int32 CopyCount = Controls_TwoBoneIK_Copy.Num();

	// Check if NEW elements were ADDED
	if (ControlCount > CopyCount)
	{
		const int32 Delta = ControlCount - CopyCount;

		for (int32 I = 0; I < Delta; ++I)
		{
			const int32 CopyIndex = CopyCount + I;

			Create_Control_TwoBoneIK(CopyIndex);

			Controls_TwoBoneIK_Copy.AddDefaulted();
			Controls_TwoBoneIK_Copy[CopyIndex] = Controls_TwoBoneIK[CopyIndex];
		}
	}
	// Check if elements were REMOVED
	if (ControlCount < CopyCount)
	{
		const int32 Delta = CopyCount - ControlCount;

		for (int32 I = CopyCount - 1; I >= CopyCount - Delta; --I)
		{
			ACsAnim_Control_TwoBoneIK* Control = Controls_TwoBoneIK_Copy[I].Actor;

			if (Control && !Control->IsPendingKill())
			{
				if (Control->Anchor && !Control->Anchor->IsPendingKill())
					Control->Anchor->Destroy();
				if (Control->EndEffector && !Control->EndEffector->IsPendingKill())
					Control->EndEffector->Destroy();
				if (Control->JointTarget && !Control->JointTarget->IsPendingKill())
					Control->JointTarget->Destroy();
				Control->Destroy();
			}
			Controls_TwoBoneIK_Copy.RemoveAt(I);
		}
	}
	// Controls_TwoBoneIK[Index].Control
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_TwoBoneIK, Control))
	{
		if (ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor)
		{
			Control->SetControlName(TwoBoneIK.Control);
		}
	}
	// Controls_TwoBoneIK[Index].IK.IKBone
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimControlInfo_TwoBoneIK_IK, IKBone))
	{
		const FName BoneName = TwoBoneIK.IK.IKBone;
		const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);

		TwoBoneIK.IK.IKBoneIndex = BoneIndex;

		TwoBoneIK.EndEffector.EffectorSpaceBoneName = BoneName;
		TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = BoneIndex;

		if (BoneName == NAME_None || BoneIndex == INDEX_NONE)
		{
			TwoBoneIK.IK.IKBone = NAME_None;
			TwoBoneIK.IK.IKBoneIndex = INDEX_NONE;
			TwoBoneIK.IK.IKBoneArrayIndex = INDEX_NONE;
			TwoBoneIK.IK.Last_IKBone = BoneName;
			TwoBoneIK.IK.ParentBone = NAME_None;
			TwoBoneIK.IK.ParentBoneIndex = INDEX_NONE;
			TwoBoneIK.IK.ParentBoneIndex = INDEX_NONE;

			TwoBoneIK.EndEffector.EffectorSpaceBoneName = NAME_None;
			TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = INDEX_NONE;
			TwoBoneIK.EndEffector.EffectorSpaceBoneArrayIndex = NAME_None;

			TwoBoneIK.JointTarget.JointTargetSpaceBoneName = NAME_None;
			TwoBoneIK.JointTarget.JointTargetSpaceBoneIndex = INDEX_NONE;
			TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

			if (ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor)
			{
				Control->StartBone = nullptr;
				Control->MiddleBone = nullptr;
				Control->EndBone = nullptr;
			}

			Controls_TwoBoneIK_Copy[Index] = TwoBoneIK;
			return;
		}

		if (BoneName == TwoBoneIK.IK.Last_IKBone)
			return;

		TwoBoneIK.IK.Last_IKBone = BoneName;

		ACsAnim_Control_TwoBoneIK* Control = TwoBoneIK.Actor;

		if (!Control)
		{
			DestroyOrphanedControlAnchors();
			DestroyOrphanedControlHelpers();
		}

		Create_Control_TwoBoneIK(Index);
		Controls_TwoBoneIK_Copy[Index] = Controls_TwoBoneIK[Index];
	}
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots(struct FPropertyChangedChainEvent& e)
{
	const int32 Index = e.GetArrayIndex(TEXT("Shots"));

	if (Index == INDEX_NONE)
		return;

	FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[Index];

	const int32 ShotCount = AnimLevelSequence.Shots.Num();
	const int32 CopyCount = AnimLevelSequence.Shots_Copy.Num();

	// Check if NEW elements were ADDED
	if (ShotCount > CopyCount)
	{
		const int32 Delta = ShotCount - CopyCount;

		for (int32 I = 0; I < Delta; ++I)
		{
			const int32 CopyIndex = CopyCount + I;

			AnimLevelSequence.Shots_Copy.AddDefaulted();
			AnimLevelSequence.Shots_Copy[CopyIndex] = AnimLevelSequence.Shots_Copy[CopyIndex];
		}
	}
	// Check if elements were REMOVED
	if (ShotCount < CopyCount)
	{
		const int32 Delta = CopyCount - ShotCount;

		for (int32 I = CopyCount - 1; I >= CopyCount - Delta; --I)
		{
			AnimLevelSequence.Shots_Copy.RemoveAt(I);
		}
	}

	// AnimLevelSequence.Shots[Index].FindOrCreate
	PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(e);
	// AnimLevelSequence.Shots[Index].Export
	PostEditChangeChainProperty_LevelSequence_Shots_Export(e);

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// AnimLevelSequence.Shots[Index].ExportInterval
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsAnimLevelSequenceInfo_Shot, Export))
	{
		Shot.ExportInterval_Internal = ECsSequencerTimeSnapInterval::ToFloat(Shot.ExportInterval);
		Shot.ExportInterval_FPS = ECsSequencerTimeSnapInterval::ToFPS(Shot.ExportInterval);
		return;
	}
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(struct FPropertyChangedChainEvent& e)
{
	const int32 Index = e.GetArrayIndex(TEXT("Shots"));

	if (Index == INDEX_NONE)
		return;

	FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[Index];

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (PropertyName != GET_MEMBER_NAME_CHECKED(FCsAnimLevelSequenceInfo_Shot, FindOrCreate))
		return;

	if (!Shot.FindOrCreate)
		return;

	Shot.FindOrCreate = false;

	USkeletalMesh* Mesh = PoseableMeshComponent->SkeletalMesh;

	if (!Mesh)
	{
		const FString Message = TEXT("SkeletalMesh is NULL.");

		UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 5.0f);

		UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(%s): %s"), *GetName(), *Message);
		return;
	}

	if (Shot.Name == TEXT(""))
	{
		const FString Message = TEXT("No Name set for AnimLevelSequence.Shots[") + FString::FromInt(Index) + TEXT("].Name.");

		UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 5.0f);

		UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(%s): %s"), *GetName(), *Message);
		return;
	}
	// Check for existing Level Sequence
	const FString BaseAssetName = GetBaseAssetName();
	const FString AssetName		= BaseAssetName + TEXT("_") + Shot.Name;

	TArray<ULevelSequence*> Sequences;
	TArray<FString> PackagePaths;
	UCsCommon_Asset::GetAssets<ULevelSequence>(AssetName, ECsStringCompare::Equals, Sequences, PackagePaths);

	const int32 SeqCount = Sequences.Num();
	// Found
	if (SeqCount > CS_EMPTY)
	{
		// If Only ONE, Set Shot
		if (SeqCount == 1)
		{
			// Verify the Shot
			ULevelSequence* Seq		= Sequences[CS_FIRST];
			UMovieScene* MovieScene = Seq->GetMovieScene();
			
			const FString MeshName = GetMeshName();
			const FString AnimName = TEXT("anim_") + MeshName + TEXT("_") + Shot.Name;

			// Check Folder Exists
			TArray<UMovieSceneFolder*>& Folders = MovieScene->GetRootFolders();
			const int32 FolderCount				= Folders.Num();

			UMovieSceneFolder* MainFolder = nullptr;

			// If NO Folders, CREATE it.
			if (FolderCount == CS_EMPTY)
			{
				MainFolder = NewObject<UMovieSceneFolder>(MovieScene, NAME_None, RF_Transactional);
				MainFolder->SetFolderName(FName(*AnimName));
				Folders.Add(MainFolder);
			}
			// If Folder does NOT Exist, CREATE it.
			else
			{
				bool Found = false;

				for (int32 I = 0; I < FolderCount; ++I)
				{
					const FString FolderName = Folders[I]->GetFolderName().ToString();

					if (AnimName.ToLower() == FolderName.ToLower())
					{
						MainFolder = Folders[I];
						Found = true;
						break;
					}
				}

				if (!Found)
				{
					MainFolder = NewObject<UMovieSceneFolder>(MovieScene, NAME_None, RF_Transactional);
					MainFolder->SetFolderName(FName(*AnimName));
					Folders.Add(MainFolder);
				}
			}

			TArray<FGuid> QueueBindPossessableGuids;
			TArray<AActor*> QueueBindPossessableActors;
			TArray<FGuid> QueueAddGuidsToFolder;

			const int32 BoneCount = Bones.Num();

			for (int32 I = 0; I < BoneCount; ++I)
			{
				const FString BoneName = Bones[I].Bone.ToString();
				ACsAnim_Bone* Actor	   = Bones[I].Actor;

				// Check if any Possessable matches Actor

				const int32 PossessableCount = MovieScene->GetPossessableCount();

				for (int32 J = 0; J < PossessableCount; J++)
				{
					bool CheckActorIsInFolder = true;

					FMovieScenePossessable& Possessable = MovieScene->GetPossessable(J);
					const FGuid Guid					= Possessable.GetGuid();
					const FString ActorName				= Possessable.GetName();

					TArray<UObject*, TInlineAllocator<1>> Objects;

					Seq->LocateBoundObjects(Guid, GetWorld(), Objects);

					const int32 ObjectCount = Objects.Num();
					// If Guid is NOT Bound and ActorName is VALID (i.e. the Actor exists), then Bind it
					if (ObjectCount == CS_EMPTY)
					{
						if (BoneName == ActorName)
						{
							QueueBindPossessableGuids.Add(Guid);
							QueueBindPossessableActors.Add(Actor);
						}
						else
						{
							CheckActorIsInFolder = false;
						}
					}
					else
					{
						bool Found = false;

						for (int32 K = 0; K < ObjectCount; K++)
						{
							if (Actor == Cast<ACsAnim_Bone>(Objects[K]))
							{
								Possessable.SetName(BoneName);
								Found = true;
								break;
							}
						}

						if (!Found)
						{
							if (BoneName == ActorName)
							{
								QueueBindPossessableGuids.Add(Guid);
								QueueBindPossessableActors.Add(Actor);
							}
							else
							{
								CheckActorIsInFolder = false;
							}
						}
					}

					if (CheckActorIsInFolder)
					{
						bool Found = false;

						const TArray<FGuid>& Bindings = MainFolder->GetChildObjectBindings();
						const int32 BindingCount	  = Bindings.Num();

						for (int32 K = 0; K < BindingCount; K++)
						{
							if (Guid == Bindings[K])
							{
								Found = true;
								break;
							}
						}

						if (!Found)
						{
							QueueAddGuidsToFolder.Add(Guid);
						}
					}
				}
			}

			// Add Queued Bindings

			int32 QueueCount = QueueBindPossessableGuids.Num();

			for (int32 I = 0; I < QueueCount; ++I)
			{
				Seq->BindPossessableObject(QueueBindPossessableGuids[I], *(QueueBindPossessableActors[I]), GetWorld());
			}

			QueueCount = QueueAddGuidsToFolder.Num();

			for (int32 I = 0; I < QueueCount; ++I)
			{
				MainFolder->AddChildObjectBinding(QueueAddGuidsToFolder[I]);
			}
			
			FString PackagePath = Seq->GetPathName();
			PackagePath			= PackagePath.Replace(*AssetName, TEXT(""));
			PackagePath			= PackagePath.Replace(TEXT("."), TEXT(""));

			if (PackagePath.EndsWith(TEXT("/")))
			{
				const int32 Len = PackagePath.Len();
				PackagePath.RemoveAt(Len - 1);
			}

			AnimLevelSequence.PackagePath = PackagePath;

			AnimLevelSequence.Shots[Index].Shot = Sequences[CS_FIRST];
		}
		// Else MORE than ONE, ERROR
		else
		{
			FString Message = TEXT("Multiple Level Sequences with the AnimLevelSequence.Shots[") + FString::FromInt(Index) + TEXT("].Name: ") + AssetName + TEXT(".");

			UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 5.0f);

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(%s): %s"), *GetName(), *Message);

			for (int32 I = 0; I < SeqCount; ++I)
			{
				const FString FullPathName = PackagePaths[I] + TEXT("/") + AssetName;
				Message = TEXT("Level Sequence already exists at ") + FullPathName;

				UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeChainProperty"), 2.0f);

				UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(%s): %s"), *GetName(), *Message);
			}
			return;
		}
	}
	// NOT Found, Create it
	else
	{
		const FString MeshName = GetMeshName();
		FString PackageName	   = PoseableMeshComponent->SkeletalMesh->GetPathName();
		PackageName			   = PackageName.Replace(*MeshName, TEXT(""));
		PackageName			   = PackageName.Replace(TEXT("."), TEXT(""));

		if (PackageName.EndsWith(TEXT("/")))
		{
			const int32 Len = PackageName.Len();
			PackageName.RemoveAt(Len - 1);
		}

		AnimLevelSequence.Shots[Index].Shot = UCsCommon_Asset::CreateLevelSequence(AssetName, PackageName);

		ULevelSequence* Seq     = AnimLevelSequence.Shots[Index].Shot;
		const float DeltaTime   = 2.0f;
		UMovieScene* MovieScene = Seq->GetMovieScene();
		MovieScene->SetPlaybackRange(FFrameNumber(0), DeltaTime);

		UMovieSceneFolder* NewFolder = NewObject<UMovieSceneFolder>(MovieScene, NAME_None, RF_Transactional);
		const FString AnimName	     = TEXT("anim_") + MeshName + TEXT("_") + Shot.Name;
		NewFolder->SetFolderName(FName(*AnimName));
		MovieScene->GetRootFolders().Add(NewFolder);

		// Populate Level Sequence with Actors

		const int32 BoneCount = Bones.Num();

		for (int32 I = 0; I < BoneCount; ++I)
		{
			FGuid Guid = MovieScene->AddPossessable(Bones[I].Actor->GetActorLabel(), Bones[I].Actor->GetClass());
			Seq->BindPossessableObject(Guid, *(Bones[I].Actor), GetWorld());
			
			AnimLevelSequence_Shot_AddTransformTrack(Index, Guid, Bones[I].Actor);

			NewFolder->AddChildObjectBinding(Guid);
		}

		// Add to Master Track
		ULevelSequence* Master = AnimLevelSequence.Master;

		if (Master)
		{
			UMovieSceneCinematicShotTrack* ShotTrack = Cast<UMovieSceneCinematicShotTrack>(Master->GetMovieScene()->FindMasterTrack(UMovieSceneCinematicShotTrack::StaticClass()));

			if (!ShotTrack)
			{
				ShotTrack = Cast<UMovieSceneCinematicShotTrack>(Master->GetMovieScene()->AddMasterTrack(UMovieSceneCinematicShotTrack::StaticClass()));
			}

			const TArray<UMovieSceneSection*>& Sections = ShotTrack->GetAllSections();

			const int32 SectionCount = Sections.Num();

			/*
			if (SectionCount > CS_EMPTY)
			{
				float LastTime = 0.0f;

				for (int32 I = 0; I < SectionCount; ++I)
				{
					if (LastTime < Sections[I]->GetEndTime())
						LastTime = Sections[I]->GetEndTime();
				}

				const float BufferTime = 0.1f;
				const float StartTime  = LastTime + BufferTime;
				const float EndTime    = StartTime + DeltaTime;

				ShotTrack->AddSequence(Seq, LastTime + BufferTime, EndTime);
			}
			else
			{
				ShotTrack->AddSequence(Seq, 0.0f, DeltaTime);
			}
			*/
		}
		else
		{
			// Warning
		}
	}
	AnimLevelSequence.Shots_Copy[Index] = AnimLevelSequence.Shots[Index];
}

void ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_Export(struct FPropertyChangedChainEvent& e)
{
	const int32 Index = e.GetArrayIndex(TEXT("Shots"));

	if (Index == INDEX_NONE)
		return;

	FCsAnimLevelSequenceInfo_Shot& Shot = AnimLevelSequence.Shots[Index];

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// AnimLevelSequence.Shots[Index].Export
	if (PropertyName != GET_MEMBER_NAME_CHECKED(FCsAnimLevelSequenceInfo_Shot, Export))
		return;

	if (!Shot.Export)
		return;

	Shot.Export = false;

	if (!Shot.Shot)
	{
		return;
	}

	if (Shot.Name == TEXT(""))
	{
		return;
	}

	ULevelSequence* Seq = Shot.Shot;

	if (!Seq->GetName().Contains(Shot.Name))
	{
		return;
	}

	// Check if an Animation has already been created
	UAnimSequence* Anim = nullptr;

	if (Shot.Anim)
	{
		Anim = Shot.Anim;
	}
	else
	{
		const FString MeshName = PoseableMeshComponent->SkeletalMesh->GetName();
		const FString AnimName = TEXT("anim_") + MeshName + TEXT("_") + Shot.Name;

		TArray<UAnimSequence*> Anims;
		TArray<FString> PackagePaths;
		UCsCommon_Asset::GetAssets<UAnimSequence>(AnimName, ECsStringCompare::Equals, Anims, PackagePaths);

		const int32 AnimCount = Anims.Num();

		// Already Exists
		if (AnimCount > CS_EMPTY)
		{
			// If ONE, Set it
			if (AnimCount == 1)
			{
				Anim = Anims[CS_FIRST];
				Shot.Anim = Anim;
			}
			// Else MORE than ONE, ERROR
			else
			{
				FString Message = TEXT("Multiple Anim Sequences found with the Name: ") + AnimName;

				UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 5.0f);

				UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_Export(%s): %s"), *GetName(), *Message);

				for (int32 I = 0; I < AnimCount; ++I)
				{
					const FString FullPathName = PackagePaths[I] + TEXT("/") + AnimName;
					Message = TEXT("Anim Sequence already exists at ") + FullPathName;

					UCsCommon::DisplayNotificationInfo(Message, TEXT("PoseableMesh"), TEXT("PostEditChangeProperty"), 2.0f);

					UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PostEditChangeChainProperty_LevelSequence_Shots_Export(%s): %s"), *GetName(), *Message);
				}
				return;
			}
		}
		// NONE Exists, Create it
		else
		{
			FString PackageName = PoseableMeshComponent->SkeletalMesh->GetPathName();
			PackageName = PackageName.Replace(*MeshName, TEXT(""));
			PackageName = PackageName.Replace(TEXT("."), TEXT(""));

			const int32 Len = PackageName.Len();
			PackageName.RemoveAt(Len - 1);

			Anim = UCsCommon_Asset::CreateAnimSequence(PoseableMeshComponent->SkeletalMesh, AnimName, PackageName);
			Shot.Anim = Anim;
		}
	}

	UCsCommon_Asset::InitAnimSequence(Anim, PoseableMeshComponent);

	// Create a sequence actor to run the sequence off of
	ALevelSequenceActor* LevelSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	LevelSequenceActor->LevelSequence = Seq;
	LevelSequenceActor->PlaybackSettings.bRestoreState = true;
	LevelSequenceActor->SequencePlayer = NewObject<ULevelSequencePlayer>(LevelSequenceActor, "AnimationPlayer");
	LevelSequenceActor->SequencePlayer->Initialize(Seq, GetWorld(), LevelSequenceActor->PlaybackSettings);

	// Now run our sequence
	UMovieScene* MovieScene = Seq->GetMovieScene();

	double StartTime		= (double)MovieScene->GetPlaybackRange().GetLowerBoundValue().Value;
	double SequenceLength   = 0.0f;// Anim->SequenceLength = MovieScene->GetPlaybackRange().Size<float>();
	const float FPS			= Shot.ExportInterval_FPS;
	int32 FrameCount		= Anim->NumFrames = FMath::CeilToInt(SequenceLength * FPS);
	double FrameCountDouble = (double)FrameCount;
	double FrameLength		= 1.0 / (double)FPS;

	USkeleton* Skeleton = Anim->GetSkeleton();
	USkeletalMesh* SkeletalMesh = PoseableMeshComponent->SkeletalMesh;

	for (int32 Frame = 0; Frame < FrameCount; ++Frame)
	{
		float CurrentTime = (float)(StartTime + FMath::Clamp(((double)Frame / FrameCountDouble) * SequenceLength, 0.0, SequenceLength));

		// Tick Sequence
		//LevelSequenceActor->SequencePlayer->SetPlaybackPosition(CurrentTime);

		// Copy data to tracks
		const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();
		const int32 TrackCount				= Anim->GetRawAnimationData().Num();

		for (int32 TrackIndex = 0; TrackIndex < TrackCount; ++TrackIndex)
		{
			// verify if this bone exists in skeleton
			int32 BoneTreeIndex = Anim->GetSkeletonIndexFromRawDataTrackIndex(TrackIndex);

			if (BoneTreeIndex != INDEX_NONE)
			{
				FRawAnimSequenceTrack& RawTrack = Anim->GetRawAnimationTrack(TrackIndex);

				int32 BoneIndex = Skeleton->GetMeshBoneIndexFromSkeletonBoneIndex(SkeletalMesh, BoneTreeIndex);

				FTransform Transform = Bones[BoneIndex].Actor->GetRootComponent()->GetRelativeTransform();
				//Transform.SetToRelativeTransform(ComponentTransform);

				RawTrack.PosKeys.Add(Transform.GetTranslation());
				RawTrack.RotKeys.Add(Transform.GetRotation());
				RawTrack.ScaleKeys.Add(Transform.GetScale3D());
			}
		}
	}

	Anim->PostProcessSequence();
	Anim->MarkPackageDirty();

	// Set Bones back to their original location
	ResetBones();

	// Clean up the temp objects we used for export
	LevelSequenceActor->SequencePlayer->Stop();
	LevelSequenceActor->SequencePlayer->MarkPendingKill();
	LevelSequenceActor->Destroy();

	// TODO - Setting just to Export the Keys set

	/*
	UMovieScene* MovieScene = Seq->GetMovieScene();

	const int32 PossessableCount = MovieScene->GetPossessableCount();

	for (int32 I = 0; I < PossessableCount; ++I)
	{
	FMovieScenePossessable& Possessable = MovieScene->GetPossessable(I);
	const FGuid Guid					= Possessable.GetGuid();

	UMovieScene3DTransformTrack* TransformTrack		= Cast<UMovieScene3DTransformTrack>(MovieScene->FindTrack(UMovieScene3DTransformTrack::StaticClass(), Guid, "Transform"));
	const TArray<UMovieSceneSection*>& Sections		= TransformTrack->GetAllSections();
	UMovieSceneSection* Section						= Sections[CS_FIRST];
	UMovieScene3DTransformSection* TransformSection = CastChecked<UMovieScene3DTransformSection>(Section);
	}
	*/
}

void ACsPoseableMeshActor::AnimLevelSequence_Shot_AddTransformTrack(const int32 &Index, const FGuid& Guid, AActor* Actor)
{
	ULevelSequence* Seq		= AnimLevelSequence.Shots[Index].Shot;
	UMovieScene* MovieScene = Seq->GetMovieScene();

	UMovieScene3DTransformTrack* TransformTrack = Cast<UMovieScene3DTransformTrack>(MovieScene->AddTrack(UMovieScene3DTransformTrack::StaticClass(), Guid));

	const bool bUnwindRotation						= false;
	const TArray<UMovieSceneSection*>& Sections	    = TransformTrack->GetAllSections();

	TransformTrack->AddSection(*TransformTrack->CreateNewSection());

	UMovieSceneSection* Section						= Sections[CS_FIRST];
	UMovieScene3DTransformSection* TransformSection = CastChecked<UMovieScene3DTransformSection>(Section);

	FTransform ActorRelativeTransform = Actor->GetRootComponent()->GetRelativeTransform();

	const FVector Location  = ActorRelativeTransform.GetTranslation();
	const FRotator Rotation = ActorRelativeTransform.GetRotation().Rotator();
	const FVector Scale     = ActorRelativeTransform.GetScale3D();
	
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Translation, EAxis::X, Location.X, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Translation, EAxis::Y, Location.Y, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Translation, EAxis::Z, Location.Z, false /*bUnwindRotation*/));

	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Rotation, EAxis::X, Rotation.Euler().X, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Rotation, EAxis::Y, Rotation.Euler().Y, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Rotation, EAxis::Z, Rotation.Euler().Z, false /*bUnwindRotation*/));

	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Scale, EAxis::X, Scale.X, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Scale, EAxis::Y, Scale.Y, false /*bUnwindRotation*/));
	//TransformSection->SetDefault(FTransformKey(EKey3DTransformChannel::Scale, EAxis::Z, Scale.Z, false /*bUnwindRotation*/));
}

void ACsPoseableMeshActor::AnimLevelSequence_Shot_AddKey(const int32 &Index, AActor* Actor)
{
	ULevelSequence* Seq		= AnimLevelSequence.Shots[Index].Shot;
	UMovieScene* MovieScene = Seq->GetMovieScene();

	// Find Guid for Actor
	FGuid Guid;

	const int32 PossessableCount = MovieScene->GetPossessableCount();

	for (int32 I = 0; I < PossessableCount; ++I)
	{
		FMovieScenePossessable Possessable = MovieScene->GetPossessable(I);
		Guid							   = Possessable.GetGuid();

		TArray<UObject*, TInlineAllocator<1>> Objects;

		Seq->LocateBoundObjects(Guid, GetWorld(), Objects);

		const int32 ObjectCount = Objects.Num();

		if (ObjectCount == CS_EMPTY)
			continue;
		
		bool Found = false;

		for (int32 J = 0; J < ObjectCount; J++)
		{
			if (Actor == Cast<AActor>(Objects[J]))
			{
				Found = true;
				break;
			}
		}

		if (Found)
			break;
	}

	UMovieScene3DTransformTrack* TransformTrack		= Cast<UMovieScene3DTransformTrack>(MovieScene->FindTrack(UMovieScene3DTransformTrack::StaticClass(), Guid, TEXT("Transform")));
	const TArray<UMovieSceneSection*>& Sections		= TransformTrack->GetAllSections();
	UMovieSceneSection* Section						= Sections[CS_FIRST];
	UMovieScene3DTransformSection* TransformSection = CastChecked<UMovieScene3DTransformSection>(Section);
	/*
	const float CurrentTime = LevelSequenceEditor->GetSequencer().Get()->GetGlobalTime();

	if (CurrentTime > TransformSection->GetEndTime())
		TransformSection->SetEndTime(CurrentTime);
	*/
	FTransform ActorRelativeTransform = Actor->GetRootComponent()->GetRelativeTransform();

	const FVector Location = ActorRelativeTransform.GetTranslation();
	const FRotator Rotation = ActorRelativeTransform.GetRotation().Rotator();
	const FVector Scale = ActorRelativeTransform.GetScale3D();

	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Translation, EAxis::X, Location.X, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Translation, EAxis::Y, Location.Y, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Translation, EAxis::Z, Location.Z, false), EMovieSceneKeyInterpolation::Auto);

	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Rotation, EAxis::X, Rotation.Euler().X, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Rotation, EAxis::Y, Rotation.Euler().Y, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Rotation, EAxis::Z, Rotation.Euler().Z, false), EMovieSceneKeyInterpolation::Auto);

	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Scale, EAxis::X, Scale.X, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Scale, EAxis::Y, Scale.Y, false), EMovieSceneKeyInterpolation::Auto);
	//TransformSection->AddKey(CurrentTime, FTransformKey(EKey3DTransformChannel::Scale, EAxis::Z, Scale.Z, false), EMovieSceneKeyInterpolation::Auto);
}

// Bones
#pragma region

void ACsPoseableMeshActor::GenerateBones()
{
	ClearBones();
	
	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

	TArray<FName> BoneNames;
	PoseableMeshComponent->GetBoneNames(BoneNames);

	const int32 Count = BoneNames.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsAnim_Bone* Bone = GetWorld()->SpawnActor<ACsAnim_Bone>();

		const FName BoneName = BoneNames[I];
		Bone->SetActorLabel(BoneName.ToString());
		Bone->Bone = BoneName;
		Bone->Root = this;

		Bone->SetActorRelativeTransform(FTransform::Identity);
	
		const FName ParentBoneName = PoseableMeshComponent->GetParentBone(BoneName);
		int32 ParentBoneIndex	   = INDEX_NONE;

		if (ParentBoneName == NAME_None)
		{
			Bone->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
		else
		{
			const int32 InfoCount = Bones.Num();

			for (int32 J = 0; J < InfoCount; J++)
			{
				if (Bones[J].Bone == ParentBoneName)
				{
					ParentBoneIndex = Bones[J].BoneIndex;
					Bone->AttachToActor(Bones[J].Actor, FAttachmentTransformRules::KeepRelativeTransform);
					break;
				}
			}
		}
		
		const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
		Bone->BoneIndex		  = BoneIndex;
		Bone->ParentBone	  = ParentBoneName;
		Bone->ParentBoneIndex = ParentBoneIndex;
		// Store Local / Relative Transform
		Bone->DefaultRelativeTransform = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];
		Bone->UpdateRelativeTransform(Bone->DefaultRelativeTransform, true);
		// Store Component Transform - WorldSpace -> ComponentSpace
		Bone->DefaultComponentTransform = PoseableMeshComponent->GetBoneTransform(BoneIndex);
		Bone->DefaultComponentTransform.SetToRelativeTransform(ComponentTransform);

		Bone->ArrayIndex = I;

		Bones.AddDefaulted();
		const int32 Index = Bones.Num() - 1;
		Bones[Index].Bone = BoneName;
		Bones[Index].BoneIndex = BoneIndex;
		Bones[Index].ParentBone = ParentBoneName;
		Bones[Index].ParentBoneIndex = ParentBoneIndex;
		Bones[Index].Actor = Bone;
	}
}

void ACsPoseableMeshActor::ClearBones()
{
	const int32 Count = Bones.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Bones[I].Actor && !Bones[I].Actor->IsPendingKill())
			Bones[I].Actor->Destroy();
	}
	Bones.Reset();
}

void ACsPoseableMeshActor::RecreateBone(const int32 &Index)
{
	ACsAnim_Bone* Bone = GetWorld()->SpawnActor<ACsAnim_Bone>();

	Bones[Index].Actor   = Bone;
	const FName BoneName = Bones[Index].Bone;
	Bone->SetActorLabel(BoneName.ToString());
	Bone->Bone = BoneName;
	Bone->Root = this;

	Bone->SetActorRelativeTransform(FTransform::Identity);

	const FName ParentBoneName = Bones[Index].ParentBone;
	int32 ParentBoneIndex = Bones[Index].ParentBoneIndex;

	if (ParentBoneName == NAME_None)
	{
		Bone->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	const int32 InfoCount = Bones.Num();

	for (int32 J = 0; J < InfoCount; J++)
	{
		if (Bones[J].Bone == ParentBoneName)
		{
			Bone->AttachToActor(Bones[J].Actor, FAttachmentTransformRules::KeepRelativeTransform);
		}

		if (Bones[J].ParentBone == BoneName)
		{
			Bones[J].Actor->AttachToActor(Bone, FAttachmentTransformRules::KeepRelativeTransform);
			Bones[J].Actor->ResetRelativeTransform();
		}
	}

	const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);
	Bone->BoneIndex		  = BoneIndex;
	Bone->ParentBone	  = ParentBoneName;
	Bone->ParentBoneIndex = ParentBoneIndex;
	// Store Local / Relative Transform
	Bone->DefaultRelativeTransform = PoseableMeshComponent->BoneSpaceTransforms[BoneIndex];
	Bone->UpdateRelativeTransform(Bone->DefaultRelativeTransform, true);
	// Store Component Transform - WorldSpace -> ComponentSpace
	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();
	Bone->DefaultComponentTransform     = PoseableMeshComponent->GetBoneTransform(BoneIndex);
	Bone->DefaultComponentTransform.SetToRelativeTransform(ComponentTransform);

	Bone->ArrayIndex = Index;
}

void ACsPoseableMeshActor::ResetBones()
{
	const int32 Count = Bones.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		Bones[I].Actor->ResetRelativeTransform();
	}
}

ACsAnim_Bone* ACsPoseableMeshActor::GetBone(const FName &BoneName)
{
	const int32 Count = Bones.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Bones[I].Bone == BoneName)
			return Bones[I].Actor;
	}
	return nullptr;
}

ACsAnim_Bone* ACsPoseableMeshActor::GetBone(const FString &BoneName)
{
	return GetBone(FName(*BoneName));
}

#pragma endregion Bones

// Controls
#pragma region 

void ACsPoseableMeshActor::DestroyOrphanedControlAnchors()
{
	TArray<AActor*> Anchors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACsAnim_ControlAnchor::StaticClass(), Anchors);

	const int32 Count = Anchors.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsAnim_ControlAnchor* Anchor = Cast<ACsAnim_ControlAnchor>(Anchors[I]);

		if (!Anchor->Control)
			Anchor->Destroy();
	}
}

void ACsPoseableMeshActor::DestroyOrphanedControlHelpers()
{
	// Check Control Children who do NOT have a parent, Delete them
	TArray<AActor*> Helpers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACsAnim_ControlHelper::StaticClass(), Helpers);

	const int32 Count = Helpers.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsAnim_ControlHelper* Helper = Cast<ACsAnim_ControlHelper>(Helpers[I]);

		if (Helper->ControlIndex == INDEX_NONE)
			Helper->Destroy();
	}
}

void ACsPoseableMeshActor::Create_Control_FK(const int32 &Index)
{
	FCsAnimControlInfo_FK& FK   = Controls_FK[Index];
	ACsAnim_Control_FK* Control = FK.Actor;

	if (!Control)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		Control = GetWorld()->SpawnActor<ACsAnim_Control_FK>();
		Control->Control = FK.Control;
		Control->ControlName = FK.Control;
		Control->ControlName.Clear();
		Control->SetActorLabel(FK.Control);
		Control->ControlIndex = Index;
		Control->Root = this;
		Control->Anchor = Anchor;

		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);

		FK.Actor = Control;

		Control->OnControlNameChanged_Event.BindUObject(this, &ACsPoseableMeshActor::OnControlNameChanged_FK);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}

	if (!Control->Anchor)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		const FTransform WorldTransform = Control->GetActorTransform();
		Control->SetActorRelativeTransform(FTransform::Identity);
		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);
		Control->SetActorTransform(WorldTransform);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}
	PerformFK(Index);
}

void ACsPoseableMeshActor::PerformFK(const int32 &Index)
{
	FCsAnimControlInfo_FK& FK   = Controls_FK[Index];
	ACsAnim_Control_FK* Control = FK.Actor;

	const int32 Count = FK.Connections.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		FCsAnimControlInfo_FK_Connection& Connection = FK.Connections[I];
		const FName BoneName						 = Connection.Bone;
		const int32 BoneArrayIndex					 = Connection.BoneArrayIndex;

		if (BoneArrayIndex == INDEX_NONE)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): Controls_FK[%d].Connections[%d].Bone %s is NOT a Valid Bone."), *GetName(), Index, I, *(BoneName.ToString()));
			continue;
		}

		if (Connection.Output.Axes == ECS_AXES_NONE)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): No Axes set for Controls_FK[%d].Connections[%d].Output.Axes = 0."), *GetName(), Index, I);
			continue;
		}

		if (Connection.Input.Axes == ECS_AXES_NONE)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): No Axes set for Controls_FK[%d].Connections[%d].Input.Axes = 0."), *GetName(), Index, I);
			continue;
		}

		const int32 NumOutputAxes = UCsCommon::GetNumBitFlags(Connection.Output.Axes, ECS_AXES_EDITOR_MAX);
		const int32 NumInputAxes  = UCsCommon::GetNumBitFlags(Connection.Input.Axes, ECS_AXES_EDITOR_MAX);

		if (NumOutputAxes > NumInputAxes)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): Number of Output Axes > Input Axes (%d > %d) for Controls_FK[%d].Connections[%d]."), *GetName(), NumOutputAxes, NumInputAxes, Index, I);
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): Valid Number of Output Axes is # Output Axes = # Input Axes OR # Output Axes = 1."), *GetName(), NumOutputAxes, NumInputAxes, Index, I);
			continue;
		}

		if (NumInputAxes > NumOutputAxes &&
			NumOutputAxes != 1)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): Number of Input Axes > Output Axes (%d > %d) AND # of Output Axes != 1 for Controls_FK[%d].Connections[%d]."), *GetName(), NumOutputAxes, NumInputAxes, Index, I);
			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::PerformFK(%s): Valid Number of Output Axes is # Output Axes = # Input Axes OR # Output Axes = 1."), *GetName(), NumOutputAxes, NumInputAxes, Index, I);
			continue;
		}

		const ECsTransformMember& OutMember = Connection.Output.Member;
		ACsAnim_Bone* Bone				   = Bones[BoneArrayIndex].Actor;
		const int32 OutAxes				   = Connection.Output.Axes;
		const ECsTransformMember& InMember  = Connection.Input.Member;
		const int32 InAxes				   = Connection.Input.Axes;
		const bool OneToMany			   = NumOutputAxes == 1;

		const bool UpdateFK = !bIsAssetEditorOpen || (bIsAssetEditorOpen && Control->HasTransformMemberChanged(OutMember, OutAxes));

		if (UpdateFK)
		{
			// Out Location
			if (OutMember == ECsTransformMember::Location)
			{
				// In Location
				if (InMember == ECsTransformMember::Location)
				{
					const FVector Location = Control->Location.GetAxes(OutAxes);
					const FVector V		   = OneToMany ? UCsCommon::BuildUniformVector(Location, OutAxes) : Location;
					Bone->UpdateLocation(V, InAxes);
					continue;
				}
				// In Rotation
				if (InMember == ECsTransformMember::Rotation)
				{
					const FVector Location  = Control->Location.GetAxes(OutAxes);
					const FRotator Rotation = FRotator(Location.Y, Location.Z, Location.X);
					const FRotator R		= OneToMany ? UCsCommon::BuildUniformRotator(Rotation, OutAxes) : Rotation;
					Bone->UpdateRotation(R, InAxes);
					continue;
				}
				// In Scale
				if (InMember == ECsTransformMember::Scale)
				{
					const FVector Location = Control->Location.GetAxes(OutAxes);
					const FVector V		   = OneToMany ? UCsCommon::BuildUniformVector(Location, OutAxes) : Location;
					Bone->UpdateScale(V, InAxes);
					continue;
				}
				continue;
			}
			// Out Rotation
			if (OutMember == ECsTransformMember::Rotation)
			{
				// In Location
				if (InMember == ECsTransformMember::Location)
				{
					const FRotator Rotation = Control->Rotation.GetAxes(OutAxes);
					const FVector Location  = FVector(Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
					const FVector V			= OneToMany ? UCsCommon::BuildUniformVector(Location, OutAxes) : Location;
					Bone->UpdateLocation(V, InAxes);
					continue;
				}
				// In Rotation
				if (InMember == ECsTransformMember::Rotation)
				{
					const FRotator Rotation = Control->Rotation.GetAxes(OutAxes);
					const FRotator R		= OneToMany ? UCsCommon::BuildUniformRotator(Rotation, OutAxes) : Rotation;
					Bone->UpdateRotation(R, InAxes);
					continue;
				}
				// In Scale
				if (InMember == ECsTransformMember::Scale)
				{
					const FRotator Rotation = Control->Rotation.GetAxes(OutAxes);
					const FVector Location  = FVector(Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
					const FVector V			= OneToMany ? UCsCommon::BuildUniformVector(Location, OutAxes) : Location;
					Bone->UpdateScale(V, InAxes);
					continue;
				}
				continue;
			}
			// Out Scale
			if (OutMember == ECsTransformMember::Scale)
			{
				// In Location
				if (InMember == ECsTransformMember::Location)
				{
					const FVector Scale = Control->Scale.GetAxes(OutAxes);
					const FVector V		= OneToMany ? UCsCommon::BuildUniformVector(Scale, OutAxes) : Scale;
					Bone->UpdateLocation(V, InAxes);
					continue;
				}
				// In Rotation
				if (InMember == ECsTransformMember::Rotation)
				{
					const FVector Scale		= Control->Scale.GetAxes(OutAxes);
					const FRotator Rotation = FRotator(Scale.Y, Scale.Z, Scale.X);
					const FRotator R		= OneToMany ? UCsCommon::BuildUniformRotator(Rotation, OutAxes) : Rotation;
					Bone->UpdateRotation(R, InAxes);
					continue;
				}
				// In Scale
				if (InMember == ECsTransformMember::Scale)
				{
					const FVector Scale = Control->Scale.GetAxes(OutAxes);
					const FVector V		= OneToMany ? UCsCommon::BuildUniformVector(Scale, OutAxes) : Scale;
					Bone->UpdateScale(V, InAxes);
					continue;
				}
				continue;
			}
		}
	}

	Control->Location.Clear();
	Control->Rotation.Clear();
	Control->Scale.Clear();
}

void ACsPoseableMeshActor::ClearControlsFK()
{
	const int32 Count = Controls_FK.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsAnim_Control_FK* Control = Controls_FK[I].Actor;

		if (Control && !Control->IsPendingKill())
		{
			if (Control->Anchor && !Control->Anchor->IsPendingKill())
				Control->Anchor->Destroy();
			Control->Destroy();
		}
	}
	Controls_FK.Reset();
}

void ACsPoseableMeshActor::Create_Control_TwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control	    = TwoBoneIK.Actor;

	if (!Control)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		Control		         = GetWorld()->SpawnActor<ACsAnim_Control_TwoBoneIK>();
		Control->Control     = TwoBoneIK.Control;
		Control->ControlName = TwoBoneIK.Control;
		Control->ControlName.Clear();
		Control->SetActorLabel(TwoBoneIK.Control);
		Control->ControlIndex = Index;
		Control->Root = this;
		Control->Anchor = Anchor;

		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);

		TwoBoneIK.Actor = Control;

		Control->OnControlNameChanged_Event.BindUObject(this, &ACsPoseableMeshActor::OnControlNameChanged_TwoBoneIK);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}

	if (!Control->Anchor)
	{
		ACsAnim_ControlAnchor* Anchor = GetWorld()->SpawnActor<ACsAnim_ControlAnchor>();

		Anchor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		const FTransform WorldTransform = Control->GetActorTransform();
		Control->SetActorRelativeTransform(FTransform::Identity);
		Control->AttachToActor(Anchor, FAttachmentTransformRules::KeepRelativeTransform);
		Control->SetActorTransform(WorldTransform);

		Anchor->Control = Control;
		Anchor->SetActorLabel(TEXT("anchor_") + Control->GetActorLabel());
	}

	const FName BoneName = TwoBoneIK.IK.IKBone;
	const int32 BoneIndex = PoseableMeshComponent->GetBoneIndex(BoneName);

	TwoBoneIK.IK.IKBoneIndex = BoneIndex;

	TwoBoneIK.EndEffector.EffectorSpaceBoneName = BoneName;
	TwoBoneIK.EndEffector.EffectorSpaceBoneIndex = BoneIndex;

	// Cache ArrayIndex
	TwoBoneIK.IK.IKBoneArrayIndex = INDEX_NONE;

	{
		const int32 Count = Bones.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (Bones[I].Bone == BoneName)
			{
				TwoBoneIK.IK.IKBoneArrayIndex = I;
				TwoBoneIK.EndEffector.EffectorSpaceBoneArrayIndex = I;
				break;
			}
		}
	}

	// Middle Bone
	const FName MiddleBoneName = PoseableMeshComponent->GetParentBone(BoneName);
	const int32 MiddleBoneIndex = PoseableMeshComponent->GetBoneIndex(MiddleBoneName);

	TwoBoneIK.IK.ParentBone = MiddleBoneName;
	TwoBoneIK.IK.ParentBoneIndex = MiddleBoneIndex;
	TwoBoneIK.IK.ParentBoneArrayIndex = INDEX_NONE;

	// Start Bone
	const FName StartBoneName = PoseableMeshComponent->GetParentBone(MiddleBoneName);
	const int32 StartBoneIndex = PoseableMeshComponent->GetBoneIndex(StartBoneName);

	TwoBoneIK.JointTarget.JointTargetSpaceBoneName = StartBoneName;
	TwoBoneIK.JointTarget.JointTargetSpaceBoneIndex = StartBoneIndex;
	TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = INDEX_NONE;

	// Change JointTarget (Start Bone)
	ACsAnim_ControlHelper_JointTarget* JointTarget = Control->JointTarget; 
	
	if (!JointTarget)
	{
		JointTarget				  = GetWorld()->SpawnActor<ACsAnim_ControlHelper_JointTarget>();
		JointTarget->ControlIndex = Index;
		JointTarget->Root		  = this;
		JointTarget->SetActorLabel(TwoBoneIK.Control + TEXT("_PoleVector"));
		Control->JointTarget = JointTarget;
		JointTarget->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);
	}

	{
		// Reset PREVIOUS Start Bone
		if (Control->StartBone)
		{
			Control->StartBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->StartBone->Bone, Control->StartBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}

		if (StartBoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (Bones[I].Bone == StartBoneName)
				{
					// Reset NEW / CURRENT Start Bone
					Control->StartBone = Bones[I].Actor;
					Control->StartBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->StartBone->Bone, Control->StartBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					JointTarget->SetActorLocation(Control->StartBone->GetActorLocation());
					JointTarget->Location = Control->StartBone->GetActorLocation();

					TwoBoneIK.JointTarget.JointTargetSpaceBoneArrayIndex = I;
					break;
				}
			}
		}
		else
		{
			Control->StartBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): JointTargetBoneName (Start Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(StartBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
	// Change Middle Bone
	{
		// Reset PREVIOUS Middle Bone
		if (Control->MiddleBone)
		{
			Control->MiddleBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->MiddleBone->Bone, Control->MiddleBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}
		// Reset NEW / CURRENT Middle Bone
		if (MiddleBoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (Bones[I].Bone == MiddleBoneName)
				{
					Control->MiddleBone = Bones[I].Actor;
					Control->MiddleBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->MiddleBone->Bone, Control->MiddleBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					TwoBoneIK.IK.ParentBoneArrayIndex = I;
				}
			}
		}
		else
		{
			Control->MiddleBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone's Parent Bone (Middle Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(MiddleBoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}
	// Change EndEffector (End Bone)
	ACsAnim_ControlHelper_EndEffector* EndEffector = Control->EndEffector;
	
	if (!EndEffector)
	{
		EndEffector				  = GetWorld()->SpawnActor<ACsAnim_ControlHelper_EndEffector>();
		EndEffector->ControlIndex = Index;
		EndEffector->Root		  = this;
		EndEffector->SetActorLabel(TwoBoneIK.Control + TEXT("_EndEffector"));
		Control->EndEffector = EndEffector;
		EndEffector->AttachToActor(Control, FAttachmentTransformRules::KeepRelativeTransform);
	}

	{
		// Reset PREVIOUS End Bone. TODO: Need to check if any other Control is referencing this bone
		if (Control->EndBone)
		{
			Control->EndBone->ResetRelativeTransform();
			PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);
		}
		if (BoneName != NAME_None)
		{
			const int32 Count = Bones.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (Bones[I].Bone == BoneName)
				{
					// Reset NEW / CURRENT End Bone
					Control->EndBone = Bones[I].Actor;
					Control->MiddleBone->ResetRelativeTransform();
					PoseableMeshComponent->SetBoneTransformByName(Control->EndBone->Bone, Control->EndBone->GetActorTransform(), EBoneSpaces::ComponentSpace);

					EndEffector->SetActorLocation(Control->EndBone->GetActorLocation());
					EndEffector->Location = Control->EndBone->GetActorLocation();
					break;
				}
			}
		}
		else
		{
			Control->EndBone = nullptr;

			UE_LOG(LogCs, Warning, TEXT("ACsPoseableMeshActor::Create_Control_TwoBoneIK(%s): IKBone (End Bone): %s is NOT found in SkeletalMesh: %s"), *GetName(), *(BoneName.ToString()), *(PoseableMeshComponent->SkeletalMesh->GetName()));
		}
	}

	if (Control->StartBone && Control->MiddleBone && Control->EndBone)
		PerformTwoBoneIK(Index);
}

// Copied from Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_TowBoneIK.cpp

void ACsPoseableMeshActor::PerformTwoBoneIK(const int32 &Index)
{
	FCsAnimControlInfo_TwoBoneIK& TwoBoneIK = Controls_TwoBoneIK[Index];
	ACsAnim_Control_TwoBoneIK* Control      = TwoBoneIK.Actor;

	ACsAnim_Bone* StartBone = Control->StartBone;
	ACsAnim_Bone* MiddleBone = Control->MiddleBone;
	ACsAnim_Bone* EndBone = Control->EndBone;

	const FTransform ComponentTransform = PoseableMeshComponent->GetComponentTransform();

	// Now get those in component space...
	FTransform StartTransform = StartBone->DefaultComponentTransform;
	FTransform MiddleTransform = MiddleBone->DefaultComponentTransform;
	FTransform EndTransform = EndBone->DefaultComponentTransform;

	// Get current position of root of limb.
	// All position are in Component space.
	const FVector StartPos		   = StartTransform.GetTranslation();
	const FVector InitialMiddlePos = MiddleTransform.GetTranslation();
	const FVector InitialEndPos    = EndTransform.GetTranslation();

	// Get JointTarget Transform in ComponentSpace
	
	const FVector JointTargetLocation = Control->JointTarget->GetActorLocation();
	FTransform JointTargetTransform(JointTargetLocation);
		// Convert JointTargetTransform WorldSpace -> ComponentSpace
	JointTargetTransform.SetToRelativeTransform(ComponentTransform);
	
	FVector	JointTargetPos = JointTargetTransform.GetTranslation();

	// Get EndEffector Transform in ComponentSpace

	const FVector EndEffectorLocation = Control->EndEffector->GetActorLocation();
	FTransform EndEffectorTransform(EndEffectorLocation);
		// Convert EndEffectorTransfrom WorldSpace -> ComponentSpace
	EndEffectorTransform.SetToRelativeTransform(ComponentTransform);

	FVector DesiredPos = EndEffectorTransform.GetTranslation();

	// IK solver
	
	StartTransform.SetLocation(StartPos);
	MiddleTransform.SetLocation(InitialMiddlePos);
	EndTransform.SetLocation(InitialEndPos);

	const bool bAllowStretching   = TwoBoneIK.IK.bAllowStretching;
	const float StartStretchRatio = TwoBoneIK.IK.StartStretchRatio;
	const float MaxStretchRatio   = TwoBoneIK.IK.MaxStretchRatio;

	AnimationCore::SolveTwoBoneIK(StartTransform, MiddleTransform, EndTransform, JointTargetPos, DesiredPos, bAllowStretching, StartStretchRatio, MaxStretchRatio);

	// Update transform for end bone.

	// only allow bTakeRotationFromEffectorSpace during bone space
	if (TwoBoneIK.EndEffector.bTakeRotationFromEffectorSpace)
	{
		EndTransform.SetRotation(EndEffectorTransform.GetRotation());
	}
	else 
	if (TwoBoneIK.EndEffector.bMaintainEffectorRelRot)
	{
		// Get Local Space transforms for our bones. We do this first in case they already are local.
		// As right after we get them in component space. (And that does the auto conversion).
		// We might save one transform by doing local first...
		const FTransform EndLocalTransform = PoseableMeshComponent->BoneSpaceTransforms[EndBone->BoneIndex];
		EndTransform					   = EndLocalTransform * MiddleTransform;
	}

	// Set World Transform. ComponentSpace -> WorldSpace

	// Start
	const FTransform StartWorldTransform = StartTransform * ComponentTransform;
	Control->StartBone->UpdateRotation(StartWorldTransform.Rotator());
	// Middle
	Control->MiddleBone->UpdateTransform(MiddleTransform * ComponentTransform);
	// End
	const FTransform EndWorldTransform = EndTransform * ComponentTransform;
	Control->EndBone->UpdateLocation(EndWorldTransform.GetTranslation());

	Control->EndEffector->Location.Clear();
	Control->JointTarget->Location.Clear();
}

void ACsPoseableMeshActor::ClearControlsTwoBoneIK()
{
	const int32 Count = Controls_TwoBoneIK.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		ACsAnim_Control_TwoBoneIK* Control = Controls_TwoBoneIK[I].Actor;

		if (Control && !Control->IsPendingKill())
		{
			if (Control->Anchor && !Control->Anchor->IsPendingKill())
				Control->Anchor->Destroy();
			if (Control->EndEffector && !Control->EndEffector->IsPendingKill())
				Control->EndEffector->Destroy();
			if (Control->JointTarget && !Control->JointTarget->IsPendingKill())
				Control->JointTarget->Destroy();
			Control->Destroy();
		}
	}
	Controls_TwoBoneIK.Reset();
}

#pragma endregion Controls

#endif // #if WITH_EDITOR