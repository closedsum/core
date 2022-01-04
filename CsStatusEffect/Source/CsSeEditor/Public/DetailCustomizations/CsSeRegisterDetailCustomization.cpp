// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

void FCsSeRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
#define CS_TEMP_REGISTER(EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(#EnumName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##EnumName##Customization::MakeInstance)))

		// StatusEffect
		{
			// ECsStatusEffect
			CS_TEMP_REGISTER(ECsStatusEffect);
			// ECsStatusEffectTriggerCondition
			CS_TEMP_REGISTER(ECsStatusEffectTriggerCondition);
			// ECsStatusEffectEvent
			CS_TEMP_REGISTER(ECsStatusEffectEvent);
		}

#undef CS_TEMP_REGISTER
	}
}