// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Engine/Classes/Engine/EngineTypes.h"
#include "Types/CsTypes.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsJavascriptLibrary.generated.h"

UCLASS()
class CSCORE_API UCsJavascriptLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ConsoleLog(const FString& String);

// Vector
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FString Vector_ToString(const FVector& V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float Vector_Size(const FVector& V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float Vector_SizeSquared(const FVector& V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector Vector_GetSafeNormal(const FVector& V);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Vector_Rotation(const FVector& V);

#pragma endregion Vector

// Rotator
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FString Rotator_ToString(const FRotator& R);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector Rotator_Vector(const FRotator& R);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Add_RotatorRotator(const FRotator& A, const FRotator& B);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FRotator Subtract_RotatorRotator(const FRotator& A, const FRotator& B);

#pragma endregion Rotator

// HitResult
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static AActor* HitResult_GetActor(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static UPrimitiveComponent* HitResult_GetComponent(const FHitResult& HitResult);

#pragma endregion HitResult

// PrimitiveComponent
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void SetCollisionResponseToChannels(UPrimitiveComponent* InComponent, const FCollisionResponseContainer& Response);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void AddMoveIngoreActor(UPrimitiveComponent* InComponent, AActor* InActor);

#pragma endregion PrimitiveComponent

// SceneComponent
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FVector GetComponentLocation(USceneComponent* InComponent);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ComponentAttachToComponent(USceneComponent* InComponent, USceneComponent* Parent, const ECsAttachmentTransformRules& AttachmentRules, const FName& SocketName = NAME_None);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ComponentDetachFromComponent(USceneComponent* InComponent, const ECsDetachmentTransformRules& DetachmentRules);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void SetComponentRelativeTransform(USceneComponent* InComponent, const FTransform& NewTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);

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
	static bool SetActorLocation(AActor* InActor, const FVector& NewLocation, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static bool SetActorRotation(AActor* InActor, const FRotator& NewRotation, const bool& bTeleportPhysics);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void SetActorRelativeRotation(AActor* InActor, const FRotator& NewRelativeRotation, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void SetActorRelativeTransform(AActor* InActor, const FTransform& NewTransform, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static bool TeleportTo(AActor* InActor, const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest = false, bool bNoCheck = false);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ActorAttachToActor(AActor* InActor, AActor* ParentActor, const ECsAttachmentTransformRules& AttachmentRules, const FName& SocketName = NAME_None);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ActorAttachToComponent(AActor* InActor, USceneComponent* Parent, const ECsAttachmentTransformRules& AttachmentRules, const FName& SocketName = NAME_None);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static void ActorDetachFromActor(AActor* InActor, const ECsDetachmentTransformRules& DetachmentRules);

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
	static FLinearColor GetLinearColor(const ECsLinearColor& Color);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static FColor GetColor(const ECsColor& Color);

#pragma endregion Color

// World
#pragma region 

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float GetTimeSeconds(UWorld* InWorld);
	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static float GetRealTimeSeconds(UWorld* InWorld);

#pragma endregion World

// CVars
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Javascript")
	static int32 GetConsoleVariableValue_int32(const FString& Name);

#pragma endregion CVars
};