// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes.h"
#include "CsPoseableMeshActor.generated.h"

// Enums
#pragma region

#pragma endregion Enums

// Structs
#pragma region

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
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

UENUM(BlueprintType)
namespace ECsSequencerTimeSnapInterval
{
	enum Type
	{
		STSI_0_001							UMETA(DisplayName = "0.001s"),
		STSI_0_01							UMETA(DisplayName = "0.01s"),
		STSI_0_1							UMETA(DisplayName = "0.1s"),
		STSI_1								UMETA(DisplayName = "1s"),
		STSI_10								UMETA(DisplayName = "10s"),
		STSI_100							UMETA(DisplayName = "100s"),
		STSI_15Fps							UMETA(DisplayName = "15 fps"),
		STSI_24Fps							UMETA(DisplayName = "24 fps (film)"),
		STSI_25Fps							UMETA(DisplayName = "25 fps (PAL/25)"),
		STSI_29_97Fps						UMETA(DisplayName = "29.97 fps (NTSC/30)"),
		STSI_30Fps							UMETA(DisplayName = "30 fps"),
		STSI_48Fps							UMETA(DisplayName = "48 fps"),
		STSI_50Fps							UMETA(DisplayName = "50 fps (PAL/50)"),
		STSI_59_94Fps						UMETA(DisplayName = "59.94 fps (NTSC/60)"),
		STSI_60Fps							UMETA(DisplayName = "60 fps"),
		STSI_120Fps							UMETA(DisplayName = "120 fps"),
		STSI_Custom							UMETA(DisplayName = "Custom"),
		ECsSequencerTimeSnapInterval_MAX	UMETA(Hidden),
	};
}

