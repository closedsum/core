// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/CsPlatformProcessRegisterDetailCustomization.h"
#include "CsPlatformProcessEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"

void FCsPlatformProcessRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		// Process
		CS_TEMP_REGISTER(ECsProcess);
	}
#undef CS_TEMP_REGISTER
}