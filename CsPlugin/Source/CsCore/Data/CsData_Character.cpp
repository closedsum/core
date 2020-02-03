// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Character.h"
#include "CsCore.h"

#include "Animation/SkeletalMeshActor.h"

UCsData_Character::UCsData_Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const int32& UCsData_Character::GetHealth() { return NCsCached::Ref::SInt; }
const float& UCsData_Character::GetRespawnTime() { return NCsCached::Ref::Float; }

#pragma endregion Stats

// Inventory
#pragma region

FCsInventoryLoadout* UCsData_Character::GetLoadout() { return nullptr; }

#pragma endregion Inventory

// Collision
#pragma region

const float& UCsData_Character::GetCapsuleRadius() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetCapsuleHalfHeight() { return NCsCached::Ref::Float; }
FCollisionResponseContainer& UCsData_Character::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }

FCsHeadCollision* UCsData_Character::GetHeadCollision() { return nullptr; }

#pragma endregion Collision

// Movement
#pragma region

const float& UCsData_Character::GetMaxWalkSpeed() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetMaxAcceleration() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetJumpHeight() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetJumpZVelocity() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetGroundToJumpPeakTime() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetGravityScale() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetAirControl() { return NCsCached::Ref::Float; }

#pragma endregion Movement

// Weapon
#pragma region

const FName& UCsData_Character::GetBoneToAttachWeaponTo() { return NCsCached::Name::None; }

#pragma endregion Weapon

// Animation
#pragma region

bool UCsData_Character::IsAnimMemberAStruct(const FECsCharacterAnim &AnimType){ return false; }

void UCsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{
	OutAnimSequence = GetAnimSequence(ViewType, GripType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, GripType, AnimType, Index, IsLow);
}

void UCsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(GripType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(GripType, AnimType, Index, IsLow);
}

void UCsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, AnimType, Index, IsLow);
}

void UCsData_Character::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(AnimType, IsLow);
	OutAnimMontage = GetAnimMontage(AnimType, Index, IsLow);
}

	// Sequence
#pragma region

UAnimSequence* UCsData_Character::GetAnimSequence(const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsFpvAnimSequence* Anim = GetFCsFpvAnimSequence(GripType, AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr; 
}

UAnimSequence* UCsData_Character::GetAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsAnimSequence* Anim = GetFCsAnimSequence(GripType, AnimType, Index))
		return Anim->Get();
	return nullptr;
}

UAnimSequence* UCsData_Character::GetAnimSequence(const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsFpvAnimSequence* Anim = GetFCsFpvAnimSequence(AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimSequence* UCsData_Character::GetAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsAnimSequence* Anim = GetFCsAnimSequence(AnimType, Index))
		return Anim->Get();
	return nullptr; 
}

