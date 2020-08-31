// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "CsUI.h"

// Settings
#include "Settings/CsUserInterfaceSettings.h"
// Data
#include "Data/CsUIGetDataRootSet.h"
// Utility
#include "Utility/CsUILog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsUIPopulateEnumMapFromSettings.h"

// UserWidget
#pragma region

namespace NCsUserWidget
{
	namespace Str
	{
		const FString UserWidget = TEXT("UserWidget");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsUserInterfaceSettings, EMCsUserWidget, FECsUserWidget>(Context, Str::UserWidget, &FCsUILog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsUserWidget>(Context, ContextRoot, DataRootSet->UserWidgets, Str::UserWidget, &FCsUILog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsUserWidget::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsUserWidget_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsUserWidget_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion UserWidget

// UserWidgetClass
#pragma region

namespace NCsUserWidgetClass
{
	namespace Str
	{
		const FString UserWidgetClass = TEXT("UserWidgetClass");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsUserWidgetClass>(Context, ContextRoot, DataRootSet->UserWidgets, Str::UserWidgetClass, &FCsUILog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsUserWidgetClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion UserWidgetClass

// UserWidgetPooled
#pragma region

namespace NCsUserWidgetPooled
{
	namespace Str
	{
		const FString UserWidgetPooled = TEXT("UserWidgetPooled");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsUserInterfaceSettings, EMCsUserWidgetPooled, FECsUserWidgetPooled>(Context, Str::UserWidgetPooled, &FCsUILog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsUserWidgetPooled>(Context, ContextRoot, DataRootSet->UserWidgetPooleds, Str::UserWidgetPooled, &FCsUILog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsUserWidgetPooled::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsUserWidgetPooled_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsUserWidgetPooled_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion UserWidgetPooled

// UserWidgetPooledClass
#pragma region

namespace NCsUserWidgetPooledClass
{
	namespace Str
	{
		const FString UserWidgetPooledClass = TEXT("UserWidgetPooledClass");
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsUserWidgetPooledClass>(Context, ContextRoot, DataRootSet->UserWidgetPooledClasses, Str::UserWidgetPooledClass, &FCsUILog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsUserWidgetPooledClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion UserWidgetPooledClass