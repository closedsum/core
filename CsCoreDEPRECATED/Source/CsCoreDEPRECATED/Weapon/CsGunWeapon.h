// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsWeapon_DEPRECATED.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Character.h"
#include "CsGunWeapon.generated.h"

// Enums
#pragma region

#pragma endregion Enums

class UCsData_Weapon;
class UCsData_WeaponMaterialSkin;

UCLASS()
class CSCOREDEPRECATED_API ACsGunWeapon : public ACsWeapon_DEPRECATED
{
	GENERATED_UCLASS_BODY()

// Data
#pragma region
public:

	virtual void ApplyData_Weapon(const FECsWeaponSlot &Slot, UCsData_Weapon* InData, UCsData_WeaponMaterialSkin* InSkin, const bool &Equipped = true);

	TWeakObjectPtr<UCsData_WeaponMaterialSkin> MyData_WeaponMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Data")
	UCsData_WeaponMaterialSkin* GetMyData_WeaponMaterialSkin();

	template<typename T>
	T* GetMyData_WeaponMaterialSkin()
	{
		return Cast<T>(GetMyData_WeaponMaterialSkin());
	}

	UFUNCTION(BlueprintCallable, Category = "Data")
	UCsData_Character* GetMyData_Character();

	template<typename T>
	T* GetMyData_Character()
	{
		return Cast<T>(GetMyData_Character());
	}

#pragma endregion Data

// Owner
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Owner")
	virtual void AttachMeshToPawn();

#pragma endregion Owner

// State
#pragma region

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FECsWeaponGrip GripType;

	virtual void OnPawnDeActivate();

#pragma endregion State

// Mesh
#pragma region

	virtual void SetMesh();

#pragma endregion Mesh

// Animation
#pragma region

	virtual const FECsCharacterAnim& GetCharacterAnimType(const FECsWeaponAnim &AnimType);

#pragma endregion Animation
};
