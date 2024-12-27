// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsTypes_Mannequin_Silhouette.generated.h"

class UStaticMeshComponent;
class USceneComponent;

namespace NCsAnimation
{
	namespace NMannequin
	{
		namespace NSilhouette
		{
			enum class EBone : uint8 
			{
				pelvis,
				thigh_l,
				thigh_r,
				calf_l,
				calf_r,
				foot_l,
				foot_r,
				spine_01,
				spine_02,
				spine_03,
				clavicle_l,
				clavicle_r,
				upperarm_l,
				upperarm_r,
				lowerarm_l,
				lowerarm_r,
				hand_r ,
				hand_l,
				neck_01,
				head,
				EBone_MAX
			};

			struct CSCORE_API FBoneControlInfo
			{
			public:

				typedef NCsAnimation::NMannequin::NSilhouette::EBone BoneType;

				BoneType Type;

				UStaticMeshComponent* Bone;

				FName BoneName;

				USceneComponent* Control;

				FTransform Transform;

				FTransform Last_Transform;

				FBoneControlInfo() :
					Type(BoneType::EBone_MAX),
					Bone(nullptr),
					BoneName(NAME_None),
					Control(nullptr),
					Transform(FTransform::Identity),
					Last_Transform(FTransform::Identity)
				{
				}

				FORCEINLINE void SetBone(const BoneType& InType, UStaticMeshComponent* Value, const FName& Name)
				{
					Type	 = InType;
					Bone	 = Value;
					BoneName = Name;
				}

				FORCEINLINE void SetControl(USceneComponent* Value) { Control = Value; }

				FORCEINLINE bool HasChanged() const
				{
					return Transform.GetLocation() != Last_Transform.GetLocation() ||
						   Transform.GetRotation() != Last_Transform.GetRotation() ||
						   Transform.GetScale3D() != Last_Transform.GetScale3D();
				}
				
				FORCEINLINE void Resolve() { Last_Transform = Transform; }

				void OnModify(FBoneControlInfo& DOb);
			};

