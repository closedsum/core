// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Level.h"
#include "CsCore.h"
#include "Types/CsTypes.h"

ACsData_Level::ACsData_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString ACsData_Level::GetMapName() { return ECsCached::Str::Empty; }
TArray<FName>* ACsData_Level::GetShortCodes() { return nullptr; }