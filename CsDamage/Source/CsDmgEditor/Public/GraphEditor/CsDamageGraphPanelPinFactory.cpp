// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsDamageGraphPanelPinFactory.h"
#include "CsDmgEditor.h"

// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"

// EnumStructs
	// Damage
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsDamageType.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsDamageData.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsHitType.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsDamageModifier.h"

TSharedPtr<SGraphPin> FCsDamagePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Damage
	{
		// FECsDamageType
		CS_TEMP_CREATE(ECsDamageType)
		// FECsDamageData
		CS_TEMP_CREATE(ECsDamageData)
		// FECsHitType
		CS_TEMP_CREATE(ECsHitType)
		// FECsDamageModifier
		CS_TEMP_CREATE(ECsDamageModifier)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

