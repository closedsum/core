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
		// Update
#include "DetailCustomizations/EnumStruct/Update/ECsUpdateGroupCustomization.h"
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
#define CS_TEMP_REGISTER(EnumShortName, EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(EnumShortName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(EnumName##Customization::MakeInstance)))

		// CVar
		CS_TEMP_REGISTER("ECsCVarLog", FECsCVarLog);
		CS_TEMP_REGISTER("ECsCVarToggle", FECsCVarToggle);
		CS_TEMP_REGISTER("ECsCVarDraw", FECsCVarDraw);
		// Asset
		CS_TEMP_REGISTER("ECsAssetType", FECsAssetType);
		CS_TEMP_REGISTER("ECsLoadAssetsType", FECsLoadAssetsType);
		// Update
		CS_TEMP_REGISTER("ECsUpdateGroup", FECsUpdateGroup);
		// Input
		{
			CS_TEMP_REGISTER("ECsInputAction", FECsInputAction);
			CS_TEMP_REGISTER("ECsInputActionMap", FECsInputActionMap);
			CS_TEMP_REGISTER("ECsGameEvent", FECsGameEvent);
			// GestureType
			CS_TEMP_REGISTER("ECsGestureType", FECsGestureType);
		}
		// SurfaceType
		CS_TEMP_REGISTER("ECsSurfaceType", FECsSurfaceType);
		// Process
		CS_TEMP_REGISTER("ECsProcess", FECsProcess);
		// FX
		CS_TEMP_REGISTER("ECsFX", FECsFX);
		// Damage
		CS_TEMP_REGISTER("ECsDamageType", FECsDamageType);
		CS_TEMP_REGISTER("ECsHitType", FECsHitType);
		// Sound
		CS_TEMP_REGISTER("ECsSound", FECsSound);
		// Sense
		CS_TEMP_REGISTER("ECsSenseActorType", FECsSenseActorType);

#undef CS_TEMP_REGISTER
	}
}