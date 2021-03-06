// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#include "CsUI.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
#include "Settings/CsUserInterfaceSettings.h"
// Data
#include "Data/CsUIGetDataRootSet.h"
// Utility
#include "Utility/CsUILog.h"
#include "Utility/CsPopulateEnumMapFromSettings.h"
#include "Utility/CsUIPopulateEnumMapFromSettings.h"

// WidgetActor
#pragma region

namespace NCsWidgetActor
{
	namespace Str
	{
		const FString WidgetActor = TEXT("WidgetActor");
	}

	void FromEnumSettings(const FString& Context)
	{
		FCsPopulateEnumMapFromSettings::FromEnumSettings<UCsUserInterfaceSettings, EMCsWidgetActor, FECsWidgetActor>(Context, Str::WidgetActor, &NCsUI::FLog::Warning);
	}

	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsWidgetActor>(Context, ContextRoot, DataRootSet->WidgetActors, Str::WidgetActor, &NCsUI::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsWidgetActor::Get().ClearUserDefinedEnums();

		// Enum Settings
		if (ModuleSettings->ECsWidgetActor_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
		{
			FromEnumSettings(Context);
		}

		// DataTable
		if (ModuleSettings->ECsWidgetActor_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
		{
			FromDataTable(Context, ContextRoot);
		}
	}
}

#pragma endregion WidgetActor

// WidgetActorClass
#pragma region

namespace NCsWidgetActorClass
{
	namespace Str
	{
		const FString WidgetActorClass = TEXT("WidgetActorClass");
	}

	const FCsUIDataRootSet* GetDataRootSet(const FString& Context, UObject* ContextRoot)
	{
		return FCsPopulateEnumMapFromSettings::GetDataRootSet<FCsUIDataRootSet, ICsUIGetDataRootSet, &ICsUIGetDataRootSet::GetCsUIDataRootSet>(Context, ContextRoot);
	}
	void FromDataTable(const FString& Context, UObject* ContextRoot)
	{
		const FCsUIDataRootSet* DataRootSet = FCsUIPopulateEnumMapFromSettings::GetDataRootSet(Context, ContextRoot);

		if (!DataRootSet)
			return;

		FCsPopulateEnumMapFromSettings::FromDataTable<EMCsWidgetActorClass>(Context, ContextRoot, DataRootSet->WidgetActorClasses, Str::WidgetActorClass, &NCsUI::FLog::Warning);
	}

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

		checkf(Settings, TEXT("%s: Failed to file settings of type: UCsDeveloperSettings."), *Context);

		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("%s: Failed to find settings of type: UCsUserInterfaceSettings."), *Context);

		EMCsWidgetActorClass::Get().ClearUserDefinedEnums();

		FromDataTable(Context, ContextRoot);
	}
}

#pragma endregion WidgetActorClass

// WidgetActorDeallocateMethod
#pragma region

namespace NCsWidgetActorDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsWidgetActorDeallocateMethod EnumMapType;

		CSUI_API CS_ADD_TO_ENUM_MAP(Complete);
		CSUI_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSUI_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsWidgetActorDeallocateMethod_MAX, "MAX");
	}

	CSUI_API const uint8 MAX = (uint8)Type::ECsWidgetActorDeallocateMethod_MAX;
}

#pragma endregion WidgetActorDeallocateMethod