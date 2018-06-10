// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsGraphPanelPinFactory.h"
#include "CsEditor.h"

#include "Types/CsTypes.h"
#include "Types/CsTypes_Input.h"
#include "Types/CsTypes_Character.h"
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Item.h"

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
	// Character
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnim.h"
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimBlueprint.h"
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterBlendSpace.h"
	// Process
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProcess.h"
	// Weapon
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponAnim.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponAnimBlueprint.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponBlendSpace.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponFireMode.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponGrip.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponOwner.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponSlot.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponSound.h"
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponState.h"
	// Blockchain
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainCommand.h"
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainContract.h"
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainContractFunction.h"
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsEthereumJavascript.h"
	// Item
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemType.h"
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemOwner.h"
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemInteraction.h"

// Managers
#include "Managers/Process/CsProcess.h"
// Blockchain
#include "Blockchain/CsBlockchainCommand.h"
#include "Blockchain/CsBlockchainContract.h"
#include "Blockchain/Ethereum/CsEthereum.h"

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
	// Character
	{
		// FECsCharacterAnim
		if (DoesPinUseScriptStruct<FECsCharacterAnim>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterAnim, InPin); }
		// FECsCharacterAnimBlueprint
		if (DoesPinUseScriptStruct<FECsCharacterAnimBlueprint>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterAnimBlueprint, InPin); }
		// FECsCharacterBlendSpace
		if (DoesPinUseScriptStruct<FECsCharacterBlendSpace>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsCharacterBlendSpace, InPin); }
	}
	// Weapon
	{
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
	}
	// FECsProcess
	if (DoesPinUseScriptStruct<FECsProcess>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProcess, InPin); }
	// Blockchain
	{
		// FECsBlockchainCommand
		if (DoesPinUseScriptStruct<FECsBlockchainCommand>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsBlockchainCommand, InPin); }
		// FECsBlockchainContract
		if (DoesPinUseScriptStruct<FECsBlockchainContract>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsBlockchainContract, InPin); }
		// FECsBlockchainContractFunction
		if (DoesPinUseScriptStruct<FECsBlockchainContractFunction>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsBlockchainContractFunction, InPin); }
		// FECsEthereumJavascript
		if (DoesPinUseScriptStruct<FECsEthereumJavascript>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsEthereumJavascript, InPin); }
	}
	// Item
	{
		// FECsItemType
		if (DoesPinUseScriptStruct<FECsItemType>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemType, InPin); }
		// FECsItemOwner
		if (DoesPinUseScriptStruct<FECsItemOwner>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemOwner, InPin); }
		// FECsItemInteraction
		if (DoesPinUseScriptStruct<FECsItemInteraction>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsItemInteraction, InPin); }
	}
	return nullptr;
}

