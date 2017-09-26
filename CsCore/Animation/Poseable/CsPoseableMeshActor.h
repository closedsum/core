// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsTypes.h"
#include "CsPoseableMeshActor.generated.h"

// Enums
#pragma region

UENUM(BlueprintType)
namespace ECsAnimControl
{
	enum Type
	{
		None				UMETA(DisplayName = "None"),
		TwoBoneIK			UMETA(DisplayName = "TwoBoneIK"),
		ECsAnimControl_MAX	UMETA(Hidden),
	};
}

namespace ECsAnimControl
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("Tick"), TEXT("tick"));
		const TCsString TwoBoneIK = TCsString(TEXT("CalcCamera"), TEXT("calccamera"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::TwoBoneIK) { return Str::TwoBoneIK.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::TwoBoneIK) { return Type::TwoBoneIK; }
		return Type::ECsAnimControl_MAX;
	}
}

#define ECS_ANIM_CONTROL_MAX (uint8)ECsAnimControl::ECsAnimControl_MAX
typedef TEnumAsByte<ECsAnimControl::Type> TCsAnimControl;

#pragma endregion Enums

// Structs
#pragma region

USTRUCT()
struct FCsPoseableMeshFK
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone")
	FName Bone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	int32 BoneIndex;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	class ACsAnim_Bone* Actor;

	FCsPoseableMeshFK()
	{
		Bone = NAME_None;
		BoneIndex = INDEX_NONE;
		Actor = nullptr;
	}
};

USTRUCT()
struct FCsAnimBoneInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone")
	FName Bone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone")
	int32 BoneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone")
	FName ParentBone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone")
	int32 ParentBoneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bone")
	class ACsAnim_Bone* Actor;

	FCsAnimBoneInfo()
	{
		Bone = NAME_None;
		BoneIndex = INDEX_NONE;
		ParentBone = NAME_None;
		ParentBoneIndex = INDEX_NONE;
		Actor = nullptr;
	}
};

	// Controls
#pragma region

USTRUCT()
struct FCsAnimControlPinInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<ECsTransformMember::Type> Member;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (Bitmask, BitmaskEnum = "ECsAxes"))
	int32 Axes;
};

USTRUCT()
struct FCsAnimControlPin
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName Bone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlPinInput Input;
};

USTRUCT()
struct FCsAnimControlInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FString Control;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	class ACsAnim_Control* Actor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TArray<FCsAnimControlPin> Pins;

	FCsAnimControlInfo()
	{
		Control = TEXT("None");
		Actor = nullptr;
	}

	FCsAnimControlInfo& operator=(const FCsAnimControlInfo& B)
	{
		Control = B.Control;
		Actor = B.Actor;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo& B) const
	{
		return Control == B.Control &&
			   Actor == B.Actor;
	}

	bool operator!=(const FCsAnimControlInfo& B) const
	{
		return !(*this == B);
	}
};

		// TwoBoneIK
#pragma region

USTRUCT()
struct FCsAnimControlInfo_TwoBoneIK_IK
{
	GENERATED_USTRUCT_BODY()

	/* Start Bone */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName IKBone;

