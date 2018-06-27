// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sense/CsManager_Sense.h"
#include "CsCore.h"

// Managers
#include "Managers/Trace/CsManager_Trace.h"
// Game
#include "Game/CsGameInstance.h"
#include "Game/CsGameState.h"
// Player
#include "Player/CsPlayerPawn.h"
// AI
#include "AI/Pawn/CsAIPawn.h"

ACsManager_Sense::ACsManager_Sense(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates = false;
	bReplicateMovement = false;

	const int32& Count = EMCsSenseActorType::Get().Num();

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsSenseActorType& Enum = EMCsSenseActorType::Get().GetEnumAt(I);

		TMap<uint64, FCsSenseInfo> Map;
		SenseMap.Add(Enum, Map);
	}

	for (int32 I = 0; I < Count; ++I)
	{
		TraceToActorIntervals.Add(EMCsSenseActorType::Get().GetEnumAt(I), 0.1f);
	}
}

void ACsManager_Sense::PostActorCreated()
{
	Super::PostActorCreated();

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	UniqueObjectId = GameInstance->GetUniqueObjectId();
}

void ACsManager_Sense::Destroyed()
{
	Super::Destroyed();

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	GameInstance->UnregisterUniqueObject(UniqueObjectId);
}

AActor* ACsManager_Sense::GetMyOwner()
{
	return MyOwner.IsValid() ? MyOwner.Get() : nullptr;
}

void ACsManager_Sense::Init(AActor* InOwner)
{
	MyOwner = InOwner;
}

void ACsManager_Sense::OnTick(const float &DeltaSeconds)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());

	const float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();

	TArray<FECsSenseActorType> TypeKeys;
	SenseMap.GetKeys(TypeKeys);

	for (const FECsSenseActorType& ActorType : TypeKeys)
	{
		TMap<uint64, FCsSenseInfo>& Map = SenseMap[ActorType];

		TArray<uint64> IdKeys;
		Map.GetKeys(IdKeys);

		for (const uint64& Id : IdKeys)
		{
			FCsSenseInfo& Info = Map[Id];

			// Player / AI
			if (Info.ActorType == ECsSenseActorType::Player ||
				Info.ActorType == ECsSenseActorType::AI)
			{
				ACsPawn* Pawn = GameInstance->GetUniqueObjectById<ACsPawn>(Info.ObserveeId);
				// Check Pawn is Alive
				if (!Pawn->bSpawnedAndActive)
					continue;
			}
			// Check Dot
			Sense_CheckMeToActorDot(Info);

			if (!Info.bSeesActorByDot)
			{
				Info.SetSeesActor(false);
				Info.SetSeesActorBody(false);
				Info.SetSeesActorHead(false);
				continue;
			}

			Info.LastTime_SeesActorByDot = GetWorld()->GetTimeSeconds();

			if (CurrentTimeSeconds - Info.StartTime_TraceMeToActorBody >= TraceToActorIntervals[Info.ActorType])
			{
				// Trace to Body
				Sense_TraceViewToActorBody(Info);

				if (Info.ActorType == ECsSenseActorType::Player ||
					Info.ActorType == ECsSenseActorType::AI)
				{
					// Trace to Head
					Sense_TraceViewToActorHead(Info);
				}

				Info.StartTime_TraceMeToActorBody = CurrentTimeSeconds;
			}
			Info.SetSeesActor(Info.bSeesActorBody || Info.bSeesActorHead);
		}
	}
}

void ACsManager_Sense::Sense_CheckMeToActorDot(FCsSenseInfo& Info)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	AActor* Actor				  = GameInstance->GetUniqueActorById(Info.ObserveeId);
	const FVector Location		  = Actor->GetActorLocation();

	AActor* Me = GetMyOwner();

	// XYZ
	const FVector MeToActor = Location - Me->GetActorLocation();
	Info.MeToActorDistance	= MeToActor.Size();
	Info.MeToActorDistanceSq = Info.MeToActorDistance * Info.MeToActorDistance;
	Info.MeToActorDir		= MeToActor / Info.MeToActorDistance;
	// XY
	const FVector MeToActorXY	= FVector(MeToActor.X, MeToActor.Y, 0.0f);
	Info.MeToActorDistanceXY	= MeToActorXY.Size();
	Info.MeToActorDistanceXYSq	= Info.MeToActorDistanceXY * Info.MeToActorDistanceXY;
	Info.MeToActorDirXY			= MeToActorXY / Info.MeToActorDistanceXY;

	FVector CurrentFaceDirXY = FVector::ZeroVector;

	// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		CurrentFaceDirXY = Pawn->CurrentRootDirXY;
	}
	else
	{
		FRotator Rotation = Me->GetActorRotation();
		Rotation.Pitch	  = 0.0f;
		CurrentFaceDirXY  = Rotation.Vector();
	}
	Info.MeToActorDot = FVector::DotProduct(CurrentFaceDirXY, Info.MeToActorDirXY);

	Info.SetSeesActorByDot(Info.MeToActorDot >= ViewMinDot);
}

