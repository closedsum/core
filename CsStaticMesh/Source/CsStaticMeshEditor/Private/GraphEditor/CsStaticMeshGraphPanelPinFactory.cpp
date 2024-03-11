// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsStaticMeshGraphPanelPinFactory.h"
#include "CsStaticMeshEditor.h"

// Types
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

// EnumStructs
	// SkeletalMesh
#include "GraphEditor/EnumStruct/StaticMesh/SCsGraphPin_ECsStaticMeshActor.h"

TSharedPtr<class SGraphPin> FCsStaticMeshPanelGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// StaticMesh
	{
		// FECsStaticMeshActor
		CS_TEMP_CREATE(ECsStaticMeshActor)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

