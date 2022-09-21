// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsDamageRegisterDetailCustomization.h"
#include "CsDmgEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
#include "DetailCustomizations/EnumStruct/ECsDamageTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsDamageDataCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsHitTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsDamageModifierCustomization.h"
	// Data
#include "DetailCustomizations/Data/CsData_DamagePtrCustomization.h"
#include "DetailCustomizations/Data/CsData_ECsDamageDataCustomization.h"

void FCsDamageRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		CS_TEMP_REGISTER(ECsDamageType);
		CS_TEMP_REGISTER(ECsDamageData);
		CS_TEMP_REGISTER(ECsHitType);
		CS_TEMP_REGISTER(ECsDamageModifier);
	}
	// Data
	{
		CS_TEMP_REGISTER(CsData_DamagePtr);
		CS_TEMP_REGISTER(CsData_ECsDamageData);
	}

#undef CS_TEMP_REGISTER
}