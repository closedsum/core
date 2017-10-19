// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Engine/Classes/Engine/EngineTypes.h"
#include "Types/CsTypes.h"
#include "CsJavascriptLibrary.generated.h"

UCLASS()
class CSCORE_API UCsJavascriptLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Vector
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FString Vector_ToString(const FVector &V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float Vector_Size(const FVector &V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float Vector_SizeSquared(const FVector &V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector Vector_GetSafeNormal(const FVector &V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Vector_Rotation(const FVector &V);

#pragma endregion Vector

// Rotator
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FString Rotator_ToString(const FRotator &R);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector Rotator_Vector(const FRotator &R);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Add_RotatorRotator(const FRotator &A, const FRotator &B);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Subtract_RotatorRotator(const FRotator &A, const FRotator &B);

#pragma endregion Rotator

// HitResult
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static AActor* HitResult_GetActor(const FHitResult &HitResult);

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static UPrimitiveComponent* HitResult_GetComponent(const FHitResult &HitResult);

#pragma endregion HitResult

// SceneComponent
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector GetComponentLocation(class USceneComponent* Component);

#pragma endregion SceneComponent

// Actor
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static class USceneComponent* GetRootComponent(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector GetActorLocation(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator GetActorRotation(AActor* InActor);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static bool SetActorLocation(AActor* InActor, const FVector &NewLocation, const bool &bSweep, FHitResult& SweepHitResult, const bool &bTeleport);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static bool SetActorRotation(AActor* InActor, const FRotator &NewRotation, const bool &bTeleportPhysics);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void SetActorRelativeRotation(AActor* InActor, const FRotator &NewRelativeRotation, const bool &bSweep, FHitResult& SweepHitResult, const bool &bTeleport);

#pragma endregion Actor

// Character
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static class UCapsuleComponent* GetCapsuleComponent(class ACharacter* InCharacter);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static class UCharacterMovementComponent* GetCharacterMovement(class ACharacter* InCharacter);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static class USkeletalMeshComponent* GetMesh(class ACharacter* InCharacter);

#pragma endregion Character

// Color
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FLinearColor GetLinearColor(const TEnumAsByte<ECsLinearColor::Type> &Color);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
		static FColor GetColor(const TEnumAsByte<ECsColor::Type> &Color);

#pragma endregion Color
};