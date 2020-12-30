// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data.h"

// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"
// World
#include "Engine/World.h"

namespace NCsData
{
	UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		UGameInstance* GameInstance = World->GetGameInstance();

		checkf(GameInstance, TEXT("%s: Failed to get GameInstace from World: %s."), *Context, *(World->GetName()));

		return GameInstance;
	}

	IData* FLibrary::GetDataChecked(const FString& Context, UObject* WorldContext, const FName& DataName)
	{
		ICsData* UData = UCsManager_Data::Get(GetContextRootChecked(Context, WorldContext))->GetDataChecked(Context, DataName);
		IData* Data	   = UData->_getIData();

		checkf(Data, TEXT("%s: Failed to get data of type: IData from Object: %s with Class: %s."), *Context, *(Data->_getUObject()->GetName()), *(Data->_getUObject()->GetClass()->GetName()));

		return Data;
	}
}