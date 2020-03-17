// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Damageable.h"
#include "CsCoreDEPRECATED.h"

UCsData_Damageable::UCsData_Damageable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

int32 UCsData_Damageable::GetHealth() { return 0; }
float UCsData_Damageable::GetRespawnTime() { return 0.0f; }

#pragma endregion Stats