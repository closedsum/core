// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsSeGraphPanelPinFactory.h"
#include "CsSeEditor.h"

// Types
#include "Types/CsTypes_StatusEffect.h"
#include "Trigger/CsTypes_StatusEffect_Trigger.h"
// EnumStructs
	// Status Effect
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffect.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectTriggerCondition.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectEvent.h"

TSharedPtr<SGraphPin> FCsSePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Status Effect
	{
		// ECsStatusEffect
		CS_TEMP_CREATE(ECsStatusEffect)
		// FECsStatusEffectTriggerCondition
		CS_TEMP_CREATE(ECsStatusEffectTriggerCondition)
		// FECsStatusEffectEvent
		CS_TEMP_CREATE(ECsStatusEffectEvent)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

