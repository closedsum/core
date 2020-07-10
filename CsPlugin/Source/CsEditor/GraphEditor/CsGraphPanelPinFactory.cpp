// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsGraphPanelPinFactory.h"
#include "CsEditor.h"

// Types
#include "Types/CsTypes.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/FX/CsTypes_FX.h"
//#include "Types/CsTypes_Character.h"
//#include "Types/CsTypes_Item.h"
//#include "Types/CsTypes_Recipe.h"
#include "Types/CsTypes_Damage.h"
#include "Managers/Sound/CsTypes_Sound.h"
//#include "Types/CsTypes_Interactive.h"
//#include "AI/CsTypes_AI.h"
#include "Managers/Sense/CsTypes_Sense.h"

#include "SlateBasics.h"

// EnumStructs
	// Asset
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsAssetType.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsLoadAssetsType.h"
	// Input
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsInputAction.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsGameEvent.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsSurfaceType.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsGestureType.h"
	// FX
#include "GraphEditor/EnumStruct/FX/SCsGraphPin_ECsFX.h"
	// Character
//#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnim.h"
//#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimVariation.h"
//#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimBlueprint.h"
//#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterBlendSpace.h"
	// Process
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProcess.h"
	// Item
//#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemType.h"
//#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemOwner.h"
//#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemInteraction.h"
	// Crafting
//#include "GraphEditor/EnumStruct/Crafting/SCsGraphPin_ECsRecipeType.h"
	// Damage
#include "GraphEditor/EnumStruct/Damage/SCsGraphPin_ECsDamageType.h"
#include "GraphEditor/EnumStruct/Damage/SCsGraphPin_ECsHitType.h"
	// Interactive
//#include "GraphEditor/EnumStruct/Interactive/SCsGraphPin_ECsInteractiveType.h"
	// Sound
#include "GraphEditor/EnumStruct/Sound/SCsGraphPin_ECsSound.h"
	// AI
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIType.h"
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIState.h"
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAISetup.h"
	// Sense
#include "GraphEditor/EnumStruct/Sense/SCsGraphPin_ECsSenseActorType.h"

// Managers
#include "Managers/Process/CsProcess.h"

TSharedPtr<class SGraphPin> FCsPanelGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Asset
	{
		// FECsAssetType
		if (DoesPinUseScriptStruct<FECsAssetType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsAssetType, InPin); }
		// FECsLoadAssetsType
		if (DoesPinUseScriptStruct<FECsLoadAssetsType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsLoadAssetsType, InPin); }
	}
	// Input
	{
		// FECsInputAction
		if (DoesPinUseScriptStruct<FECsInputAction>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsInputAction, InPin); }
		// FECsGameEvent
		if (DoesPinUseScriptStruct<FECsGameEvent>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsGameEvent, InPin); }
	}
	// FECsSurfaceType
	if (DoesPinUseScriptStruct<FECsSurfaceType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsSurfaceType, InPin); }
	// FECsGestureType
	if (DoesPinUseScriptStruct<FECsGestureType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsGestureType, InPin); }
	// FX
	{
		// FECsFX
		if (DoesPinUseScriptStruct<FECsFX>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsFX, InPin); }
	}
	// Character
	{
		// FECsCharacterAnim
		//if (DoesPinUseScriptStruct<FECsCharacterAnim>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterAnim, InPin); }
		// FECsCharacterAnimVariation
		//if (DoesPinUseScriptStruct<FECsCharacterAnimVariation>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterAnimVariation, InPin); }
		// FECsCharacterAnimBlueprint
		//if (DoesPinUseScriptStruct<FECsCharacterAnimBlueprint>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterAnimBlueprint, InPin); }
		// FECsCharacterBlendSpace
		//if (DoesPinUseScriptStruct<FECsCharacterBlendSpace>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterBlendSpace, InPin); }
	}
	// FECsProcess
	if (DoesPinUseScriptStruct<FECsProcess>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProcess, InPin); }
	// Item
	{
		// FECsItemType
		//if (DoesPinUseScriptStruct<FECsItemType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemType, InPin); }
		// FECsItemOwner
		//if (DoesPinUseScriptStruct<FECsItemOwner>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemOwner, InPin); }
		// FECsItemInteraction
		//if (DoesPinUseScriptStruct<FECsItemInteraction>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemInteraction, InPin); }
	}
	// Crafting
	{
		// FECsRecipeType
		//if (DoesPinUseScriptStruct<FECsRecipeType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsRecipeType, InPin); }
	}
	// Damage
	{
		// FECsDamageType
		if (DoesPinUseScriptStruct<FECsDamageType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsDamageType, InPin); }
		// FECsHitType
		if (DoesPinUseScriptStruct<FECsHitType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsHitType, InPin); }
	}
	// Interactive
	{
		// FECsInteractiveType
		//if (DoesPinUseScriptStruct<FECsInteractiveType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsInteractiveType, InPin); }
	}
	// FECsSound
	if (DoesPinUseScriptStruct<FECsSound>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsSound, InPin); }
	// AI
	{
		// FECsAIType
		//if (DoesPinUseScriptStruct<FECsAIType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsAIType, InPin); }
		// FECsAIState
		//if (DoesPinUseScriptStruct<FECsAIState>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsAIState, InPin); }
		// FECsAISetup
		//if (DoesPinUseScriptStruct<FECsAISetup>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsAISetup, InPin); }
	}
	// Sense
	{
		// FECsSenseActorType
		if (DoesPinUseScriptStruct<FECsSenseActorType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsSenseActorType, InPin); }
	}
	return nullptr;
}