			enum class EBoneControlApplication : uint8
			{
				/** Set controls values on the AnimInstance from transform changes on components.
					Corresponding member values will also get updated. */
				Component,
				/** Set control values on the AnimInstance from member value changes.
					Corresponding components will also get updated. */
				Member,
				EBoneControlApplication_MAX,
			};
		}
	}
}

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControl_Core
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin")
	float HeightOffset;

	FCsMannequinSilhouette_BoneControl_Core() :
		Height(1.0f),
		Depth(1.0f),
		Width(1.0f),
		HeightOffset(0.0f)
	{
	}

	FORCEINLINE void SetFromScale(const FVector3d& InScale)
	{
		static const float MIN = 0.01f;

		Height = FMath::Max(MIN, InScale.X);
		Depth  = FMath::Max(MIN, InScale.Y);
		Width  = FMath::Max(MIN, InScale.Z);
	}

	FORCEINLINE FVector3d GetScale() const { return FVector3d(Height, Depth, Width); }

	using InfoType = NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo;

	void OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Core& DOb, InfoType& Info);
	void OnUpdateByMember(InfoType& DObInfo, InfoType& Info);

	FORCEINLINE bool IsModified(const FString& MemberName, const TSet<FString>& PropertyNames)
	{
		if (PropertyNames.Contains(MemberName) &&
			(PropertyNames.Contains("Height") ||
			 PropertyNames.Contains("Depth") ||
			 PropertyNames.Contains("Width") ||
			 PropertyNames.Contains("HeightOffset")))
		{
			return true;
		}
		return false;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControl_Limb
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Thickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Width;

	FCsMannequinSilhouette_BoneControl_Limb() :
		Length(1.0f),
		Thickness(1.0f),
		Depth(1.0f),
		Width(1.0f)
	{
	}

	FORCEINLINE void SetFromScale(const FVector3d& InScale)
	{
		static const float MIN = 0.01f;

		Length = FMath::Max(MIN, InScale.X);
		Depth  = FMath::Max(MIN, InScale.Y);
		Width  = FMath::Max(MIN, InScale.Z);
	}

	FORCEINLINE FVector3d GetScale() const { return FVector3d(Length, Depth, Width); }

	using InfoType = NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo;

	void OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Limb& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);
	void OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);

	FORCEINLINE bool IsModified(const FString& MemberName, const TSet<FString>& PropertyNames)
	{
		if (PropertyNames.Contains(MemberName) &&
			(PropertyNames.Contains("Length") ||
			 PropertyNames.Contains("Thickness") ||
			 PropertyNames.Contains("Depth") ||
			 PropertyNames.Contains("Width")))
		{
			return true;
		}
		return false;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControl_Foot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Scale;

	FCsMannequinSilhouette_BoneControl_Foot() :
		Height(1.0f),
		Length(1.0f),
		Width(1.0f),
		Scale(1.0f)
	{
	}

	FORCEINLINE void SetFromScale(const FVector3d& InScale)
	{
		static const float MIN = 0.01f;

		Height = FMath::Max(MIN, InScale.X);
		Length = FMath::Max(MIN, InScale.Y);
		Width  = FMath::Max(MIN, InScale.Z);
	}

	FORCEINLINE FVector3d GetScale() const { return FVector3d(Height, Length, Width); }

	using InfoType = NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo;

	void OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Foot& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);
	void OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);

	FORCEINLINE bool IsModified(const FString& MemberName, const TSet<FString>& PropertyNames)
	{
		if (PropertyNames.Contains(MemberName) &&
			(PropertyNames.Contains("Height") ||
			 PropertyNames.Contains("Length") ||
			 PropertyNames.Contains("Width") ||
			 PropertyNames.Contains("Scale")))
		{
			return true;
		}
		return false;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControl_Hand
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Thickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Scale;

	FCsMannequinSilhouette_BoneControl_Hand() :
		Length(1.0f),
		Thickness(1.0f),
		Width(1.0f),
		Scale(1.0f)
	{
	}

	FORCEINLINE void SetFromScale(const FVector3d& InScale)
	{
		static const float MIN = 0.01f;

		Length	  = FMath::Max(MIN, InScale.X);
		Thickness = FMath::Max(MIN, InScale.Y);
		Width	  = FMath::Max(MIN, InScale.Z);
	}

	FORCEINLINE FVector3d GetScale() const { return FVector3d(Length, Thickness, Width); }

	using InfoType = NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo;

	void OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Hand& DOb, InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);
	void OnUpdateByMember(InfoType& LeftDOb, InfoType& Left, InfoType& RightDOb, InfoType& Right);

	FORCEINLINE bool IsModified(const FString& MemberName, const TSet<FString>& PropertyNames)
	{
		if (PropertyNames.Contains(MemberName) &&
			(PropertyNames.Contains("Length") ||
			 PropertyNames.Contains("Thickness") ||
			 PropertyNames.Contains("Width") ||
			 PropertyNames.Contains("Scale")))
		{
			return true;
		}
		return false;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsMannequinSilhouette_BoneControl_Head
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Anim|Mannequin")
	float HeightOffset;

	FCsMannequinSilhouette_BoneControl_Head() :
		Height(1.0f),
		Depth(1.0f),
		Width(1.0f),
		Scale(1.0f),
		HeightOffset(0.0f)
	{
	}

	FORCEINLINE void SetFromScale(const FVector3d& InScale)
	{
		static const float MIN = 0.01f;

		Height = FMath::Max(MIN, InScale.X);
		Depth  = FMath::Max(MIN, InScale.Y);
		Width  = FMath::Max(MIN, InScale.Z);
	}

	FORCEINLINE FVector3d GetScale() const { return FVector3d(Height, Depth, Width); }

	using InfoType = NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo;

	void OnUpdateByComponent(FCsMannequinSilhouette_BoneControl_Head& DOb, InfoType& Info);
	void OnUpdateByMember(InfoType& DObInfo, InfoType& Info);

	FORCEINLINE bool IsModified(const FString& MemberName, const TSet<FString>& PropertyNames)
	{
		if (PropertyNames.Contains(MemberName) &&
			(PropertyNames.Contains("Height") ||
			 PropertyNames.Contains("Depth") ||
			 PropertyNames.Contains("Width") ||
			 PropertyNames.Contains("Scale") ||
			 PropertyNames.Contains("HeightOffset")))
		{
			return true;
		}
		return false;
	}
};