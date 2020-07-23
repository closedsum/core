// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Damage/CsStatusEffect_DamageSphere.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Managers/Damage/Shape/CsDamageSphereEmu.h"

const FName UCsStatusEffect_DamageSphere::Name = FName("UCsStatusEffect_DamageSphere");

UCsStatusEffect_DamageSphere::UCsStatusEffect_DamageSphere(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsStatusEffect_DamageSphere::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsStatusEffect_DamageSphere>())
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
			DamageSphereEmu = new FCsDamageSphereEmu();
			DamageSphere.SetExpression(static_cast<FCsDamageSphereEmu*>(DamageSphereEmu));
		}
		bLoaded = false;
	}
}

void UCsStatusEffect_DamageSphere::BeginDestroy()
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
		FCsDamageSphereEmu* Emu = static_cast<FCsDamageSphereEmu*>(DamageSphereEmu);
		delete Emu;
		DamageSphereEmu = nullptr;
	}
}

#pragma endregion UObject Interface