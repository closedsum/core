// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsUserInterfaceRegisterDetailCustomization.h"
#include "CsUIEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// WidgetActpr
#include "DetailCustomizations/EnumStruct/ECsWidgetActorCustomization.h"
#include "DetailCustomizations/EnumStruct/ECsWidgetActorClassCustomization.h"

void FCsUserInterfaceRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// ECsWidgetActor
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWidgetActor", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWidgetActorCustomization::MakeInstance));
		// ECsWidgetActorCLass
		PropertyModule.RegisterCustomPropertyTypeLayout("ECsWidgetActorClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWidgetActorClassCustomization::MakeInstance));
	}
}