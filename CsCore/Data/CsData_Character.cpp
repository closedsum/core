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

const int32& ACsData_Character::GetHealth() { return ECsCached::Ref::SInt; }
const float& ACsData_Character::GetRespawnTime() { return ECsCached::Ref::Float; }

#pragma endregion Stats

// Inventory
#pragma region

FCsInventoryLoadout* ACsData_Character::GetLoadout() { return nullptr; }

#pragma endregion Inventory

// Collision
#pragma region

const float& ACsData_Character::GetCapsuleRadius() { return ECsCached::Ref::Float; }
const float& ACsData_Character::GetCapsuleHalfHeight() { return ECsCached::Ref::Float; }
FCollisionResponseContainer& ACsData_Character::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }

FCsHeadCollision* ACsData_Character::GetHeadCollision() { return nullptr; }

#pragma endregion Collision

// Movement
#pragma region

const float& ACsData_Character::GetMaxWalkSpeed() { return ECsCached::Ref::Float; }
const float& ACsData_Character::GetMaxAcceleration() { return ECsCached::Ref::Float; }
const float& ACsData_Character::GetJumpZVelocity() { return ECsCached::Ref::Float; }
const float& ACsData_Character::GetGravityScale() { return ECsCached::Ref::Float; }
const float& ACsData_Character::GetAirControl() { return ECsCached::Ref::Float; }

#pragma endregion Movement

// Weapon
#pragma region

const FName& ACsData_Character::GetBoneToAttachWeaponTo() { return ECsCached::Name::None; }

#pragma endregion Weapon

// Animation
#pragma region

bool ACsData_Character::IsAnimMemberAStruct(const TCsCharacterAnim &AnimType){ return false; }

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{
	OutAnimSequence = GetAnimSequence(ViewType, GripType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, GripType, AnimType, Index, IsLow);
}

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(GripType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(GripType, AnimType, Index, IsLow);
}

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, AnimType, Index, IsLow);
}

void ACsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(AnimType, Index, IsLow);
}

	// Sequence
#pragma region

UAnimSequence* ACsData_Character::GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsFpsAnimSequence* Anim = GetFCsFpsAnimSequence(GripType, AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr; 
}

UAnimSequence* ACsData_Character::GetAnimSequence(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsAnimSequence* Anim = GetFCsAnimSequence(GripType, AnimType, Index))
		return Anim->Get();
	return nullptr;
}

