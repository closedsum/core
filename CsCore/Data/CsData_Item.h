// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Item.h"
#include "CsData_Item.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Item : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsItemType BaseItemType;

	TCsItemType GetBaseItemType();

// Stats
#pragma region
public:

	virtual TArray<FName>* GetContents();

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

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UMaterialInstanceConstant* GetMaterial();

	virtual FCsUint8MatrixDimension* GetDimension();

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