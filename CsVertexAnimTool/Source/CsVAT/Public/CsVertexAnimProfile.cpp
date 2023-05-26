// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsVertexAnimProfile.h"
#include "CsVAT.h"

// Animation
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimationAsset.h"
#include "Animation/Vertex/CsVertexAnimInfo.h"

#if WITH_EDITOR
// Animation
#include "CsGetVertexAnimTool.h"
// Engine
#include "Engine/Engine.h"
#endif // #if WITH_EDITOR

// FCsVertexAnim_SequenceData
#pragma region

void FCsVertexAnim_SequenceData::CopyToInfo(FCsVertexAnimInfo* Info, const float& ScaleLength /*=1.0f*/) const
{
	Info->NumFrames = NumFrames;
	Info->AnimStartGenerated = AnimStart_Generated;
	Info->SpeedGenerated = Speed_Generated;

	if (UAnimSequenceBase* Asset = Cast<UAnimSequenceBase>(SequenceRef.LoadSynchronous()))
	{
		Info->Length = ScaleLength * Asset->GetPlayLength();
	}

	if (Info->PlayRate == 0.0f)
	{
		Info->PlayRate = 1.0f;
	}
}

int32 FCsVertexAnim_SequenceData_Short::GetNumFrames() const
{
	if (UAnimSequenceBase* Asset = Cast<UAnimSequenceBase>(SequenceRef.LoadSynchronous()))
	{
		const float Length = Asset->GetPlayLength();

		// Custom
		if (FrameRate == ECsVertexAnimSequenceDataFrameRate::Fps_Custom)
			return FMath::CeilToInt(Length * Fps);
		// Custom Frames
		if (FrameRate == ECsVertexAnimSequenceDataFrameRate::Fps_Custom_Frames)
			return NumFrames;

		const float _Fps = NCsVertexAnimSequenceDataFrameRate::GetFramesPerSecond(FrameRate);

		return FMath::CeilToInt(Length * _Fps);
	}
	return NumFrames;
}

#pragma endregion FCsVertexAnim_SequenceData

