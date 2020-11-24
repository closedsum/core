// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Settings
#include "Settings/CsDeveloperSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"

#pragma once

// NOTE: Should only be included in .h files

class UObject;
class UDataTable;

/**
* Utility class to help populate a EnumStructMap. Called internally by the 
* namespace associated with the appropriate EnumStruct.
*/
struct CSCORE_API FCsPopulateEnumMapFromSettings final
{
private:

	static const FName NamePropertyName;
	static const FName DisplayNamePropertyName;

public:

	/**
	*
	*
	* @param Context
	* @param ContextRoot
	* return
	*/
	template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType&(GetDataRootSetType::*GetDataRootSetFn)() const>
	static const DataRootSetType* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		// Get DataRootSet
		UObject* DataRootSetImpl = nullptr;

		// Check context to determine how to load DataRootSetImpl
		if (ContextRoot &&
			Cast<UGameInstance>(ContextRoot))
		{
			DataRootSetImpl = UCsManager_Data::Get(ContextRoot)->DataRootSet.GetObject();
		}
		else
		{
			TSoftClassPtr<UObject> SoftObject = Settings->DataRootSet;
			UClass* Class					  = SoftObject.LoadSynchronous();
			DataRootSetImpl					  = Class->GetDefaultObject();
		}

		if (!DataRootSetImpl)
			return nullptr;

		GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(DataRootSetImpl);

		if (!GetDataRootSet)
			return nullptr;

		const DataRootSetType& DataRootSet = (GetDataRootSet->*GetDataRootSetFn)();

		return &DataRootSet;
	}

	/**
	*
	*
	* @param Context
	* @param ContextRoot
	* return
	*/
	template<typename DataRootSetType, typename GetDataRootSetType, const DataRootSetType& (GetDataRootSetType::* GetDataRootSetFn)() const>
	static const DataRootSetType* GetDataRootSet(const FString& Context, UObject* ContextRoot, UObject*& OutDataRootSetImpl)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		// Get DataRootSet
		OutDataRootSetImpl = nullptr;

		// Check context to determine how to load DataRootSetImpl
		if (ContextRoot &&
			Cast<UGameInstance>(ContextRoot))
		{
			OutDataRootSetImpl = UCsManager_Data::Get(ContextRoot)->DataRootSet.GetObject();
		}
		else
		{
			TSoftClassPtr<UObject> SoftObject = Settings->DataRootSet;
			UClass* Class					  = SoftObject.LoadSynchronous();
			OutDataRootSetImpl				  = Class->GetDefaultObject();
		}

		if (!OutDataRootSetImpl)
			return nullptr;

		GetDataRootSetType* GetDataRootSet = Cast<GetDataRootSetType>(OutDataRootSetImpl);

		if (!GetDataRootSet)
			return nullptr;

		const DataRootSetType& DataRootSet = (GetDataRootSet->*GetDataRootSetFn)();

		return &DataRootSet;
	}

	/**
	*
	*
	* @param Context
	* @param EnumName
	* @param Log
	*/
	template<typename ModuleSettingsType, typename EnumMap, typename EnumType>
	static void FromEnumSettings(const FString& Context, const FString& EnumName, void(*Log)(const FString&))
	{
		ModuleSettingsType* ModuleSettings = GetMutableDefault<ModuleSettingsType>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: ModuleSettingsType."), *Context);

		const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<EnumType>();
		const FString& EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<EnumType>();

		if (Enums.Num() > CS_EMPTY)
		{
			for (const FCsSettings_Enum& Enum : Enums)
			{
				const FString& Name		   = Enum.Name;
				const FString& DisplayName = Enum.DisplayName;

				if (Name.IsEmpty())
				{
#if !UE_BUILD_SHIPPING
					Log(FString::Printf(TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath));
#endif // #if !UE_BUILD_SHIPPING
					return;
				}

				checkf(!EnumMap::Get().IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

				if (!Enum.DisplayName.IsEmpty())
				{
					checkf(!EnumMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

					EnumMap::Get().Create(Name, DisplayName, true);
				}
				else
				{
					EnumMap::Get().Create(Name, true);
				}
			}
		}
		else
		{
#if !UE_BUILD_SHIPPING
			Log(FString::Printf(TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath));
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	/**
	*/
	template<typename EnumMap>
	static void FromDataTable(const FString& Context, UObject* ContextRoot, UDataTable* DataTable, const FString& EnumName, void(*Log)(const FString&))
	{
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
				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& RowName = Pair.Key;
					const uint8* RowPtr  = Pair.Value;

					const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
					const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

					checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != %s Name (%s != %s)."), *Context, *EnumName, *(RowName.ToString()), *Name);

					checkf(!EnumMap::Get().IsValidEnum(Name), TEXT("%s: %s (Name): %s already exists (declared in native)."), *Context, *EnumName, *Name);

					if (!DisplayName.IsEmpty())
					{
						checkf(!EnumMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: %s (DisplayName): %s already exists (declared in native)."), *Context, *EnumName, *DisplayName);

						EnumMap::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EnumMap::Get().Create(Name, true);
					}
				}
			}
			else
			{
#if !UE_BUILD_SHIPPING
				Log(FString::Printf(TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName())));
#endif // #if !UE_BUILD_SHIPPING
			}
		}
	}

	/**
	*/
	template<typename EnumMap>
	static void FromDataTable(const FString& Context, UObject* ContextRoot, TSoftObjectPtr<UDataTable> DT_SoftObject, const FString& EnumName, void(*Log)(const FString&))
	{
		UDataTable* DT = nullptr;

		// Check context to determine how to load the DataTable
		if (ContextRoot &&
			Cast<UGameInstance>(ContextRoot))
		{
			DT = UCsManager_Data::Get(ContextRoot)->GetDataTable(DT_SoftObject);
		}
		else
		{
			DT = DT_SoftObject.LoadSynchronous();
		}

		if (DT)
		{
			FromDataTable<EnumMap>(Context, ContextRoot, DT, EnumName, Log);
		}
		else
		{
#if !UE_BUILD_SHIPPING
			Log(FString::Printf(TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString())));
#endif // #if !UE_BUILD_SHIPPING
		}
	}
};