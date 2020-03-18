// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/AI/Sense/CsLibrary_Manager_AI_Sense.h"
#include "CsCore.h"

#include "Managers/AI/Sense/CsManager_AI_Sense.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

UCsLibrary_Manager_AI_Sense::UCsLibrary_Manager_AI_Sense(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsLibrary_Manager_AI_Sense::ReportNoiseEvent(const UObject* WorldContextObject, const FECsNoiseEvent& EventType, const FVector& Location, const float& Loudness /*= 1.0f*/, AActor* Instigator /*= nullptr*/, const float& MaxRange /*= 0.0f*/, const FName& Tag /*= NAME_None*/)
{
	if (UCsManager_AI_Sense* Manager = UCsManager_AI_Sense::Get())
	{
		Manager->ReportNoiseEvent(EventType, Location, Loudness, Instigator, MaxRange, Tag);
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsLibrary_Manager_AI_Sense::ReportNoiseEvent: No Manager AI Sense of type UCsManager_AI_Sense was created."));
	}
}