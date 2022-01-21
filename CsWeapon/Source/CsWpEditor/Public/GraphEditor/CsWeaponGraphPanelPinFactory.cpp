// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsWeaponGraphPanelPinFactory.h"
#include "CsWpEditor.h"

// Types
#include "Types/CsTypes_Weapon.h"

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

TSharedPtr<SGraphPin> FCsWeaponPanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// FECsWeapon
	if (DoesPinUseScriptStruct<FECsWeapon>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeapon, InPin); }
	// FECsWeaponClass
	if (DoesPinUseScriptStruct<FECsWeaponClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponClass, InPin); }
	// FECsWeaponAnim
	if (DoesPinUseScriptStruct<FECsWeaponAnim>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponAnim, InPin); }
	// FECsWeaponAnimBlueprint
	if (DoesPinUseScriptStruct<FECsWeaponAnimBlueprint>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponAnimBlueprint, InPin); }
	// FECsWeaponBlendSpace
	if (DoesPinUseScriptStruct<FECsWeaponBlendSpace>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponBlendSpace, InPin); }
	// FECsWeaponFireMode
	if (DoesPinUseScriptStruct<FECsWeaponFireMode>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponFireMode, InPin); }
	// FECsWeaponGrip
	if (DoesPinUseScriptStruct<FECsWeaponGrip>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponGrip, InPin); }
	// FECsWeaponOwner
	if (DoesPinUseScriptStruct<FECsWeaponOwner>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponOwner, InPin); }
	// FECsWeaponSlot
	if (DoesPinUseScriptStruct<FECsWeaponSlot>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponSlot, InPin); }
	// FECsWeaponSound
	if (DoesPinUseScriptStruct<FECsWeaponSound>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponSound, InPin); }
	// FECsWeaponState
	if (DoesPinUseScriptStruct<FECsWeaponState>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponState, InPin); }
	// FECsWeaponData
	if (DoesPinUseScriptStruct<FECsWeaponData>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsWeaponData, InPin); }
	return nullptr;
}

