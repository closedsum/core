// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
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
struct FCsAnimControlInfo_FK_ConnectionOutput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<ECsTransformMember::Type> Member;

	TCsTransformMember Last_Member;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (Bitmask, BitmaskEnum = "ECsAxes"))
	int32 Axes;

	int32 Last_Axes;

	FCsAnimControlInfo_FK_ConnectionOutput()
	{
		Member = ECsTransformMember::Rotation;
		Last_Member = Member;
		Axes = 0;
		Last_Axes = Axes;
	}

	FCsAnimControlInfo_FK_ConnectionOutput& operator=(const FCsAnimControlInfo_FK_ConnectionOutput& B)
	{
		Member = B.Member;
		Last_Member = B.Last_Member;
		Axes = B.Axes;
		Last_Axes = B.Last_Axes;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_FK_ConnectionOutput& B) const
	{
		return Member == B.Member &&
			   Last_Member == B.Last_Member &&
			   Axes == B.Axes &&
			   Last_Axes == B.Last_Axes;
	}

	bool operator!=(const FCsAnimControlInfo_FK_ConnectionOutput& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_FK_ConnectionInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<ECsTransformMember::Type> Member;

	TCsTransformMember Last_Member;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (Bitmask, BitmaskEnum = "ECsAxes"))
	int32 Axes;

	int32 Last_Axes;

	FCsAnimControlInfo_FK_ConnectionInput()
	{
		Member = ECsTransformMember::Rotation;
		Last_Member = Member;
		Axes = 0;
		Last_Axes = Axes;
	}

	FCsAnimControlInfo_FK_ConnectionInput& operator=(const FCsAnimControlInfo_FK_ConnectionInput& B)
	{
		Member = B.Member;
		Last_Member = B.Last_Member;
		Axes = B.Axes;
		Last_Axes = B.Last_Axes;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_FK_ConnectionInput& B) const
	{
		return Member == B.Member &&
			   Last_Member == B.Last_Member &&
			   Axes == B.Axes &&
			   Last_Axes == B.Last_Axes;
	}

	bool operator!=(const FCsAnimControlInfo_FK_ConnectionInput& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_FK_Connection
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName Bone;

	FName Last_Bone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 BoneIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	int32 BoneArrayIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool SnapToBone;

	bool Last_SnapToBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_FK_ConnectionOutput Output;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_FK_ConnectionInput Input;

	FCsAnimControlInfo_FK_Connection()
	{
		Bone = NAME_None;
		Last_Bone = NAME_None;
		BoneIndex = INDEX_NONE;
		BoneArrayIndex = INDEX_NONE;
		SnapToBone = false;
		Last_SnapToBone = false;
	}

	FCsAnimControlInfo_FK_Connection& operator=(const FCsAnimControlInfo_FK_Connection& B)
	{
		Bone = B.Bone;
		Bone = B.Last_Bone;
		BoneIndex = B.BoneIndex;
		BoneArrayIndex = B.BoneArrayIndex;
		SnapToBone = B.SnapToBone;
		Output = B.Output;
		Input = B.Input;
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_FK_Connection& B) const
	{
		return Bone == B.Bone &&
			   Bone == B.Last_Bone &&
			   BoneIndex == B.BoneIndex &&
			   BoneArrayIndex == B.BoneArrayIndex &&
			   SnapToBone == B.SnapToBone &&
			   Output == B.Output &&
			   Input == B.Input;
	}

	bool operator!=(const FCsAnimControlInfo_FK_Connection& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimControlInfo_FK
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FString Control;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
	class ACsAnim_Control_FK* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TArray<FCsAnimControlInfo_FK_Connection> Connections;

	TArray<FCsAnimControlInfo_FK_Connection> Connections_Copy;

	FCsAnimControlInfo_FK()
	{
		Control = TEXT("None");
		Actor = nullptr;
	}

	FCsAnimControlInfo_FK& operator=(const FCsAnimControlInfo_FK& B)
	{
		Control = B.Control;
		Actor = B.Actor;

		Connections.Reset();
		Connections_Copy.Reset();

		const int32 Count = B.Connections.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Connections.AddDefaulted();
			Connections[I] = B.Connections[I];
			Connections_Copy.AddDefaulted();
			Connections_Copy[I] = B.Connections[I];
		}
		return *this;
	}

	bool operator==(const FCsAnimControlInfo_FK& B) const
	{
		if (Control != B.Control)
			return false;
		if (Actor != B.Actor)
			return false;

		const int32 Count = Connections.Num();

		if (Count != B.Connections.Num())
			return false;

		for (int32 I = 0; I < Count; I++)
		{
			if (Connections[I] != B.Connections[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsAnimControlInfo_FK& B) const
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

	// Level Sequence
#pragma region

USTRUCT()
struct FCsAnimLevelSequenceInfo_Shot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool FindOrCreate;
	/* seq_ + BaseName (usually part of SkeletalMesh Name) is appended to Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FName PackagePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class ULevelSequence* Shot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Export;
	/* anim_ + BaseName (usually part of SkeletalMesh Name) is appended to Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class UAnimSequence* Anim;

	FCsAnimLevelSequenceInfo_Shot()
	{
		FindOrCreate = false;
		Name = NAME_None;
		PackagePath = NAME_None;
		Shot = nullptr;
		Export = false;
		Anim = nullptr;
	}

	FCsAnimLevelSequenceInfo_Shot& operator=(const FCsAnimLevelSequenceInfo_Shot& B)
	{
		FindOrCreate = B.FindOrCreate;
		Name = B.Name;
		PackagePath = B.PackagePath;
		Shot = B.Shot;
		Export = B.Export;
		Anim = B.Anim;
		return *this;
	}

	bool operator==(const FCsAnimLevelSequenceInfo_Shot& B) const
	{
		return FindOrCreate == B.FindOrCreate &&
			   Name == B.Name &&
			   PackagePath == B.PackagePath &&
			   Shot == B.Shot &&
			   Export == B.Export &&
			   Anim == B.Anim;
	}

	bool operator!=(const FCsAnimLevelSequenceInfo_Shot& B) const
	{
		return !(*this == B);
	}
};

USTRUCT()
struct FCsAnimLevelSequenceInfo_Master
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Open;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool FindOrCreate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FName PackagePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class ULevelSequence* Master;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	TArray<FCsAnimLevelSequenceInfo_Shot> Shots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Export;

	FCsAnimLevelSequenceInfo_Master()
	{
		Open = false;
		FindOrCreate = false;
		PackagePath = NAME_None;
		Master = nullptr;
		Export = false;
	}

	FCsAnimLevelSequenceInfo_Master& operator=(const FCsAnimLevelSequenceInfo_Master& B)
	{
		Open = B.Open;
		FindOrCreate = B.FindOrCreate;
		PackagePath = B.PackagePath;
		Master = B.Master;

		Shots.Reset();
		const int32 Count = B.Shots.Num();

		for (int32 I = 0; I < Count; I++)
		{
			Shots.AddDefaulted();
			Shots[I] = B.Shots[I];
		}

		Export = B.Export;
		return *this;
	}

	bool operator==(const FCsAnimLevelSequenceInfo_Master& B) const
	{
		if (Open != B.Open)
			return false;
		if (FindOrCreate != B.FindOrCreate)
			return false;
		if (PackagePath != B.PackagePath)
			return false;
		if (Master != B.Master)
			return false;

		if (Shots.Num() != B.Shots.Num())
			return false;

		const int32 Count = Shots.Num();

		for (int32 I = 0; I < Count; I++)
		{
			if (Shots[I] != B.Shots[I])
				return false;
		}

		if (Export != B.Export)
			return false;
		return true;
	}

	bool operator!=(const FCsAnimLevelSequenceInfo_Master& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Level Sequence

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
	TArray<FCsAnimControlInfo_FK> Controls_FK;

	TArray<FCsAnimControlInfo_FK> Controls_FK_Copy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK;

	TArray<FCsAnimControlInfo_TwoBoneIK> Controls_TwoBoneIK_Copy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	FCsAnimLevelSequenceInfo_Master LevelSequence;

#if WITH_EDITOR

	void OnControlNameChanged_FK(const int32 &Index);
	void OnControlNameChanged_TwoBoneIK(const int32 &Index);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	void PostEditChangeProperty_LevelSequence_Master(struct FPropertyChangedEvent& e);
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;
	void PostEditChangeChainProperty_Control_FK(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_Control_FK_Connection(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_TwoBoneIK(struct FPropertyChangedChainEvent& e);
	void PostEditChangeChainProperty_LevelSequence_Shots(struct FPropertyChangedChainEvent& e);

	virtual void GenerateBones();
	virtual void ClearBones();
	void RecreateBone(const int32 &Index);

	void DestroyOrphanedControlAnchors();
	void DestroyOrphanedControlHelpers();

	void Create_Control_FK(const int32 &Index);
	void PerformFK(const int32 &Index);
	void ClearControlsFK();

	void Create_Control_TwoBoneIK(const int32 &Index);
	void PerformTwoBoneIK(const int32 &Index);
	void ClearControlsTwoBoneIK();

#endif // #if WITH_EDITOR
};