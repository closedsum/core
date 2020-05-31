// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsProjectileRegisterDetailCustomization.h"
#include "CsPrjEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Projectile
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"

void FCsProjectileRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// Projectile
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProjectile", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProjectileCustomization::MakeInstance));
	}
}