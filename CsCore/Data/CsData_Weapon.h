// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_Weapon.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Weapon : public ACsData
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region

	virtual void* GetFireTypeStruct(const uint8 &Index);
	virtual UScriptStruct* GetFireTypeScriptStruct();

	virtual class ACsData_Projectile* GetData_Projectile(const TCsWeaponFire &FireType, const bool &IsCharged = false);

#pragma endregion Stats

// FX
#pragma region

	virtual FCsFxElement* GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFire &FireType, const int32 &Index = 0);

#pragma endregion FX

// Sound
#pragma region

	virtual FCsSoundElement* GetSound(const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType);

	virtual void PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);
	virtual void PlaySoundEX(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location);
	virtual void StopSound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent);

#pragma endregion Sound
};