void ACsManager_Sense::Sense_TraceViewToActorBody(FCsSenseInfo& Info)
{
	ACsManager_Trace* Manager_Trace = ACsManager_Trace::Get(GetWorld());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

	SenseTraceRequestMap.Add(Request->Id, &Info);

	Request->Caller	  = this;
	Request->CallerId = UniqueObjectId;
	Request->OnResponse_Event.AddUObject(this, &ACsManager_Sense::Async_Sense_TraceViewToActorBody_Response);

	AActor* Me = GetMyOwner();

	FVector Start = FVector::ZeroVector;

	// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		Start = Pawn->CurrentViewLocation;
	}
	else
	{
		Start = Me->GetActorLocation();
	}
	Request->Start = Start;

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	AActor* Actor				  = GameInstance->GetUniqueActorById(Info.ObserveeId);

	Request->End	= Actor->GetActorLocation();
	Request->bAsync = true;
	Request->Type	= ECsTraceType::Line;
	Request->Method = ECsTraceMethod::Multi;
	Request->Query	= ECsTraceQuery::ObjectType;

	// Player / AI
	// TODO: Put Query Types in SenseInfo
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
		Request->ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	Request->Params.AddIgnoredActor(Me);

	Request->ReplacePending = true;
	Request->PendingId		= Info.TraceRequestId_MeToActorBody;

	Manager_Trace->Trace(Request);
}

void ACsManager_Sense::Async_Sense_TraceViewToActorBody_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	FCsSenseInfo* InfoPtr = SenseTraceRequestMap[RequestId];
	FCsSenseInfo& Info	  = *InfoPtr;

	SenseTraceRequestMap.Remove(RequestId);

	Info.TraceRequestId_MeToActorBody = CS_INVALID_TRACE_REQUEST_ID;

	if (!Info.bSeesActorByDot)
		return;
	if (!Response->bResult)
		return;

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	ACsPawn* Pawn				  = nullptr;
	
	// Player / AI
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
		Pawn = GameInstance->GetUniqueObjectById<ACsPawn>(Info.ObserveeId);

	for (FHitResult& Hit : Response->OutHits)
	{
		// TODO: May need to have the ability to pass in an array of which channels block vision
		if (UPrimitiveComponent* Component = Hit.GetComponent())
		{
			const ECollisionChannel CollisionChannel = Component->GetCollisionObjectType();

			if (CollisionChannel == ECC_WorldStatic ||
				CollisionChannel == ECC_WorldDynamic)
				return;
		}

		// Player / AI
		if (Info.ActorType == ECsSenseActorType::Player ||
			Info.ActorType == ECsSenseActorType::AI)
		{
			ACsPawn* P = Cast<ACsPawn>(Hit.GetActor());

			if (Pawn == P)
			{
				Info.SetSeesActor(true);
				Info.SetSeesActorBody(true);

				Info.LastTime_SeesActor		= GetWorld()->GetTimeSeconds();
				Info.LastTime_SeesActorBody = GetWorld()->GetTimeSeconds();
				return;
			}
		}
	}
}

void ACsManager_Sense::Sense_TraceViewToActorHead(FCsSenseInfo& Info)
{
	ACsManager_Trace* Manager_Trace = ACsManager_Trace::Get(GetWorld());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();

	SenseTraceRequestMap.Add(Request->Id, &Info);

	Request->Caller = this;
	Request->CallerId = UniqueObjectId;
	Request->OnResponse_Event.AddUObject(this, &ACsManager_Sense::Async_Sense_TraceViewToActorBody_Response);

	AActor* Me = GetMyOwner();

	FVector Start = FVector::ZeroVector;

	// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		Start = Pawn->CurrentViewLocation;
	}
	else
	{
		Start = Me->GetActorLocation();
	}
	Request->Start = Start;

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	AActor* Actor				  = GameInstance->GetUniqueActorById(Info.ObserveeId);

	Request->End	= Actor->GetActorLocation();
	Request->bAsync = true;
	Request->Type	= ECsTraceType::Line;
	Request->Method = ECsTraceMethod::Multi;
	Request->Query	= ECsTraceQuery::ObjectType;

	// Player / AI
	// TODO: Put Query Types in SenseInfo
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
		Request->ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	Request->Params.AddIgnoredActor(Me);

	Request->ReplacePending = true;
	Request->PendingId		= Info.TraceRequestId_MeToActorBody;

	Manager_Trace->Trace(Request);
}

void ACsManager_Sense::Async_Sense_TraceViewToActorHead_Response(const uint8 &RequestId, FCsTraceResponse* Response)
{
	FCsSenseInfo* InfoPtr = SenseTraceRequestMap[RequestId];
	FCsSenseInfo& Info	  = *InfoPtr;

	SenseTraceRequestMap.Remove(RequestId);

	Info.TraceRequestId_MeToActorHead = CS_INVALID_TRACE_REQUEST_ID;

	if (!Info.bSeesActorByDot)
		return;
	if (!Response->bResult)
		return;

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	ACsPawn* Pawn				  = nullptr;

	// Player / AI
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
		Pawn = GameInstance->GetUniqueObjectById<ACsPawn>(Info.ObserveeId);

	for (FHitResult& Hit : Response->OutHits)
	{
		// TODO: May need to have the ability to pass in an array of which channels block vision
		if (UPrimitiveComponent* Component = Hit.GetComponent())
		{
			const ECollisionChannel CollisionChannel = Component->GetCollisionObjectType();

			if (CollisionChannel == ECC_WorldStatic ||
				CollisionChannel == ECC_WorldDynamic)
				return;
		}

		// Player / AI
		if (Info.ActorType == ECsSenseActorType::Player ||
			Info.ActorType == ECsSenseActorType::AI)
		{
			ACsPawn* P = Cast<ACsPawn>(Hit.GetActor());

			if (Pawn == P)
			{
				Info.SetSeesActor(true);
				Info.SetSeesActorHead(true);

				Info.LastTime_SeesActor		= GetWorld()->GetTimeSeconds();
				Info.LastTime_SeesActorHead = GetWorld()->GetTimeSeconds();
				return;
			}
		}
	}
}