UCsVertexAnimProfile::UCsVertexAnimProfile(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	// AnimProfile
	bBake(false),
	SkeletalMesh(nullptr),
	AutoSize(true),
	MaxWidth(2048),
	// VertAnim
	UVMergeDuplicateVerts(true),
	OverrideSize_Vert(0, 0),
	Anims_Vert(),
	// BoneAnim
	FullBoneSkinning(false),
	OverrideSize_Bone(0, 0),
	Anims_Bone(),
	// AnimProfileGenerated
	StaticMesh(nullptr),
	// Generated_VertAnim
	UVChannel_VertAnim(INDEX_NONE),
	OffsetsTexture(nullptr),
	NormalsTexture(nullptr),
	RowsPerFrame_Vert(0),
	MaxValueOffset_Vert(0.0f),
	// Generated_BoneAnim
	UVChannel_BoneAnim(INDEX_NONE),
	UVChannel_BoneAnim_Full(INDEX_NONE),
	BonePosTexture(nullptr),
	BoneRotTexture(nullptr),
	MaxValuePosition_Bone(0)
{
}

int32 UCsVertexAnimProfile::CalcTotalNumOfFrames_Vert() const
{
	int32 Out = 0;

	for (int32 i = 0; i < Anims_Vert.Num(); i++)
	{
		Out += Anims_Vert[i].NumFrames;
	}
	return Out;
}

int32 UCsVertexAnimProfile::CalcTotalRequiredHeight_Vert() const
{
	return RowsPerFrame_Vert * CalcTotalNumOfFrames_Vert();
}

int32 UCsVertexAnimProfile::CalcTotalNumOfFrames_Bone() const
{
	int32 Out = 0;

	for (int32 i = 0; i < Anims_Bone.Num(); i++)
	{
		Out += Anims_Bone[i].NumFrames;
	}
	return Out;
}

int32 UCsVertexAnimProfile::CalcTotalRequiredHeight_Bone() const
{
	return CalcTotalNumOfFrames_Bone();
}

int32 UCsVertexAnimProfile::CalcStartHeightOfAnim_Vert(const int32 AnimIndex) const
{
	int32 Out = 0;

	for (int32 i = 0; i < AnimIndex; i++)
	{
		 Out += Anims_Vert[i].NumFrames;
	}
	return RowsPerFrame_Vert * Out;
}

int32 UCsVertexAnimProfile::CalcStartHeightOfAnim_Bone(const int32 AnimIndex) const
{
	int32 Out = 0;

	for (int32 i = 0; i < AnimIndex; i++)
	{
		Out += Anims_Bone[i].NumFrames;
	}
	return Out + 1;
}

bool UCsVertexAnimProfile::IsValid() const
{
	// Invalid Offsets or Normals Texture
	if ((!AutoSize) && (OverrideSize_Vert.GetMax() < 8)) 
	{
		UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Deactivated Auto Size, but invalid Override Size."), *(GetName()));
		return false;
	}

	// Profile has not Anims
	if ((Anims_Vert.Num() == 0) && (Anims_Bone.Num() == 0)) 
	{
		UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has no Anims."), *(GetName()));
		return false;
	}
		
	USkeleton* Skeleton = nullptr;

	if (Anims_Vert.Num())
	{
		if (UAnimationAsset* Asset = Anims_Vert[0].SequenceRef.LoadSynchronous())
		{
			Skeleton = Asset->GetSkeleton();
		}
	}

	if (Anims_Bone.Num())
	{
		if (UAnimationAsset* Asset = Anims_Bone[0].SequenceRef.LoadSynchronous())
		{
			Skeleton = Asset->GetSkeleton();
		}
	}

	{
		for (int32 i = 0; i < Anims_Vert.Num(); i++)
		{
			UAnimationAsset* OtherAsset = Anims_Vert[i].SequenceRef.LoadSynchronous();

			// Invalid Sequence Ref
			if (!OtherAsset)
			{
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anim with invalid Sequence Ref."), *(GetName()));
				return false;
			}
				
			if (OtherAsset->GetSkeleton() != Skeleton)
			{
				// Anims have different Skeletons
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anims with different skeletons."), *(GetName()));
				return false;
			}

			if ((Anims_Vert[i].NumFrames < 1))
			{
				// Anim has Num Frames less than 1
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anim with Num Frames less than 1."), *(GetName()));
				return false;
			}
		}
	}
	{
		for (int32 i = 0; i < Anims_Bone.Num(); i++)
		{
			UAnimationAsset* OtherAsset = Anims_Bone[i].SequenceRef.LoadSynchronous();

			// Invalid Sequence Ref
			if (!OtherAsset)
			{
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anim with invalid Sequence Ref."), *(GetName()));
				return false;
			}

			if (OtherAsset->GetSkeleton() != Skeleton)
			{
				// Anims have different Skeletons
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anims with different skeletons."), *(GetName()));
				return false;
			}
			if ((Anims_Bone[i].NumFrames < 1))
			{
				// Anim has Num Frames less than 1
				UE_LOG(LogCsVAT, Warning, TEXT("UCsVertexAnimProfile::IsValid: %s: Selected Profile has anim with Num Frames less than 1."), *(GetName()));
				return false;
			}
		}
	}

	//Profile->LODInSkeletalMesh;
	return true;
}

// Editor
#pragma region

#if WITH_EDITOR

bool UCsVertexAnimProfile::PerformBake()
{
	if (IsValid())
	{
		typedef NCsAnimation::NVertex::NTool::FImpl VertexAnimToolType;

		ICsGetVertexAnimTool* GetVertexAnimTool = Cast<ICsGetVertexAnimTool>(GEngine);
		VertexAnimToolType* VertexAnimTool		= GetVertexAnimTool->GetVertexAnimTool();
	
		VertexAnimTool->DoBackProcessImpl(this);
		return true;
	}
	return false;
} 
#endif // #if WITH_EDITOR