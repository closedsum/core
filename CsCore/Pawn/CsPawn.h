// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "CsPawn.generated.h"

UCLASS()
class CSCORE_API ACsPawn : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

// View
#pragma region

	UPROPERTY(BlueprintReadOnly, Category = "View")
	FRotator CurrentViewRotation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewLocation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewDir;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewRight;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentViewRightXY;

	virtual void RecordView();

#pragma endregion View

// Body / Root
#pragma region

	UPROPERTY(BlueprintReadOnly, Category = "View")
	FRotator CurrentRootRotation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootLocation;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootDir;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootRight;
	UPROPERTY(BlueprintReadOnly, Category = "View")
	FVector CurrentRootRightXY;

	virtual void RecordRoot();

#pragma endregion Body / Root

// Movement
#pragma region

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDir;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityDirZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentSpeedZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentVelocityRightXY;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDir;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDirXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityZ;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityDirZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedXY;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float CurrentCapsuleSpeedZ;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRight;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector CurrentCapsuleVelocityRightXY;

	virtual void RecordVelocityAndSpeed();

#pragma endregion Movement
};