// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsProjectileGraphPanelPinFactory.h"
#include "CsPrjEditor.h"

// Types
#include "Types/CsTypes_Projectile.h"
#include "Payload/CsTypes_Payload_Projectile.h"

// EnumStructs
	// Projectile
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectile.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileClass.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileData.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectilePayload.h"

TSharedPtr<SGraphPin> FCsProjectilePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Projectile
	{
		// FECsProjectile
		if (DoesPinUseScriptStruct<FECsProjectile>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProjectile, InPin); }
		// FECsProjectileClass
		if (DoesPinUseScriptStruct<FECsProjectileClass>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProjectileClass, InPin); }
		// FECsProjectileData
		if (DoesPinUseScriptStruct<FECsProjectileData>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProjectileData, InPin); }
		// FECsProjectilePayload
		if (DoesPinUseScriptStruct<FECsProjectilePayload>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProjectilePayload, InPin); }
	}
	return nullptr;
}

