// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
#include "CsCore.h"

#include "Managers/PlayerProfile/CsPlayerProfile.h"

// static initializations
UCsManager_PlayerProfile* UCsManager_PlayerProfile::s_Instance;
bool UCsManager_PlayerProfile::s_bShutdown = false;

UCsManager_PlayerProfile::UCsManager_PlayerProfile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_PlayerProfile* UCsManager_PlayerProfile::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_PlayerProfile>(GetTransientPackage(), UCsManager_PlayerProfile::StaticClass(), TEXT("Manager_PlayerProfile_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->Initialize();
	}

	return s_Instance;
}

/*static*/ bool UCsManager_PlayerProfile::IsValid()
{
	return s_Instance != nullptr;
}

/*static*/ void UCsManager_PlayerProfile::Init()
{
	s_bShutdown = false;
	UCsManager_PlayerProfile::Get();
}

/*static*/ void UCsManager_PlayerProfile::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
}

/*static*/ bool UCsManager_PlayerProfile::HasShutdown()
{
	return s_bShutdown;
}

void UCsManager_PlayerProfile::Initialize()
{
}

void UCsManager_PlayerProfile::CleanUp()
{
	/*
	for (TPair<ECsPlayerProfile, UCsPlayerProfile*>& Pair : Profiles)
	{
		UCsPlayerProfile* P = Pair.Value;

		if (P && !P->IsPendingKill())
		{
			P->BeginDestroy();
		}
		Pair.Value = nullptr;
	}
	*/
	Profiles.Reset();
}

#pragma endregion Singleton

void UCsManager_PlayerProfile::OnTick(const float& DeltaSeconds)
{
	for (TPair<ECsPlayerProfile, UCsPlayerProfile*>& Pair : ProfileMap)
	{
		Pair.Value->OnTick(DeltaSeconds);
	}
}

UCsPlayerProfile* UCsManager_PlayerProfile::CreateProfile(const ECsPlayerProfile& ProfileType)
{
	// TODO: May need to tie Profile to ULocalPlayer

	if (UCsPlayerProfile** ProfilePtr = ProfileMap.Find(ProfileType))
	{
		// LOG
		return *ProfilePtr;
	}

	UCsPlayerProfile* P = NewObject<UCsPlayerProfile>(this, UCsPlayerProfile::StaticClass());

	P->SetProfileType(ProfileType);

	Profiles.Add(P);
	ProfileMap.Add(ProfileType, P);

	return P;
}

UCsPlayerProfile* UCsManager_PlayerProfile::GetProfile(const ECsPlayerProfile& ProfileType)
{
	if (UCsPlayerProfile** ProfilePtr = ProfileMap.Find(ProfileType))
	{
		return *ProfilePtr;
	}
	return nullptr;
}