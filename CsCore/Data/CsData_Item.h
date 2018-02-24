// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Item.h"
#include "CsData_Item.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Item : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsItemType BaseItemType;

	TCsItemType GetBaseItemType();

// Stats
#pragma region
public:

	virtual TArray<FName>* GetContents();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual bool GetIsIngredient();

#pragma endregion Stats

// Members
#pragma region
public:

	virtual UScriptStruct* GetMembersScriptStruct();

	virtual TArray<FCsItemMemberDescription>* GetMembers();

#pragma endregion Members

// UI
#pragma region
public:

	/** Name to show in Inventory */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();
	/** Material used in Inventory */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UMaterialInstanceConstant* GetMaterial();
	/** Row Span and Column Span of Slot in the Inventory */
	virtual FCsUint8MatrixDimension* GetDimension();
	/** Slot Capacity (i.e. Max number of items held in slot) in the Inventory */
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual int32 GetCapacity();

#pragma endregion UI

// Drop
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Drop")
	virtual bool OnDropSpawnActor();

	virtual FName GetSpawnedActorDataShortCode();

#pragma endregion Drop

// Consume
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Consume")
	virtual bool OnConsumeDropContents();

#pragma endregion Consume
};