namespace ECsSequencerTimeSnapInterval
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString STSI_0_001 = TCsString(TEXT("STSI_0_001"), TEXT("stsi_0_001"), TEXT("0.001"));
		const TCsString STSI_0_01 = TCsString(TEXT("STSI_0_01"), TEXT("stsi_0_01"), TEXT("0.01"));
		const TCsString STSI_0_1 = TCsString(TEXT("STSI_0_1"), TEXT("stsi_0_1"), TEXT("0.1"));
		const TCsString STSI_1 = TCsString(TEXT("STSI_1"), TEXT("stsi_1"), TEXT("1"));
		const TCsString STSI_10 = TCsString(TEXT("STSI_10"), TEXT("stsi_10"), TEXT("10"));
		const TCsString STSI_100 = TCsString(TEXT("STSI_100"), TEXT("stsi_100"), TEXT("100"));
		const TCsString STSI_15Fps = TCsString(TEXT("STSI_15Fps"), TEXT("stsi_15fps"), TEXT("15fps"));
		const TCsString STSI_24Fps = TCsString(TEXT("STSI_24Fps"), TEXT("stsi_24fps"), TEXT("24fps"));
		const TCsString STSI_25Fps = TCsString(TEXT("STSI_25Fps"), TEXT("stsi_25fps"), TEXT("25fps"));
		const TCsString STSI_29_97Fps = TCsString(TEXT("STSI_29_97Fps"), TEXT("stsi_29_97fps"), TEXT("29.97fps"));
		const TCsString STSI_30Fps = TCsString(TEXT("STSI_30Fps"), TEXT("stsi_30fps"), TEXT("30fps"));
		const TCsString STSI_48Fps = TCsString(TEXT("STSI_48Fps"), TEXT("stsi_48fps"), TEXT("48fps"));
		const TCsString STSI_50Fps = TCsString(TEXT("STSI_50Fps"), TEXT("stsi_50fps"), TEXT("50fps"));
		const TCsString STSI_59_94Fps = TCsString(TEXT("STSI_59_94Fps"), TEXT("stsi_59_94fps"), TEXT("59.94fps"));
		const TCsString STSI_60Fps = TCsString(TEXT("STSI_60Fps"), TEXT("stsi_60fps"), TEXT("60fps"));
		const TCsString STSI_120Fps = TCsString(TEXT("STSI_120Fps"), TEXT("stsi_120fps"), TEXT("120fps"));
		const TCsString STSI_Custom = TCsString(TEXT("STSI_Custom"), TEXT("stsi_custom"), TEXT("custom"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::STSI_0_001) { return Str::STSI_0_001.Value; }
		if (EType == Type::STSI_0_01) { return Str::STSI_0_01.Value; }
		if (EType == Type::STSI_0_1) { return Str::STSI_0_1.Value; }
		if (EType == Type::STSI_1) { return Str::STSI_1.Value; }
		if (EType == Type::STSI_10) { return Str::STSI_10.Value; }
		if (EType == Type::STSI_100) { return Str::STSI_100.Value; }
		if (EType == Type::STSI_15Fps) { return Str::STSI_15Fps.Value; }
		if (EType == Type::STSI_24Fps) { return Str::STSI_24Fps.Value; }
		if (EType == Type::STSI_25Fps) { return Str::STSI_25Fps.Value; }
		if (EType == Type::STSI_29_97Fps) { return Str::STSI_29_97Fps.Value; }
		if (EType == Type::STSI_30Fps) { return Str::STSI_30Fps.Value; }
		if (EType == Type::STSI_48Fps) { return Str::STSI_48Fps.Value; }
		if (EType == Type::STSI_50Fps) { return Str::STSI_50Fps.Value; }
		if (EType == Type::STSI_59_94Fps) { return Str::STSI_59_94Fps.Value; }
		if (EType == Type::STSI_60Fps) { return Str::STSI_60Fps.Value; }
		if (EType == Type::STSI_120Fps) { return Str::STSI_120Fps.Value; }
		if (EType == Type::STSI_Custom) { return Str::STSI_Custom.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::STSI_0_001) { return Type::STSI_0_001; }
		if (String == Str::STSI_0_01) { return Type::STSI_0_01; }
		if (String == Str::STSI_0_1) { return Type::STSI_0_1; }
		if (String == Str::STSI_1) { return Type::STSI_1; }
		if (String == Str::STSI_10) { return Type::STSI_10; }
		if (String == Str::STSI_100) { return Type::STSI_100; }
		if (String == Str::STSI_15Fps) { return Type::STSI_15Fps; }
		if (String == Str::STSI_24Fps) { return Type::STSI_24Fps; }
		if (String == Str::STSI_25Fps) { return Type::STSI_25Fps; }
		if (String == Str::STSI_29_97Fps) { return Type::STSI_29_97Fps; }
		if (String == Str::STSI_30Fps) { return Type::STSI_30Fps; }
		if (String == Str::STSI_48Fps) { return Type::STSI_48Fps; }
		if (String == Str::STSI_50Fps) { return Type::STSI_50Fps; }
		if (String == Str::STSI_59_94Fps) { return Type::STSI_59_94Fps; }
		if (String == Str::STSI_60Fps) { return Type::STSI_60Fps; }
		if (String == Str::STSI_120Fps) { return Type::STSI_120Fps; }
		if (String == Str::STSI_Custom) { return Type::STSI_Custom; }
		return Type::ECsSequencerTimeSnapInterval_MAX;
	}

	FORCEINLINE float ToFloat(const Type &EType)
	{
		if (EType == Type::STSI_0_001) { return 0.001f; }
		if (EType == Type::STSI_0_01) { return 0.01f; }
		if (EType == Type::STSI_0_1) { return 0.1f; }
		if (EType == Type::STSI_1) { return 1.0f; }
		if (EType == Type::STSI_10) { return 10.0f; }
		if (EType == Type::STSI_100) { return 100.0f; }
		if (EType == Type::STSI_15Fps) { return 1.0f / 15.0f; }
		if (EType == Type::STSI_24Fps) { return 1.0f / 24.0f; }
		if (EType == Type::STSI_25Fps) { return 1.0f / 25.0f; }
		if (EType == Type::STSI_29_97Fps) { return 1.0f / 29.97f; }
		if (EType == Type::STSI_30Fps) { return 1.0f / 30.0f; }
		if (EType == Type::STSI_48Fps) { return 1.0f / 48.0f; }
		if (EType == Type::STSI_50Fps) { return 1.0f / 50.0f; }
		if (EType == Type::STSI_59_94Fps) { return 1.0f / 59.94f; }
		if (EType == Type::STSI_60Fps) { return 1.0f / 60.0f; }
		if (EType == Type::STSI_120Fps) { return 1.0f / 120.0f; }
		if (EType == Type::STSI_Custom) { return 0.01f; }
		return 1.0f;
	}

	FORCEINLINE float ToFPS(const Type &EType)
	{
		if (EType == Type::STSI_0_001) { return 1000.0f; }
		if (EType == Type::STSI_0_01) { return 100.0f; }
		if (EType == Type::STSI_0_1) { return 10.0f; }
		if (EType == Type::STSI_1) { return 1.0f; }
		if (EType == Type::STSI_10) { return 0.1f; }
		if (EType == Type::STSI_100) { return 0.01f; }
		if (EType == Type::STSI_15Fps) { return 15.0f; }
		if (EType == Type::STSI_24Fps) { return 24.0f; }
		if (EType == Type::STSI_25Fps) { return 25.0f; }
		if (EType == Type::STSI_29_97Fps) { return 29.97f; }
		if (EType == Type::STSI_30Fps) { return 30.0f; }
		if (EType == Type::STSI_48Fps) { return 48.0f; }
		if (EType == Type::STSI_50Fps) { return 50.0f; }
		if (EType == Type::STSI_59_94Fps) { return 59.94f; }
		if (EType == Type::STSI_60Fps) { return 60.0f; }
		if (EType == Type::STSI_120Fps) { return 120.0f; }
		if (EType == Type::STSI_Custom) { return 100.0f; }
		return 1.0f;
	}
}

