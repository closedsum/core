// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Item.h"
#include "CsData_Item.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Item : public ACsData
{
	GENERATED_UCLASS_BODY()

// UI
#pragma region

#pragma endregion UI

// World
#pragma region

	virtual class UStaticMesh* GetWorldStaticMesh();
	virtual class USkeletalMesh* GetWorldSkeletalMesh();
	virtual TArray<class UMaterialInstanceConstant*>* GetWorldMaterials();

#pragma endregion World
};