	FName Last_IKBone;
	/* Start Bone Index in Bone Array in SkeletalMesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 IKBoneIndex;
	/* Start Bone Index in Bone Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 IKBoneArrayIndex;
	/* Middle Bone */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	FName ParentBone;
	/* Middle Bone Index in Bone Array in SkeletalMesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 ParentBoneIndex;
	/* Middle Bone Index in Bone Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 ParentBoneArrayIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool bAllowStretching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float StartStretchRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MaxStretchRatio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TEnumAsByte<EBoneControlSpace> EffectorLocationSpace;

	FCsAnimControlInfo_TwoBoneIK_IK()
	{
		IKBone = NAME_None;
		Last_IKBone = IKBone;
		IKBoneIndex = INDEX_NONE;
		IKBoneArrayIndex = INDEX_NONE;
		ParentBone = NAME_None;
		ParentBoneIndex = INDEX_NONE;
		ParentBoneArrayIndex = INDEX_NONE;
		bAllowStretching = false;
		StartStretchRatio = 1.0f;
		MaxStretchRatio = 1.2f;
		EffectorLocationSpace = BCS_BoneSpace;
	}

	FCsAnimControlInfo_TwoBoneIK_IK& operator=(const FCsAnimControlInfo_TwoBoneIK_IK& B)
	{
		IKBone = B.IKBone;
		Last_IKBone = B.Last_IKBone;
		IKBoneIndex = B.IKBoneIndex;
		IKBoneArrayIndex = B.IKBoneArrayIndex;
		ParentBone = B.ParentBone;
		ParentBoneIndex = B.ParentBoneIndex;
		ParentBoneArrayIndex = B.ParentBoneArrayIndex;
		bAllowStretching = B.bAllowStretching;
		StartStretchRatio = B.StartStretchRatio;
		MaxStretchRatio = B.MaxStretchRatio;
		EffectorLocationSpace = B.EffectorLocationSpace;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_TwoBoneIK_IK& B) const
	{
		return IKBone == B.IKBone &&
			   Last_IKBone == B.Last_IKBone &&
			   IKBoneIndex == B.IKBoneIndex &&
			   IKBoneArrayIndex == B.IKBoneArrayIndex &&
			   ParentBone == B.ParentBone &&
		  	   ParentBoneIndex == B.ParentBoneIndex &&
			   ParentBoneArrayIndex == B.ParentBoneArrayIndex &&
			   bAllowStretching == B.bAllowStretching &&
			   StartStretchRatio == B.StartStretchRatio &&
			   MaxStretchRatio == B.MaxStretchRatio &&
			   EffectorLocationSpace == B.EffectorLocationSpace;
	}

	bool operator!=(const FCsAnimControlInfo_TwoBoneIK_IK& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_TwoBoneIK_EndEffector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool bTakeRotationFromEffectorSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool bMaintainEffectorRelRot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	FName EffectorSpaceBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 EffectorSpaceBoneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 EffectorSpaceBoneArrayIndex;

	FCsAnimControlInfo_TwoBoneIK_EndEffector()
	{
		bTakeRotationFromEffectorSpace = false;
		bMaintainEffectorRelRot = false;
		EffectorSpaceBoneName = NAME_None;
		EffectorSpaceBoneIndex = INDEX_NONE;
		EffectorSpaceBoneArrayIndex = INDEX_NONE;
	}

	FCsAnimControlInfo_TwoBoneIK_EndEffector& operator=(const FCsAnimControlInfo_TwoBoneIK_EndEffector& B)
	{
		bTakeRotationFromEffectorSpace = B.bTakeRotationFromEffectorSpace;
		bMaintainEffectorRelRot = B.bMaintainEffectorRelRot;
		EffectorSpaceBoneName = B.EffectorSpaceBoneName;
		EffectorSpaceBoneIndex = B.EffectorSpaceBoneIndex;
		EffectorSpaceBoneArrayIndex = B.EffectorSpaceBoneArrayIndex;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_TwoBoneIK_EndEffector& B) const
	{
		return bTakeRotationFromEffectorSpace == B.bTakeRotationFromEffectorSpace &&
			   bMaintainEffectorRelRot == B.bMaintainEffectorRelRot &&
		  	   EffectorSpaceBoneName == B.EffectorSpaceBoneName &&
			   EffectorSpaceBoneIndex == B.EffectorSpaceBoneIndex &&
			   EffectorSpaceBoneArrayIndex == B.EffectorSpaceBoneArrayIndex;
	}

	bool operator!=(const FCsAnimControlInfo_TwoBoneIK_EndEffector& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_TwoBoneIK_JoinTarget
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	FName JointTargetSpaceBoneName;

	FName Last_JointTargetSpaceBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 JointTargetSpaceBoneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 JointTargetSpaceBoneArrayIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	TEnumAsByte<EBoneControlSpace> JointTargetLocationSpace;

	FCsAnimControlInfo_TwoBoneIK_JoinTarget()
	{
		JointTargetSpaceBoneName = NAME_None;
		Last_JointTargetSpaceBoneName = JointTargetSpaceBoneName;
		JointTargetSpaceBoneIndex = INDEX_NONE;
		JointTargetSpaceBoneArrayIndex = INDEX_NONE;
		JointTargetLocationSpace = BCS_ParentBoneSpace;
	}

	FCsAnimControlInfo_TwoBoneIK_JoinTarget& operator=(const FCsAnimControlInfo_TwoBoneIK_JoinTarget& B)
	{
		JointTargetSpaceBoneName = B.JointTargetSpaceBoneName;
		Last_JointTargetSpaceBoneName = B.Last_JointTargetSpaceBoneName;
		JointTargetSpaceBoneIndex = B.JointTargetSpaceBoneIndex;
		JointTargetSpaceBoneArrayIndex = B.JointTargetSpaceBoneArrayIndex;
		JointTargetLocationSpace = B.JointTargetLocationSpace;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_TwoBoneIK_JoinTarget& B) const
	{
		return JointTargetSpaceBoneName == B.JointTargetSpaceBoneName &&
			   Last_JointTargetSpaceBoneName == B.Last_JointTargetSpaceBoneName &&
			   JointTargetSpaceBoneIndex == B.JointTargetSpaceBoneIndex &&
			   JointTargetSpaceBoneArrayIndex == B.JointTargetSpaceBoneArrayIndex &&
			   JointTargetLocationSpace == B.JointTargetLocationSpace;
	}

	bool operator!=(const FCsAnimControlInfo_TwoBoneIK_JoinTarget& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_TwoBoneIK
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FString Control;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	class ACsAnim_Control_TwoBoneIK* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_TwoBoneIK_IK IK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_TwoBoneIK_EndEffector EndEffector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_TwoBoneIK_JoinTarget JointTarget;

	FCsAnimControlInfo_TwoBoneIK()
	{
		Control = TEXT("None");
		Actor = nullptr;
	}

	FCsAnimControlInfo_TwoBoneIK& operator=(const FCsAnimControlInfo_TwoBoneIK& B)
	{
		Control = B.Control;
		Actor = B.Actor;
		IK = B.IK;
		EndEffector = B.EndEffector;
		JointTarget = B.JointTarget;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_TwoBoneIK& B) const
	{
		return Control == B.Control && 
			   Actor == B.Actor && 
			   IK == B.IK && 
			   EndEffector == B.EndEffector && 
			   JointTarget == B.JointTarget;
	}

	bool operator!=(const FCsAnimControlInfo_TwoBoneIK& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion TwoBoneIK

#pragma endregion Controls

#pragma endregion Structs

UCLASS()
class CSCORE_API ACsPoseableMeshActor : public AActor
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
	class UCsPoseableMeshComponent* PoseableMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	class USkeletalMesh* Last_SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	TArray<FCsAnimBoneInfo> Bones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK;

	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK_Copy;

#if WITH_EDITOR

	void OnControlNameChanged_TwoBoneIK(const int32 &Index);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

	virtual void GenerateBones();
	virtual void ClearBones();

	void DestroyOrphanedControlAnchors();
	void DestroyOrphanedControlHelpers();

	void RecreateBone(const int32 &Index);

	void Create_Control_TwoBoneIK(const int32 &Index);
	void PerformTwoBoneIK(const int32 &Index);

#endif // #if WITH_EDITOR
};