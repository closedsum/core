// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/Sense/CsManager_AI_Sense.h"
#include "CsCoreDEPRECATED.h"

// static initializations
UCsManager_AI_Sense* UCsManager_AI_Sense::s_Instance;
bool UCsManager_AI_Sense::s_bShutdown = false;

UCsManager_AI_Sense::UCsManager_AI_Sense(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsManager_AI_Sense::BeginDestroy()
{
	Super::BeginDestroy();

	UCsManager_AI_Sense::Shutdown();
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsManager_AI_Sense::OnRegister()
{
	Super::OnRegister();

	Init(this);
}

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

/*static*/ UCsManager_AI_Sense* UCsManager_AI_Sense::Get()
{
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsManager_AI_Sense::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
}

/*static*/ void UCsManager_AI_Sense::Init(UCsManager_AI_Sense* Manager)
{
	s_bShutdown = false;

	if (s_Instance)
	{
		UE_LOG(LogCsCoreDEPRECATED, Warning, TEXT("UCsManager_AI_Sense::Init: This is being called before the previous instance of the manager has been Shutdown."));
	}
	s_Instance = Manager;
}

/*static*/ void UCsManager_AI_Sense::Shutdown()
{
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
}

void UCsManager_AI_Sense::Initialize()
{
}

void UCsManager_AI_Sense::CleanUp()
{
}

#pragma endregion Singleton

void UCsManager_AI_Sense::OnTick(const float& DeltaSeconds)
{
}

// Noise
#pragma region

void UCsManager_AI_Sense::ReportNoiseEvent(const FECsNoiseEvent& EventType, const FVector& Location, const float& Loudness /*= 1.0f*/, AActor* Instigator /*= nullptr*/, const float& MaxRange /*= 0.0f*/, const FName& Tag /*= NAME_None*/)
{

}

#pragma endregion Noise