UAnimSequence* ACsData_Character::GetAnimSequence(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsFpsAnimSequence* Anim = GetFCsFpsAnimSequence(AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimSequence* ACsData_Character::GetAnimSequence(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsAnimSequence* Anim = GetFCsAnimSequence(AnimType, Index))
		return Anim->Get();
	return nullptr; 
}

FCsAnimSequence* ACsData_Character::GetFCsAnimSequence(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsAnimSequence* ACsData_Character::GetFCsAnimSequence(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsAnimSequence* ACsData_Character::GetFCsFpsAnimSequence(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsAnimSequence* ACsData_Character::GetFCsFpsAnimSequence(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion Sequence

	// Montage
#pragma region

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsFpsAnimMontage* Anim = GetFCsFpsAnimMontage(GripType, AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsAnimMontage* Anim = GetFCsAnimMontage(GripType, AnimType, Index))
		return Anim->Get();
	return nullptr;
}

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const bool &IsLow /*=false*/)
{
	return GetAnimMontage(ViewType, GripType, AnimType, 0, IsLow);
}

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsFpsAnimMontage* Anim = GetFCsFpsAnimMontage(AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimMontage* ACsData_Character::GetAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsAnimMontage* Anim = GetFCsAnimMontage(AnimType, Index))
		return Anim->Get();
	return nullptr; 
}

FCsAnimMontage* ACsData_Character::GetFCsAnimMontage(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsAnimMontage* ACsData_Character::GetFCsAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsAnimMontage* ACsData_Character::GetFCsFpsAnimMontage(const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsAnimMontage* ACsData_Character::GetFCsFpsAnimMontage(const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion Montage

	// BlendSpace1D
#pragma region

UBlendSpace1D* ACsData_Character::GetBlendSpace1D(const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{
	if (FCsFpsBlendSpace1D* Blend = GetFCsFpsBlendSpace1D(GripType, BlendType))
		return Blend->Get(ViewType, false);
	return nullptr;
}

UBlendSpace1D* ACsData_Character::GetBlendSpace1D(const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{ 
	if (FCsBlendSpace1D* Blend = GetFCsBlendSpace1D(GripType, BlendType))
		return Blend->Get();
	return nullptr;
}

UBlendSpace1D* ACsData_Character::GetBlendSpace1D(const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{ 
	if (FCsBlendSpace1D* Blend = GetFCsBlendSpace1D(BlendType))
		return Blend->Get();
	return nullptr;
}

FCsBlendSpace1D* ACsData_Character::GetFCsBlendSpace1D(const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsBlendSpace1D* ACsData_Character::GetFCsBlendSpace1D(const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsBlendSpace1D* ACsData_Character::GetFCsFpsBlendSpace1D(const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsBlendSpace1D* ACsData_Character::GetFCsFpsBlendSpace1D(const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion BlendSpace1D

	// BlendSpace
#pragma region

bool ACsData_Character::IsBlendMemberStruct(const TCsCharacterBlendSpace &BlendType){ return false; }

UBlendSpace* ACsData_Character::GetBlendSpace(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }
UBlendSpace* ACsData_Character::GetBlendSpace(const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }

FCsBlendSpace* ACsData_Character::GetFCsBlendSpace(const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsBlendSpace* ACsData_Character::GetFCsBlendSpace(const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsBlendSpace* ACsData_Character::GetFCsFpsBlendSpace(const TCsWeaponGrip &GripType, const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpsBlendSpace* ACsData_Character::GetFCsFpsBlendSpace(const TCsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion BlendSpace

USkeleton* ACsData_Character::GetSkeleton(const TCsViewType &ViewType, const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{
	if (UBlendSpace* Blend = GetBlendSpace(ViewType, BlendType, IsLow))
		return Blend->GetSkeleton();
	return nullptr;
}

USkeleton* ACsData_Character::GetSkeleton(const TCsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/)
{
	if (UBlendSpace* Blend = GetBlendSpace(BlendType, IsLow))
		return Blend->GetSkeleton();
	return nullptr;
}

USkeleton* ACsData_Character::GetSkeleton(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	if (UAnimBlueprintGeneratedClass* Blueprint = GetAnimBlueprint(ViewType, BlueprintType, IsLow))
		return Blueprint->TargetSkeleton;
	return nullptr;
}

USkeleton* ACsData_Character::GetSkeleton(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	if (UAnimBlueprintGeneratedClass* Blueprint = GetAnimBlueprint(BlueprintType, IsLow))
		return Blueprint->TargetSkeleton;
	return nullptr;
}

	// AnimBlueprint
#pragma region

bool ACsData_Character::IsAnimBlueprintMemberStruct(const TCsCharacterAnimBlueprint &BlueprintType){ return false; }

UAnimBlueprintGeneratedClass* ACsData_Character::GetAnimBlueprint(const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/) { return nullptr; }
UAnimBlueprintGeneratedClass* ACsData_Character::GetAnimBlueprint(const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/) { return nullptr; }

void ACsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(ViewType, BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void ACsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void ACsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(Mesh, ViewType, BlueprintType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, BlueprintType, IsLow);
}

void ACsData_Character::SetAnimBlueprint(UObject* InObject, const TCsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(Mesh, BlueprintType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, BlueprintType, IsLow);
}

#pragma endregion AnimBlueprint

	// Play
#pragma region

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, GripType, AnimType, Index, IsLow);

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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void ACsData_Character::PlayAnimation(UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, AnimType, Index, PlayRate, IsLooping, IsLow);
}

#pragma endregion Play

	// JumpTo
#pragma region

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, GripType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(GripType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *((*CharacterAnimToString)(AnimType)), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), GripType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, ViewType, GripType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(UObject* InObject, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, GripType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), GripType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, ViewType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), ViewType, AnimType, SectionName, Index, IsLow);
}

void ACsData_Character::Montage_JumpToSection(UObject* InObject, const TCsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), AnimType, SectionName, Index, IsLow);
}

#pragma endregion JumpTo

	// Stop
#pragma region 

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(GripType, AnimType, Index, IsLow);

	if (!Anim)
		return;

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		if (AnimInstance->Montage_IsPlaying(Anim))
			AnimInstance->Montage_Stop(BlendOutTime, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsWeaponGrip &GripType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, GripType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsViewType &ViewType, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, ViewType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_Character::StopAnimation(class UObject* InObject, const TCsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, AnimType, Index, BlendOutTime, IsLow);
}

#pragma endregion Stop

#pragma endregion Animation