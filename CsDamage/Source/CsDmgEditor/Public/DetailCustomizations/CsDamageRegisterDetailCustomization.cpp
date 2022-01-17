// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsDamageRegisterDetailCustomization.h"
#include "CsDmgEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Damage
#include "DetailCustomizations/EnumStruct/ECsDamageTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsDamageDataCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsHitTypeCustomization.h"

void FCsDamageRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
#define CS_TEMP_REGISTER(EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(#EnumName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##EnumName##Customization::MakeInstance)))

		// Damage
		CS_TEMP_REGISTER(ECsDamageType);
		CS_TEMP_REGISTER(ECsDamageData);
		CS_TEMP_REGISTER(ECsHitType);

#undef CS_TEMP_REGISTER
	}
}