// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Damage.h"

// DamageType
EMCsDamageType* EMCsDamageType::Instance;

EMCsDamageType& EMCsDamageType::Get()
{
	if (!Instance)
		Instance = new EMCsDamageType();
	return *Instance;
}

// HitType
EMCsHitType* EMCsHitType::Instance;

EMCsHitType& EMCsHitType::Get()
{
	if (!Instance)
		Instance = new EMCsHitType();
	return *Instance;
}