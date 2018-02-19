// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Item.h"
#include "CsCore.h"

ACsData_Item::ACsData_Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsItemType ACsData_Item::GetBaseItemType() { return BaseItemType; }

// Stats
#pragma region

TArray<FName>* ACsData_Item::GetContents() { return nullptr; }
bool ACsData_Item::GetIsIngredient() { return false; }

#pragma endregion Stats

// Members
#pragma region

UScriptStruct* ACsData_Item::GetMembersScriptStruct() { return nullptr; }

TArray<FCsItemMemberDescription>* ACsData_Item::GetMembers() { return nullptr; }

#pragma endregion Members

// UI
#pragma region

FString ACsData_Item::GetDisplayName() { return ECsCachedString::Str::INVALID; }
UMaterialInstanceConstant* ACsData_Item::GetMaterial() { return nullptr; }
FCsUint8MatrixDimension* ACsData_Item::GetDimension() { return nullptr; }
int32 ACsData_Item::GetCapacity() { return 0; }

#pragma endregion UI

// Drop
#pragma region

bool ACsData_Item::OnDropSpawnActor() { return false; }
FName ACsData_Item::GetSpawnedActorDataShortCode() { return NAME_None; }

#pragma endregion Drop

// Consume
#pragma region

bool ACsData_Item::OnConsumeDropContents() { return false; }

#pragma endregion Consume