// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Javascript/CsJavascriptLibrary.h"
#include "CsCore.h"

UCsJavascriptLibrary::UCsJavascriptLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Vector
#pragma region

FString UCsJavascriptLibrary::Vector_ToString(const FVector &V) { return V.ToString(); }
float UCsJavascriptLibrary::Vector_Size(const FVector &V) { return V.Size(); }
float UCsJavascriptLibrary::Vector_SizeSquared(const FVector &V) { return V.SizeSquared(); }
FVector UCsJavascriptLibrary::Vector_GetSafeNormal(const FVector &V) { return V.GetSafeNormal(); }
FRotator UCsJavascriptLibrary::Vector_Rotation(const FVector &V) { return V.Rotation(); }

#pragma endregion Vector

// Rotator
#pragma region

FString UCsJavascriptLibrary::Rotator_ToString(const FRotator &R) { return R.ToString(); }
FVector UCsJavascriptLibrary::Rotator_Vector(const FRotator &R) { return R.Vector(); }
FRotator UCsJavascriptLibrary::Add_RotatorRotator(const FRotator &A, const FRotator &B) { return A + B; }
FRotator UCsJavascriptLibrary::Subtract_RotatorRotator(const FRotator &A, const FRotator &B) { return A - B; }

#pragma endregion Rotator

// HitResult
#pragma region

AActor* UCsJavascriptLibrary::HitResult_GetActor(const FHitResult &HitResult) { return HitResult.GetActor(); }
UPrimitiveComponent* UCsJavascriptLibrary::HitResult_GetComponent(const FHitResult &HitResult) { return HitResult.GetComponent(); }

#pragma endregion HitResult

// SceneComponent
#pragma region

FVector UCsJavascriptLibrary::GetComponentLocation(USceneComponent* Component) { return Component->GetComponentLocation(); }

#pragma endregion SceneComponent

// Actor
#pragma region

USceneComponent* UCsJavascriptLibrary::GetRootComponent(AActor* InActor) { return InActor->GetRootComponent(); }
FVector UCsJavascriptLibrary::GetActorLocation(AActor* InActor) { return InActor->GetActorLocation(); }
FRotator UCsJavascriptLibrary::GetActorRotation(AActor* InActor) { return InActor->GetActorRotation(); }

bool UCsJavascriptLibrary::SetActorLocation(AActor* InActor, const FVector& NewLocation, const bool &bSweep, FHitResult& SweepHitResult, const bool &bTeleport)
{
	return InActor->K2_SetActorLocation(NewLocation, bSweep, SweepHitResult, bTeleport);
}

bool UCsJavascriptLibrary::SetActorRotation(AActor* InActor, const FRotator &NewRotation, const bool &bTeleportPhysics)
{
	return InActor->K2_SetActorRotation(NewRotation, bTeleportPhysics);
}

void UCsJavascriptLibrary::SetActorRelativeRotation(AActor* InActor, const FRotator &NewRelativeRotation, const bool &bSweep, FHitResult& SweepHitResult, const bool &bTeleport)
{
	InActor->K2_SetActorRelativeRotation(NewRelativeRotation, bSweep, SweepHitResult, bTeleport);
}

#pragma endregion Actor

// Character
#pragma region

UCapsuleComponent* UCsJavascriptLibrary::GetCapsuleComponent(ACharacter* InCharacter) { return InCharacter->GetCapsuleComponent(); }
UCharacterMovementComponent* UCsJavascriptLibrary::GetCharacterMovement(ACharacter* InCharacter) { return InCharacter->GetCharacterMovement(); }
USkeletalMeshComponent* UCsJavascriptLibrary::GetMesh(class ACharacter* InCharacter) { return InCharacter->GetMesh(); }

#pragma endregion Character

// Color
#pragma region

FLinearColor UCsJavascriptLibrary::GetLinearColor(const TEnumAsByte<ECsLinearColor::Type> &Color) { return ECsLinearColor::ToLinearColor(Color); }
FColor UCsJavascriptLibrary::GetColor(const TEnumAsByte<ECsColor::Type> &Color) { return ECsColor::ToColor(Color); }

#pragma endregion Color

// World
#pragma region 

float UCsJavascriptLibrary::GetTimeSeconds(UWorld* InWorld) { return InWorld->GetTimeSeconds(); }

#pragma endregion World