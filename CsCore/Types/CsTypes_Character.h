// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Character.generated.h"
#pragma once

// Character
#pragma region

namespace ECsCharacterAnim
{
	enum Type : uint8;
}

typedef ECsCharacterAnim::Type TCsCharacterAnim;

// CharacterAnimToString
typedef const FString&(*TCsCharacterAnimToString)(const TCsCharacterAnim&);
// StringToCharacterAnim
typedef TCsCharacterAnim(*TCsStringToCharacterAnim)(const FString&);

#define CS_DECLARE_CHARACTER_ANIM	TCsCharacterAnim CharacterAnim_MAX; \
									uint8 CHARACTER_ANIM_MAX; \
									TCsCharacterAnimToString CharacterAnimToString; \
									TCsStringToCharacterAnim StringToCharacterAnim;

#define CS_DEFINE_CHARACTER_ANIM	CharacterAnim_MAX = ECsCharacterAnim::ECsCharacterAnim_MAX;\
									CHARACTER_ANIM_MAX = (uint8)CharacterAnim_MAX \
									CharacterAnimToString = &ECsCharacterAnim::ToString; \
									StringToCharacterAnim = &ECsCharacterAnim::ToType;

namespace ECsCharacterBlendSpace
{
	enum Type : uint8;
}

typedef ECsCharacterBlendSpace::Type TCsCharacterBlendSpace;

// CharacterBlendSpaceToString
typedef const FString&(*TCsCharacterBlendSpaceToString)(const TCsCharacterBlendSpace&);
// StringToCharacterBlendSpace
typedef TCsCharacterBlendSpace(*TCsStringToCharacterBlendSpace)(const FString&);

#define CS_DECLARE_CHARACTER_BLEND_SPACE	TCsCharacterBlendSpace CharacterBlendSpace_MAX; \
											uint8 CHARACTER_BLEND_SPACE_MAX; \
											TCsCharacterBlendSpaceToString CharacterBlendSpaceToString; \
											TCsStringToCharacterBlendSpace StringToCharacterBlendSpace;

#define CS_DEFINE_CHARACTER_BLEND_SPACE		CharacterBlendSpace_MAX = ECsCharacterBlendSpace::ECsCharacterBlendSpace_MAX;\
											CHARACTER_BLEND_SPACE_MAX = (uint8)CharacterBlendSpace_MAX \
											CharacterBlendSpaceToString = &ECsCharacterBlendSpace::ToString; \
											StringToCharacterBlendSpace = &ECsCharacterBlendSpace::ToType;

namespace ECsCharacterAnimBlueprint
{
	enum Type : uint8;
}

typedef ECsCharacterAnimBlueprint::Type TCsCharacterAnimBlueprint;

// CharacterAnimBlueprintToString
typedef const FString&(*TCsCharacterAnimBlueprintToString)(const TCsCharacterAnimBlueprint&);
// StringToCharacterAnimBlueprint
typedef TCsCharacterAnimBlueprint(*TCsStringToCharacterAnimBlueprint)(const FString&);

#define CS_DECLARE_CHARACTER_ANIM_BLUEPRINT	TCsCharacterAnimBlueprint CharacterAnimBlueprint_MAX; \
											uint8 CHARACTER_ANIM_BLUEPRINT_MAX; \
											TCsCharacterAnimBlueprintToString CharacterAnimBlueprintToString; \
											TCsStringToCharacterAnimBlueprint StringToCharacterAnimBlueprint;

#define CS_DEFINE_CHARACTER_ANIM_BLUEPRINT	CharacterAnimBlueprint_MAX = ECsCharacterAnimBlueprint::ECsCharacterAnimBlueprint_MAX;\
											CHARACTER_ANIM_BLUEPRINT_MAX = (uint8)CharacterAnimBlueprint_MAX \
											CharacterAnimBlueprintToString = &ECsCharacterAnimBlueprint::ToString; \
											StringToCharacterAnimBlueprint = &ECsCharacterAnimBlueprint::ToType;

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
struct FCsHeadCollision
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

	FCsHeadCollision() {}
	~FCsHeadCollision() {}

	FCsHeadCollision& operator=(const FCsHeadCollision& B)
	{
		Radius = B.Radius;
		BoneName = B.BoneName;
		Offset = B.Offset;
		return *this;
	}

	bool operator==(const FCsHeadCollision& B) const
	{
		return Radius != B.Radius && BoneName != BoneName && Offset == B.Offset;
	}

	bool operator!=(const FCsHeadCollision& B) const
	{
		return !(*this == B);		
	}
};

#pragma endregion Character