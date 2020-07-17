// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsSeRegisterDetailCustomization.h"
#include "CsSeEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// StatusEffect
#include "DetailCustomizations/EnumStruct/ECsStatusEffectTriggerConditionCustomization.h"

void FCsSeRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// ECsStatusEffectTriggerCondition
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsStatusEffectTriggerCondition", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsStatusEffectTriggerConditionCustomization::MakeInstance));
	}
}