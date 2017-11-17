// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "CsCore.h"
// Data
#include "Data/CsData_Projectile.h"
// Managers
#include "Managers/Sound/CsManager_Sound.h"

ACsData_Weapon::ACsData_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

void* ACsData_Weapon::GetFireTypeStruct(const uint8 &Index) { return nullptr; }
UScriptStruct* ACsData_Weapon::GetFireTypeScriptStruct() { return nullptr; }

bool ACsData_Weapon::UseFakeProjectile(const TCsWeaponFire &FireType){ return false; }
ACsData_Projectile* ACsData_Weapon::GetData_Projectile(const TCsWeaponFire &FireType, const bool &IsCharged){ return nullptr; }

#pragma endregion Stats

// FX
#pragma region

FCsFxElement* ACsData_Weapon::GetMuzzleFX(const TCsViewType &ViewType, const TCsWeaponFire &FireType, const int32 &Index /*=0*/){ return nullptr; }

#pragma endregion FX

// Sounds
#pragma region

FCsSoundElement* ACsData_Weapon::GetSound(const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType){ return nullptr;  }

void ACsData_Weapon::PlaySound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireType, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, InParent);
}

void ACsData_Weapon::PlaySoundEX(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, const FVector &Location)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireType, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}

void ACsData_Weapon::StopSound(UWorld* InWorld, const TCsViewType &ViewType, const TCsWeaponFire &FireType, const TCsWeaponSound &SoundType, UObject* InOwner, UObject* InParent)
{
	FCsSoundElement* SoundElement   = GetSound(ViewType, FireType, SoundType);
	ACsManager_Sound* Manager_Sound = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Stop(SoundElement, InOwner, InParent);
}

#pragma endregion Sounds