// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/Navigation/CsManager_AI_Navigation.h"
#include "CsCore.h"

// static initializations
UCsManager_AI_Navigation* UCsManager_AI_Navigation::s_Instance;
bool UCsManager_AI_Navigation::s_bShutdown = false;

UCsManager_AI_Navigation::UCsManager_AI_Navigation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsManager_AI_Navigation::BeginDestroy()
{
	Super::BeginDestroy();

	UCsManager_AI_Navigation::Shutdown();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_AI_Navigation::OnRegister()
{
	Super::OnRegister();

	Init(this);
}

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

/*static*/ UCsManager_AI_Navigation* UCsManager_AI_Navigation::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_AI_Navigation::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
}

/*static*/ void UCsManager_AI_Navigation::Init(UCsManager_AI_Navigation* Manager)
{
	s_bShutdown = false;

	if (s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_AI_Navigation::Init: This is being called before the previous instance of the manager has been Shutdown."));
	}
	s_Instance = Manager;
}

/*static*/ void UCsManager_AI_Navigation::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_AI_Navigation::Initialize()
{
}

void UCsManager_AI_Navigation::CleanUp()
{
}

#pragma endregion Singleton

void UCsManager_AI_Navigation::OnTick(const float& DeltaSeconds)
{
}