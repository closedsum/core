// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Data/CsLibrary_Manager_Data.h"
#include "CsCore.h"

// Managers
#include "Managers/Data/CsManager_Data.h"

UCsLibrary_Manager_Data::UCsLibrary_Manager_Data(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Get
#pragma region

	// DataTable
#pragma region

UDataTable* UCsLibrary_Manager_Data::GetDataTable(const UObject* WorldContextObject, const FName& TableName)
{
#if WITH_EDITOR
	if (UCsManager_Data* Manager = UCsManager_Data::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Data* Manager = UCsManager_Data::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetDataTable(TableName);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Data::GetDataTable: No Manager Data of type UCsManager_Data was created."));
	}
	return nullptr;
}

UDataTable* UCsLibrary_Manager_Data::GetDataTableByPath(const UObject* WorldContextObject, const FSoftObjectPath& Path)
{
#if WITH_EDITOR
	if (UCsManager_Data* Manager = UCsManager_Data::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Data* Manager = UCsManager_Data::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetDataTable(Path);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Data::GetDataTableByPath: No Manager Data of type UCsManager_Data was created."));
	}
	return nullptr;
}

UDataTable* UCsLibrary_Manager_Data::GetDataTableBySoftObject(const UObject* WorldContextObject, TSoftObjectPtr<UDataTable> SoftObject)
{
#if WITH_EDITOR
	if (UCsManager_Data* Manager = UCsManager_Data::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Data* Manager = UCsManager_Data::Get())
#endif // #if WITH_EDITOR
	{
		return Manager->GetDataTable(SoftObject);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_Data::GetDataTableByPath: No Manager Data of type UCsManager_Data was created."));
	}
	return nullptr;
}

#pragma endregion DataTable

#pragma endregion Get