FCsAnimSequence* UCsData_Character::GetFCsAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsAnimSequence* UCsData_Character::GetFCsAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAnimSequence* UCsData_Character::GetFCsFpvAnimSequence(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAnimSequence* UCsData_Character::GetFCsFpvAnimSequence(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion Sequence

	// Montage
#pragma region

UAnimMontage* UCsData_Character::GetAnimMontage(const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsFpvAnimMontage* Anim = GetFCsFpvAnimMontage(GripType, AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimMontage* UCsData_Character::GetAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	if (FCsAnimMontage* Anim = GetFCsAnimMontage(GripType, AnimType, Index))
		return Anim->Get();
	return nullptr;
}

UAnimMontage* UCsData_Character::GetAnimMontage(const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const bool &IsLow /*=false*/)
{
	return GetAnimMontage(ViewType, GripType, AnimType, 0, IsLow);
}

UAnimMontage* UCsData_Character::GetAnimMontage(const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsFpvAnimMontage* Anim = GetFCsFpvAnimMontage(AnimType, Index))
		return Anim->Get(ViewType, IsLow);
	return nullptr;
}

UAnimMontage* UCsData_Character::GetAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) 
{ 
	if (FCsAnimMontage* Anim = GetFCsAnimMontage(AnimType, Index))
		return Anim->Get();
	return nullptr; 
}

FCsAnimMontage* UCsData_Character::GetFCsAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsAnimMontage* UCsData_Character::GetFCsAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAnimMontage* UCsData_Character::GetFCsFpvAnimMontage(const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAnimMontage* UCsData_Character::GetFCsFpvAnimMontage(const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion Montage

	// BlendSpace1D
#pragma region

UBlendSpace1D* UCsData_Character::GetBlendSpace1D(const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{
	if (FCsFpvBlendSpace1D* Blend = GetFCsFpvBlendSpace1D(GripType, BlendType))
		return Blend->Get(ViewType, false);
	return nullptr;
}

UBlendSpace1D* UCsData_Character::GetBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{ 
	if (FCsBlendSpace1D* Blend = GetFCsBlendSpace1D(GripType, BlendType))
		return Blend->Get();
	return nullptr;
}

UBlendSpace1D* UCsData_Character::GetBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{ 
	if (FCsBlendSpace1D* Blend = GetFCsBlendSpace1D(BlendType))
		return Blend->Get();
	return nullptr;
}

FCsBlendSpace1D* UCsData_Character::GetFCsBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsBlendSpace1D* UCsData_Character::GetFCsBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvBlendSpace1D* UCsData_Character::GetFCsFpvBlendSpace1D(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvBlendSpace1D* UCsData_Character::GetFCsFpvBlendSpace1D(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion BlendSpace1D

	// BlendSpace
#pragma region

bool UCsData_Character::IsBlendMemberStruct(const FECsCharacterBlendSpace &BlendType){ return false; }

UBlendSpace* UCsData_Character::GetBlendSpace(const ECsViewType& ViewType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }
UBlendSpace* UCsData_Character::GetBlendSpace(const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }

FCsBlendSpace* UCsData_Character::GetFCsBlendSpace(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsBlendSpace* UCsData_Character::GetFCsBlendSpace(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvBlendSpace* UCsData_Character::GetFCsFpvBlendSpace(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvBlendSpace* UCsData_Character::GetFCsFpvBlendSpace(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion BlendSpace

	// AimOffset
#pragma region

UAimOffsetBlendSpace* UCsData_Character::GetAimOffset(const ECsViewType& ViewType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }
UAimOffsetBlendSpace* UCsData_Character::GetAimOffset(const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) { return nullptr; }

FCsAimOffset* UCsData_Character::GetFCsAimOffset(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsAimOffset* UCsData_Character::GetFCsAimOffset(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAimOffset* UCsData_Character::GetFCsFpvAimOffset(const FECsWeaponGrip &GripType, const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }
FCsFpvAimOffset* UCsData_Character::GetFCsFpvAimOffset(const FECsCharacterBlendSpace &BlendType, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion BlendSpace

USkeleton* UCsData_Character::GetSkeleton(const ECsViewType& ViewType, const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/) 
{
	if (UBlendSpace* Blend = GetBlendSpace(ViewType, BlendType, IsLow))
		return Blend->GetSkeleton();
	return nullptr;
}

USkeleton* UCsData_Character::GetSkeleton(const FECsCharacterBlendSpace &BlendType, const bool &IsLow /*=false*/)
{
	if (UBlendSpace* Blend = GetBlendSpace(BlendType, IsLow))
		return Blend->GetSkeleton();
	return nullptr;
}

USkeleton* UCsData_Character::GetSkeleton(const ECsViewType& ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	if (UAnimBlueprintGeneratedClass* Blueprint = GetAnimBlueprint(ViewType, BlueprintType, IsLow))
		return Blueprint->TargetSkeleton;
	return nullptr;
}

USkeleton* UCsData_Character::GetSkeleton(const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	if (UAnimBlueprintGeneratedClass* Blueprint = GetAnimBlueprint(BlueprintType, IsLow))
		return Blueprint->TargetSkeleton;
	return nullptr;
}

	// AnimBlueprint
#pragma region

bool UCsData_Character::IsAnimBlueprintMemberStruct(const FECsCharacterAnimBlueprint &BlueprintType){ return false; }

UAnimBlueprintGeneratedClass* UCsData_Character::GetAnimBlueprint(const ECsViewType& ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/) { return nullptr; }
UAnimBlueprintGeneratedClass* UCsData_Character::GetAnimBlueprint(const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/) { return nullptr; }

void UCsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(ViewType, BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void UCsData_Character::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	UAnimBlueprintGeneratedClass* AnimBlueprint = GetAnimBlueprint(BlueprintType, IsLow);

	InMesh->SetAnimInstanceClass(AnimBlueprint);
}

void UCsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, BlueprintType, IsLow);
}

void UCsData_Character::SetAnimBlueprint(class ASkeletalMeshActor* InActor, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), BlueprintType, IsLow);
}

void UCsData_Character::SetAnimBlueprint(UObject* InObject, const ECsViewType& ViewType, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(Mesh, ViewType, BlueprintType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, BlueprintType, IsLow);
}

void UCsData_Character::SetAnimBlueprint(UObject* InObject, const FECsCharacterAnimBlueprint &BlueprintType, const bool &IsLow /*=false*/)
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

void UCsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::PlayAnimation(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::PlayAnimation (%s): Warning. Attempting to play: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(UObject* InObject, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, GripType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(UObject* InObject, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		PlayAnimation(InMesh, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		PlayAnimation(Actor, ViewType, AnimType, Index, PlayRate, IsLooping, IsLow);
}

void UCsData_Character::PlayAnimation(UObject* InObject, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1*/, const bool &IsLooping /*=false*/, const bool &IsLow /*=false*/)
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

void UCsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, GripType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *(AnimType.Name), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(GripType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *(AnimType.Name), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *(AnimType.Name), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::Montage_JumpToSection(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(AnimType, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Anim %s NOT found for %s."), *ShortCode.ToString(), *(AnimType.Name), *InMesh->GetName());
		return;
	}

	if (UAnimInstance* AnimInstance = InMesh->GetAnimInstance())
	{
		AnimInstance->Montage_JumpToSection(SectionName, Anim);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::Montage_JumpToSection (%s): Warning. Attemping to Montage_JumpToSection for %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), GripType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	Montage_JumpToSection(InActor->GetSkeletalMeshComponent(), AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(UObject* InObject, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, ViewType, GripType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, GripType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), GripType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(UObject* InObject, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		Montage_JumpToSection(InMesh, ViewType, AnimType, SectionName, Index, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		Montage_JumpToSection(Actor->GetSkeletalMeshComponent(), ViewType, AnimType, SectionName, Index, IsLow);
}

void UCsData_Character::Montage_JumpToSection(UObject* InObject, const FECsCharacterAnim &AnimType, const FName &SectionName, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
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

void UCsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::StopAnimation(USkeletalMeshComponent* InMesh, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_Character::StopAnimation (%s): Warning. Attemping to stop: %s. No AnimInstance for %s."), *ShortCode.ToString(), *Anim->GetName(), *InMesh->GetName());
	}
}

void UCsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), GripType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class ASkeletalMeshActor* InActor, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class UObject* InObject, const ECsViewType& ViewType, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class UObject* InObject, const FECsWeaponGrip &GripType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, GripType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, GripType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class UObject* InObject, const ECsViewType& ViewType, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		StopAnimation(InMesh, ViewType, AnimType, Index, BlendOutTime, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		StopAnimation(Actor, ViewType, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_Character::StopAnimation(class UObject* InObject, const FECsCharacterAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0*/, const bool &IsLow /*=false*/)
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

// Sense
#pragma region

FCsSenseData_DEPRECATED* UCsData_Character::GetSenseData() { return nullptr; }
const bool& UCsData_Character::GetUseSenseRadius() { return NCsCached::Ref::False; }
const float& UCsData_Character::GetSenseRadius() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetSenseRadiusSq() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetSenseViewMinAngle() { return NCsCached::Ref::Float; }
const float& UCsData_Character::GetSenseViewMinDot() { return NCsCached::Ref::Float; }

#pragma endregion Sense

// AI
#pragma region

const float& UCsData_Character::GetAimTime() { return NCsCached::Ref::Float; }

#pragma endregion AI