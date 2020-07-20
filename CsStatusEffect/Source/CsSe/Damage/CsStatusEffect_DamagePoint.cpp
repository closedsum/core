// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Damage/CsStatusEffect_DamagePoint.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Expression/CsDamagePointEmu.h"

const FName UCsStatusEffect_DamagePoint::Name = FName("UCsStatusEffect_DamagePoint");

UCsStatusEffect_DamagePoint::UCsStatusEffect_DamagePoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsStatusEffect_DamagePoint::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsStatusEffect_DamagePoint>())
	{
		// ICsGetInterfaceMap
		{
			// Setup InterfaceMap
			InterfaceMap = new FCsInterfaceMap();
			
			InterfaceMap->Add<ICsStatusEffect>(Cast<ICsStatusEffect>(this));
			InterfaceMap->Add<ICsStatusEffect_Damage>(Cast<ICsStatusEffect_Damage>(this));
		}
		// ICsStatusEffect_Damage
		{
			DamagePointEmu = new FCsDamagePointEmu();
			DamagePoint.SetExpression(static_cast<FCsDamagePointEmu*>(DamagePointEmu));
		}
		bLoaded = false;
	}
}

void UCsStatusEffect_DamagePoint::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsStatusEffect_Damage
	if (DamagePointEmu)
	{
		FCsDamagePointEmu* Emu = static_cast<FCsDamagePointEmu*>(DamagePointEmu);
		delete Emu;
		DamagePointEmu = nullptr;
	}
}

#pragma endregion UObject Interface