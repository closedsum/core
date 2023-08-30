// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Utility/CsPopulateEnumMapFromSettings.h"

// Library
#include "Managers/Data/CsLibrary_Manager_Data.h"
	// Settings
#include "Settings/CsLibrary_DeveloperSettings.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
// Engine
#include "Engine/DataTable.h"

const FName FCsPopulateEnumMapFromSettings::NamePropertyName = FName("Name");
const FName FCsPopulateEnumMapFromSettings::DisplayNamePropertyName = FName("DisplayName");

UObject* FCsPopulateEnumMapFromSettings::GetDataRootSetImpl(const FString& Context, UObject* ContextRoot)
{
	// Check context to determine how to load DataRootSetImpl
	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	if (GameInstanceLibrary::IsSafe(ContextRoot))
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataRootSetImplChecked(Context, ContextRoot);
	}
	else
	{
		typedef NCsCore::NSettings::FLibrary SettingsLibrary;

		TSoftClassPtr<UObject> SoftObject = SettingsLibrary::GetDataRootSetChecked(Context);
		UClass* Class					  = SoftObject.LoadSynchronous();
		return Class->GetDefaultObject();
	}
	return nullptr;
}

UDataTable* FCsPopulateEnumMapFromSettings::GetDataTable(const FString& Context, const UObject* ContextRoot, const TSoftObjectPtr<UDataTable>& DT_SoftObject)
{
	// Check context to determine how to load the DataTable
	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	if (GameInstanceLibrary::IsSafe(ContextRoot))
	{
		typedef NCsData::NManager::FLibrary DataManagerLibrary;

		return DataManagerLibrary::GetDataTableChecked(Context, ContextRoot, DT_SoftObject);
	}
	else
	{
		return DT_SoftObject.LoadSynchronous();
	}
	return nullptr;
}