// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
#include "CsEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Asset
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
		// Input
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsGameEventCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsGestureTypeCustomization.h"
		// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"
		// Damage
#include "DetailCustomizations/EnumStruct/Damage/ECsDamageTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/Damage/ECsHitTypeCustomization.h"
		// Sound
#include "DetailCustomizations/EnumStruct/ECsSoundTypeCustomization.h"
		// Sense
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

void FCsRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// Asset
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsAssetType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsAssetTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsLoadAssetsType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsLoadAssetsTypeCustomization::MakeInstance));
		// Input
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsInputAction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInputActionCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsGameEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGameEventCustomization::MakeInstance));
		// SurfaceType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSurfaceType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSurfaceTypeCustomization::MakeInstance));
		// GestureType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsGestureType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGestureTypeCustomization::MakeInstance));
		// Process
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProcess", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProcessCustomization::MakeInstance));
		// Damage
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsDamageType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsDamageTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsHitType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsHitTypeCustomization::MakeInstance));
		// Sound
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSoundType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSoundTypeCustomization::MakeInstance));
		// Sense
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSenseActorType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSenseActorTypeCustomization::MakeInstance));
	}
}