// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamagePoint.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

const FName UCsData_StatusEffect_DamagePoint::Name = FName("UCsData_StatusEffect_DamagePoint");

UCsData_StatusEffect_DamagePoint::UCsData_StatusEffect_DamagePoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsData_StatusEffect_DamagePoint::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_StatusEffect_DamagePoint>())
	{
		// ICsGetInterfaceMap
		{
			// Setup InterfaceMap
			InterfaceMap = new FCsInterfaceMap();
			
			InterfaceMap->Add<ICsData_StatusEffect>(Cast<ICsData_StatusEffect>(this));
			InterfaceMap->Add<ICsData_StatusEffect_Damage>(Cast<ICsData_StatusEffect_Damage>(this));
		}
		// ICsStatusEffect_Damage
		{
			DamagePointEmu = new FCsData_DamagePointEmu();
			DamagePoint.SetData(static_cast<FCsData_DamagePointEmu*>(DamagePointEmu));
		}
		bLoaded = false;
	}
}

void UCsData_StatusEffect_DamagePoint::BeginDestroy()
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
		FCsData_DamagePointEmu* Emu = static_cast<FCsData_DamagePointEmu*>(DamagePointEmu);
		delete Emu;
		DamagePointEmu = nullptr;
	}
}

#pragma endregion UObject Interface