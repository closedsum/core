// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Item.h"
#include "CsData_Item.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Item : public ACsData
{
	GENERATED_UCLASS_BODY()

	TCsItemType ItemType;

// Members
#pragma region

	virtual UScriptStruct* GetMembersScriptStruct();

#pragma endregion Members

// UI
#pragma region

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();

#pragma endregion UI

// Drop
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Drop")
	virtual bool OnDropSpawnActor();

	virtual FName GetSpawnedActorDataShortCode();

#pragma endregion Drop
};