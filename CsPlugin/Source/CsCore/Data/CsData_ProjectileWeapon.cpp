// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

void* ACsData_ProjectileWeapon::GetFireModeStruct(const FECsWeaponFireMode &FireMode) { return nullptr; }
UScriptStruct* ACsData_ProjectileWeapon::GetFireModeScriptStruct() { return nullptr; }

float ACsData_ProjectileWeapon::GetLocationDamageModifier(const FECsWeaponFireMode &FireMode, const FName &Bone) { return 1.0f; }

const bool& ACsData_ProjectileWeapon::UseFakeProjectile(const FECsWeaponFireMode &FireMode) { return NCsCached::Ref::False; }
ACsData_Projectile* ACsData_ProjectileWeapon::GetData_Projectile(const FECsWeaponFireMode &FireMode, const bool &IsCharged) { return nullptr; }

const FName& ACsData_ProjectileWeapon::GetMuzzleBone(const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const uint8 &Index /*=0*/) { return NCsCached::Name::None; }
const FName& ACsData_ProjectileWeapon::GetMuzzleBone(const FECsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return NCsCached::Name::None; }

FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const uint8 &Index /*=0*/)
{ 
	return GetMuzzleLocation(InMesh, (TCsViewType)ViewType, FireMode, Index);
}

FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const uint8 &Index /*=0*/) { return FVector::ZeroVector; }
FVector ACsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const uint8 &Index /*=0*/){ return FVector::ZeroVector; }

const FECsWeaponGrip& ACsData_ProjectileWeapon::GetGripType() { return EMCsWeaponGrip::Get().GetMAX(); }

const int32& ACsData_ProjectileWeapon::GetMaxAmmo() { return NCsCached::Ref::SInt; }
int32* ACsData_ProjectileWeapon::GetMaxAmmoAddr() { return nullptr; }
const float& ACsData_ProjectileWeapon::GetRechargeStartupDelay() { return NCsCached::Ref::Float; }
float* ACsData_ProjectileWeapon::GetRechargeStartupDelayAddr() { return nullptr; }
const float& ACsData_ProjectileWeapon::GetRechargeSecondsPerAmmo() { return NCsCached::Ref::Float; }
float* ACsData_ProjectileWeapon::GetRechargeSecondsPerAmmoAddr() { return nullptr; }
const float& ACsData_ProjectileWeapon::GetReloadTime() { return NCsCached::Ref::Float; }
float* ACsData_ProjectileWeapon::GetReloadTimeAddr() { return nullptr; }

#pragma endregion Stats

// Anims
#pragma region

UAnimMontage* ACsData_ProjectileWeapon::GetAnimMontage(const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimMontage* ACsData_ProjectileWeapon::GetAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) { return nullptr; }

UAnimSequence* ACsData_ProjectileWeapon::GetAnimSequence(const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimSequence* ACsData_ProjectileWeapon::GetAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/) { return nullptr; }

void ACsData_ProjectileWeapon::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);
}

void ACsData_ProjectileWeapon::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(FireMode, AnimType, Index, IsLow);
}

void ACsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
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

void ACsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
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

void ACsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, PlayRate, IsLow);
}

void ACsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, PlayRate, IsLow);
}

void ACsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s and ViewType: %s."), *ShortCode.ToString(), *(AnimType.Name), *ECsViewType::ToString(ViewType));
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

void ACsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s."), *ShortCode.ToString(), *(AnimType.Name));
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

void ACsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, BlendOutTime, IsLow);
}

void ACsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, BlendOutTime, IsLow);
}

FCsAnimSequence* ACsData_ProjectileWeapon::GetFCsAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType) { return nullptr; }
FCsAnimMontage* ACsData_ProjectileWeapon::GetFCsAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType) { return nullptr; }
FCsFpvAnimSequence* ACsData_ProjectileWeapon::GetFCsFpvAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType) { return nullptr; }
FCsFpvAnimMontage* ACsData_ProjectileWeapon::GetFCsFpvAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType) { return nullptr; }

#pragma endregion Anims

// FX
#pragma region

FCsFxElement* ACsData_ProjectileWeapon::GetMuzzleFX(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const int32 &Index /*=0*/){ return nullptr; }
FCsFxElement* ACsData_ProjectileWeapon::GetMuzzleFX(const FECsWeaponFireMode &FireMode, const int32 &Index /*=0*/) { return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* ACsData_ProjectileWeapon::GetSound(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType) { return nullptr; }
FCsSoundElement* ACsData_ProjectileWeapon::GetSound(const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType) { return nullptr; }

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);
	
	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement = GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
}

void ACsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);
	
	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("ACsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
}

void ACsData_ProjectileWeapon::StopSound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

void ACsData_ProjectileWeapon::StopSound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

#pragma endregion Sounds