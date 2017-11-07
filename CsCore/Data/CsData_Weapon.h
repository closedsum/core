// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "CsData_Weapon.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Weapon : public ACsData
{
	GENERATED_UCLASS_BODY()

	virtual void* GetFireTypeStruct(const uint8 &Index);
	virtual UScriptStruct* GetFireTypeScriptStruct();

	//virtual class ACsData_Projectile* GetData_Projectile(const TCsWeaponFire &FireType, const bool &IsCharged = false);
};