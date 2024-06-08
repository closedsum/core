// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Types
#include "Animation/Mannequin/Silhouette/CsTypes_Mannequin_Silhouette.h"

#include "CsMannequin_Silhouette.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControlInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FTransform Transform;

	UPROPERTY()
	FTransform Last_Transform;

	FCsMannequinSilhouette_BoneControlInfo() :
		Transform(FTransform::Identity),
		Last_Transform(FTransform::Identity)
	{
	}

	FORCEINLINE bool HasChanged() const 
	{ 
		return Transform.GetLocation() != Last_Transform.GetLocation() ||
			   Transform.GetRotation() != Last_Transform.GetRotation() ||
			   Transform.GetScale3D() != Last_Transform.GetScale3D(); 
	}
	FORCEINLINE void Resolve() { Last_Transform = Transform; }
};

class UCsAnimInstance_Mannequin_Silhouette;
class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class CSCORE_API ACsMannequin_Silhouette : public AActor
{
	GENERATED_UCLASS_BODY()

// AActor Interface
#pragma region
public:

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

#pragma endregion AActor Interface

private:

	UFUNCTION()
	void OnDestroy(AActor* Actor);

#if WITH_EDITOR
	void TickInEditor(const float& DeltaSeconds);
#endif // #if WITH_EDITOR

private:

	UCsAnimInstance_Mannequin_Silhouette* Last_AnimInstance;

// Components
#pragma region
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* pelvis;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* thigh_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* thigh_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* calf_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* calf_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* foot_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* foot_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* spine_01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* spine_02;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* spine_03;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* clavicle_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* clavicle_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* upperarm_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* upperarm_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* lowerarm_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* lowerarm_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* hand_l;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* hand_r;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* neck_01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* head;

	// Controls
#pragma region

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* pelvis_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* thigh_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* thigh_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* calf_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* calf_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* foot_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* foot_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* spine_01_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* spine_02_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* spine_03_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* clavicle_l_ctrl;

	UPROPERTY()
	FCsMannequinSilhouette_BoneControlInfo clavicle_l_ctrl_info;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* clavicle_r_ctrl;

	UPROPERTY()
	FCsMannequinSilhouette_BoneControlInfo clavicle_r_ctrl_info;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* upperarm_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* upperarm_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* lowerarm_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* lowerarm_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* hand_l_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* hand_r_ctrl;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* neck_01_ctrl;

	UPROPERTY()
	FCsMannequinSilhouette_BoneControlInfo neck_01_ctrl_info;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Controls", meta = (AllowPrivateAccess = "true"))
	USceneComponent* head_ctrl;

#define BoneControlInfoType NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo
#define BoneType NCsAnimation::NMannequin::NSilhouette::EBone

	TArray<BoneControlInfoType> BoneControlInfos;

public:

	FORCEINLINE BoneControlInfoType& GetBoneControlInfo(const BoneType& Type) { return BoneControlInfos[(uint8)Type]; }

#undef BoneControlInfoType
#undef BoneType

#pragma endregion Controls

private:

	void SetupAttachements();

#pragma endregion Components

// Bone 
#pragma region 

	// Controls
#pragma region
public:

#define BoneControlApplicationType NCsAnimation::NMannequin::NSilhouette::EBoneControlApplication

	bool bBoneControlApplication;

	BoneControlApplicationType BoneControlApplication;

#undef BoneControlApplicationType

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Pelvis"))
	FCsMannequinSilhouette_BoneControl_Core PelvisControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Lower Torso"))
	FCsMannequinSilhouette_BoneControl_Core LowerTorsoControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Upper Torso"))
	FCsMannequinSilhouette_BoneControl_Core UpperTorsoControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Chest"))
	FCsMannequinSilhouette_BoneControl_Core ChestControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Head"))
	FCsMannequinSilhouette_BoneControl_Head HeadControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls")
	float LatSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls")
	float LatHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Upperarm"))
	FCsMannequinSilhouette_BoneControl_Limb UpperarmControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Lowerarm"))
	FCsMannequinSilhouette_BoneControl_Limb LowerarmControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Hand"))
	FCsMannequinSilhouette_BoneControl_Hand HandControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Thigh"))
	FCsMannequinSilhouette_BoneControl_Limb ThighControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Calf"))
	FCsMannequinSilhouette_BoneControl_Limb CalfControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone|Controls", meta = (DisplayName = "Foot"))
	FCsMannequinSilhouette_BoneControl_Foot FootControl;

#pragma endregion Controls

#pragma endregion Bone
// Editor
#pragma region
public:

#if WITH_EDITOR

	virtual void PreEditChange(FProperty* PropertyThatWillChange) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

	void OnObjectModified(UObject* Object);

	FDelegateHandle OnObjectModifiedHandle;

#endif // #if WITH_EDITOR

#pragma endregion Editor
};