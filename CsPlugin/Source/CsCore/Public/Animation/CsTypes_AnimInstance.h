// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
//#include "Types/Enum/.h"

#include "CsTypes_AnimInstance.generated.h"
#pragma once

// FCsAnimInstance_AnimSequence
#pragma region

class UAnimSequence;

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

	FCsAnimInstance_AnimSequence() :
		Anim(nullptr),
		Last_Anim(nullptr),
		Anim_Internal(nullptr),
		UseDataValueAsDefault(true)
	{
	}

	FORCEINLINE UAnimSequence* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FORCEINLINE bool HasChanged() { return Anim != Last_Anim; }
	FORCEINLINE void Update() { Last_Anim = Anim; }
};

#pragma endregion FCsAnimInstance_AnimSequence

// FCsAnimInstance_AnimMontage
#pragma region

class UAnimMontage;

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

	FCsAnimInstance_AnimMontage() :
		Anim(nullptr),
		Last_Anim(nullptr),
		Anim_Internal(nullptr),
		UseDataValueAsDefault(true)
	{
	}

	FORCEINLINE UAnimMontage* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FORCEINLINE bool HasChanged() { return Anim != Last_Anim; }
	FORCEINLINE void Update() { Last_Anim = Anim; }
};

#pragma endregion FCsAnimInstance_AnimMontage

// FCsAnimInstance_BlendSpace1D
#pragma region

class UBlendSpace1D;

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

	FCsAnimInstance_BlendSpace1D() :
		Blend(nullptr),
		Last_Blend(nullptr),
		Blend_Internal(nullptr),
		UseDataValueAsDefault(true)
	{
	}

	FORCEINLINE UBlendSpace1D* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FORCEINLINE bool HasChanged() { return Blend != Last_Blend; }
	FORCEINLINE void Update() { Last_Blend = Blend; }
};

#pragma endregion FCsAnimInstance_BlendSpace1D

// FCsAnimInstance_BlendSpace
#pragma region

class UBlendSpace;

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

	FCsAnimInstance_BlendSpace() :
		Blend(nullptr),
		Last_Blend(nullptr),
		Blend_Internal(nullptr),
		UseDataValueAsDefault(true)
	{
	}

	FORCEINLINE UBlendSpace* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
	}

	FORCEINLINE bool HasChanged() { return Blend != Last_Blend; }
	FORCEINLINE void Update() { Last_Blend = Blend; }
};


#pragma endregion FCsAnimInstance_BlendSpace

// FCsAnimInstance_AimOffset
#pragma region

class UAimOffsetBlendSpace;

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

	FCsAnimInstance_AimOffset() :
		Blend(nullptr),
		Last_Blend(nullptr),
		Blend_Internal(nullptr),
		UseDataValueAsDefault(true)
	{
	}

	FORCEINLINE UAimOffsetBlendSpace* Get() const
	{
		return Blend_Internal.IsValid() ? Blend_Internal.Get() : nullptr;
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

	FORCEINLINE UBlueprintGeneratedClass* Get() const { return Blueprint_Internal; }
};

#pragma endregion FCsAnimInstance_Blueprint

// NCsAnim::NInstance::ERoutine
#pragma region

namespace NCsAnim
{
	namespace NInstance
	{

	}
}

#pragma endregion NCsAnim::NInstance::ERoutine