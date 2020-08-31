// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_DataRootSet.h"

// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

UObject* FCsLibrary_DataRootSet::GetImplChecked(const FString& Context, UObject* ContextRoot)
{
	checkf(ContextRoot, TEXT("%s: ContextRoot is NULL."), *Context);

	UWorld* World				  = ContextRoot->GetWorld();
	UCsManager_Data* Manager_Data = UCsManager_Data::Get(World->GetGameInstance());
	UObject* DataRootSetImpl	  = Manager_Data->DataRootSet.GetObject();

	checkf(DataRootSetImpl, TEXT("%s: DataRootSetImpl is NULL. Failed to find DataRootSet."), *Context);

	return DataRootSetImpl;
}