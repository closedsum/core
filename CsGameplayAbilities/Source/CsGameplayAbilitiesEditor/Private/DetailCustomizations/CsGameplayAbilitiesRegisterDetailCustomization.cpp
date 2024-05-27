// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/CsGameplayAbilitiesRegisterDetailCustomization.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// Asset
#include "DetailCustomizations/Asset/CsAttributeSetCustomization.h"
#include "DetailCustomizations/Asset/CsGameplayAbilityCustomization.h"
#include "DetailCustomizations/Asset/CsGameplayEffectCustomization.h"

void FCsGameplayAbilitiesRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// Asset
	{
		// CsAttributeSet
		CS_TEMP_REGISTER(CsAttributeSet);
		// CsGameplayAbility
		CS_TEMP_REGISTER(CsGameplayAbility);
		// CsGameplayEffect
		CS_TEMP_REGISTER(CsGameplayEffect);
	}

	#undef CS_TEMP_REGISTER
}