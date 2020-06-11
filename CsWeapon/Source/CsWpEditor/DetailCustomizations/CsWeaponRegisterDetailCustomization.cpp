// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsWeaponRegisterDetailCustomization.h"
#include "CsWpEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponAnimBlueprintCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponBlendSpaceCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponFireModeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponGripCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponOwnerCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSlotCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponSoundCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponStateCustomization.h"

void FCsWeaponRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// FECsWeaponAnim
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponAnim", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponAnimCustomization::MakeInstance));
		// FECsWeaponAnimBlueprint
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponAnimBlueprint", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponAnimBlueprintCustomization::MakeInstance));
		// FECsWeaponBlendSpace
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponBlendSpace", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponBlendSpaceCustomization::MakeInstance));
		// FECsWeaponFireMode
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponFireMode", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponFireModeCustomization::MakeInstance));
		// FECsWeaponGrip
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponGrip", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponGripCustomization::MakeInstance));
		// FECsWeaponOwner
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponOwner", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponOwnerCustomization::MakeInstance));
		// FECsWeaponSlot
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponSlot", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponSlotCustomization::MakeInstance));
		// FECsWeaponSound
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponSound", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponSoundCustomization::MakeInstance));
		// FECsWeaponState
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWeaponState", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWeaponStateCustomization::MakeInstance));
	}
}