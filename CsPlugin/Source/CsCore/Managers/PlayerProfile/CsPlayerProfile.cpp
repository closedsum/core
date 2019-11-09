// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsPlayerProfile.h"
#include "CsCore.h"

// Managers
#include "Managers/Save/CsManager_Save.h"
#include "Managers/Achievement/CsManager_Achievement.h"

#include "Engine/World.h"

#include "Engine/LocalPlayer.h"

UCsPlayerProfile::UCsPlayerProfile(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Manager_Save_Class = UCsManager_Save::StaticClass();
	Manager_Achievement_Class = UCsManager_Achievement::StaticClass();
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
	Manager_Save = NewObject<UCsManager_Save>(this, Manager_Save_Class);
	Manager_Save->SetLocalPlayer(LocalPlayer);
	Manager_Save->SetProfileType(ProfileType);
	Manager_Save->SetProfileName(EMCsPlayerProfile::Get().ToString(ProfileType));
	Manager_Save->SetProfileFileNamePrefix(EMCsPlayerProfile::Get().ToString(ProfileType));
	Manager_Save->Init();

	Manager_Achievement = NewObject<UCsManager_Achievement>(this, Manager_Achievement_Class);
	Manager_Achievement->SetCurrentWorld(GetCurrentWorld());
	Manager_Achievement->SetLocalPlayer(LocalPlayer);
	Manager_Achievement->Init();
}

void UCsPlayerProfile::OnTick(const float& DeltaSeconds)
{
	Manager_Save->OnTick(DeltaSeconds);
	Manager_Achievement->OnTick(DeltaSeconds);
}