// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsGunWeapon.h"
#include "CsFpsWeapon.generated.h"

// Enums
#pragma region

namespace ECsFpsWeaponMultiValueMember
{
	// Spread
	extern CSCORE_API const FECsWeaponMultiValueMember MovingSpreadBonus;
	extern CSCORE_API const FECsWeaponMultiValueMember JumpSpreadImpulse;
	extern CSCORE_API const FECsWeaponMultiValueMember ScopeAccuracyBonus;
	// Scope
	extern CSCORE_API const FECsWeaponMultiValueMember DoScopePower;
	extern CSCORE_API const FECsWeaponMultiValueMember MaxScopePower;
	extern CSCORE_API const FECsWeaponMultiValueMember ScopePowerGrowthRate;
	extern CSCORE_API const FECsWeaponMultiValueMember CurrentScopePower;
	extern CSCORE_API const FECsWeaponMultiValueMember LastScopePower;
	// Movement
	extern CSCORE_API const FECsWeaponMultiValueMember DoSlowWhileFiring;
	extern CSCORE_API const FECsWeaponMultiValueMember SlowWhileFiringRate;
	extern CSCORE_API const FECsWeaponMultiValueMember DoKickback;
	extern CSCORE_API const FECsWeaponMultiValueMember DoKickbackOnGround;
	extern CSCORE_API const FECsWeaponMultiValueMember KickbackStrength;
}

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsFpsWeapon : public ACsGunWeapon
{
	GENERATED_UCLASS_BODY()

// Members
#pragma region

	virtual void InitMultiValueMembers() override;

	// Set
#pragma region

	virtual void SetMemberValue_float(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode, const float &Value) override;

	virtual void SetMultiValueMembers() override;

#pragma endregion Set

	// Get
#pragma region

	virtual bool GetMemberValue_bool(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode) override;
	virtual float GetMemberValue_float(const FECsWeaponMultiValueMember &Member, const FECsWeaponFireMode &FireMode) override;

#pragma endregion Get

#pragma endregion Members

// Owner
#pragma region

	virtual void AttachMeshToPawn() override;

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual USkeletalMeshComponent* GetCharacterMesh(const TEnumAsByte<ECsViewType::Type> &ViewType);

#pragma endregion Owner

// State
#pragma region

	virtual void OnTick(const float &DeltaSeconds) override;
	virtual void Disable() override;
	virtual void Show() override;
	virtual void Hide() override;

#pragma endregion State

// Mesh
#pragma region
public:

	virtual void SetMesh() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh1P;

	void SetMesh1P();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh3P;

	void SetMesh3P();

	USkeletalMeshComponent* GetMesh(const TCsViewType &ViewType);
	USkeletalMeshComponent* GetCurrentMesh();

	bool UseMesh3PLow;
	bool UseMeleeAttachment;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeleeAttachment1P;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeleeAttachment3P;

protected:

	TArray<class UMaterialInstanceDynamic*> MeshMIDs1P;
	TArray<class UMaterialInstanceDynamic*> MeshMIDs3P;

#pragma endregion Mesh

// Firing
#pragma region

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const FECsWeaponFireMode &FireMode) override;

	// Spread

	FCsWeapon_TMapRef_float MovingSpreadBonus;
	virtual float GetMovingSpreadBonus(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float JumpSpreadImpulse;
	virtual float GetJumpSpreadImpulse(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float ScopeAccuracyBonus;
	virtual float GetScopeAccuracyBonus(const FECsWeaponFireMode &FireMode);

	UPROPERTY()
	bool Last_OwnerIsFalling;

	// Scope

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode ScopeDataFireMode;

	bool IsScopeActive;
	bool Last_IsScopeActive;
	bool IsScopeActive_Toggle;
	float ScopeActiveStartTime;

	FCsWeapon_TMapRef_bool DoScopePower;
	FCsWeapon_TMapRef_float MaxScopePower;
	virtual float GetMaxScopePower(const FECsWeaponFireMode &FireMode);
	FCsWeapon_TMapRef_float ScopePowerGrowthRate;
	virtual float GetScopePowerGrowthRate(const FECsWeaponFireMode &FireMode);

	FCsWeapon_TMap_float CurrentScopePower;
	FCsWeapon_TMap_float LastScopePower;

	virtual void FireProjectile_Internal(const FECsWeaponFireMode &FireMode, FCsProjectileFirePayload* Payload) override;

#pragma endregion Firing

// Movement
#pragma region

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Firing")
	FECsData_Weapon_FireMode MovementDataFireMode;

	FCsWeapon_TMapRef_bool DoSlowWhileFiring;
	FCsWeapon_TMapRef_float SlowWhileFiringRate;
	FCsWeapon_TMapRef_bool DoKickback;
	FCsWeapon_TMapRef_bool DoKickbackOnGround;
	FCsWeapon_TMapRef_float KickbackStrength;

#pragma endregion Movement
};
