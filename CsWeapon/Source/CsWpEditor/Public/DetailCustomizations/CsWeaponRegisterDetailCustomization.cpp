// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsWeaponRegisterDetailCustomization.h"
#include "CsWpEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
#include "DetailCustomizations/EnumStruct/ECsWeaponCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponClassCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimBlueprintCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponBlendSpaceCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponFireModeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponGripCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponOwnerCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSlotCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSoundCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponStateCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponDataCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponModifierCustomization.h"
	// Data
#include "DetailCustomizations/Data/CsData_ECsWeaponCustomization.h"
#include "DetailCustomizations/Data/CsData_WeaponPtrCustomization.h"

void FCsWeaponRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// EnumStruct
	{
		// ECsWeapon
		CS_TEMP_REGISTER(ECsWeapon);
		// ECsWeaponClass
		CS_TEMP_REGISTER(ECsWeaponClass);
		// ECsWeaponAnim
		CS_TEMP_REGISTER(ECsWeaponAnim);
		// ECsWeaponAnimBlueprint
		CS_TEMP_REGISTER(ECsWeaponAnimBlueprint);
		// ECsWeaponBlendSpace
		CS_TEMP_REGISTER(ECsWeaponBlendSpace);
		// ECsWeaponFireMode
		CS_TEMP_REGISTER(ECsWeaponFireMode);
		// ECsWeaponGrip
		CS_TEMP_REGISTER(ECsWeaponGrip);
		// ECsWeaponOwner
		CS_TEMP_REGISTER(ECsWeaponOwner);
		// ECsWeaponSlot
		CS_TEMP_REGISTER(ECsWeaponSlot);
		// ECsWeaponSound
		CS_TEMP_REGISTER(ECsWeaponSound);
		// ECsWeaponState
		CS_TEMP_REGISTER(ECsWeaponState);
		// ECsWeaponData
		CS_TEMP_REGISTER(ECsWeaponData);
		// ECsWeaponModifier
		CS_TEMP_REGISTER(ECsWeaponModifier);
	}
	// Data
	{
		// CsData_ECsWeapon
		CS_TEMP_REGISTER(CsData_ECsWeapon);
		// CsData_WeaponPtr
		CS_TEMP_REGISTER(CsData_WeaponPtr);
	}

	#undef CS_TEMP_REGISTER
}