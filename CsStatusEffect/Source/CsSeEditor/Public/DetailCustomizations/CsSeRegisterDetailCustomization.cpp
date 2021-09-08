// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsSeRegisterDetailCustomization.h"
#include "CsSeEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// StatusEffect
#include "DetailCustomizations/EnumStruct/ECsStatusEffectTriggerConditionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsStatusEffectEventCustomization.h"

void FCsSeRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// ECsStatusEffectTriggerCondition
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsStatusEffectTriggerCondition", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsStatusEffectTriggerConditionCustomization::MakeInstance));
		// ECsStatusEffectEvent
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsStatusEffectEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsStatusEffectEventCustomization::MakeInstance));
	}
}