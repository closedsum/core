// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsProjectileRegisterDetailCustomization.h"
#include "CsPrjEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Projectile
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsProjectileClassCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsProjectileDataCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsProjectilePayloadCustomization.h"

void FCsProjectileRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// ECsProjectile
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProjectile", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProjectileCustomization::MakeInstance));
		// ECsProjectileCLass
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProjectileClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProjectileClassCustomization::MakeInstance));
		// ECsProjectileData
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProjectileData", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProjectileDataCustomization::MakeInstance));
		// ECsProjectilePayload
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProjectilePayload", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProjectilePayloadCustomization::MakeInstance));
	}
}