// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/CsBeamRegisterDetailCustomization.h"
#include "CsBeamEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Beam
#include "DetailCustomizations/EnumStruct/ECsBeamCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsBeamClassCustomization.h"

void FCsBeamRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// ECsBeam
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsBeam", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsBeamCustomization::MakeInstance));
		// ECsBeamCLass
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsBeamClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsBeamClassCustomization::MakeInstance));
	}
}