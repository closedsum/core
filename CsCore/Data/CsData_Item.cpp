// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Item.h"
#include "CsCore.h"

ACsData_Item::ACsData_Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Members
#pragma region

UScriptStruct* ACsData_Item::GetMembersScriptStruct() { return nullptr; }

#pragma endregion Members

// Consume
#pragma region

bool ACsData_Item::OnConsumeSpawnActor() { return false; }

#pragma endregion Consume