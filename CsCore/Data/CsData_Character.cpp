// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Character.h"
#include "CsCore.h"

#include "Animation/SkeletalMeshActor.h"

ACsData_Character::ACsData_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

int32 ACsData_Character::GetHealth() { return 0; }

#pragma endregion Stats

// Collision
#pragma region

float ACsData_Character::GetCapsuleRadius() { return 0.0f; }
float ACsData_Character::GetCapsuleHalfHeight() { return 0.0f; }

#pragma endregion Collision

// Weapon
#pragma region

FName ACsData_Character::GetBoneToAttachWeaponTo() { return NAME_None; }

#pragma endregion Weapon

// Animation
#pragma region

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow) 
{
	OutAnimSequence = GetAnimSequence(ViewType, GripType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, GripType, AnimType, Index, IsLow);
}

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow)
{
	OutAnimSequence = GetAnimSequence(ViewType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, AnimType, Index, IsLow);
}

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow)
{
	OutAnimSequence = GetAnimSequence(AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(AnimType, Index, IsLow);
}

UAnimSequence* ACsData_Character::GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const bool &IsLow) { return nullptr; }
UAnimSequence* ACsData_Character::GetAnimSequence(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const bool &IsLow) { return nullptr; }
UAnimSequence* ACsData_Character::GetAnimSequence(const TCsCharacterAnim &AnimType, const bool &IsLow) { return nullptr; }

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow) { return nullptr; }
UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const bool &IsLow) { return nullptr; }
UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow) { return nullptr; }
UAnimMontage* ACsData_Character::GetAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index, const bool &IsLow) { return nullptr; }

UBlendSpace* ACsData_Character::GetBlendSpace(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow) { return nullptr; }
UBlendSpace* ACsData_Character::GetBlendSpace(const TCsCharacterBlendSpace &BlendType, const bool &IsLow) { return nullptr; }

USkeleton* ACsData_Character::GetSkeleton(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow) { return nullptr; }
USkeleton* ACsData_Character::GetSkeleton(const TCsCharacterBlendSpace &BlendType, const bool &IsLow) { return nullptr; }
USkeleton* ACsData_Character::GetSkeleton(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow) { return nullptr; }
USkeleton* ACsData_Character::GetSkeleton(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow) { return nullptr; }

UAnimBlueprintGeneratedClass* ACsData_Character::GetAnimBlueprint(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow) { return nullptr; }
UAnimBlueprintGeneratedClass* ACsData_Character::GetAnimBlueprint(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow) { return nullptr; }

void ACsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(ViewType, BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void ACsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void ACsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(Mesh, ViewType, BlueprintType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(UObject* InObject, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(Mesh, BlueprintType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, BlueprintType, IsLow);
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, ViewType, GripType, AnimType, Index, IsLow);

	if (Seq)
	{
		InMesh->PlayAnimation(Seq, IsLooping);
		return;
	}

	if (!Mon)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Mon, PlayRate);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, ViewType, AnimType, Index, IsLow);

	if (Seq)
	{
		InMesh->PlayAnimation(Seq, IsLooping);
		return;
	}

	if (!Mon)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Mon, PlayRate);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, AnimType, Index, IsLow);

	if (Seq)
	{
		InMesh->PlayAnimation(Seq, IsLooping);
		return;
	}

	if (!Mon)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_Play(Mon, PlayRate);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(Mesh, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(Mesh, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index, const float &PlayRate, const bool &IsLooping, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(Mesh, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, GripType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s"), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s"), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s"), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index, const bool &IsLow)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, GripType, AnimType, Index, IsLow);

	if (!Anim)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		if (AnimInstance->Montage_IsPlaying(Anim))
			AnimInstance->Montage_Stop(BlendOutTime, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, AnimType, Index, IsLow);

	if (!Anim)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		if (AnimInstance->Montage_IsPlaying(Anim))
			AnimInstance->Montage_Stop(BlendOutTime, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	UAnimMontage* Anim = GetAnimMontage(AnimType, Index, IsLow);

	if (!Anim)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		if (AnimInstance->Montage_IsPlaying(Anim))
			AnimInstance->Montage_Stop(BlendOutTime, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s"), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(Mesh, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(Mesh, ViewType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index, const float &BlendOutTime, const bool &IsLow)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(Mesh, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, AnimType, Index, BlendOutTime, IsLow);
}

FCsFpsAnimSequence* ACsData_Character::GetFCsFpsAnimSequence(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType) { return nullptr; }
FCsFpsAnimSequence* ACsData_Character::GetFCsFpsAnimSequence(const TCsCharacterAnim &AnimType) { return nullptr; }
FCsFpsAnimMontage* ACsData_Character::GetFCsFpsAnimMontage(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType) { return nullptr; }
FCsFpsAnimMontage* ACsData_Character::GetFCsFpsAnimMontage(const TCsCharacterAnim &AnimType) { return nullptr; }

#pragma endregion Animation