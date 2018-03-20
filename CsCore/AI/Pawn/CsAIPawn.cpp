// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "AI/Pawn/CsAIPawn.h"
#include "CsCore.h"
#include "Coroutine/CsCoroutineScheduler.h"

#include "AI/CsAIController.h"
#include "AI/CsAIPlayerState.h"

// Data
#include "Data/CsData_Character.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();

	PlayerSeesBodyAngle			= 70.0f;
	PlayerSeesBodyMinDot		= FMath::Cos(FMath::DegreesToRadians(70.0f));
	CheckPlayerSeesBodyInterval = 0.1f;
}


void ACsAIPawn::Init(const int32 &Index, const TCsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);
}

void ACsAIPawn::OnPostCreatePool(){}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal(Payload);
}

template<typename T>
void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Allocate<T>(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr, InObject, OnDeAllocate);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, Time, RealTime, Frame, InOwner, InParent);

	Allocate_Internal(Payload);
}

void ACsAIPawn::Allocate(const uint16 &ActiveIndex, FCsAIPawnPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Allocate(ActiveIndex, Payload, Time, RealTime, Frame, nullptr, nullptr);
}

void ACsAIPawn::Allocate_Internal(FCsAIPawnPayload* Payload)
{
	if (Payload->TeleportLocation || Payload->TeleportRotation)
	{
		SpawnLocation = Payload->TeleportLocation ? Payload->Location : GetActorLocation();
		SpawnRotation = Payload->TeleportRotation ? Payload->Rotation : GetActorRotation();

		TeleportTo(SpawnLocation, SpawnRotation, false, false);
	}
	SetActorHiddenInGame(false);
}

void ACsAIPawn::DeAllocate()
{
	Cache.Reset();

	SetActorHiddenInGame(true);
}

void ACsAIPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalculatePlayerToMeDot();
}

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}

// Player
#pragma region

void ACsAIPawn::CalculatePlayerToMeDot()
{
	ACsPawn* LocalPawn = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());
	FVector PlayerToMe = GetActorLocation() - LocalPawn->GetActorLocation();
	PlayerToMe.Z	   = 0.0f;
	PlayerToMeDot	   = FVector::DotProduct(LocalPawn->CurrentRootDirXY, PlayerToMe);
}

void ACsAIPawn::CheckPlayerSeesBody()
{
	if (PlayerToMeDot < PlayerSeesBodyMinDot)
	{
		bPlayerSeesBody = false;
		return;
	}

	if (GetWorld()->GetTimeSeconds() - CheckPlayerSeesBodyStartTime < CheckPlayerSeesBodyInterval)
		return;

	CheckPlayerSeesBodyStartTime = GetWorld()->GetTimeSeconds();

	ACsManager_Trace* Manager_Trace = ACsManager_Trace::Get(GetWorld());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

	ACsPawn* LocalPawn = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());

	Request->Caller		= this;
	Request->CallerId	= UniqueObjectId;
	Request->OnResponse_Event.AddUObject(this, &ACsAIPawn::CheckPlayerSeesBody_Response);
	Request->Start		= GetActorLocation();
	Request->End		= LocalPawn->GetActorLocation();
	Request->bAsync		= true;
	Request->Type		= ECsTraceType::Line;
	Request->Method		= ECsTraceMethod::Multi;
	Request->Query		= ECsTraceQuery::ObjectType;
	Request->ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	Request->Params.AddIgnoredActor(this);
	Request->Params.AddIgnoredActor(LocalPawn);

	Manager_Trace->Trace(Request);
}

void ACsAIPawn::CheckPlayerSeesBody_Response(FCsTraceResponse* Response)
{
	if (PlayerToMeDot < PlayerSeesBodyMinDot)
	{
		bPlayerSeesBody = false;
		Response->Reset();
		return;
	}

	if (!Response->bResult)
	{
		Response->Reset();
		return;
	}

	ACsPawn* LocalPawn = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());

	const uint8 Count = Response->OutHits.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		ACsPawn* Pawn = Cast<ACsPawn>(Response->OutHits[I].GetActor());

		if (LocalPawn == Pawn)
		{
			bPlayerSeesBody = true;
			Response->Reset();
			return;
		}
	}
	Response->Reset();
}

#pragma endregion Player