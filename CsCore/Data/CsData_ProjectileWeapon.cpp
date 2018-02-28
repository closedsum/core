// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileWeapon.h"
#include "CsCore.h"

// Data
#include "Data/CsData_Projectile.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

ACsData_ProjectileWeapon::ACsData_ProjectileWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

void* ACsData_ProjectileWeapon::GetFireModeStruct(const uint8 &Index) { return nullptr; }
UScriptStruct* ACsData_ProjectileWeapon::GetFireModeScriptStruct() { return nullptr; }

uint8 ACsData_ProjectileWeapon::GetLocationDamageModifierCount(const TCsWeaponFireMode &FireMode) { return 0; }
FName ACsData_ProjectileWeapon::GetLocationDamageModifierBone(const TCsWeaponFireMode &FireMode, const uint8 &Index) { return NAME_None; }
float ACsData_ProjectileWeapon::GetLocationDamageModifierMultiplier(const TCsWeaponFireMode &FireMode, const uint8 &Index) { return 0.0f; }

bool ACsData_ProjectileWeapon::UseFakeProjectile(const TCsWeaponFireMode &FireMode) { return false; }
ACsData_Projectile* ACsData_ProjectileWeapon::GetData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged) { return nullptr; }

FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return FVector::ZeroVector; }
FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return FVector::ZeroVector; }

int32* ACsData_ProjectileWeapon::GetMaxAmmoAddr() { return nullptr; }
float* ACsData_ProjectileWeapon::GetRechargeStartupDelayAddr() { return nullptr; }
float* ACsData_ProjectileWeapon::GetRechargeSecondsPerAmmoAddr() { return nullptr; }
float* ACsData_ProjectileWeapon::GetReloadTimeAddr() { return nullptr; }

#pragma endregion Stats

// Anims
#pragma region

UAnimMontage* ACsData_ProjectileWeapon::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimMontage* ACsData_ProjectileWeapon::GetAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) { return nullptr; }

UAnimSequence* ACsData_ProjectileWeapon::GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimSequence* ACsData_ProjectileWeapon::GetAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) { return nullptr; }

void ACsData_ProjectileWeapon::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);
}

void ACsData_ProjectileWeapon::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(FireMode, AnimType, Index, IsLow);
}

void ACsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, ViewType, FireMode, AnimType, Index);

	if (Seq)
	{
		InMesh->PlayAnimation(Seq, false);
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	UAnimSequence* Seq = nullptr;
	UAnimMontage* Mon = nullptr;

	GetAnim(Seq, Mon, FireMode, AnimType, Index);

	if (Seq)
	{
		InMesh->PlayAnimation(Seq, false);
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, PlayRate, IsLow);
}

void ACsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, PlayRate, IsLow);
}

void ACsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s and ViewType: %s."), *ShortCode.ToString(), *((*WeaponAnimToString)(AnimType)), *ECsViewType::ToString(ViewType));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void ACsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s."), *ShortCode.ToString(), *((*WeaponAnimToString)(AnimType)));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void ACsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, BlendOutTime, IsLow);
}

FCsAnimSequence* ACsData_ProjectileWeapon::GetFCsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }
FCsAnimMontage* ACsData_ProjectileWeapon::GetFCsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }
FCsFpsAnimSequence* ACsData_ProjectileWeapon::GetFCsFpsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }
FCsFpsAnimMontage* ACsData_ProjectileWeapon::GetFCsFpsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }

#pragma endregion Anims

// FX
#pragma region

FCsFxElement* ACsData_ProjectileWeapon::GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const int32 &Index /*=0*/){ return nullptr; }
FCsFxElement* ACsData_ProjectileWeapon::GetMuzzleFX(const TCsWeaponFireMode &FireMode, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* ACsData_ProjectileWeapon::GetSound(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType) { return nullptr; }
FCsSoundElement* ACsData_ProjectileWeapon::GetSound(const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType) { return nullptr; }

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, InParent);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}

void ACsData_ProjectileWeapon::StopSound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, InParent);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}

void ACsData_ProjectileWeapon::StopSound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

#pragma endregion Sounds