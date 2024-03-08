// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsUserInterfaceGraphPanelPinFactory.h"
#include "CsUIEditor.h"

// Types
#include "Managers/Menu/CsTypes_Menu.h"
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Payload/CsTypes_Payload_UserWidget.h"

// EnumStructs
	// Menu
#include "GraphEditor/EnumStruct/Menu/SCsGraphPin_ECsMenu.h"
#include "GraphEditor/EnumStruct/Menu/SCsGraphPin_ECsMenuEvent.h"
	// WidgetActor
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActor.h"
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActorClass.h"
	// UserWidget
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidget.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetClass.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooled.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooledClass.h"
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPayload.h"

TSharedPtr<SGraphPin> FCsUserInterfacePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Menu
	{
		// FECsMenu
		CS_TEMP_CREATE(ECsMenu)
		// FECsMenuEvent
		CS_TEMP_CREATE(ECsMenuEvent)
	}
	// WidgetActor
	{
		// FECsWidgetActor
		CS_TEMP_CREATE(ECsWidgetActor)
		// FECsWidgetActorClass
		CS_TEMP_CREATE(ECsWidgetActorClass)
	}
	// UserWidget
	{
		// FECsUserWidget
		CS_TEMP_CREATE(ECsUserWidget)
		// FECsUserWidgetClass
		CS_TEMP_CREATE(ECsUserWidgetClass)
		// FECsUserWidgetPooled
		CS_TEMP_CREATE(ECsUserWidgetPooled)
		// FECsUserWidgetPooledClass
		CS_TEMP_CREATE(ECsUserWidgetPooledClass)
		// FECsUserWidgetPayload
		CS_TEMP_CREATE(ECsUserWidgetPayload)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

