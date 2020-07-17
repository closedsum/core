// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileWeapon_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"

// Data
#include "Data/CsData_ProjectileBase.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

#include "Animation/SkeletalMeshActor.h"

UCsData_ProjectileWeapon_DEPRECATED::UCsData_ProjectileWeapon_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

void* UCsData_ProjectileWeapon_DEPRECATED::GetFireModeStruct(const FECsWeaponFireMode& FireMode) { return nullptr; }
UScriptStruct* UCsData_ProjectileWeapon_DEPRECATED::GetFireModeScriptStruct() { return nullptr; }

float UCsData_ProjectileWeapon_DEPRECATED::GetLocationDamageModifier(const FECsWeaponFireMode& FireMode, const FName& Bone) { return 1.0f; }

const bool& UCsData_ProjectileWeapon_DEPRECATED::UseFakeProjectile(const FECsWeaponFireMode& FireMode) { return NCsCached::Ref::False; }
UCsData_ProjectileBase* UCsData_ProjectileWeapon_DEPRECATED::GetData_Projectile(const FECsWeaponFireMode& FireMode, const bool& IsCharged) { return nullptr; }

const FName& UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleBone(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/) { return NCsCached::Name::None; }
const FName& UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleBone(const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/){ return NCsCached::Name::None; }

FVector UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/) { return FVector::ZeroVector; }
FVector UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/){ return FVector::ZeroVector; }

const FECsWeaponGrip& UCsData_ProjectileWeapon_DEPRECATED::GetGripType() { return EMCsWeaponGrip::Get().GetMAX(); }

const int32& UCsData_ProjectileWeapon_DEPRECATED::GetMaxAmmo() { return NCsCached::Ref::SInt; }
int32* UCsData_ProjectileWeapon_DEPRECATED::GetMaxAmmoAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon_DEPRECATED::GetRechargeStartupDelay() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon_DEPRECATED::GetRechargeStartupDelayAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon_DEPRECATED::GetRechargeSecondsPerAmmo() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon_DEPRECATED::GetRechargeSecondsPerAmmoAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon_DEPRECATED::GetReloadTime() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon_DEPRECATED::GetReloadTimeAddr() { return nullptr; }

#pragma endregion Stats

// Anims
#pragma region

UAnimMontage* UCsData_ProjectileWeapon_DEPRECATED::GetAnimMontage(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/){ return nullptr; }
UAnimMontage* UCsData_ProjectileWeapon_DEPRECATED::GetAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/) { return nullptr; }

UAnimSequence* UCsData_ProjectileWeapon_DEPRECATED::GetAnimSequence(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimSequence* UCsData_ProjectileWeapon_DEPRECATED::GetAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/) { return nullptr; }

void UCsData_ProjectileWeapon_DEPRECATED::GetAnim(UAnimSequence*& OutAnimSequence, UAnimMontage*& OutAnimMontage, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);
}

void UCsData_ProjectileWeapon_DEPRECATED::GetAnim(UAnimSequence*& OutAnimSequence, UAnimMontage*& OutAnimMontage, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(FireMode, AnimType, Index, IsLow);
}

void UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
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
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, PlayRate, IsLow);
}

void UCsData_ProjectileWeapon_DEPRECATED::PlayAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, PlayRate, IsLow);
}

void UCsData_ProjectileWeapon_DEPRECATED::StopAnimation(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::StopAnimation (%s): No Animation found for AnimType: %s and ViewType: %s."), *ShortCode.ToString(), *(AnimType.Name), EMCsViewType::Get().ToChar(ViewType));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void UCsData_ProjectileWeapon_DEPRECATED::StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::StopAnimation (%s): No Animation found for AnimType: %s."), *ShortCode.ToString(), *(AnimType.Name));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void UCsData_ProjectileWeapon_DEPRECATED::StopAnimation(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_ProjectileWeapon_DEPRECATED::StopAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, BlendOutTime, IsLow);
}

FCsAnimSequence* UCsData_ProjectileWeapon_DEPRECATED::GetFCsAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsAnimMontage* UCsData_ProjectileWeapon_DEPRECATED::GetFCsAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsFpvAnimSequence* UCsData_ProjectileWeapon_DEPRECATED::GetFCsFpvAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsFpvAnimMontage* UCsData_ProjectileWeapon_DEPRECATED::GetFCsFpvAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }

#pragma endregion Anims

// FX
#pragma region

FCsFxElement_DEPRECATED* UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleFX(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const int32& Index /*=0*/){ return nullptr; }
FCsFxElement_DEPRECATED* UCsData_ProjectileWeapon_DEPRECATED::GetMuzzleFX(const FECsWeaponFireMode& FireMode, const int32& Index /*=0*/) { return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* UCsData_ProjectileWeapon_DEPRECATED::GetSound(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType) { return nullptr; }
FCsSoundElement* UCsData_ProjectileWeapon_DEPRECATED::GetSound(const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType) { return nullptr; }

void UCsData_ProjectileWeapon_DEPRECATED::PlaySound(UWorld* InWorld, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	/*
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);
	
	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
	*/
}

void UCsData_ProjectileWeapon_DEPRECATED::PlaySound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	/*
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
	*/
}

void UCsData_ProjectileWeapon_DEPRECATED::PlaySound(UWorld* InWorld, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, const FVector& Location)
{
	/*
	FCsSoundElement* SoundElement = GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
	*/
}

void UCsData_ProjectileWeapon_DEPRECATED::PlaySound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, const FVector& Location)
{
	/*
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);
	
	if (!SoundElement->Get())
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsData_ProjectileWeapon_DEPRECATED::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
	*/
}

void UCsData_ProjectileWeapon_DEPRECATED::StopSound(UWorld* InWorld, const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	/*
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
	*/
}

void UCsData_ProjectileWeapon_DEPRECATED::StopSound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	/*
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
	*/
}

#pragma endregion Sounds