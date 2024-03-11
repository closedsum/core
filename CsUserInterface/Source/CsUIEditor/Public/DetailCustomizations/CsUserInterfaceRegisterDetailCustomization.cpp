// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/CsUserInterfaceRegisterDetailCustomization.h"
#include "CsUIEditor.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

// DetailCustomizations
	// Asset
		// UserWidget
#include "DetailCustomizations/Asset/CsUserWidgetCustomization.h"
#include "DetailCustomizations/Asset/CsUserWidgetPtrCustomization.h"
	// EnumStruct
		// WidgetActpr
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorCustomization.h"
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorClassCustomization.h"
		// UserWidget
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetClassCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPooledClassCustomization.h"
#include "DetailCustomizations/EnumStruct/UserWidget/ECsUserWidgetPayloadCustomization.h"

void FCsUserInterfaceRegisterDetailCustomization::Register()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

#define CS_TEMP_REGISTER(StructName) PropertyModule.RegisterCustomPropertyTypeLayout(#StructName, FOnGetPropertyTypeCustomizationInstance::CreateStatic(&(F##StructName##Customization::MakeInstance)))

	// Asset
	{
		// FCsUserWidget
		CS_TEMP_REGISTER(CsUserWidget);
		// FCsUserWidgetPtr
		CS_TEMP_REGISTER(CsUserWidgetPtr);
	}
	// EnumStruct
	{
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
			// ECsUserWidgetPayload
			CS_TEMP_REGISTER(ECsUserWidgetPayload);
		}
	}
#undef CS_TEMP_REGISTER
}