#define ECS_SEQUENCER_TIME_SNAP_INTERVAL_MAX (uint8)ECsSequencerTimeSnapInterval::ECsSequencerTimeSnapInterval_MAX
typedef TEnumAsByte<ECsSequencerTimeSnapInterval::Type> TCsSequencerTimeSnapInterval;

USTRUCT(BlueprintType)
struct FCsAnimLevelSequenceInfo_Shot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool FindOrCreate;
	/* seq_ + BaseName (usually part of SkeletalMesh Name) is appended to Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FString PackagePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class ULevelSequence* Shot;
	/* Export Shot to AnimSequence */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Export;
	/* Interval at which to Save AnimSequence (i.e. 30 Fps, 60 Fps, ... etc) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	TEnumAsByte<ECsSequencerTimeSnapInterval::Type> ExportInterval;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	float ExportInterval_Internal;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	float ExportInterval_FPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Import;

	/* anim_ + BaseName (usually part of SkeletalMesh Name) is appended to Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class UAnimSequence* Anim;

	FCsAnimLevelSequenceInfo_Shot()
	{
		FindOrCreate = false;
		Name = TEXT("");
		PackagePath = TEXT("");
		Shot = nullptr;
		Export = false;
		ExportInterval = ECsSequencerTimeSnapInterval::STSI_30Fps;
		ExportInterval_Internal = ECsSequencerTimeSnapInterval::ToFloat(ExportInterval);
		ExportInterval_FPS = ECsSequencerTimeSnapInterval::ToFPS(ExportInterval);
		Anim = nullptr;
	}

	FCsAnimLevelSequenceInfo_Shot& operator=(const FCsAnimLevelSequenceInfo_Shot& B)
	{
		FindOrCreate = B.FindOrCreate;
		Name = B.Name;
		PackagePath = B.PackagePath;
		Shot = B.Shot;
		Export = B.Export;
		ExportInterval = B.ExportInterval;
		ExportInterval_Internal = B.ExportInterval_Internal;
		ExportInterval_FPS = B.ExportInterval_FPS;
		Import = B.Import;
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
			   ExportInterval == B.ExportInterval &&
			   ExportInterval_Internal == B.ExportInterval_Internal &&
			   ExportInterval_FPS == B.ExportInterval_FPS &&
			   Import == B.Import &&
			   Anim == B.Anim;
	}

	bool operator!=(const FCsAnimLevelSequenceInfo_Shot& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsAnimLevelSequenceInfo_Master
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Open;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool FindOrCreate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	FString PackagePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	class ULevelSequence* Master;
	/* Export all Shots to AnimSequences */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	bool Export;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Sequence")
	TArray<FCsAnimLevelSequenceInfo_Shot> Shots;

	TArray<FCsAnimLevelSequenceInfo_Shot> Shots_Copy;

	FCsAnimLevelSequenceInfo_Master()
	{
		Open = false;
		FindOrCreate = false;
		Name = TEXT("");
		PackagePath = TEXT("");
		Master = nullptr;
		Export = false;
	}

	FCsAnimLevelSequenceInfo_Master& operator=(const FCsAnimLevelSequenceInfo_Master& B)
	{
		Open = B.Open;
		FindOrCreate = B.FindOrCreate;
		Name = B.Name;
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
		if (Name != B.Name)
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
	FCsAnimLevelSequenceInfo_Master AnimLevelSequence;

#if WITH_EDITOR

	bool bIsAssetEditorOpen;
	bool IsAssetEditorOpen();

	class FLevelSequenceEditorToolkit* LevelSequenceEditor;
	class FLevelSequenceEditorToolkit* GetOpenAssetEditor();

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

	class ACsAnim_Bone* GetBone(const FName &BoneName);
	class ACsAnim_Bone* GetBone(const FString &BoneName);

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