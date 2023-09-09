// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

#define PayloadType FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsPopulateEnumMapFromSettings::FromDataTable(const FString& Context, PayloadType& Payload)
{
#undef PayloadType
	UDataTable* DataTable		= Payload.DataTable ? Payload.DataTable : GetDataTable(Context, Payload.ContextRoot, Payload.DataTableSoftObject);
	const FString& EnumName		= Payload.EnumName;
	void(*Log)(const FString&)  = Payload.Log;

	const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	{
		// Set if the Row Struct has the properties Name and DisplayName

		FStrProperty* NameProperty		  = CastField<FStrProperty>(RowStruct->FindPropertyByName(NamePropertyName));
		NameProperty					  = NameProperty ? NameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(NamePropertyName));
		FStrProperty* DisplayNameProperty = CastField<FStrProperty>(RowStruct->FindPropertyByName(DisplayNamePropertyName));
		DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(DisplayNamePropertyName));

		if (NameProperty &&
			DisplayNameProperty)
		{
			if (RowMap.Num() == CS_EMPTY)
			{
				CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
			}

			const FName Name_NewRow = FName("NewRow");

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName = Pair.Key;
				const uint8* RowPtr  = Pair.Value;

				const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
				const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

				// If Making a New Row, skip
				if (RowName == Name_NewRow &&
					Name.IsEmpty() &&
					DisplayName.IsEmpty())
				{
					continue;
				}

				checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);

				checkf(!Payload.IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

				if (!DisplayName.IsEmpty())
				{
					checkf(!Payload.IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

					Payload.CreateCustom(Name, DisplayName, true);
				}
				else
				{
					Payload.Create(Name, true);
				}
			}
		}
		else
		{
			CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()))));
		}
	}
}

#define PayloadType FCsPopulateEnumMapFromSettings::FFromDataTable::FPayload
void FCsPopulateEnumMapFromSettings::FromDataTable_RowAsName(const FString& Context, PayloadType Payload)
{
#undef PayloadType
	UDataTable* DataTable		= Payload.DataTable ? Payload.DataTable : GetDataTable(Context, Payload.ContextRoot, Payload.DataTableSoftObject);
	const FString& EnumName		= Payload.EnumName;
	void(*Log)(const FString&)  = Payload.Log;

	const UScriptStruct* RowStruct	  = DataTable->GetRowStruct();
	const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();
	{
		if (RowMap.Num() == CS_EMPTY)
		{
			CS_NON_SHIPPING_EXPR(Log(FString::Printf(TEXT("%s: No entries found for %s."), *Context, *(DataTable->GetName()))));
		}

		const FName Name_NewRow = FName("NewRow");
		FString Name;
		FString DisplayName;

		for (const TPair<FName, uint8*>& Pair : RowMap)
		{
			const FName& RowName = Pair.Key;
			const uint8* RowPtr  = Pair.Value;

			Name		= RowName.ToString();
			DisplayName = Name;

			// If Making a New Row, skip
			if (RowName == Name_NewRow &&
				Name.IsEmpty() &&
				DisplayName.IsEmpty())
			{
				continue;
			}

			checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);

			checkf(!Payload.IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

			if (!DisplayName.IsEmpty())
			{
				checkf(!Payload.IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

				Payload.CreateCustom(Name, DisplayName, true);
			}
			else
			{
				Payload.Create(Name, true);
			}
		}
	}
}