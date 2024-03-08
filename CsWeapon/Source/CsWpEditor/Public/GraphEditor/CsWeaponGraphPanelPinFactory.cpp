// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsWeaponGraphPanelPinFactory.h"
#include "CsWpEditor.h"

// Types
#include "Types/CsTypes_Weapon.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"

// EnumStructs
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeapon.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponClass.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponAnim.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponAnimBlueprint.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponBlendSpace.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponFireMode.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponGrip.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponOwner.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponSlot.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponSound.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponState.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponData.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponModifier.h"

TSharedPtr<SGraphPin> FCsWeaponPanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// FECsWeapon
	CS_TEMP_CREATE(ECsWeapon)
	// FECsWeaponClass
	CS_TEMP_CREATE(ECsWeaponClass)
	// FECsWeaponAnim
	CS_TEMP_CREATE(ECsWeaponAnim)
	// FECsWeaponAnimBlueprint
	CS_TEMP_CREATE(ECsWeaponAnimBlueprint)
	// FECsWeaponBlendSpace
	CS_TEMP_CREATE(ECsWeaponBlendSpace)
	// FECsWeaponFireMode
	CS_TEMP_CREATE(ECsWeaponFireMode)
	// FECsWeaponGrip
	CS_TEMP_CREATE(ECsWeaponGrip)
	// FECsWeaponOwner
	CS_TEMP_CREATE(ECsWeaponOwner)
	// FECsWeaponSlot
	CS_TEMP_CREATE(ECsWeaponSlot)
	// FECsWeaponSound
	CS_TEMP_CREATE(ECsWeaponSound)
	// FECsWeaponState
	CS_TEMP_CREATE(ECsWeaponState)
	// FECsWeaponData
	CS_TEMP_CREATE(ECsWeaponData)
	// FECsWeaponModifier
	CS_TEMP_CREATE(ECsWeaponModifier)

#undef CS_TEMP_CREATE

	return nullptr;
}

