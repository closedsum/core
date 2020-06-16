// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsWp.h"

// Settings
#include "Settings/CsWeaponSettings.h"

// Weapon
#pragma region

namespace NCsWeapon
{
	// TODO: Need to Pass in Root so we can get DataTable from Manager_Data and NOT do a LoadSynchronous
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>())
		{
#if WITH_EDITOR
			EMCsWeapon::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Enum Settings
			if (Settings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsWeapon>();
				const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsWeapon>();

				if (Enums.Num() > CS_EMPTY)
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCsWp, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsWeapon::Get().IsValidEnum(Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsWeapon::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

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
			if (Settings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
			{
				for (FCsWeaponSettings_DataTable_Weapons& Weapons : Settings->Weapons)
				{
					// Check DataTable of Weapons
					TSoftObjectPtr<UDataTable> DT_SoftObject = Weapons.Weapons;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct    = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();

						// See if the Row Struct derives from FCsWeaponEntry
						if (RowStruct->IsChildOf(FCsWeaponEntry::StaticStruct()))
						{
							for (const TPair<FName, uint8*>& Pair : RowMap)
							{
								const FName& Name			= Pair.Key;
								const FCsWeaponEntry* Entry = reinterpret_cast<const FCsWeaponEntry*>(Pair.Value);

								checkf(Entry->Name.Compare(Name.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Weapon Name (%s != %s)."), *Context, *(Entry->Name), *(Name.ToString()));

								checkf(!EMCsWeapon::Get().IsValidEnum(Entry->Name), TEXT("%s: Weapon (Name): %s already exists (declared in native)."), *Context, *(Entry->Name));

								if (!Entry->DisplayName.IsEmpty())
								{
									checkf(!EMCsWeapon::Get().IsValidEnumByDisplayName(Entry->DisplayName), TEXT("%s: Weapon (DisplayName): %s already exists (declared in native)."), *Context, *(Entry->DisplayName));

									EMCsWeapon::Get().Create(Entry->Name, Entry->DisplayName, true);
								}
								else
								{
									EMCsWeapon::Get().Create(Entry->Name, true);
								}
							}
						}
						// Set if the Row Struct has the properties Name and DisplayName
						else
						{
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
					}
					else
					{
						UE_LOG(LogCsWp, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
	}
}

#pragma endregion Weapon

// WeaponData
#pragma region

namespace NCsWeaponData
{
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, Weapon, "ICsData_Weapon");
	CSWP_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsWeaponData, ProjectileWeapon, "ICsData_ProjectileWeapon");
}

#pragma endregion WeaponData