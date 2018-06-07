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

	virtual void* GetFireModeStruct(const FECsWeaponFireMode &FireMode);
	virtual UScriptStruct* GetFireModeScriptStruct();
	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual float GetLocationDamageModifier(const FECsWeaponFireMode &FireMode, const FName &Bone);

	virtual const bool& UseFakeProjectile(const FECsWeaponFireMode &FireMode);
	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual class ACsData_Projectile* GetData_Projectile(const FECsWeaponFireMode &FireMode, const bool &IsCharged = false);

	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const uint8 &Index = 0);
	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const uint8 &Index = 0);
	virtual FVector GetMuzzleLocation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const uint8 &Index = 0);

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual const FECsWeaponGrip& GetGripType();

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual const int32& GetMaxAmmo();
	virtual int32* GetMaxAmmoAddr();

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual const float& GetRechargeStartupDelay();
	virtual float* GetRechargeStartupDelayAddr();

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual const float& GetRechargeSecondsPerAmmo();
	virtual float* GetRechargeSecondsPerAmmoAddr();

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual const float& GetReloadTime();
	virtual float* GetReloadTimeAddr();

#pragma endregion Stats

	// Anims
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual UAnimMontage* GetAnimMontage(const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimMontage* GetAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual UAnimSequence* GetAnimSequence(const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual UAnimSequence* GetAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Weapon Data")
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const TEnumAsByte<ECsViewType::Type> &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);
	virtual void GetAnim(UAnimSequence* &OutAnimSequence, UAnimMontage* &OutAnimMontage, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const bool &IsLow = false);

	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);
	virtual void PlayAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &PlayRate = 1.0f, const bool &IsLow = false);

	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(USkeletalMeshComponent* InMesh, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);
	virtual void StopAnimation(class ASkeletalMeshActor* InActor, const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType, const int32 &Index = 0, const float &BlendOutTime = 0.0f, const bool &IsLow = false);

	virtual FCsAnimSequence* GetFCsAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType);
	virtual FCsAnimMontage* GetFCsAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType);
	virtual FCsFpsAnimSequence* GetFCsFpsAnimSequence(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType);
	virtual FCsFpsAnimMontage* GetFCsFpsAnimMontage(const FECsWeaponFireMode &FireMode, const FECsWeaponAnim &AnimType);

#pragma endregion Anims

// FX
#pragma region

	virtual FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const int32 &Index = 0);
	virtual FCsFxElement* GetMuzzleFX(const FECsWeaponFireMode &FireMode, const int32 &Index = 0);

#pragma endregion FX

// Sound
#pragma region

	virtual FCsSoundElement* GetSound(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType);
	virtual FCsSoundElement* GetSound(const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType);

	virtual void PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);
	virtual void PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, const FVector &Location);
	virtual void StopSound(UWorld* InWorld, const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);

	virtual void PlaySound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);
	virtual void PlaySound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, const FVector &Location);
	virtual void StopSound(UWorld* InWorld, const FECsWeaponFireMode &FireMode, const FECsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);

#pragma endregion Sound
};