// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"

#include "CsTypes_Recipe.generated.h"
#pragma once

// Recipe
#pragma region

	// RecipeType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsRecipeType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsRecipeType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsRecipeType)

struct CSCOREDEPRECATED_API EMCsRecipeType : public TCsEnumStructMap<FECsRecipeType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsRecipeType, FECsRecipeType, uint8)
};

#pragma endregion RecipeType

	// FCsRecipeIngredient 
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsRecipeIngredient
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

#pragma endregion FCsRecipeIngredient

#pragma endregion Recipe

// Crafting
#pragma region 

#define CS_INVALID_CRAFTING_PAYLOAD_BAG 255

class UObject;
class ACsManager_Inventory;
class UCsData_Recipe;

	// FCsCraftingPayload
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsCraftingPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool bAllocated;
	UPROPERTY()
	uint64 Id;
	UPROPERTY()
	TWeakObjectPtr<UObject> Instigator;
	UPROPERTY()
	TWeakObjectPtr<ACsManager_Inventory> Manager_Inventory;
	UPROPERTY()
	TWeakObjectPtr<UCsData_Recipe> Recipe;
	UPROPERTY()
	uint8 Bag;
	UPROPERTY()
	uint16 Count;
	
	TMap<FName, TArray<struct FCsItem*>> ItemMap;
	
	UPROPERTY()
	bool AddToInventory;

	TArray<struct FCsItem*> OutItems;

	FCsCraftingPayload()
	{
		Reset();
	}
	~FCsCraftingPayload() {}

	FORCEINLINE void Reset()
	{
		bAllocated = false;
		Id = 0;
		Instigator.Reset();
		Instigator = nullptr;
		Bag = CS_INVALID_CRAFTING_PAYLOAD_BAG;
		Count = CS_EMPTY;
		ItemMap.Reset();
		AddToInventory = false;
		OutItems.Reset();
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }
	FORCEINLINE ACsManager_Inventory* GetManager_Inventory() { return Manager_Inventory.IsValid() ? Manager_Inventory.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetManager_Inventory() { return Cast<T>(GetManager_Inventory()); }
	FORCEINLINE UCsData_Recipe* GetRecipe() { return Recipe.IsValid() ? Recipe.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetRecipe() { return Cast<T>(GetRecipe()); }

	void ProcessItems(const FName &ShortCode, const int32 &ItemCount, TArray<struct FCsItem*> &OutProcessedItems)
	{
		TArray<struct FCsItem*>& Items = ItemMap[ShortCode];

		for (FCsItem* Item : Items)
		{
			OutProcessedItems.Add(Item);
		}
		
		// Transpose the first ItemCount elements to the end of the array
		const int32 CurrentCount = Items.Num();

		for (int32 I = ItemCount; I < CurrentCount; ++I)
		{
			FCsItem* Temp		 = Items[I - ItemCount];
			Items[I - ItemCount] = Items[I];
			Items[I]			 = Temp;
		}
		// Remove the last ItemCount elements of the array
		for (int32 I = CurrentCount - 1; I > CurrentCount - 1 - ItemCount; --I)
		{
			Items.RemoveAt(I);
		}
	}
};

#pragma endregion FCsCraftingPayload

#pragma endregion Crafting