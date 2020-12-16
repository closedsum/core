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
#define CS_TEMP_REGISTER(EnumShortName, EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(EnumShortName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(EnumName##Customization::MakeInstance)))

		// WidgetActor
		{
			// ECsWidgetActor
			CS_TEMP_REGISTER("ECsWidgetActor", FECsWidgetActor);
			// ECsWidgetActorCLass
			CS_TEMP_REGISTER("ECsWidgetActorClass", FECsWidgetActorClass);
		}
		// UserWidget
		{
			// ECsUserWidget
			CS_TEMP_REGISTER("ECsUserWidget", FECsUserWidget);
			// ECsUserWidgetCLass
			CS_TEMP_REGISTER("ECsUserWidgetClass", FECsUserWidgetClass);
			// ECsUserWidgetPooled
			CS_TEMP_REGISTER("ECsUserWidgetPooled", FECsUserWidgetPooled);
			// ECsUserWidgetPooledClass
			CS_TEMP_REGISTER("ECsUserWidgetPooledClass", FECsUserWidgetPooledClass);
		}

#undef CS_TEMP_REGISTER
	}
}