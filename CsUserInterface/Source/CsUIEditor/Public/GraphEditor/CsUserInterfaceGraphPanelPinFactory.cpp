// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsUserInterfaceGraphPanelPinFactory.h"
#include "CsUIEditor.h"

// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"

// EnumStructs
	// WidgetActor
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActor.h"
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActorClass.h"
	// UserWidget
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidget.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetClass.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooled.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooledClass.h"

TSharedPtr<SGraphPin> FCsUserInterfacePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName, EnumShortName) if (DoesPinUseScriptStruct<EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumShortName, InPin); }

	// WidgetActor
	{
		// FECsWidgetActor
		CS_TEMP_CREATE(FECsWidgetActor, ECsWidgetActor)
		// FECsWidgetActorClass
		CS_TEMP_CREATE(FECsWidgetActorClass, ECsWidgetActorClass)
	}
	// UserWidget
	{
		// FECsUserWidget
		CS_TEMP_CREATE(FECsUserWidget, ECsUserWidget)
		// FECsUserWidgetClass
		CS_TEMP_CREATE(FECsUserWidgetClass, ECsUserWidgetClass)
		// FECsUserWidgetPooled
		CS_TEMP_CREATE(FECsUserWidgetPooled, ECsUserWidgetPooled)
		// FECsUserWidgetPooledClass
		CS_TEMP_CREATE(FECsUserWidgetPooledClass, ECsUserWidgetPooledClass)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

