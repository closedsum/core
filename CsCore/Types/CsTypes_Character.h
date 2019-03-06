// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Character.generated.h"
#pragma once

// CharacterAnim
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterAnim : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnim)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnim)

struct CSCORE_API EMCsCharacterAnim : public TCsEnumStructMap<FECsCharacterAnim, uint8>
{
protected:
	EMCsCharacterAnim() {}
	EMCsCharacterAnim(const EMCsCharacterAnim &) = delete;
	EMCsCharacterAnim(EMCsCharacterAnim &&) = delete;
public:
	~EMCsCharacterAnim() {}
private:
	static EMCsCharacterAnim* Instance;

public:
	static EMCsCharacterAnim& Get();
};

#pragma endregion CharacterAnim

// CharacterBlendSpace
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterBlendSpace : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterBlendSpace)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterBlendSpace)

struct CSCORE_API EMCsCharacterBlendSpace : public TCsEnumStructMap<FECsCharacterBlendSpace, uint8>
{
protected:
	EMCsCharacterBlendSpace() {}
	EMCsCharacterBlendSpace(const EMCsCharacterBlendSpace &) = delete;
	EMCsCharacterBlendSpace(EMCsCharacterBlendSpace &&) = delete;
public:
	~EMCsCharacterBlendSpace() {}
private:
	static EMCsCharacterBlendSpace* Instance;

public:
	static EMCsCharacterBlendSpace& Get();
};

#pragma endregion CharacterBlendSpace

// CharacterAnimBlueprint
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCharacterAnimBlueprint : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnimBlueprint)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnimBlueprint)

struct CSCORE_API EMCsCharacterAnimBlueprint : public TCsEnumStructMap<FECsCharacterAnimBlueprint, uint8>
{
protected:
	EMCsCharacterAnimBlueprint() {}
	EMCsCharacterAnimBlueprint(const EMCsCharacterAnimBlueprint &) = delete;
	EMCsCharacterAnimBlueprint(EMCsCharacterAnimBlueprint &&) = delete;
public:
	~EMCsCharacterAnimBlueprint() {}
private:
	static EMCsCharacterAnimBlueprint* Instance;

public:
	static EMCsCharacterAnimBlueprint& Get();
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
struct CSCORE_API FECsCharacterAnimVariation : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCharacterAnimVariation)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCharacterAnimVariation)

struct CSCORE_API EMCsCharacterAnimVariation : public TCsEnumStructMap<FECsCharacterAnimVariation, uint8>
{
protected:
	EMCsCharacterAnimVariation() {}
	EMCsCharacterAnimVariation(const EMCsCharacterAnimVariation &) = delete;
	EMCsCharacterAnimVariation(EMCsCharacterAnimVariation &&) = delete;
public:
	~EMCsCharacterAnimVariation() {}
private:
	static EMCsCharacterAnimVariation* Instance;

public:
	static EMCsCharacterAnimVariation& Get();
};

#pragma endregion CharacterAnimVariation

USTRUCT(BlueprintType)
struct CSCORE_API FCsHeadCollision
{
	GENERATED_USTRUCT_BODY()

	/** Radius of collision sphere around head. Used for in Big Head Mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius;

	/** Name of the bone / joint where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FName BoneName;

	/** Offset from BoneName from where the head collision will be checked */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
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

struct CSCORE_API EMCsCharacterJumpMovementState : public TCsEnumMap<ECsCharacterJumpMovementState>
{
protected:
	EMCsCharacterJumpMovementState() {}
	EMCsCharacterJumpMovementState(const EMCsCharacterJumpMovementState &) = delete;
	EMCsCharacterJumpMovementState(EMCsCharacterJumpMovementState &&) = delete;
public:
	~EMCsCharacterJumpMovementState() {}
private:
	static EMCsCharacterJumpMovementState* Instance;

public:
	static EMCsCharacterJumpMovementState& Get();
};

namespace NCsCharacterJumpMovementState
{
	namespace Ref
	{
		typedef ECsCharacterJumpMovementState Type;

		extern CSCORE_API const Type Grounded;
		extern CSCORE_API const Type Up;
		extern CSCORE_API const Type Down;
		extern CSCORE_API const Type ECsCharacterJumpMovementState_MAX;
	}
}

#pragma endregion CharacterJumpMovementState