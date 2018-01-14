// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Damageable.h"
#include "CsCore.h"

ACsData_Damageable::ACsData_Damageable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

int32 ACsData_Damageable::GetHealth() { return 0; }
float ACsData_Damageable::GetRespawnTime() { return 0.0f; }

#pragma endregion Stats