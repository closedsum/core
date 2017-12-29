// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimBlueprint.h"

#include "CsTypes_AnimInstance.generated.h"
#pragma once

// Anim Instance
#pragma region

USTRUCT(BlueprintType)
struct FCsAnimInstance_AnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UAnimSequence> Anim;

	TAssetPtr<UAnimSequence> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimSequence> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimSequence()
	{
		UseDataValueAsDefault = true;
	}

	UAnimSequence* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FCsAnimInstance_AnimSequence& operator=(const FCsAnimInstance_AnimSequence& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_AnimSequence& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_AnimSequence& B) const
	{
		return !(*this == B);
	}

	bool HasChanged() { return Anim != Last_Anim; }
	void Update() { Last_Anim = Anim; }
};

USTRUCT(BlueprintType)
struct FCsAnimInstance_AnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UAnimMontage> Anim;

	TAssetPtr<UAnimMontage> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimMontage> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimMontage()
	{
		UseDataValueAsDefault = true;
	}

	UAnimMontage* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FCsAnimInstance_AnimMontage& operator=(const FCsAnimInstance_AnimMontage& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_AnimMontage& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_AnimMontage& B) const
	{
		return !(*this == B);
	}

	bool HasChanged() { return Anim != Last_Anim; }
	void Update() { Last_Anim = Anim; }
};

USTRUCT(BlueprintType)
struct FCsAnimInstance_Blueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<class UBlueprint> Blueprint;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:

	UBlueprintGeneratedClass * Get() const
	{
		return Blueprint_Internal;
	}

	FCsAnimInstance_Blueprint& operator=(const FCsAnimInstance_Blueprint& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_Internal = B.Blueprint_Internal;
		return *this;
	}

	bool operator==(const FCsAnimInstance_Blueprint& B) const
	{
		return Blueprint == B.Blueprint && Blueprint_Internal == B.Blueprint_Internal;
	}

	bool operator!=(const FCsAnimInstance_Blueprint& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsDataAnimInstance_WeaponPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_Weapon> Data;

	TAssetSubclassOf<class ACsData_Weapon> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Data")
	TWeakObjectPtr<class ACsData_Weapon> Data_Internal;

public:
	FCsDataAnimInstance_WeaponPtr()
	{
	}

	FCsDataAnimInstance_WeaponPtr& operator=(const FCsDataAnimInstance_WeaponPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsDataAnimInstance_WeaponPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsDataAnimInstance_WeaponPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_Weapon* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : NULL;
	}

	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
};

USTRUCT(BlueprintType)
struct FCsDataAnimInstance_WeaponMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_WeaponMaterialSkin> Data;

	TAssetSubclassOf<class ACsData_WeaponMaterialSkin> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Data")
	TWeakObjectPtr<class ACsData_WeaponMaterialSkin> Data_Internal;

public:
	FCsDataAnimInstance_WeaponMaterialSkinPtr()
	{
	}

	FCsDataAnimInstance_WeaponMaterialSkinPtr& operator=(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsDataAnimInstance_WeaponMaterialSkinPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_WeaponMaterialSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : NULL;
	}

	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
};

#pragma endregion Anim Instance