// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamageSphere.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Data/Shape/CsData_DamageSphereEmu.h"

const FName UCsData_StatusEffect_DamageSphere::Name = FName("UCsData_StatusEffect_DamageSphere");

UCsData_StatusEffect_DamageSphere::UCsData_StatusEffect_DamageSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsData_StatusEffect_DamageSphere::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_StatusEffect_DamageSphere>())
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
			DamageSphereEmu = new FCsData_DamageSphereEmu();
			DamageSphere.SetData(static_cast<FCsData_DamageSphereEmu*>(DamageSphereEmu));
		}
		bLoaded = false;
	}
}

void UCsData_StatusEffect_DamageSphere::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsStatusEffect_Damage
	if (DamageSphereEmu)
	{
		FCsData_DamageSphereEmu* Emu = static_cast<FCsData_DamageSphereEmu*>(DamageSphereEmu);
		delete Emu;
		DamageSphereEmu = nullptr;
	}
}

#pragma endregion UObject Interface