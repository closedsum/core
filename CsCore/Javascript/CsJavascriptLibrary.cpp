// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Javascript/CsJavascriptLibrary.h"
#include "CsCore.h"

#include "Runtime/Core/Public/HAL/IConsoleManager.h"

UCsJavascriptLibrary::UCsJavascriptLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsJavascriptLibrary::ConsoleLog(const FString& String)
{
	UE_LOG(LogCs, Log, TEXT("Javascript: %s"), *String);
}

// Vector
#pragma region

FString UCsJavascriptLibrary::Vector_ToString(const FVector& V) { return V.ToString(); }
float UCsJavascriptLibrary::Vector_Size(const FVector& V) { return V.Size(); }
float UCsJavascriptLibrary::Vector_SizeSquared(const FVector& V) { return V.SizeSquared(); }
FVector UCsJavascriptLibrary::Vector_GetSafeNormal(const FVector& V) { return V.GetSafeNormal(); }
FRotator UCsJavascriptLibrary::Vector_Rotation(const FVector& V) { return V.Rotation(); }

#pragma endregion Vector

// Rotator
#pragma region

FString UCsJavascriptLibrary::Rotator_ToString(const FRotator& R) { return R.ToString(); }
FVector UCsJavascriptLibrary::Rotator_Vector(const FRotator& R) { return R.Vector(); }
FRotator UCsJavascriptLibrary::Add_RotatorRotator(const FRotator& A, const FRotator& B) { return A + B; }
FRotator UCsJavascriptLibrary::Subtract_RotatorRotator(const FRotator& A, const FRotator& B) { return A - B; }

#pragma endregion Rotator

// HitResult
#pragma region

AActor* UCsJavascriptLibrary::HitResult_GetActor(const FHitResult& HitResult) { return HitResult.GetActor(); }
UPrimitiveComponent* UCsJavascriptLibrary::HitResult_GetComponent(const FHitResult& HitResult) { return HitResult.GetComponent(); }

#pragma endregion HitResult

// PrimitiveComponent
#pragma region

void UCsJavascriptLibrary::SetCollisionResponseToChannels(UPrimitiveComponent* InComponent, const FCollisionResponseContainer& Response) { InComponent->SetCollisionResponseToChannels(Response); }
void UCsJavascriptLibrary::AddMoveIngoreActor(UPrimitiveComponent* InComponent, AActor* InActor) { InComponent->MoveIgnoreActors.Add(InActor); }

#pragma endregion PrimitiveComponent

// SceneComponent
#pragma region

FVector UCsJavascriptLibrary::GetComponentLocation(USceneComponent* InComponent) { return InComponent->GetComponentLocation(); }

void UCsJavascriptLibrary::ComponentAttachToComponent(USceneComponent* InComponent, USceneComponent* Parent, const TEnumAsByte<ECsAttachmentTransformRules::Type>& AttachmentRules, const FName& SocketName /*= NAME_None*/)
{
	InComponent->AttachToComponent(Parent, ECsAttachmentTransformRules::ToRule(AttachmentRules), SocketName);
}

void UCsJavascriptLibrary::ComponentDetachFromComponent(USceneComponent* InComponent, const TEnumAsByte<ECsDetachmentTransformRules::Type>& DetachmentRules)
{
	InComponent->DetachFromComponent(ECsDetachmentTransformRules::ToRule(DetachmentRules));
}

void UCsJavascriptLibrary::SetComponentRelativeTransform(USceneComponent* InComponent, const FTransform& NewTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport)
{
	InComponent->K2_SetRelativeTransform(NewTransform, bSweep, SweepHitResult, bTeleport);
}

#pragma endregion SceneComponent

// Actor
#pragma region

USceneComponent* UCsJavascriptLibrary::GetRootComponent(AActor* InActor) { return InActor->GetRootComponent(); }
FVector UCsJavascriptLibrary::GetActorLocation(AActor* InActor) { return InActor->GetActorLocation(); }
FRotator UCsJavascriptLibrary::GetActorRotation(AActor* InActor) { return InActor->GetActorRotation(); }

bool UCsJavascriptLibrary::SetActorLocation(AActor* InActor, const FVector& NewLocation, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport)
{
	return InActor->K2_SetActorLocation(NewLocation, bSweep, SweepHitResult, bTeleport);
}

bool UCsJavascriptLibrary::SetActorRotation(AActor* InActor, const FRotator& NewRotation, const bool& bTeleportPhysics)
{
	return InActor->K2_SetActorRotation(NewRotation, bTeleportPhysics);
}

void UCsJavascriptLibrary::SetActorRelativeRotation(AActor* InActor, const FRotator& NewRelativeRotation, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport)
{
	InActor->K2_SetActorRelativeRotation(NewRelativeRotation, bSweep, SweepHitResult, bTeleport);
}

void UCsJavascriptLibrary::SetActorRelativeTransform(AActor* InActor, const FTransform& NewTransform, const bool& bSweep, FHitResult& SweepHitResult, const bool& bTeleport)
{
	InActor->K2_SetActorRelativeTransform(NewTransform, bSweep, SweepHitResult, bTeleport);
}

bool UCsJavascriptLibrary::TeleportTo(AActor* InActor, const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest /*= false*/, bool bNoCheck /*= false*/)
{
	return InActor->TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);
}

void UCsJavascriptLibrary::ActorAttachToActor(AActor* InActor, AActor* ParentActor, const TEnumAsByte<ECsAttachmentTransformRules::Type>& AttachmentRules, const FName& SocketName /*= NAME_None*/)
{
	InActor->AttachToActor(ParentActor, ECsAttachmentTransformRules::ToRule(AttachmentRules), SocketName);
}

void UCsJavascriptLibrary::ActorAttachToComponent(AActor* InActor, USceneComponent* Parent, const TEnumAsByte<ECsAttachmentTransformRules::Type>& AttachmentRules, const FName& SocketName /*= NAME_None*/)
{
	InActor->AttachToComponent(Parent, ECsAttachmentTransformRules::ToRule(AttachmentRules), SocketName);
}

void UCsJavascriptLibrary::ActorDetachFromActor(AActor* InActor, const TEnumAsByte<ECsDetachmentTransformRules::Type>& DetachmentRules)
{
	InActor->DetachFromActor(ECsDetachmentTransformRules::ToRule(DetachmentRules));
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

FLinearColor UCsJavascriptLibrary::GetLinearColor(const ECsLinearColor& Color) { return NCsLinearColor::ToLinearColor(Color); }
FColor UCsJavascriptLibrary::GetColor(const ECsColor& Color) { return NCsColor::ToColor(Color); }

#pragma endregion Color

// World
#pragma region 

float UCsJavascriptLibrary::GetTimeSeconds(UWorld* InWorld) { return InWorld->GetTimeSeconds(); }
float UCsJavascriptLibrary::GetRealTimeSeconds(UWorld* InWorld) { return InWorld->GetRealTimeSeconds(); }

#pragma endregion World

// Coroutine
#pragma region

uint8 UCsJavascriptLibrary::CoroutineScheduleToUint8(const ECsCoroutineSchedule& Schedule) { return (uint8)Schedule; }
uint8 UCsJavascriptLibrary::GetCoroutineScheduleMax() { return ECS_COROUTINE_SCHEDULE_MAX; }

#pragma endregion Coroutine

// CVars
#pragma region

int32 UCsJavascriptLibrary::GetConsoleVariableValue_int32(const FString& Name)
{
	if (IConsoleVariable* Variable = IConsoleManager::Get().FindConsoleVariable(*Name))
		return Variable->GetInt();
	return 0;
}

#pragma endregion CVars