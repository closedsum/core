// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsInteractiveRegisterDetailCustomization.h"
#include "CsInteractiveEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Menu
#include "DetailCustomizations/EnumStruct/Interaction/ECsInteractionCustomization.h"

void FCsInteractiveRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
#define CS_TEMP_REGISTER(EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(#EnumName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##EnumName##Customization::MakeInstance)))

		// Interaction
		{
			// ECsInteraction
			CS_TEMP_REGISTER(ECsInteraction);
		}

#undef CS_TEMP_REGISTER
	}
}