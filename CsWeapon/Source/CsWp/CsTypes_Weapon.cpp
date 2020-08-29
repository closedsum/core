// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_Weapon.h"
#include "CsWp.h"

// Data
#include "Data/CsWpGetDataRootSet.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsWeaponSettings.h"
// Utility
#include "Utility/CsWpLog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsWpPopulateEnumMapFromSettings.h"

// Weapon
#pragma region

namespace NCsWeapon
{
	namespace Str
	{
		const FString Weapon = TEXT("Weapon");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsWeaponSettings, EMCsWeapon, FECsWeapon>(Context, Str::Weapon, &FCsWpLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsWpDataRootSet* DataRootSet = FCsWpPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		for (const FCsWeaponSettings_DataTable_Weapons& Weapons : DataRootSet->Weapons)
		{
			FCsPopulateEnumMapFromSettings::FromDataTable<EMCsWeapon>(Context, ContextRoot, Weapons.Weapons, Str::Weapon, &FCsWpLog::Warning);
		}
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

		EMCsWeapon::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsWeapon_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion Weapon

// WeaponClass
#pragma region

namespace NCsWeaponClass
{
	namespace Str
	{
		const FString WeaponClass = TEXT("WeaponClass");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsWeaponSettings, EMCsWeaponClass, FECsWeaponClass>(Context, Str::WeaponClass, &FCsWpLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsWpDataRootSet* DataRootSet = FCsWpPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsWeapon>(Context, ContextRoot, DataRootSet->WeaponClasses, Str::WeaponClass, &FCsWpLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

		EMCsWeaponClass::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsWeaponClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsWeaponClass_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion WeaponClass

// WeaponState
#pragma region

namespace NCsWeaponState
{
	namespace Str
	{
		const FString WeaponState = TEXT("WeaponState");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsWeaponSettings, EMCsWeaponState, FECsWeaponState>(Context, Str::WeaponState, &FCsWpLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsWeaponSettings* ModuleSettings = GetMutableDefault<UCsWeaponSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsWeaponSettings."), *Context);

		EMCsWeaponState::Get().ClearUserDefinedEnums();

		FromEnumSettings(Context);
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