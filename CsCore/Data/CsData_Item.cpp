// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Item.h"
#include "CsCore.h"

ACsData_Item::ACsData_Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// World
#pragma region

UStaticMesh* ACsData_Item::GetWorldStaticMesh() { return nullptr; }
USkeletalMesh* ACsData_Item::GetWorldSkeletalMesh() { return nullptr; }
TArray<UMaterialInstanceConstant*>* ACsData_Item::GetWorldMaterials() { return nullptr; }

#pragma endregion World