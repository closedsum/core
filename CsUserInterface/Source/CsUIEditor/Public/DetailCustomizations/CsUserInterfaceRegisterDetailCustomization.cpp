// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/CsUserInterfaceRegisterDetailCustomization.h"
#include "CsUIEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// EnumStruct
		// Menu
#include "DetailCustomizations/EnumStruct/Menu/ECsMenuCustomization.h"
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
#define CS_TEMP_REGISTER(EnumName) PropertyModule.RegisterCustomPropertyTypeLayout(#EnumName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##EnumName##Customization::MakeInstance)))

		// Menu
		{
			// ECsMenu
			CS_TEMP_REGISTER(ECsWidgetActor);
		}
		// WidgetActor
		{
			// ECsWidgetActor
			CS_TEMP_REGISTER(ECsWidgetActor);
			// ECsWidgetActorCLass
			CS_TEMP_REGISTER(ECsWidgetActorClass);
		}
		// UserWidget
		{
			// ECsUserWidget
			CS_TEMP_REGISTER(ECsUserWidget);
			// ECsUserWidgetCLass
			CS_TEMP_REGISTER(ECsUserWidgetClass);
			// ECsUserWidgetPooled
			CS_TEMP_REGISTER(ECsUserWidgetPooled);
			// ECsUserWidgetPooledClass
			CS_TEMP_REGISTER(ECsUserWidgetPooledClass);
		}

#undef CS_TEMP_REGISTER
	}
}