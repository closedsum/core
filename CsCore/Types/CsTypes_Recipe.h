// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Recipe.generated.h"
#pragma once

// Recipe
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsRecipeType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsRecipeType() {}
	FECsRecipeType(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsRecipeType(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsRecipeType() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsRecipeType& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsRecipeType : public TCsEnumStructMap<FECsRecipeType, uint8>
{
protected:
	EMCsRecipeType() {}
	EMCsRecipeType(const EMCsRecipeType &) = delete;
	EMCsRecipeType(EMCsRecipeType &&) = delete;
public:
	~EMCsRecipeType() {}
private:
	static EMCsRecipeType* Instance;

public:
	static EMCsRecipeType& Get();
};

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

USTRUCT(BlueprintType)
struct FCsCraftingPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool IsAllocated;
	UPROPERTY()
	uint64 Id;
	UPROPERTY()
	TWeakObjectPtr<UObject> Instigator;
	UPROPERTY()
	TWeakObjectPtr<class ACsManager_Inventory> Manager_Inventory;
	UPROPERTY()
	TWeakObjectPtr<class ACsData_Recipe> Recipe;
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

	FORCEINLINE class UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }
	FORCEINLINE class ACsManager_Inventory* GetManager_Inventory() { return Manager_Inventory.IsValid() ? Manager_Inventory.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetManager_Inventory() { return Cast<T>(GetManager_Inventory()); }
	FORCEINLINE class ACsData_Recipe* GetRecipe() { return Recipe.IsValid() ? Recipe.Get() : nullptr; }
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

#pragma endregion Crafting