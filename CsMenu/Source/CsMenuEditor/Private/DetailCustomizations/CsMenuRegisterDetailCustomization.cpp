// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/CsMenuRegisterDetailCustomization.h"
#include "CsMenuEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Menu
#include "DetailCustomizations/EnumStruct/Menu/ECsMenuCustomization.h"
#include "DetailCustomizations/EnumStruct/Menu/ECsMenuEventCustomization.h"

void FCsMenuRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		// Menu
		{
			// ECsMenu
			CS_TEMP_REGISTER(ECsMenu);
			// ECsMenuEvent
			CS_TEMP_REGISTER(ECsMenuEvent);
		}
	}
#undef CS_TEMP_REGISTER
}