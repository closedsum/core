// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Weapon.h"

// WeaponState
EMCsWeaponState* EMCsWeaponState::Instance;

EMCsWeaponState& EMCsWeaponState::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponState();
	return *Instance;
}

// WeaponSlot
EMCsWeaponSlot* EMCsWeaponSlot::Instance;

EMCsWeaponSlot& EMCsWeaponSlot::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponSlot();
	return *Instance;
}

// WeaponFireMode
EMCsWeaponFireMode* EMCsWeaponFireMode::Instance;

EMCsWeaponFireMode& EMCsWeaponFireMode::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponFireMode();
	return *Instance;
}

// WeaponGrip
EMCsWeaponGrip* EMCsWeaponGrip::Instance;

EMCsWeaponGrip& EMCsWeaponGrip::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponGrip();
	return *Instance;
}

// WeaponAnim
EMCsWeaponAnim* EMCsWeaponAnim::Instance;

EMCsWeaponAnim& EMCsWeaponAnim::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponAnim();
	return *Instance;
}

// WeaponBlendSpace
EMCsWeaponBlendSpace* EMCsWeaponBlendSpace::Instance;

EMCsWeaponBlendSpace& EMCsWeaponBlendSpace::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponBlendSpace();
	return *Instance;
}

// WeaponAnimBlueprint
EMCsWeaponAnimBlueprint* EMCsWeaponAnimBlueprint::Instance;

EMCsWeaponAnimBlueprint& EMCsWeaponAnimBlueprint::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponAnimBlueprint();
	return *Instance;
}

// WeaponSound
EMCsWeaponSound* EMCsWeaponSound::Instance;

EMCsWeaponSound& EMCsWeaponSound::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponSound();
	return *Instance;
}

// WeaponOwner
EMCsWeaponOwner* EMCsWeaponOwner::Instance;

EMCsWeaponOwner& EMCsWeaponOwner::Get()
{
	if (!Instance)
		Instance = new EMCsWeaponOwner();
	return *Instance;
}