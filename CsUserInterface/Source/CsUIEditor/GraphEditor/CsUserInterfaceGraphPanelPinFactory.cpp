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

	// WidgetActor
	{
		// FECsWidgetActor
		if (DoesPinUseScriptStruct<FECsWidgetActor>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWidgetActor, InPin); }
		// FECsWidgetActorClass
		if (DoesPinUseScriptStruct<FECsWidgetActorClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWidgetActorClass, InPin); }
	}
	// UserWidget
	{
		// FECsUserWidget
		if (DoesPinUseScriptStruct<FECsUserWidget>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsUserWidget, InPin); }
		// FECsUserWidgetClass
		if (DoesPinUseScriptStruct<FECsUserWidgetClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsUserWidgetClass, InPin); }
		// FECsUserWidgetPooled
		if (DoesPinUseScriptStruct<FECsUserWidgetPooled>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsUserWidgetPooled, InPin); }
		// FECsUserWidgetPooledClass
		if (DoesPinUseScriptStruct<FECsUserWidgetPooledClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsUserWidgetPooledClass, InPin); }
	}
	return nullptr;
}

