// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Recipe.generated.h"
#pragma once

// Recipe
#pragma region

namespace ECsRecipeType
{
	enum Type : uint8;
}

typedef ECsRecipeType::Type TCsRecipeType;

// RecipeToString
typedef FString(*TCsRecipeTypeToString)(const TCsRecipeType&);
// StringToRecipe
typedef TCsRecipeType(*TCsStringToRecipeType)(const FString&);

#define CS_DECLARE_RECIPE_TYPE	TCsRecipeType RecipeType_MAX;\
								uint8 RECIPE_TYPE_MAX; \
								TCsRecipeTypeToString RecipeTypeToString; \
								TCsStringToRecipeType StringToRecipeType;

#define CS_DEFINE_RECIPE_TYPE	RecipeType_MAX = ECsRecipeType::ECsRecipeType_MAX; \
								RECIPE_TYPE_MAX = (uint8)RecipeType_MAX; \
								RecipeTypeToString = &ECsRecipeType::ToString; \
								StringToRecipeType = &ECsRecipeType::ToType;

UENUM(BlueprintType)
namespace ECsItemCraftingState
{
	enum Type
	{
		Single					UMETA(DisplayName = "Single"),
		GroupHomogeneous		UMETA(DisplayName = "Group Homogeneous"),
		GroupMixed				UMETA(DisplayName = "Group Mixed"),
		ECsItemCraftingState_MAX	UMETA(Hidden),
	};
}

namespace ECsItemCraftingState
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Single = TCsString(TEXT("Single"), TEXT("single"), TEXT("single"));
		const TCsString GroupHomogeneous = TCsString(TEXT("GroupHomogeneous"), TEXT("grouphomogeneous"), TEXT("group homogeneous"));
		const TCsString GroupMixed = TCsString(TEXT("GroupMixed"), TEXT("groupmixed"), TEXT("group mixed"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Single) { return Str::Single.Value; }
		if (EType == Type::GroupHomogeneous) { return Str::GroupHomogeneous.Value; }
		if (EType == Type::GroupMixed) { return Str::GroupMixed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Single) { return Type::Single; }
		if (String == Str::GroupHomogeneous) { return Type::GroupHomogeneous; }
		if (String == Str::GroupMixed) { return Type::GroupMixed; }
		return Type::ECsItemCraftingState_MAX;
	}
}

#define ECS_ITEM_CRAFTING_STATE_MAX (uint8)ECsItemCraftingState::ECsItemCraftingState_MAX
typedef TEnumAsByte<ECsItemCraftingState::Type> TCsItemCraftingState;

USTRUCT(BlueprintType)
struct FCsRecipeIngredient
{
	GENERATED_USTRUCT_BODY()

	/** ShortCode for the Item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	FName ShortCode;
	/** Number of Items needed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	int32 Count;

	FCsRecipeIngredient() 
	{
		Count = 1;
	}
	~FCsRecipeIngredient() {}

	FCsRecipeIngredient& operator=(const FCsRecipeIngredient& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		return *this;
	}

	bool operator==(const FCsRecipeIngredient& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		return true;
	}

	bool operator!=(const FCsRecipeIngredient& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Recipe