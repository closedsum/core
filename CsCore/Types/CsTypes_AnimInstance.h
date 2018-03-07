// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Animation/AnimSequence.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/BlendSpace.h"
#include "Animation/BlendSpace1D.h"

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
struct FCsAnimInstance_BlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UBlendSpace1D> Blend;

	TAssetPtr<UBlendSpace1D> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UBlendSpace1D> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_BlendSpace1D()
	{
		UseDataValueAsDefault = true;
	}

	UBlendSpace1D* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FCsAnimInstance_BlendSpace1D& operator=(const FCsAnimInstance_BlendSpace1D& B)
	{
		Blend = B.Blend;
		Last_Blend = B.Last_Blend;
		Blend_Internal = B.Blend_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_BlendSpace1D& B) const
	{
		return Blend == B.Blend && Last_Blend == B.Last_Blend && Blend_Internal == B.Blend_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_BlendSpace1D& B) const
	{
		return !(*this == B);
	}

	bool HasChanged() { return Blend != Last_Blend; }
	void Update() { Last_Blend = Blend; }
};

USTRUCT(BlueprintType)
struct FCsAnimInstance_BlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UBlendSpace> Blend;

	TAssetPtr<UBlendSpace> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UBlendSpace> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_BlendSpace()
	{
		UseDataValueAsDefault = true;
	}

	UBlendSpace* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FCsAnimInstance_BlendSpace& operator=(const FCsAnimInstance_BlendSpace& B)
	{
		Blend = B.Blend;
		Last_Blend = B.Last_Blend;
		Blend_Internal = B.Blend_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_BlendSpace& B) const
	{
		return Blend == B.Blend && Last_Blend == B.Last_Blend && Blend_Internal == B.Blend_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_BlendSpace& B) const
	{
		return !(*this == B);
	}

	bool HasChanged() { return Blend != Last_Blend; }
	void Update() { Last_Blend = Blend; }
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
struct FCsDataAnimInstance_CharacterPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_Character> Data;

	TAssetSubclassOf<class ACsData_Character> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_Character> Data_Internal;

public:
	FCsDataAnimInstance_CharacterPtr()
	{
	}

	FCsDataAnimInstance_CharacterPtr& operator=(const FCsDataAnimInstance_CharacterPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_Character* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	T* Get() const 
	{
		return Cast<T>(Get());
	}
	
	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
};

USTRUCT(BlueprintType)
struct FCsDataAnimInstance_CharacterMeshSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_CharacterMeshSkin> Data;

	TAssetSubclassOf<class ACsData_CharacterMeshSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_CharacterMeshSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMeshSkinPtr()
	{
	}

	FCsDataAnimInstance_CharacterMeshSkinPtr& operator=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_CharacterMeshSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	T* Get() const 
	{
		return Cast<T>(Get());
	}

	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
};

USTRUCT(BlueprintType)
struct FCsDataAnimInstance_CharacterMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TAssetSubclassOf<class ACsData_CharacterMaterialSkin> Data;

	TAssetSubclassOf<class ACsData_CharacterMaterialSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_CharacterMaterialSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMaterialSkinPtr()
	{
	}

	FCsDataAnimInstance_CharacterMaterialSkinPtr& operator=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	bool operator==(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	bool operator!=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return !(*this == B);
	}

	class ACsData_CharacterMaterialSkin* Get() const
	{
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	T* Get() const
	{
		return Cast<T>(Get());
	}

	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
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
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	T* Get() const 
	{
		return Cast<T>(Get());
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
		return Data_Internal.IsValid() ? Data_Internal.Get() : nullptr;
	}

	template<typename T>
	T* Get() const 
	{
		return Cast<T>(Get());
	}

	bool HasChanged() { return Data != Last_Data; }
	void Update() { Last_Data = Data; }
};

#pragma endregion Anim Instance