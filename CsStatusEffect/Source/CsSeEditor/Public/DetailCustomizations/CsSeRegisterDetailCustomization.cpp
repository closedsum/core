// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsSeRegisterDetailCustomization.h"
#include "CsSeEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// StatusEffect
#include "DetailCustomizations/EnumStruct/ECsStatusEffectCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsStatusEffectTriggerConditionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsStatusEffectEventCustomization.h"
	// Data
#include "DetailCustomizations/Data/CsData_ECsStatusEffectCustomization.h"
#include "DetailCustomizations/Data/CsData_StatusEffectPtrCustomization.h"

void FCsSeRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	#define CS_TEMP_REGISTER(EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(#EnumName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##EnumName##Customization::MakeInstance)))

	// EnumStruct
	{
		// ECsStatusEffect
		CS_TEMP_REGISTER(ECsStatusEffect);
		// ECsStatusEffectTriggerCondition
		CS_TEMP_REGISTER(ECsStatusEffectTriggerCondition);
		// ECsStatusEffectEvent
		CS_TEMP_REGISTER(ECsStatusEffectEvent);
	}
	// Data
	{
		// CsData_ECsStatusEffect
		CS_TEMP_REGISTER(CsData_ECsStatusEffect);
		// CsData_StatusEffectPtr
		CS_TEMP_REGISTER(CsData_StatusEffectPtr);
	}

	#undef CS_TEMP_REGISTER
}