// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Level.h"
#include "CsCore.h"
#include "Types/CsTypes.h"

UCsData_Level::UCsData_Level(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString UCsData_Level::GetMapName() { return NCsCached::Str::Empty; }
TArray<FName>* UCsData_Level::GetShortCodes() { return nullptr; }