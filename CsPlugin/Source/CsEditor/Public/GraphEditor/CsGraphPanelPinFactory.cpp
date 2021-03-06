// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsGraphPanelPinFactory.h"
#include "CsEditor.h"

// CVar
#include "CsCVars.h"
// Types
#include "Types/CsTypes.h"
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
#include "Managers/FX/CsTypes_FX.h"
//#include "Types/CsTypes_Item.h"
//#include "Types/CsTypes_Recipe.h"
#include "Managers/Damage/CsTypes_Damage.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
//#include "Types/CsTypes_Interactive.h"
//#include "AI/CsTypes_AI.h"
#include "Managers/Sense/CsTypes_Sense.h"

#include "SlateBasics.h"

// EnumStructs
	// CVar
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarLog.h"
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarToggle.h"
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarDraw.h"
	// Asset
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsAssetType.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsLoadAssetsType.h"
	// Update
#include "GraphEditor/EnumStruct/Update/SCsGraphPin_ECsUpdateGroup.h"
	// Input
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputAction.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputActionMap.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEvent.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEventCoordinatorGroup.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGestureType.h"
	// FX
#include "GraphEditor/EnumStruct/FX/SCsGraphPin_ECsFX.h"
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
	// StaticMesh
#include "GraphEditor/EnumStruct/StaticMesh/SCsGraphPin_ECsStaticMeshActor.h"
	// SkeletalMesh
#include "GraphEditor/EnumStruct/SkeletalMesh/SCsGraphPin_ECsSkeletalMeshActor.h"
	// AI
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIType.h"
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIState.h"
//#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAISetup.h"
	// Sense
#include "GraphEditor/EnumStruct/Sense/SCsGraphPin_ECsSenseActorType.h"

#include "GraphEditor/EnumStruct/SCsGraphPin_ECsSurfaceType.h"

// Managers
#include "Managers/Process/CsProcess.h"

TSharedPtr<class SGraphPin> FCsPanelGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// CVar
	{
		// FECsCVarLog
		CS_TEMP_CREATE(ECsCVarLog)
		// FECsCVarToggle
		CS_TEMP_CREATE(ECsCVarToggle)
		// FECsCVarDraw
		CS_TEMP_CREATE(ECsCVarDraw)
	}
	// Asset
	{
		// FECsAssetType
		CS_TEMP_CREATE(ECsAssetType)
		// FECsLoadAssetsType
		CS_TEMP_CREATE(ECsLoadAssetsType)
	}
	// Update
	{
		// FECsUpdateGroup
		CS_TEMP_CREATE(ECsUpdateGroup)
	}
	// Input
	{
		// FECsInputAction
		CS_TEMP_CREATE(ECsInputAction)
		// FECsInputActionMap
		CS_TEMP_CREATE(ECsInputActionMap)
		// FECsGameEvent
		CS_TEMP_CREATE(ECsGameEvent)
		// FECsGameEventCoordinatorGroup
		CS_TEMP_CREATE(ECsGameEventCoordinatorGroup)
		// FECsGestureType
		CS_TEMP_CREATE(ECsGestureType)
	}
	// FECsSurfaceType
	CS_TEMP_CREATE(ECsSurfaceType)
	// FX
	{
		// FECsFX
		CS_TEMP_CREATE(ECsFX)
	}
	// FECsProcess
	CS_TEMP_CREATE(ECsProcess)
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
		CS_TEMP_CREATE(ECsDamageType)
		// FECsHitType
		CS_TEMP_CREATE(ECsHitType)
	}
	// Interactive
	{
		// FECsInteractiveType
		//if (DoesPinUseScriptStruct<FECsInteractiveType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsInteractiveType, InPin); }
	}
	// Sound
	{
		// FECsSound
		CS_TEMP_CREATE(ECsSound)
	}
	// StaticMesh
	{
		// FECsStaticMeshActor
		CS_TEMP_CREATE(ECsStaticMeshActor)
	}
	// SkeletalMesh
	{
		// FECsSkeletalMeshActor
		CS_TEMP_CREATE(ECsSkeletalMeshActor)
	}
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
		CS_TEMP_CREATE(ECsSenseActorType)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

