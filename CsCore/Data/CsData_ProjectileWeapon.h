// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Weapon.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_ProjectileWeapon.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_ProjectileWeapon : public ACsData_Weapon
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region

	virtual void* GetFireModeStruct(const uint8 &Index);
	virtual UScriptStruct* GetFireModeScriptStruct();

	virtual uint8 GetLocationDamageModifierCount(const TCsWeaponFireMode &FireMode);
	virtual FName GetLocationDamageModifierBone(const TCsWeaponFireMode &FireMode, const uint8 &Index);
	virtual float GetLocationDamageModifierMultiplier(const TCsWeaponFireMode &FireMode, const uint8 &Index);

	virtual bool UseFakeProjectile(const TCsWeaponFireMode &FireMode);
	virtual class ACsData_Projectile* GetData_Projectile(const TCsWeaponFireMode &FireMode, const bool &IsCharged = false);

	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const uint8 &Index = 0);
	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const uint8 &Index = 0);

#pragma endregion Stats

	// Anims
#pragma region

	virtual UAnimMontage* GetAnimMontage(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual UAnimSequence* GetAnimSequence(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);

	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);

	virtual FCsAnimSequence* GetFCsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType);
	virtual FCsAnimMontage* GetFCsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType);
	virtual FCsFpsAnimSequence* GetFCsFpsAnimSequence(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType);
	virtual FCsFpsAnimMontage* GetFCsFpsAnimMontage(const TCsWeaponFireMode &FireMode, const TCsWeaponAnim &AnimType);

#pragma endregion Anims

// FX
#pragma region

	virtual FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const int32 &Index = 0);
	virtual FCsFxElement* GetMuzzleFX(const TCsWeaponFireMode &FireMode, const int32 &Index = 0);

#pragma endregion FX

// Sound
#pragma region

	virtual FCsSoundElement* GetSound(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType);
	virtual FCsSoundElement* GetSound(const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType);

	virtual void PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);
	virtual void PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location);
	virtual void StopSound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);

	virtual void PlaySound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);
	virtual void PlaySound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location);
	virtual void StopSound(UWorld* InWorld, const TCsWeaponFireMode &FireMode, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);

#pragma endregion Sound
};