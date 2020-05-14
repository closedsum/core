// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsTdGraphPanelPinFactory.h"
#include "CsTdEditor.h"

// Types
#include "Managers/Creep/CsTdTypes_Creep.h"

//#include "SlateBasics.h"

// EnumStructs
	// Creep
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsTdCreep.h"

TSharedPtr<SGraphPin> FCsTdPanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Creep
	{
		// FECsTdCreep
		if (DoesPinUseScriptStruct<FECsTdCreep>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsTdCreep, InPin); }
	}
	return nullptr;
}

