// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/CsSkeletalMeshGraphPanelPinFactory.h"
#include "CsSkeletalMeshEditor.h"

// Types
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

// EnumStructs
	// SkeletalMesh
#include "GraphEditor/EnumStruct/SkeletalMesh/SCsGraphPin_ECsSkeletalMeshActor.h"

TSharedPtr<class SGraphPin> FCsSkeletalMeshPanelGraphPinFactory::CreatePin(class UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// SkeletalMesh
	{
		// FECsSkeletalMeshActor
		CS_TEMP_CREATE(ECsSkeletalMeshActor)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

