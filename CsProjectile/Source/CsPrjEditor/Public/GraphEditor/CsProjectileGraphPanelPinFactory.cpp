// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsProjectileGraphPanelPinFactory.h"
#include "CsPrjEditor.h"

// Types
#include "Types/CsTypes_Projectile.h"
#include "Payload/CsTypes_Payload_Projectile.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"

// EnumStructs
	// Projectile
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectile.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileClass.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileData.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectilePayload.h"
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileModifier.h"

TSharedPtr<SGraphPin> FCsProjectilePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

#define CS_TEMP_CREATE(EnumName) if (DoesPinUseScriptStruct<F##EnumName>(InPin, K2Schema)) { return SNew(SCsGraphPin_##EnumName, InPin); }

	// Projectile
	{
		// FECsProjectile
		CS_TEMP_CREATE(ECsProjectile)
		// FECsProjectileClass
		CS_TEMP_CREATE(ECsProjectileClass)
		// FECsProjectileData
		CS_TEMP_CREATE(ECsProjectileData)
		// FECsProjectilePayload
		CS_TEMP_CREATE(ECsProjectilePayload)
		// FECsProjectileModifier
		CS_TEMP_CREATE(ECsProjectileModifier)
	}

#undef CS_TEMP_CREATE

	return nullptr;
}

