// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
#include "DetailCustomizations/EnumStruct/ECsProjectileModifierCustomization.h"
	// Data
#include "DetailCustomizations/Data/CsData_ProjectilePtrCustomization.h"
#include "DetailCustomizations/Data/CsData_ECsProjectileCustomization.h"

void FCsProjectileRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		// ECsProjectile
		CS_TEMP_REGISTER(ECsProjectile);
		// ECsProjectileClass
		CS_TEMP_REGISTER(ECsProjectileClass);
		// ECsProjectileData
		CS_TEMP_REGISTER(ECsProjectileData);
		// ECsProjectilePayload
		CS_TEMP_REGISTER(ECsProjectilePayload);
		// ECsProjectileModifier
		CS_TEMP_REGISTER(ECsProjectileModifier);
	}
	// CsData_ProjectilePtr
	CS_TEMP_REGISTER(CsData_ProjectilePtr);
	// CsData_ECsProjectile
	CS_TEMP_REGISTER(CsData_ECsProjectile);

	#undef CS_TEMP_REGISTER
}