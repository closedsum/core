// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "CsPawn.generated.h"

UCLASS()
class CSCORE_API ACsPawn : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

// Movement
#pragma region

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocity;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocityDir;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocityXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocityDirXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocityZ;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentVelocityDirZ;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentSpeedXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentSpeedZ;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocity;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocityDir;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocityXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocityDirXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocityZ;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector CurrentCapsuleVelocityDirZ;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentCapsuleSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentCapsuleSpeedXY;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float CurrentCapsuleSpeedZ;

	virtual void RecordVelocityAndSpeed();

#pragma endregion Movement
};