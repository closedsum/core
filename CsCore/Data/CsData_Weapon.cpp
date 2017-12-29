// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "CsCore.h"
// Data
#include "Data/CsData_Projectile.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_Weapon::ACsData_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

void* ACsData_Weapon::GetFireModeStruct(const uint8 &Index) { return nullptr; }
UScriptStruct* ACsData_Weapon::GetFireModeScriptStruct() { return nullptr; }

bool ACsData_Weapon::UseFakeProjectile(const TCsWeaponFireMode &FireMode){ return false; }
ACsData_Projectile* ACsData_Weapon::GetData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged){ return nullptr; }

#pragma endregion Stats

// Mesh
#pragma region

USkeletalMesh* ACsData_Weapon::GetMesh(const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	return nullptr;
}

void ACsData_Weapon::SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	InMesh->SetSkeletalMesh(GetMesh(ViewType, IsLow));
}

void ACsData_Weapon::SetMesh(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_Weapon::SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	if (USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(mesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType, IsLow);
}

void ACsData_Weapon::GetDefaultMaterials(TArray<UMaterialInstanceConstant*> &OutMaterials, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	USkeletalMesh* Mesh = GetMesh(ViewType, IsLow);

	OutMaterials.Reset();

	const int32 Count = Mesh->Materials.Num();

	for (int32 I = 0; I < Count; I++)
	{
		OutMaterials.Add(Cast<UMaterialInstanceConstant>(Mesh->Materials[I].MaterialInterface->GetMaterial()));
	}
}

#pragma endregion Mesh

// Anims
#pragma region

void ACsData_Weapon::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/){}

void ACsData_Weapon::SetAnimBlueprint(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_Weapon::SetAnimBlueprint(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	if (USkeletalMeshComponent* mesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(mesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, IsLow);
}

UAnimMontage* ACsData_Weapon::GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	return nullptr;
}

UAnimSequence* ACsData_Weapon::GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	return nullptr;
}

void ACsData_Weapon::GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const bool &IsLow /*=false*/)
{
	OutAnimSequence = GetAnimSequence(ViewType, FireMode, AnimType, Index, IsLow);
	OutAnimMontage = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);
}

void ACsData_Weapon::PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
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
		UE_LOG(LogCs, Warning, TEXT("ACsData_Weapon::PlayAnimation (%s): Warning. No AnimInstance for %s"), *Mon->GetName(), *InMesh->GetName());
	}
}

void ACsData_Weapon::PlayAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &PlayRate /*=1.0f*/, const bool &IsLow /*=false*/)
{
	PlayAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, PlayRate, IsLow);
}

void ACsData_Weapon::StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	UAnimMontage* Anim = GetAnimMontage(ViewType, FireMode, AnimType, Index, IsLow);

	if (!Anim)
	{
		UE_LOG(LogCs, Warning, TEXT("AMCsData_Weapon::StopAnimation (%s): No Animation found for AnimType: %s and ViewType: %s"), *ShortCode.ToString(), *((*WeaponAnimToString)(AnimType)), *ECsViewType::ToString(ViewType));
		return;
	}

	UAnimInstance* AnimInstance = InMesh->GetAnimInstance();

	if (!AnimInstance)
	{
		UE_LOG(LogCs, Warning, TEXT("AMboData_Weapon::StopAnimation (%s): No AnimInstance"), *ShortCode.ToString());
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Anim))
		AnimInstance->Montage_Stop(BlendOutTime, Anim);
}

void ACsData_Weapon::StopAnimation(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index /*=0*/, const float &BlendOutTime /*=0.0f*/, const bool &IsLow /*=false*/)
{
	StopAnimation(InActor->GetSkeletalMeshComponent(), ViewType, FireMode, AnimType, Index, BlendOutTime, IsLow);
}

FCsAnimSequence* ACsData_Weapon::GetFCsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }
FCsAnimMontage* ACsData_Weapon::GetFCsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType) { return nullptr; }
FCsFpsAnimSequence* ACsData_Weapon::GetFCsFpsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType){ return nullptr; }
FCsFpsAnimMontage* ACsData_Weapon::GetFCsFpsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType){ return nullptr; }

#pragma endregion Anims

// FX
#pragma region

FCsFxElement* ACsData_Weapon::GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const int32 &Index /*=0*/){ return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* ACsData_Weapon::GetSound(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType){ return nullptr;  }

void ACsData_Weapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, InParent);
}

void ACsData_Weapon::PlaySoundEX(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}

void ACsData_Weapon::StopSound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireMode, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

#pragma endregion Sounds