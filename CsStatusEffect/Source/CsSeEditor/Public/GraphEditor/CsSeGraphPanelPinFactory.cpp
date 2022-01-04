// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsSeGraphPanelPinFactory.h"
#include "CsSeEditor.h"

// Types
#include "CsTypes_StatusEffect.h"
#include "Trigger/CsTypes_StatusEffect_Trigger.h"
// EnumStructs
	// Status Effect
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectTriggerCondition.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectEvent.h"

TSharedPtr<SGraphPin> FCsSePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/
	// Status Effect
	{
		// FECsStatusEffectTriggerCondition
		if (DoesPinUseScriptStruct<FECsStatusEffectTriggerCondition>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsStatusEffectTriggerCondition, InPin); }
		// FECsStatusEffectEvent
		if (DoesPinUseScriptStruct<FECsStatusEffectEvent>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsStatusEffectEvent, InPin); }
	}
	return nullptr;
}

