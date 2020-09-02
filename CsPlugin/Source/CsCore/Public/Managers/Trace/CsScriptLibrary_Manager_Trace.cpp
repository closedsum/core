// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Trace/CsScriptLibrary_Manager_Trace.h"
#include "CsCore.h"

// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Actor
#include "GameFramework/Actor.h"

UCsScriptLibrary_Manager_Trace::UCsScriptLibrary_Manager_Trace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Line
#pragma region

bool UCsScriptLibrary_Manager_Trace::LineTraceSingleByChannel(UObject* WorldContextObject, const FVector Start, const FVector End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit)
{
#if WITH_EDITOR
	if (UCsManager_Trace* Manager = UCsManager_Trace::GetFromWorldContextObject(WorldContextObject))
#else
	if (UCsManager_Trace* Manager = UCsManager_Trace::Get())
#endif // #if WITH_EDITOR
	{
		// Fill out Request
		FCsTraceRequest* Request = Manager->AllocateRequest();
		Request->Start				  = Start;
		Request->End				  = End;
		Request->Channel			  = Channel;
		Request->Params.bTraceComplex = bTraceComplex;

		if (bIgnoreSelf)
		{
			if (AActor* Actor = Cast<AActor>(WorldContextObject))
				Request->Params.AddIgnoredActor(Actor);
		}

		Request->Params.AddIgnoredActors(ActorsToIgnore);

		// Check Response
		if (FCsTraceResponse* Response = Manager->Trace(Request))
		{
			if (Response->bResult)
			{
				OutHit = Response->OutHits[CS_FIRST];
			}
			return Response->bResult;
		}
		return false;
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsScriptLibrary_Manager_Trace::LineTraceSingleByChannel: No Manager Trace of type UCsManager_Trace was created."));
	}
	return false;
}

#pragma endregion Line