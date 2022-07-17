// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Tracking/CsData_Projectile_Tracking.h"
#include "CsPrj.h"

const FName NCsProjectile::NData::NTracking::ITracking::Name = FName("NCsProjectile::NData::NTracking::ITracking");

const FName ICsData_Projectile_Tracking::Name = FName("ICsData_Projectile_Tracking");

UCsData_Projectile_Tracking::UCsData_Projectile_Tracking(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}