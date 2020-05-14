// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsTdRegisterDetailCustomization.h"
#include "CsTdEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Creep
#include "DetailCustomizations/EnumStruct/ECsTdCreepCustomization.h"

void FCsTdRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// Creep
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsTdCreep", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsTdCreepCustomization::MakeInstance));
	}
}