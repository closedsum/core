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
struct FCsAnimBoneInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	FName Bone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	class ACsAnim_Bone* Actor;

	FCsAnimBoneInfo()
	{
		Bone = NAME_None;
		Actor = nullptr;
	}
};

USTRUCT()
struct FCsAnimControlInfo_IK
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName IKBone;

	UPROPERTY()
	FName Last_IKBone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool AllowStretching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float StartStretchRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MaxStretchRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<EBoneControlSpace> EffectorLocationSpace;

	FCsAnimControlInfo_IK()
	{
		IKBone = NAME_None;
		Last_IKBone = IKBone;
		AllowStretching = false;
		StartStretchRatio = 1.0f;
		MaxStretchRatio = 1.2f;
		EffectorLocationSpace = BCS_BoneSpace;
	}
};

USTRUCT()
struct FCsAnimControlInfo_EndEffector
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool TakeRotationFromEffectorSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	bool MaintainEffectorRelRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName EffectorSpaceBoneName;

	UPROPERTY()
	FName Last_EffectorSpaceBoneName;

	FCsAnimControlInfo_EndEffector()
	{
		TakeRotationFromEffectorSpace = false;
		MaintainEffectorRelRot = false;
		EffectorSpaceBoneName = NAME_None;
		Last_EffectorSpaceBoneName = EffectorSpaceBoneName;
	}
};

USTRUCT()
struct FCsAnimControlInfo_JoinTarget
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FName JointTargetSpaceBoneName;

	UPROPERTY()
	FName Last_JointTargetSpaceBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<EBoneControlSpace> JointTargetLocationSpace;

	FCsAnimControlInfo_JoinTarget()
	{
		JointTargetLocationSpace = BCS_ParentBoneSpace;
	}
};

USTRUCT()
struct FCsAnimControlInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	TEnumAsByte<ECsAnimControl::Type> Type;

	UPROPERTY()
	TEnumAsByte<ECsAnimControl::Type> Last_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FString Control;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Control")
	class ACsAnim_Control* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_IK IK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_EndEffector EndEffector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	FCsAnimControlInfo_JoinTarget JointTarget;

	FCsAnimControlInfo()
	{
		Type = ECsAnimControl::None;
		Last_Type = Type;
		Control = TEXT("None");
		Actor = nullptr;
	}
};

#pragma endregion Structs

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsPoseableMeshActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	class UCsPoseableMeshComponent* PoseableMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "00 PoseableMesh")
	class USkeletalMesh* Last_SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 PoseableMesh")
	TArray<FCsAnimBoneInfo> Bones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 PoseableMesh")
	TArray<FCsAnimControlInfo> Controls;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

	virtual void GenerateBones();
	virtual void ClearBones();

#endif // #if WITH_EDITOR
};