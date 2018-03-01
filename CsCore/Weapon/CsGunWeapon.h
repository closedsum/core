// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Weapon/CsWeapon.h"
#include "CsGunWeapon.generated.h"

// Enums
#pragma region

#pragma endregion Enums

UCLASS()
class CSCORE_API ACsGunWeapon : public ACsWeapon
{
	GENERATED_UCLASS_BODY()

// Members
#pragma region

	// Set
#pragma region

#pragma endregion Set

	// Get
#pragma region

#pragma endregion Get

#pragma endregion Members

// Data
#pragma region
public:

	virtual void ApplyData_Weapon(const TCsWeaponSlot &Slot, class ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped = true);

	TWeakObjectPtr<class ACsData_WeaponMaterialSkin> MyData_WeaponMaterialSkin;

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_WeaponMaterialSkin* GetMyData_WeaponMaterialSkin();

	template<typename T>
	T* GetMyData_WeaponMaterialSkin()
	{
		return Cast<T>(GetMyData_WeaponMaterialSkin());
	}

	UFUNCTION(BlueprintCallable, Category = "Data")
	class ACsData_Character* GetMyData_Character();

	template<typename T>
	T* GetMyData_Character()
	{
		return Cast<T>(GetMyData_Character());
	}

#pragma endregion Data

// State
#pragma region

	virtual void OnTick(const float &DeltaSeconds) override;
	virtual void Disable() override;
	virtual void Show() override;
	virtual void Hide() override;

#pragma endregion State

// Firing
#pragma region

	virtual FVector GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode) override;

#pragma endregion Firing
};
