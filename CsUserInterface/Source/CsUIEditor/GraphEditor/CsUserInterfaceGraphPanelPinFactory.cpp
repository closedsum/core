// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsUserInterfaceGraphPanelPinFactory.h"
#include "CsUIEditor.h"

// Types
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"

// EnumStructs
	// Projectile
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWidgetActor.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWidgetActorClass.h"

TSharedPtr<SGraphPin> FCsUserInterfacePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Projectile
	{
		// FECsWidgetActor
		if (DoesPinUseScriptStruct<FECsWidgetActor>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWidgetActor, InPin); }
		// FECsWidgetActorClass
		if (DoesPinUseScriptStruct<FECsWidgetActorClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWidgetActorClass, InPin); }
	}
	return nullptr;
}

