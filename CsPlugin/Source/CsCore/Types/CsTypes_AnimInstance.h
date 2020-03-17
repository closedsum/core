// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
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

// FCsAnimInstance_AnimSequence
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_AnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimSequence> Anim;

	TSoftObjectPtr<UAnimSequence> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UAnimSequence> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

#pragma endregion FCsAnimInstance_AnimSequence

// FCsAnimInstance_AnimMontage
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_AnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UAnimMontage> Anim;

	TSoftObjectPtr<UAnimMontage> Last_Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UAnimMontage> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

#pragma endregion FCsAnimInstance_AnimMontage

// FCsAnimInstance_BlendSpace1D
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_BlendSpace1D
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UBlendSpace1D> Blend;

	TSoftObjectPtr<UBlendSpace1D> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UBlendSpace1D> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

#pragma endregion FCsAnimInstance_BlendSpace1D

// FCsAnimInstance_BlendSpace
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_BlendSpace
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UBlendSpace> Blend;

	TSoftObjectPtr<UBlendSpace> Last_Blend;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	TWeakObjectPtr<UBlendSpace> Blend_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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


#pragma endregion FCsAnimInstance_BlendSpace

// FCsAnimInstance_AimOffset
#pragma region

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

#pragma endregion FCsAnimInstance_AimOffset

// FCsAnimInstance_Blueprint
#pragma region

class UBlueprint;
class UBlueprintGeneratedClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsAnimInstance_Blueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UBlueprint> Blueprint;

	UPROPERTY(Transient, VisibleDefaultsOnly)
	UBlueprintGeneratedClass* Blueprint_Internal;

public:

	UBlueprintGeneratedClass* Get() const
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

#pragma endregion FCsAnimInstance_Blueprint