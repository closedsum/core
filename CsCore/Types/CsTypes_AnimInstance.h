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
#include "Animation/AimOffsetBlendSpace.h"

#include "CsTypes_AnimInstance.generated.h"
#pragma once

// Anim Instance
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_AnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UAnimSequence> Anim;

	TSoftObjectPtr<UAnimSequence> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimSequence> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimSequence()
	{
		UseDataValueAsDefault = true;
	}

	FORCEINLINE UAnimSequence* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FORCEINLINE FCsAnimInstance_AnimSequence& operator=(const FCsAnimInstance_AnimSequence& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimInstance_AnimSequence& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	FORCEINLINE bool operator!=(const FCsAnimInstance_AnimSequence& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool HasChanged() { return Anim != Last_Anim; }
	FORCEINLINE void Update() { Last_Anim = Anim; }
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_AnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UAnimMontage> Anim;

	TSoftObjectPtr<UAnimMontage> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimMontage> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimMontage()
	{
		UseDataValueAsDefault = true;
	}

	FORCEINLINE UAnimMontage* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FORCEINLINE FCsAnimInstance_AnimMontage& operator=(const FCsAnimInstance_AnimMontage& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimInstance_AnimMontage& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	FORCEINLINE bool operator!=(const FCsAnimInstance_AnimMontage& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool HasChanged() { return Anim != Last_Anim; }
	FORCEINLINE void Update() { Last_Anim = Anim; }
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_BlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UBlendSpace1D> Blend;

	TSoftObjectPtr<UBlendSpace1D> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UBlendSpace1D> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_BlendSpace1D()
	{
		UseDataValueAsDefault = true;
	}

	FORCEINLINE UBlendSpace1D* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FORCEINLINE FCsAnimInstance_BlendSpace1D& operator=(const FCsAnimInstance_BlendSpace1D& B)
	{
		Blend = B.Blend;
		Last_Blend = B.Last_Blend;
		Blend_Internal = B.Blend_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimInstance_BlendSpace1D& B) const
	{
		return Blend == B.Blend && Last_Blend == B.Last_Blend && Blend_Internal == B.Blend_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	FORCEINLINE bool operator!=(const FCsAnimInstance_BlendSpace1D& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool HasChanged() { return Blend != Last_Blend; }
	FORCEINLINE void Update() { Last_Blend = Blend; }
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_BlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UBlendSpace> Blend;

	TSoftObjectPtr<UBlendSpace> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UBlendSpace> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_BlendSpace()
	{
		UseDataValueAsDefault = true;
	}

	FORCEINLINE UBlendSpace* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FORCEINLINE FCsAnimInstance_BlendSpace& operator=(const FCsAnimInstance_BlendSpace& B)
	{
		Blend = B.Blend;
		Last_Blend = B.Last_Blend;
		Blend_Internal = B.Blend_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimInstance_BlendSpace& B) const
	{
		return Blend == B.Blend && Last_Blend == B.Last_Blend && Blend_Internal == B.Blend_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	FORCEINLINE bool operator!=(const FCsAnimInstance_BlendSpace& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool HasChanged() { return Blend != Last_Blend; }
	FORCEINLINE void Update() { Last_Blend = Blend; }
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_AimOffset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<UAimOffsetBlendSpace> Blend;

	TSoftObjectPtr<UAimOffsetBlendSpace> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAimOffsetBlendSpace> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AimOffset()
	{
		UseDataValueAsDefault = true;
	}

	FORCEINLINE UAimOffsetBlendSpace* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FORCEINLINE FCsAnimInstance_AimOffset& operator=(const FCsAnimInstance_AimOffset& B)
	{
		Blend = B.Blend;
		Last_Blend = B.Last_Blend;
		Blend_Internal = B.Blend_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsAnimInstance_AimOffset& B) const
	{
		return Blend == B.Blend && Last_Blend == B.Last_Blend && Blend_Internal == B.Blend_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	FORCEINLINE bool operator!=(const FCsAnimInstance_AimOffset& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool HasChanged() { return Blend != Last_Blend; }
	FORCEINLINE void Update() { Last_Blend = Blend; }
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_Blueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TSoftObjectPtr<class UBlueprint> Blueprint;

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
struct CSCORE_API FCsDataAnimInstance_CharacterPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_Character> Data;

	TSoftClassPtr<class ACsData_Character> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_Character> Data_Internal;

public:
	FCsDataAnimInstance_CharacterPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterPtr& operator=(const FCsDataAnimInstance_CharacterPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_Character* Get() const
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataAnimInstance_CharacterMeshSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_CharacterMeshSkin> Data;

	TSoftClassPtr<class ACsData_CharacterMeshSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_CharacterMeshSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMeshSkinPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterMeshSkinPtr& operator=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterMeshSkinPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_CharacterMeshSkin* Get() const
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataAnimInstance_CharacterMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_CharacterMaterialSkin> Data;

	TSoftClassPtr<class ACsData_CharacterMaterialSkin> Last_Data;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACsData_CharacterMaterialSkin> Data_Internal;

public:
	FCsDataAnimInstance_CharacterMaterialSkinPtr()
	{
	}

	FORCEINLINE FCsDataAnimInstance_CharacterMaterialSkinPtr& operator=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B)
	{
		Data = B.Data;
		Data_Internal = B.Data_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return Data == B.Data && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataAnimInstance_CharacterMaterialSkinPtr& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE class ACsData_CharacterMaterialSkin* Get() const
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataAnimInstance_WeaponPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_Weapon> Data;

	TSoftClassPtr<class ACsData_Weapon> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Data")
	TWeakObjectPtr<class ACsData_Weapon> Data_Internal;

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

	FORCEINLINE class ACsData_Weapon* Get() const
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

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataAnimInstance_WeaponMaterialSkinPtr
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Data")
	TSoftClassPtr<class ACsData_WeaponMaterialSkin> Data;

	TSoftClassPtr<class ACsData_WeaponMaterialSkin> Last_Data;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = "Data")
	TWeakObjectPtr<class ACsData_WeaponMaterialSkin> Data_Internal;

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

	FORCEINLINE class ACsData_WeaponMaterialSkin* Get() const
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

#pragma endregion Anim Instance