// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsMenuGraphPanelPinFactory.h"
#include "CsMenuEditor.h"

// Types
#include "Managers/Menu/CsTypes_Menu.h"

// EnumStructs
	// Menu
#include "GraphEditor/EnumStruct/Menu/SCsGraphPin_ECsMenu.h"
#include "GraphEditor/EnumStruct/Menu/SCsGraphPin_ECsMenuEvent.h"

TSharedPtr<SGraphPin> FCsMenuPanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
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

#undef CS_TEMP_CREATE

	return nullptr;
}

