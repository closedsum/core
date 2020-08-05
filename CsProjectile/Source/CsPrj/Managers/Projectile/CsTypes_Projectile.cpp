// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "CsPrj.h"

// Data
#include "Data/CsPrjGetDataRootSet.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsProjectileSettings.h"
// Managers
#include "Managers/Data/CsManager_Data.h"
// Game
#include "Engine/GameInstance.h"

// ProjectileRelevance
#pragma region

namespace NCsProjectileRelevance
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealVisible, "Real Visible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealInvisible, "Real Invisible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileRelevance, Fake);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, ECsProjectileRelevance_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileRelevance_MAX;
}

#pragma endregion ProjectileRelevance

// Projectile
#pragma region

namespace NCsProjectile
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
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
		EMCsProjectile::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

		// Enum Settings
		if (ModuleSettings->ECsProjectile_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			const TArray<FCsSettings_Enum>& Enums = ModuleSettings->GetSettingsEnum<FECsProjectile>();
			const FString EnumSettingsPath		  = ModuleSettings->GetSettingsEnumPath<FECsProjectile>();

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

					checkf(!EMCsProjectile::Get().IsValidEnum(Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsProjectile::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsProjectile::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsProjectile::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCsPrj, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}

		// DataTable
		if (ModuleSettings->ECsProjectile_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			for (const FCsProjectileSettings_DataTable_Projectiles& Projectiles : DataRootSet.Projectiles)
			{
				// Check DataTable of Projectiles
				TSoftObjectPtr<UDataTable> DT_SoftObject = Projectiles.Projectiles;

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

								checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Projectile Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

								checkf(!EMCsProjectile::Get().IsValidEnum(Name), TEXT("%s: Projectile (Name): %s already exists (declared in native)."), *Context, *Name);

								if (!DisplayName.IsEmpty())
								{
									checkf(!EMCsProjectile::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: Projectile (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

									EMCsProjectile::Get().Create(Name, DisplayName, true);
								}
								else
								{
									EMCsProjectile::Get().Create(Name, true);
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
		}
	}
}

#pragma endregion Projectile

// ProjectileClass
#pragma region

namespace NCsProjectileClass
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
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
	}
}

#pragma endregion ProjectileClass

// ProjectileState
#pragma region

namespace NCsProjectileState
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, Active);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, DeActivating);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, InActive);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileState, ECsProjectileState_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileState_MAX;
}

#pragma endregion ProjectileState

// ProjectileDeActivate
#pragma region

namespace NCsProjectileDeActivate
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Collision);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Movement);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Mesh);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileDeActivate, ECsProjectileDeActivate_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileDeActivate_MAX;
}

#pragma endregion ProjectileDeActivate

// ProjectileMovement
#pragma region

namespace NCsProjectileMovement
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Simulated);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Function);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovement, ECsProjectileMovement_MAX,"MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovement_MAX;
}

#pragma endregion ProjectileMovement

// ProjectileMovementFunctionType
#pragma region

namespace NCsProjectileMovementFunctionType
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Linear);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Sine);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovementFunctionType, ECsProjectileMovementFunctionType_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovementFunctionType_MAX;
}

#pragma endregion ProjectileMovementFunctionType

// ProjectileData
#pragma region

namespace NCsProjectileData
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, Projectile, "ICsData_Projectile");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileCollision, "ICsData_ProjectileCollision");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileStaticMeshVisual, "ICsData_ProjectileStaticMeshVisual");
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsProjectileData, ProjectileTrailVisual, "ICsData_ProjectileTrailVisual");
}

#pragma endregion ProjectileData