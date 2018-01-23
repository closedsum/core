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

// UI
#pragma region

FString ACsData_Item::GetDisplayName() { return ECsCachedString::Str::INVALID; }

#pragma endregion UI

// Drop
#pragma region

bool ACsData_Item::OnDropSpawnActor() { return false; }
FName ACsData_Item::GetSpawnedActorDataShortCode() { return NAME_None; }

#pragma endregion Drop