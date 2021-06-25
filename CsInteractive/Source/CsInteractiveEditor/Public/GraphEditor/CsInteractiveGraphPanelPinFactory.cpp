// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsInteractiveGraphPanelPinFactory.h"
#include "CsInteractiveEditor.h"

// Types
//#include "Managers/Menu/CsTypes_Menu.h"

// EnumStructs
	// Interaction
//#include "GraphEditor/EnumStruct/Interaction/SCsGraphPin_ECsInteraction.h"

TSharedPtr<SGraphPin> FCsInteractivePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Interaction
	{
		// FECsInteraction
		//CS_TEMP_CREATE(ECsInteraction)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

