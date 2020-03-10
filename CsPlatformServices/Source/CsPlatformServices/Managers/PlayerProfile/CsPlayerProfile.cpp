// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsPlayerProfile.h"
#include "CsPlatformServices.h"

// Managers
#include "Managers/Save/CsManager_Save.h"
#include "Managers/Achievement/CsManager_Achievement.h"

#include "Engine/World.h"

#include "Engine/LocalPlayer.h"

UCsPlayerProfile::UCsPlayerProfile(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsPlayerProfile::SetProfileType(const ECsPlayerProfile& InProfileType)
{
	ProfileType = InProfileType;
}

// World
#pragma region

void UCsPlayerProfile::SetCurrentWorld(UWorld* World)
{
	CurrentWorld = World;
}

UWorld* UCsPlayerProfile::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

#pragma endregion World

// Player
#pragma region

void UCsPlayerProfile::SetLocalPlayer(ULocalPlayer* Player)
{
	LocalPlayer = Player;
}

#pragma endregion Player

void UCsPlayerProfile::Init()
{
}

void UCsPlayerProfile::Update(const float& DeltaSeconds)
{
}