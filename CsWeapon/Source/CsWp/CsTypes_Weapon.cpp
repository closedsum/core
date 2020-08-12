// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsWp.h"

// Data
#include "Data/CsWpGetDataRootSet.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"

// Weapon
#pragma region

namespace NCsWeapon
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

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
			return;

		ICsWpGetDataRootSet* GetDataRootSet = Cast<ICsWpGetDataRootSet>(DataRootSetImpl);

		if (!GetDataRootSet)
			return;

		const FCsWpDataRootSet& DataRootSet = GetDataRootSet->GetCsWpDataRootSet();

#if WITH_EDITOR
		EMCsWeapon::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsWeapon>();
			const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsWeapon>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCsWp, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsWeapon::Get().IsValidEnum(Name), TEXT("%s: Weapon (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsWeapon::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Weapon (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsWeapon::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsWeapon::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}

		// DataTable
		if (ModuleSettings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			for (const FCsWeaponSettings_DataTable_Weapons& Weapons : DataRootSet.Weapons)
			{
				// Check DataTable of Weapons
				TSoftObjectPtr<UDataTable> DT_SoftObject = Weapons.Weapons;

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
					const UScriptStruct* RowStruct    = DT->GetRowStruct();
					const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

					// Set if the Row Struct has the properties Name and DisplayName
	
					UStrProperty* NameProperty		  = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("Name")));
					NameProperty					  = NameProperty ? NameProperty : Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
					UStrProperty* DisplayNameProperty = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("DisplayName"))); 
					DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty: Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

					if (NameProperty &&
						DisplayNameProperty)
					{
						for (const TPair<FName, uint8*>& Pair : RowMap)
						{
							const FName& RowName = Pair.Key;
							const uint8* RowPtr = Pair.Value;

							const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
							const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

							checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Weapon Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

							checkf(!EMCsWeapon::Get().IsValidEnum(Name), TEXT("%s: Weapon (Name): %s already exists (declared in native)."), *Context, *Name);

							if (!DisplayName.IsEmpty())
							{
								checkf(!EMCsWeapon::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Weapon (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

								EMCsWeapon::Get().Create(Name, DisplayName, true);
							}
							else
							{
								EMCsWeapon::Get().Create(Name, true);
							}
						}
					}
					else
					{
						UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
					}
				}
				else
				{
					UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
				}
			}
		}
	}
}

#pragma endregion Weapon

// WeaponClass
#pragma region

namespace NCsWeaponClass
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

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
			return;

		ICsWpGetDataRootSet* GetDataRootSet = Cast<ICsWpGetDataRootSet>(DataRootSetImpl);

		if (!GetDataRootSet)
			return;

		const FCsWpDataRootSet& DataRootSet = GetDataRootSet->GetCsWpDataRootSet();

#if WITH_EDITOR
		EMCsWeapon::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsWeaponClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsWeaponClass>();
			const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsWeaponClass>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCsWp, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsWeaponClass::Get().IsValidEnum(Name), TEXT("%s: Weapon Class (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsWeaponClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Weapon Class (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsWeaponClass::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsWeaponClass::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}

		// DataTable
		if (ModuleSettings->ECsWeaponClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			// Check DataTable of WeaponClasses
			TSoftObjectPtr<UDataTable> DT_SoftObject = DataRootSet.WeaponClasses;

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
				const UScriptStruct* RowStruct    = DT->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

				// Set if the Row Struct has the properties Name and DisplayName
	
				UStrProperty* NameProperty		  = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("Name")));
				NameProperty					  = NameProperty ? NameProperty : Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
				UStrProperty* DisplayNameProperty = Cast<UStrProperty>(RowStruct->FindPropertyByName(FName("DisplayName"))); 
				DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty: Cast<UStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

				if (NameProperty &&
					DisplayNameProperty)
				{
					for (const TPair<FName, uint8*>& Pair : RowMap)
					{
						const FName& RowName = Pair.Key;
						const uint8* RowPtr = Pair.Value;

						const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
						const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

						checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Weapon Class Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

						checkf(!EMCsWeaponClass::Get().IsValidEnum(Name), TEXT("%s: Weapon Class (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!DisplayName.IsEmpty())
						{
							checkf(!EMCsWeaponClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Weapon Class (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsWeaponClass::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsWeaponClass::Get().Create(Name, true);
						}
					}
				}
				else
				{
					UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
			}
		}
	}
}

#pragma endregion WeaponClass

// WeaponState
#pragma region

namespace NCsWeaponState
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

#if WITH_EDITOR
		EMCsWeaponState::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsWeaponState>();
		const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsWeaponState>();

		if (Enums.Num() > CS_EMPTY)
		{
			for (const FCsSettings_Enum& Enum : Enums)
			{
				const FString& Name		   = Enum.Name;
				const FString& DisplayName = Enum.DisplayName;

				if (Name.IsEmpty())
				{
					UE_LOG(LogCsWp, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
					return;
				}

				checkf(!EMCsWeaponState::Get().IsValidEnum(Name), TEXT("%s: Weapon State (Name): %s already exists (declared in native)."), *Context, *Name);

				if (!Enum.DisplayName.IsEmpty())
				{
					checkf(!EMCsWeaponState::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Weapon State (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

					EMCsWeaponState::Get().Create(Name, DisplayName, true);
				}
				else
				{
					EMCsWeaponState::Get().Create(Name, true);
				}
			}
		}
		else
		{
			UE_LOG(LogCsWp, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
		}
	}
}

#pragma endregion WeaponState

// WeaponData
#pragma region

namespace NCsWeaponData
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, Weapon, "ICsData_Weapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, ProjectileWeapon, "ICsData_ProjectileWeapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, ProjectileWeaponSound, "ICsData_ProjectileWeaponSound");
}

#pragma endregion WeaponData