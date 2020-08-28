// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsUserInterfaceRegisterDetailCustomization.h"
#include "CsUIEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// WidgetActpr
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorCustomization.h"
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorClassCustomization.h"
		// UserWidget
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetClassCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledClassCustomization.h"

void FCsUserInterfaceRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	// EnumStruct
	{
		// WidgetActor
		{
			// ECsWidgetActor
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsWidgetActor", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWidgetActorCustomization::MakeInstance));
			// ECsWidgetActorCLass
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsWidgetActorClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsWidgetActorClassCustomization::MakeInstance));
		}
		// UserWidget
		{
			// ECsUserWidget
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsUserWidget", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsUserWidgetCustomization::MakeInstance));
			// ECsUserWidgetCLass
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsUserWidgetClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsUserWidgetClassCustomization::MakeInstance));
			// ECsUserWidgetPooled
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsUserWidgetPooled", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsUserWidgetPooledCustomization::MakeInstance));
			// ECsUserWidgetPooledCLass
			PropertyModule.RegisterCustomPropertyTypeLayout("ECsUserWidgetPooledClass", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FECsUserWidgetPooledClassCustomization::MakeInstance));
		}
	}
}