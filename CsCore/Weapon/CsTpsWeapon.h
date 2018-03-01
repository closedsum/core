// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsGunWeapon.h"
#include "CsTpsWeapon.generated.h"

UCLASS()
class CSCORE_API ACsTpsWeapon : public ACsGunWeapon
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

// Data
#pragma region
public:

	virtual void ApplyData_Weapon(const TCsWeaponSlot &Slot, class ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped = true) override;

#pragma endregion Data

// Owner
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual USkeletalMeshComponent* GetCharacterMesh();

#pragma endregion Owner

// State
#pragma region

	virtual void OnTick(const float &DeltaSeconds) override;
	virtual void Show() override;
	virtual void Hide() override;

#pragma endregion State

// Mesh
#pragma region
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	virtual void SetMesh() override;

	USkeletalMeshComponent* GetMesh();

	bool UseMeshLow;

protected:

	TArray<class UMaterialInstanceDynamic*> MeshMIDs;

#pragma endregion Mesh

// Firing
#pragma region

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode) override;

#pragma endregion Firing
};
