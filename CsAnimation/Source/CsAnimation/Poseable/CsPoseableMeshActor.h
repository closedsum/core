// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
// Types
#include "Types/CsTypes.h"
#include "Poseable/CsTypes_Poseable.h"

#include "CsPoseableMeshActor.generated.h"

class UCsPoseableMeshComponent;
class USkeletalMesh;
class FLevelSequenceEditorToolkit;
class ACsAnim_Bone;

UCLASS()
class CSANIMATION_API ACsPoseableMeshActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

#if WITH_EDITOR
	void OnTick_Editor(const float &DeltaSeconds);
#endif // #if WITH_EDITOR

	bool HasTickedInEditor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	UCsPoseableMeshComponent* PoseableMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	USkeletalMesh* Last_SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	TArray<FCsAnimBoneInfo> Bones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	TArray<FCsAnimControlInfo_FK> Controls_FK;

	TArray<FCsAnimControlInfo_FK> Controls_FK_Copy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK;

	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK_Copy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	FCsAnimLevelSequenceInfo_Master AnimLevelSequence;

#if WITH_EDITOR

	bool bIsAssetEditorOpen;
	bool IsAssetEditorOpen();

	FLevelSequenceEditorToolkit* LevelSequenceEditor;
	FLevelSequenceEditorToolkit* GetOpenAssetEditor();

	int32 OpenShotIndex;
	int32 GetOpenShotIndexInEditor();

	void OnControlNameChanged_FK(const int32 &Index);
	void OnControlNameChanged_TwoBoneIK(const int32 &Index);

	FString GetMeshName();
	FString GetBaseAssetName();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	void PostEditChangeProperty_LevelSequence_Master(struct FPropertyChangedEvent& e);

	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

	void PostEditChangeChainProperty_Control_FK(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_Control_FK_Connection(struct FPropertyChangedChainEvent& e);

	void PostEditChangeChainProperty_TwoBoneIK(struct FPropertyChangedChainEvent& e);

	void PostEditChangeChainProperty_LevelSequence_Shots(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_LevelSequence_Shots_FindOrCreate(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_LevelSequence_Shots_Export(struct FPropertyChangedChainEvent& e);

	void AnimLevelSequence_Shot_AddTransformTrack(const int32 &Index, const FGuid& Guid, AActor* Actor);
	void AnimLevelSequence_Shot_AddKey(const int32 &Index, AActor* Actor);
	//void AnimLevelSequence_Shot_Export(const int32 &Index);

	// Bones
#pragma region

	virtual void GenerateBones();
	virtual void ClearBones();
	void RecreateBone(const int32 &Index);
	void ResetBones();

	ACsAnim_Bone* GetBone(const FName &BoneName);
	ACsAnim_Bone* GetBone(const FString &BoneName);

#pragma endregion Bones

	// Controls
#pragma region

	void DestroyOrphanedControlAnchors();
	void DestroyOrphanedControlHelpers();

	void Create_Control_FK(const int32 &Index);
	void PerformFK(const int32 &Index);
	void ClearControlsFK();

	void Create_Control_TwoBoneIK(const int32 &Index);
	void PerformTwoBoneIK(const int32 &Index);
	void ClearControlsTwoBoneIK();

#pragma endregion Controls

#endif // #if WITH_EDITOR
};