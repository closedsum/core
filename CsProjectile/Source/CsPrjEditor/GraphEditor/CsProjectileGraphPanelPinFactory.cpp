// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/CsProjectileGraphPanelPinFactory.h"
#include "CsPrjEditor.h"

// Types
#include "Managers/Projectile/CsTypes_Projectile.h"

//#include "SlateBasics.h"

// EnumStructs
	// Projectile
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectile.h"

TSharedPtr<SGraphPin> FCsProjectilePanelGraphPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
	/*
	Check if pin is struct, and then check if that pin is of struct type we want customize
	*/

	// Creep
	{
		// FECsTdCreep
		if (DoesPinUseScriptStruct<FECsProjectile>(InPin, K2Schema)) { return SNew(SCsGraphPin_ECsProjectile, InPin); }
	}
	return nullptr;
}

