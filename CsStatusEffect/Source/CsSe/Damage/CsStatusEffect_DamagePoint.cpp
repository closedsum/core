// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Damage/CsStatusEffect_DamagePoint.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/CsData_DamagePointEmu.h"

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
			DamagePointEmu = new FCsData_DamagePointEmu();
			DamagePoint.SetData(static_cast<FCsData_DamagePointEmu*>(DamagePointEmu));
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
		FCsData_DamagePointEmu* Emu = static_cast<FCsData_DamagePointEmu*>(DamagePointEmu);
		delete Emu;
		DamagePointEmu = nullptr;
	}
}

#pragma endregion UObject Interface