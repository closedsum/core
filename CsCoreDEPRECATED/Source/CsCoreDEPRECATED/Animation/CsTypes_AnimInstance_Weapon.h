// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "CsTypes_AnimInstance_Weapon.generated.h"
#pragma once

// FCsDataAnimInstance_WeaponPtr
#pragma region

class UCsData_Weapon;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataAnimInstance_WeaponPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCsData_Weapon> Data;

	TSoftClassPtr<UCsData_Weapon> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UCsData_Weapon> Data_Internal;

public:
	FCsDataAnimInstance_WeaponPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_WeaponPtr& operator=(const FCsDataAnimInstance_WeaponPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_WeaponPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_WeaponPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_Weapon* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE bool HasChanged() { return Data != Last_Data; }
	FORCEINLINE void Update() { Last_Data = Data; }
};

#pragma endregion FCsDataAnimInstance_WeaponPtr

// FCsDataAnimInstance_WeaponMaterialSkinPtr
#pragma region

class UCsData_WeaponMaterialSkin;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsDataAnimInstance_WeaponMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UCsData_WeaponMaterialSkin> Data;

	TSoftClassPtr<UCsData_WeaponMaterialSkin> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UCsData_WeaponMaterialSkin> Data_Internal;

public:
	FCsDataAnimInstance_WeaponMaterialSkinPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_WeaponMaterialSkinPtr& operator=(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UCsData_WeaponMaterialSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	FORCEINLINE T* Get() const
	{
		return Cast<T>(Get());
	}

	FORCEINLINE bool HasChanged() { return Data != Last_Data; }
	FORCEINLINE void Update() { Last_Data = Data; }
};

#pragma endregion FCsDataAnimInstance_WeaponMaterialSkinPtr