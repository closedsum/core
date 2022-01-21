// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"

#include "CsAnimInstance_Mannequin_Silhouette.generated.h"

class ACsMannequin_Silhouette;

UCLASS()
class CSCORE_API UCsAnimInstance_Mannequin_Silhouette : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

// UAnimInstance Interface
#pragma region
public:

	/** Init */
	virtual void NativeInitializeAnimation() override;

	/** Tick */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

#pragma endregion UAnimInstance Interface

// Owner
#pragma region
public:

	ACsMannequin_Silhouette* MyOwner;

#pragma endregion Owner

// Controls
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float PelvisHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float PelvisDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float PelvisWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float PelvisHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerTorsoHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerTorsoDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerTorsoWidth;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	//float LowerTorsoHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperTorsoHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperTorsoDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperTorsoWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ChestHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ChestDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ChestWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HeadHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HeadDepth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HeadWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HeadScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LatSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float LatHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperarmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperarmThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperarmThickness_Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float UpperarmThickness_Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerarmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerarmThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerarmThickness_Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float LowerarmThickness_Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HandLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HandThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HandWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float HandScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ThighLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ThighThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ThighThickness_Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float ThighThickness_Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float CalfLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float CalfThickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float CalfThickness_Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float CalfThickness_Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float FootHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float FootLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float FootWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls", meta = (UIMin = "0.01", ClampMin = "0.01"))
	float FootScale;

#pragma endregion Controls
};