// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/PlayerProfile/CsPlayerProfile.h"

// Managers
#include "Managers/Save/CsManager_Save.h"
#include "Managers/Achievement/CsManager_Achievement.h"

#include "Engine/World.h"

#include "Engine/LocalPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPlayerProfile)

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