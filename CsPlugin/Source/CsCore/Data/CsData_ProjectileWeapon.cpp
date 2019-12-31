// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileWeapon.h"
#include "CsCore.h"

// Data
#include "Data/CsData_ProjectileBase.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

UCsData_ProjectileWeapon::UCsData_ProjectileWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

void* UCsData_ProjectileWeapon::GetFireModeStruct(const FECsWeaponFireMode& FireMode) { return nullptr; }
UScriptStruct* UCsData_ProjectileWeapon::GetFireModeScriptStruct() { return nullptr; }

float UCsData_ProjectileWeapon::GetLocationDamageModifier(const FECsWeaponFireMode& FireMode, const FName& Bone) { return 1.0f; }

const bool& UCsData_ProjectileWeapon::UseFakeProjectile(const FECsWeaponFireMode& FireMode) { return NCsCached::Ref::False; }
UCsData_ProjectileBase* UCsData_ProjectileWeapon::GetData_Projectile(const FECsWeaponFireMode& FireMode, const bool& IsCharged) { return nullptr; }

const FName& UCsData_ProjectileWeapon::GetMuzzleBone(const TEnumAsByte<ECsViewType::Type>& ViewType, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/) { return NCsCached::Name::None; }
const FName& UCsData_ProjectileWeapon::GetMuzzleBone(const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/){ return NCsCached::Name::None; }

FVector UCsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TEnumAsByte<ECsViewType::Type>& ViewType, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/)
{ 
	return GetMuzzleLocation(InMesh, (TCsViewType)ViewType, FireMode, Index);
}

FVector UCsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/) { return FVector::ZeroVector; }
FVector UCsData_ProjectileWeapon::GetMuzzleLocation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const uint8& Index /*=0*/){ return FVector::ZeroVector; }

const FECsWeaponGrip& UCsData_ProjectileWeapon::GetGripType() { return EMCsWeaponGrip::Get().GetMAX(); }

const int32& UCsData_ProjectileWeapon::GetMaxAmmo() { return NCsCached::Ref::SInt; }
int32* UCsData_ProjectileWeapon::GetMaxAmmoAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon::GetRechargeStartupDelay() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon::GetRechargeStartupDelayAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon::GetRechargeSecondsPerAmmo() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon::GetRechargeSecondsPerAmmoAddr() { return nullptr; }
const float& UCsData_ProjectileWeapon::GetReloadTime() { return NCsCached::Ref::Float; }
float* UCsData_ProjectileWeapon::GetReloadTimeAddr() { return nullptr; }

#pragma endregion Stats

// Anims
#pragma region

UAnimMontage* UCsData_ProjectileWeapon::GetAnimMontage(const TEnumAsByte<ECsViewType::Type>& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/){ return nullptr; }
UAnimMontage* UCsData_ProjectileWeapon::GetAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/) { return nullptr; }

UAnimSequence* UCsData_ProjectileWeapon::GetAnimSequence(const TEnumAsByte<ECsViewType::Type>& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool &IsLow /*=false*/){ return nullptr; }
UAnimSequence* UCsData_ProjectileWeapon::GetAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/) { return nullptr; }

void UCsData_ProjectileWeapon::GetAnim(UAnimSequence*& OutAnimSequence, UAnimMontage*& OutAnimMontage, const TEnumAsByte<ECsViewType::Type>& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);
}

void UCsData_ProjectileWeapon::GetAnim(UAnimSequence*& OutAnimSequence, UAnimMontage*& OutAnimMontage, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const bool& IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(FireMode, AnimType, Index, IsLow);
}

void UCsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_ProjectileWeapon::PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlayAnimation (%s): Warning. No AnimInstance for %s."), *Mon->GetName(), *InMesh->GetName());
	}
}

void UCsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, PlayRate, IsLow);
}

void UCsData_ProjectileWeapon::PlayAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& PlayRate /*=1.0f*/, const bool& IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, PlayRate, IsLow);
}

void UCsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s and ViewType: %s."), *ShortCode.ToString(), *(AnimType.Name), *ECsViewType::ToString(ViewType));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void UCsData_ProjectileWeapon::StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::StopAnimation (%s): No Animation found for AnimType: %s."), *ShortCode.ToString(), *(AnimType.Name));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::StopAnimation (%s): No AnimInstance."), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void UCsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, BlendOutTime, IsLow);
}

void UCsData_ProjectileWeapon::StopAnimation(ASkeletalMeshActor* InActor, const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType, const int32& Index /*=0*/, const float& BlendOutTime /*=0.0f*/, const bool& IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), FireMode, AnimType, Index, BlendOutTime, IsLow);
}

FCsAnimSequence* UCsData_ProjectileWeapon::GetFCsAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsAnimMontage* UCsData_ProjectileWeapon::GetFCsAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsFpvAnimSequence* UCsData_ProjectileWeapon::GetFCsFpvAnimSequence(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }
FCsFpvAnimMontage* UCsData_ProjectileWeapon::GetFCsFpvAnimMontage(const FECsWeaponFireMode& FireMode, const FECsWeaponAnim& AnimType) { return nullptr; }

#pragma endregion Anims

// FX
#pragma region

FCsFxElement* UCsData_ProjectileWeapon::GetMuzzleFX(const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const int32& Index /*=0*/){ return nullptr; }
FCsFxElement* UCsData_ProjectileWeapon::GetMuzzleFX(const FECsWeaponFireMode& FireMode, const int32& Index /*=0*/) { return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* UCsData_ProjectileWeapon::GetSound(const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType) { return nullptr; }
FCsSoundElement* UCsData_ProjectileWeapon::GetSound(const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType) { return nullptr; }

void UCsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);
	
	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
}

void UCsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Parent = InParent;

	Manager_Sound->Play(Payload);
}

void UCsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, const FVector& Location)
{
	FCsSoundElement* SoundElement = GetSound(ViewType, FireMode, SoundType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
}

void UCsData_ProjectileWeapon::PlaySound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, const FVector& Location)
{
	FCsSoundElement* SoundElement = GetSound(FireMode, SoundType);
	
	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_ProjectileWeapon::PlaySound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
}

void UCsData_ProjectileWeapon::StopSound(UWorld* InWorld, const TCsViewType& ViewType, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(ViewType, FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

void UCsData_ProjectileWeapon::StopSound(UWorld* InWorld, const FECsWeaponFireMode& FireMode, const FECsWeaponSound& SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement	= GetSound(FireMode, SoundType);
	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

#pragma endregion Sounds