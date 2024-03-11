// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsGraphPanelPinFactory.h"
#include "CsEditor.h"

// CVar
#include "CsCVars.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/Sound/CsTypes_Sound.h"
#include "Team/CsTypes_Team.h"
#include "Data/CsTypes_DataEntry.h"
// Input
#include "Managers/Input/Action/CsInputActionMap.h"
#include "Managers/Input/Action/CsInputAction.h"
// GameEvent
#include "Managers/Input/GameEvent/CsGameEvent.h"
// Anim
#include "Animation/Vertex/CsVertexAnimNotify.h"

// EnumStructs
	// CVar
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarLog.h"
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarToggle.h"
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarDraw.h"
	// Data
#include "GraphEditor/EnumStruct/Data/SCsGraphPin_ECsDataEntryData.h"
	// Update
#include "GraphEditor/EnumStruct/Update/SCsGraphPin_ECsUpdateGroup.h"
	// Input
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputAction.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputActionMap.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEvent.h"
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEventCoordinatorGroup.h"
	// FX
#include "GraphEditor/EnumStruct/FX/SCsGraphPin_ECsFX.h"
	// Sound
#include "GraphEditor/EnumStruct/Sound/SCsGraphPin_ECsSound.h"
	// Team
#include "GraphEditor/EnumStruct/Team/SCsGraphPin_ECsTeam.h"
	// Anim
#include "GraphEditor/EnumStruct/Anim/SCsGraphPin_ECsVertexAnimNotify.h"

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
	// Data
	{
		// FECsDataEntryData
		CS_TEMP_CREATE(ECsDataEntryData)
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
	}
	// FX
	{
		// FECsFX
		CS_TEMP_CREATE(ECsFX)
	}
	// Sound
	{
		// FECsSound
		CS_TEMP_CREATE(ECsSound)
	}
	// Team
	{
		// FECsTeam
		CS_TEMP_CREATE(ECsTeam)
	}
	// Anim
	{
		// FECsVertexAnimNotify
		CS_TEMP_CREATE(ECsVertexAnimNotify)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

