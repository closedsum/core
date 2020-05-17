// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Character.generated.h"
#pragma once

// CharacterAnim
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsCharacterAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnim)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnim)

struct CSCOREDEPRECATED_API EMCsCharacterAnim : public TCsEnumStructMap<FECsCharacterAnim, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnim, FECsCharacterAnim, uint8)
};

#pragma endregion CharacterAnim

// CharacterBlendSpace
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsCharacterBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterBlendSpace)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterBlendSpace)

struct CSCOREDEPRECATED_API EMCsCharacterBlendSpace : public TCsEnumStructMap<FECsCharacterBlendSpace, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCharacterBlendSpace, FECsCharacterBlendSpace, uint8)
};

#pragma endregion CharacterBlendSpace

// CharacterAnimBlueprint
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsCharacterAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnimBlueprint)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnimBlueprint)

struct CSCOREDEPRECATED_API EMCsCharacterAnimBlueprint : public TCsEnumStructMap<FECsCharacterAnimBlueprint, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint, uint8)
};

#pragma endregion CharacterAnimBlueprint

// CharacterAnimVariation
#pragma region

namespace ECsCharacterAnimVariation
{
	enum Type : uint8;
}

typedef ECsCharacterAnimVariation::Type TCsCharacterAnimVariation;

// CharacterAnimVariationToString
typedef const FString&(*TCsCharacterAnimVariationToString)(const TCsCharacterAnimVariation&);
// StringToCharacterAnim
typedef TCsCharacterAnimVariation(*TCsStringToCharacterAnimVariation)(const FString&);

#define CS_DECLARE_CHARACTER_ANIM_VARIATION	TCsCharacterAnimVariation CharacterAnimVariation_MAX; \
											uint8 CHARACTER_ANIM_VARIATION_MAX; \
											TCsCharacterAnimVariationToString CharacterAnimVariationToString; \
											TCsStringToCharacterAnimVariation StringToCharacterAnimVariation;

#define CS_DEFINE_CHARACTER_ANIM_VARIATION	CharacterAnimVariation_MAX = ECsCharacterAnimVariation::ECsCharacterAnimVariation_MAX;\
											CHARACTER_ANIM_VARIATION_MAX = (uint8)CharacterAnimVariation_MAX \
											CharacterAnimVariationToString = &ECsCharacterAnimVariation::ToString; \
											StringToCharacterAnimVariation = &ECsCharacterAnimVariation::ToType;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsCharacterAnimVariation : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnimVariation)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnimVariation)

struct CSCOREDEPRECATED_API EMCsCharacterAnimVariation : public TCsEnumStructMap<FECsCharacterAnimVariation, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnimVariation, FECsCharacterAnimVariation, uint8)
};

#pragma endregion CharacterAnimVariation

// FCsHeadCollision
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsHeadCollision
{
	GENERATED_USTRUCT_BODY()

	/** Radius of collision sphere around head. Used for in Big Head Mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	/** Name of the bone / joint where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneName;

	/** Offset from BoneName from where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Offset;

	FCsHeadCollision() :
		Radius(0.0f),
		BoneName(NAME_None),
		Offset(0.0f)
	{
	}
	~FCsHeadCollision() {}

	FORCEINLINE FCsHeadCollision& operator=(const FCsHeadCollision& B)
	{
		Radius = B.Radius;
		BoneName = B.BoneName;
		Offset = B.Offset;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsHeadCollision& B) const
	{
		return Radius != B.Radius && BoneName != BoneName && Offset == B.Offset;
	}

	FORCEINLINE bool operator!=(const FCsHeadCollision& B) const
	{
		return !(*this == B);		
	}
};

#pragma endregion FCsHeadCollision

// CharacterJumpMovementState
#pragma region

UENUM(BlueprintType)
enum class ECsCharacterJumpMovementState : uint8
{
	Grounded							UMETA(DisplayName = "Grounded"),
	Up									UMETA(DisplayName = "Up"),
	Down								UMETA(DisplayName = "Down"),
	ECsCharacterJumpMovementState_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsCharacterJumpMovementState : public TCsEnumMap<ECsCharacterJumpMovementState>
{
	CS_ENUM_MAP_BODY(EMCsCharacterJumpMovementState, ECsCharacterJumpMovementState)
};

namespace NCsCharacterJumpMovementState
{
	namespace Ref
	{
		typedef ECsCharacterJumpMovementState Type;

		extern CSCOREDEPRECATED_API const Type Grounded;
		extern CSCOREDEPRECATED_API const Type Up;
		extern CSCOREDEPRECATED_API const Type Down;
		extern CSCOREDEPRECATED_API const Type ECsCharacterJumpMovementState_MAX;
	}
}

#pragma endregion CharacterJumpMovementState