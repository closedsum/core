// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsBeamGraphPanelPinFactory.h"
#include "CsBeamEditor.h"

// Types
#include "Types/CsTypes_Beam.h"

// EnumStructs
	// Beam
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsBeam.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsBeamClass.h"

TSharedPtr<SGraphPin> FCsBeamPanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Beam
	{
		// FECsBeam
		if (DoesPinUseScriptStruct<FECsBeam>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsBeam, InPin); }
		// FECsBeamClass
		if (DoesPinUseScriptStruct<FECsBeamClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsBeamClass, InPin); }
	}
	return nullptr;
}

