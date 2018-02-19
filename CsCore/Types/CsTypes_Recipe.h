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
	/** Whether to Consume the Item in the crafting process */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	bool Consume;
	/** Whether to Add the Item to the resulting Item's Contents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	bool AddToContents;

	FCsRecipeIngredient() 
	{
		Count = 1;
		Consume = true;
		AddToContents = false;
	}
	~FCsRecipeIngredient() {}

	FCsRecipeIngredient& operator=(const FCsRecipeIngredient& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		Consume = B.Consume;
		AddToContents = B.AddToContents;
		return *this;
	}

	bool operator==(const FCsRecipeIngredient& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		if (Consume != B.Consume) { return false; }
		if (AddToContents != B.AddToContents) { return false; }
		return true;
	}

	bool operator!=(const FCsRecipeIngredient& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Recipe

// Crafting
#pragma region 

#define CS_INVALID_CRAFTING_PAYLOAD_BAG 255

struct FCsCraftingPayload
{
	bool IsAllocated;
	uint64 Id;
	TWeakObjectPtr<UObject> Instigator;
	TWeakObjectPtr<class ACsManager_Inventory> Manager_Inventory;
	TWeakObjectPtr<class ACsData_Recipe> Recipe;
	uint8 Bag;
	uint16 Count;
	TMap<FName, TArray<struct FCsItem*>> ItemMap;
	bool AddToInventory;
	TArray<struct FCsItem*> OutItems;

	FCsCraftingPayload()
	{
		Reset();
	}
	~FCsCraftingPayload() {}

	void Reset()
	{
		IsAllocated = false;
		Id = 0;
		Instigator.Reset();
		Instigator = nullptr;
		Bag = CS_INVALID_CRAFTING_PAYLOAD_BAG;
		Count = CS_EMPTY;
		ItemMap.Reset();
		AddToInventory = false;
		OutItems.Reset();
	}

	class UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	class ACsManager_Inventory* GetManager_Inventory() { return Manager_Inventory.IsValid() ? Manager_Inventory.Get() : nullptr; }
	class ACsData_Recipe* GetRecipe() { return Recipe.IsValid() ? Recipe.Get() : nullptr; }

	void ProcessItems(const FName &ShortCode, const int32 &ItemCount, TArray<struct FCsItem*> &OutProcessedItems)
	{
		TArray<struct FCsItem*>* ItemsPtr = ItemMap.Find(ShortCode);

		for (int32 I = 0; I < ItemCount; ++I)
		{
			OutProcessedItems.Add((*ItemsPtr)[I]);
		}
		
		// Transpose the first ItemCount elements to the end of the array
		const int32 ItemsPtrCount = ItemsPtr->Num();

		for (int32 I = ItemCount; I < ItemsPtrCount; ++I)
		{
			FCsItem* Temp			   = (*ItemsPtr)[I - ItemCount];
			(*ItemsPtr)[I - ItemCount] = (*ItemsPtr)[I];
			(*ItemsPtr)[I]			   = Temp;
		}
		// Remove the last ItemCount elements of the array
		for (int32 I = ItemsPtrCount - 1; I > ItemsPtrCount - 1 - ItemCount; --I)
		{
			ItemsPtr->RemoveAt(I);
		}
	}
};

#pragma endregion Crafting