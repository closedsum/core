// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsRegisterDetailCustomization.h"
#include "CsEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// CVar
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarLogCustomization.h"
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarToggleCustomization.h"
#include "DetailCustomizations/EnumStruct/CVar/ECsCVarDrawCustomization.h"
		// Asset
#include "DetailCustomizations/EnumStruct/ECsAssetTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsLoadAssetsTypeCustomization.h"
		// Input
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionMapCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsGameEventCustomization.h"
#include "DetailCustomizations/EnumStruct/Input/ECsGestureTypeCustomization.h"
		// Process
#include "DetailCustomizations/EnumStruct/ECsProcessCustomization.h"
		// FX
#include "DetailCustomizations/EnumStruct/FX/ECsFXCustomization.h"
		// Damage
#include "DetailCustomizations/EnumStruct/Damage/ECsDamageTypeCustomization.h"
#include "DetailCustomizations/EnumStruct/Damage/ECsHitTypeCustomization.h"
		// Sound
#include "DetailCustomizations/EnumStruct/Sound/ECsSoundCustomization.h"
		// Sense
#include "DetailCustomizations/EnumStruct/Sense/ECsSenseActorTypeCustomization.h"

#include "DetailCustomizations/EnumStruct/ECsSurfaceTypeCustomization.h"

void FCsRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// CVar
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCVarLog", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCVarLogCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCVarToggle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCVarToggleCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsCVarDraw", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsCVarDrawCustomization::MakeInstance));
		// Asset
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsAssetType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsAssetTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsLoadAssetsType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsLoadAssetsTypeCustomization::MakeInstance));
		// Input
		{
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsInputAction", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInputActionCustomization::MakeInstance));
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsInputActionMap", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsInputActionMapCustomization::MakeInstance));
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsGameEvent", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGameEventCustomization::MakeInstance));
			// GestureType
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsGestureType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsGestureTypeCustomization::MakeInstance));
		}
		// SurfaceType
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSurfaceType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSurfaceTypeCustomization::MakeInstance));
		// Process
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsProcess", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsProcessCustomization::MakeInstance));
		// FX
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsFX", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsFXCustomization::MakeInstance));
		// Damage
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsDamageType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsDamageTypeCustomization::MakeInstance));
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsHitType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsHitTypeCustomization::MakeInstance));
		// Sound
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSound", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSoundCustomization::MakeInstance));
		// Sense
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsSenseActorType", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsSenseActorTypeCustomization::MakeInstance));
	}
}