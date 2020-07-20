// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Damage/CsStatusEffect_DamagePoint.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"

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
			/*
			InterfaceMap->Add<ICsData>(Cast<ICsData>(this));
			InterfaceMap->Add<ICsData_Projectile>(Cast<ICsData_Projectile>(this));
			InterfaceMap->Add<ICsData_ProjectileCollision>(Cast<ICsData_ProjectileCollision>(this));
			InterfaceMap->Add<ICsData_ProjectileStaticMeshVisual>(Cast<ICsData_ProjectileStaticMeshVisual>(this));
			InterfaceMap->Add<ICsData_ProjectileTrailVisual>(Cast<ICsData_ProjectileTrailVisual>(this));
			InterfaceMap->Add<ICsData_ProjectileImpactVisual>(Cast<ICsData_ProjectileImpactVisual>(this));
			InterfaceMap->Add<ICsData_ProjectileDamage>(Cast<ICsData_ProjectileDamage>(this));
			*/
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
}

#pragma endregion UObject Interface