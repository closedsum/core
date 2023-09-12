// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsSenseGraphPanelPinFactory.h"
#include "CsSenseEditor.h"

#include "Types/CsTypes_Sense.h"

#include "SlateBasics.h"

// EnumStructs
	// Sense
#include "GraphEditor/EnumStruct/Sense/SCsGraphPin_ECsSenseActorType.h"

TSharedPtr<class SGraphPin> FCsSensePanelGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Sense
	{
		// FECsSenseActorType
		CS_TEMP_CREATE(ECsSenseActorType)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

