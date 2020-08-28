// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "CsUI.h"

// Settings
#include "Settings/CsDeveloperSettings.h"

// UserWidget
#pragma region

namespace NCsUserWidget
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
	/*
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsFX::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

				if (Enums.Num() > CS_EMPTY)
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsFX::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsFX::Get().Create(Name, true);
						}
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
				}
			}

			// DataTable
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
			{
				for (TSoftObjectPtr<UDataTable>& SoftObjectPtr : Settings->FXs)
				{
					// Check DataTable of Projectiles
					TSoftObjectPtr<UDataTable> DT_SoftObject = SoftObjectPtr;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct	  = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
						{
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

									checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != FX Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

									checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

									if (!DisplayName.IsEmpty())
									{
										checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

										EMCsFX::Get().Create(Name, DisplayName, true);
									}
									else
									{
										EMCsFX::Get().Create(Name, true);
									}
								}
							}
							else
							{
								UE_LOG(LogCs, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
		*/
	}
}

#pragma endregion UserWidget

// UserWidgetClass
#pragma region

namespace NCsUserWidgetClass
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
	/*
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

		// Get DataRootSet for Projectiles
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

		ICsPrjGetDataRootSet* GetDataRootSet = Cast<ICsPrjGetDataRootSet>(DataRootSetImpl);

		if (!GetDataRootSet)
			return;

		const FCsPrjDataRootSet& DataRootSet = GetDataRootSet->GetCsPrjDataRootSet();

#if WITH_EDITOR
		EMCsProjectileClass::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsProjectileClass>();
			const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsProjectileClass>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCsPrj, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsProjectileClass::Get().IsValidEnum(Name), TEXT("%s: ProjectileClass (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsProjectileClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: ProjectileClass (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsProjectileClass::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsProjectileClass::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}

		// DataTable
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			// Check DataTable of Projectiles
			TSoftObjectPtr<UDataTable> DT_SoftObject = DataRootSet.ProjectileClasses;

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
				const UScriptStruct* RowStruct	  = DT->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
				{
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

							checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != ProjectileClass Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

							checkf(!EMCsProjectileClass::Get().IsValidEnum(Name), TEXT("%s: ProjectileClass (Name): %s already exists (declared in native)."), *Context, *Name);

							if (!DisplayName.IsEmpty())
							{
								checkf(!EMCsProjectileClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: ProjectileClass (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

								EMCsProjectileClass::Get().Create(Name, DisplayName, true);
							}
							else
							{
								EMCsProjectileClass::Get().Create(Name, true);
							}
						}
					}
					else
					{
						UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
					}
				}
			}
			else
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
			}
		}
		*/
	}
}

#pragma endregion UserWidgetClass

// UserWidgetPooled
#pragma region

namespace NCsUserWidgetPooled
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
	/*
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsFX::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

				if (Enums.Num() > CS_EMPTY)
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsFX::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsFX::Get().Create(Name, true);
						}
					}
				}
				else
				{
					UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
				}
			}

			// DataTable
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
			{
				for (TSoftObjectPtr<UDataTable>& SoftObjectPtr : Settings->FXs)
				{
					// Check DataTable of Projectiles
					TSoftObjectPtr<UDataTable> DT_SoftObject = SoftObjectPtr;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct	  = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
						{
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

									checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != FX Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

									checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

									if (!DisplayName.IsEmpty())
									{
										checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

										EMCsFX::Get().Create(Name, DisplayName, true);
									}
									else
									{
										EMCsFX::Get().Create(Name, true);
									}
								}
							}
							else
							{
								UE_LOG(LogCs, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
		*/
	}
}

#pragma endregion UserWidgetPooled

// UserWidgetPooledClass
#pragma region

namespace NCsUserWidgetPooledClass
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
	/*
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsProjectileSettings* ModuleSettings = GetMutableDefault<UCsProjectileSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsProjectileSettings."), *Context);

		// Get DataRootSet for Projectiles
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

		ICsPrjGetDataRootSet* GetDataRootSet = Cast<ICsPrjGetDataRootSet>(DataRootSetImpl);

		if (!GetDataRootSet)
			return;

		const FCsPrjDataRootSet& DataRootSet = GetDataRootSet->GetCsPrjDataRootSet();

#if WITH_EDITOR
		EMCsProjectileClass::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsProjectileClass>();
			const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsProjectileClass>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCsPrj, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsProjectileClass::Get().IsValidEnum(Name), TEXT("%s: ProjectileClass (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsProjectileClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: ProjectileClass (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsProjectileClass::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsProjectileClass::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}

		// DataTable
		if (ModuleSettings->ECsProjectileClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			// Check DataTable of Projectiles
			TSoftObjectPtr<UDataTable> DT_SoftObject = DataRootSet.ProjectileClasses;

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
				const UScriptStruct* RowStruct	  = DT->GetRowStruct();
				const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
				{
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

							checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != ProjectileClass Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

							checkf(!EMCsProjectileClass::Get().IsValidEnum(Name), TEXT("%s: ProjectileClass (Name): %s already exists (declared in native)."), *Context, *Name);

							if (!DisplayName.IsEmpty())
							{
								checkf(!EMCsProjectileClass::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: ProjectileClass (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

								EMCsProjectileClass::Get().Create(Name, DisplayName, true);
							}
							else
							{
								EMCsProjectileClass::Get().Create(Name, true);
							}
						}
					}
					else
					{
						UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
					}
				}
			}
			else
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
			}
		}
		*/
	}
}

#pragma endregion UserWidgetPooledClass