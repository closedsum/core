// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Settings/Tool/CsSettingsTool.h"
#include "CsEditor.h"

// Types
#include "Types/CsTypes_Macro.h"

#include "ISettingsModule.h"
#include "Framework/Docking/TabManager.h"

namespace NCsSettings
{
	namespace NTool
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSettings::FTool, ToggleProjectSettings);
			}

			namespace Name
			{
				const FName ProjectSettings = FName("ProjectSettings");
			}
		}
	}

	#define USING_NS_CACHED using namespace NCsSettings::NTool::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsSettings::NTool::NCached; \
		const FString& Context = Str::##__FunctionName

	void FTool::ToggleProjectSettings()
	{
		SET_CONTEXT(ToggleProjectSettings);

		FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
		TSharedPtr<SDockTab> DockTab = FGlobalTabmanager::Get()->TryInvokeTab(Name::ProjectSettings);
		TSharedPtr<FTabManager> TabManager = DockTab->GetTabManagerPtr();
		FGlobalTabmanager::Get()->DrawAttentionToTabManager(TabManager.ToSharedRef());
		DockTab->RequestCloseTab();
	}

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
}