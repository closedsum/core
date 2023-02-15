// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine/DataAsset.h"

#include "CsVertexAnimProfile.generated.h"

class UAnimationAsset;
struct FCsVertexAnimInfo;

/**
* Struct Holding helper data specific to an Animation Sequence needed for the baking process
*/
USTRUCT(BlueprintType)
struct CSVAT_API FCsVertexAnim_SequenceData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = BakeSequence)
	TSoftObjectPtr<UAnimationAsset> SequenceRef;
	
	UPROPERTY(EditAnywhere, Category = BakeSequence, meta = (UIMin = "1", ClampMin = "1"))
	int32 NumFrames;

	UPROPERTY(EditAnywhere, Category = BakeSequenceGenerated, meta = (UIMin = "0", ClampMin = "0"))
	int32 AnimStart_Generated;

	UPROPERTY(EditAnywhere, Category = BakeSequenceGenerated, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Speed_Generated;

	FCsVertexAnim_SequenceData() :
		SequenceRef(nullptr),
		NumFrames(8),
		AnimStart_Generated(0),
		Speed_Generated(1.0f)
	{
	}

	void CopyToInfo(FCsVertexAnimInfo* Info) const;
};

USTRUCT(BlueprintType)
struct CSVAT_API FCsVertexAnim_SequenceData_Short
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = BakeSequence)
	TSoftObjectPtr<UAnimationAsset> SequenceRef;
	
	UPROPERTY(EditAnywhere, Category = BakeSequence, meta = (UIMin = "1", ClampMin = "1"))
	int32 NumFrames;

	FCsVertexAnim_SequenceData_Short() :
		SequenceRef(nullptr),
		NumFrames(8)
	{
	}
};

class USkeletalMesh;
class UStaticMesh;
class UTexture2D;

/**
* Data asset holding all the helper data needed for the baking process
*/
UCLASS(BlueprintType)
class CSVAT_API UCsVertexAnimProfile : public UDataAsset
{
	GENERATED_UCLASS_BODY()

public:

// AnimProfile

	UPROPERTY(EditAnywhere, Category = AnimProfile)
	bool bBake;

	UPROPERTY(EditAnywhere, Category = AnimProfile)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = AnimProfile)
	bool AutoSize;

	UPROPERTY(EditAnywhere, Category = AnimProfile, meta = (UIMin = "0", ClampMin = "0"))
	int32 MaxWidth;
	
// VertAnim

	UPROPERTY(EditAnywhere, Category = VertAnim)
	bool UVMergeDuplicateVerts;

	UPROPERTY(EditAnywhere, Category = VertAnim)
	FIntPoint OverrideSize_Vert;

	UPROPERTY(EditAnywhere, Category = VertAnim)
	TArray<FCsVertexAnim_SequenceData> Anims_Vert;

// BoneAnim

	UPROPERTY(EditAnywhere, Category = BoneAnim)
	bool FullBoneSkinning;

	UPROPERTY(EditAnywhere, Category = BoneAnim)
	FIntPoint OverrideSize_Bone;

	UPROPERTY(EditAnywhere, Category = BoneAnim)
	TArray<FCsVertexAnim_SequenceData> Anims_Bone;

// AnimProfileGenerated

	UPROPERTY(EditAnywhere, Category = AnimProfileGenerated)
	TSoftObjectPtr<UStaticMesh> StaticMesh;

// Generated_VertAnim

	UPROPERTY(EditAnywhere, Category = Generated_VertAnim)
	int32 UVChannel_VertAnim;

	UPROPERTY(EditAnywhere, Category = Generated_VertAnim)
	TSoftObjectPtr<UTexture2D> OffsetsTexture;

	UPROPERTY(EditAnywhere, Category = Generated_VertAnim)
	TSoftObjectPtr<UTexture2D> NormalsTexture;

	UPROPERTY(EditAnywhere, Category = Generated_VertAnim)
	int32 RowsPerFrame_Vert;

	UPROPERTY(EditAnywhere, Category = Generated_VertAnim)
	float MaxValueOffset_Vert;

// Generated_BoneAnim

	UPROPERTY(EditAnywhere, Category = Generated_BoneAnim)
	int32 UVChannel_BoneAnim;

	UPROPERTY(EditAnywhere, Category = Generated_BoneAnim)
	int32 UVChannel_BoneAnim_Full;

	UPROPERTY(EditAnywhere, Category = Generated_BoneAnim)
	TSoftObjectPtr<UTexture2D> BonePosTexture;

	UPROPERTY(EditAnywhere, Category = Generated_BoneAnim)
	TSoftObjectPtr<UTexture2D> BoneRotTexture;

	UPROPERTY(EditAnywhere, Category = Generated_BoneAnim)
	float MaxValuePosition_Bone;

	int32 CalcTotalNumOfFrames_Vert() const;
	int32 CalcTotalRequiredHeight_Vert() const;

	int32 CalcTotalNumOfFrames_Bone() const;
	int32 CalcTotalRequiredHeight_Bone() const;

	int32 CalcStartHeightOfAnim_Vert(const int32 AnimIndex) const;
	int32 CalcStartHeightOfAnim_Bone(const int32 AnimIndex) const;

	bool IsValid() const;

// Editor
#pragma region
public:

#if WITH_EDITOR
	
	bool PerformBake();

#endif // #if WITH_EDITOR

#pragma endregion Editor
};
