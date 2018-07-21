// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sense/CsManager_Sense.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

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

	for (int32 I = 0; I < Count; ++I)
	{
		const FECsSenseActorType& ActorType = EMCsSenseActorType::Get().GetEnumAt(I);

		bSeesAnyByRadius.Add(ActorType, false);
		bSeesAnyByDot.Add(ActorType, false);
		bSeesAnyBody.Add(ActorType, false);
		bSeesAndBodyHandle.Add(ActorType);
		bSeesAndBodyHandle[ActorType].Set(&(bSeesAnyBody[ActorType]));
		bFirstSeesAnyBody.Add(ActorType, false);
		bFirstUnSeesAnyBody.Add(ActorType, false);

		SeesAnyBodyTime.Add(ActorType, 0.0f);
		NotSeesAnyBodyTime.Add(ActorType, 0.0f);
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

const FECsSenseActorType& ACsManager_Sense::GetActorType(AActor* Actor)
{
	if (Cast<ACsPlayerPawn>(Actor))
		return ECsSenseActorType::Player;
	if (Cast<ACsAIPawn>(Actor))
		return ECsSenseActorType::AI;
	return EMCsSenseActorType::Get().GetMAX();
}

FCsSenseInfo* ACsManager_Sense::Add(AActor* Actor, const TCsSenseTeam& Team)
{
	if (ACsPawn* Pawn = Cast<ACsPawn>(Actor))
	{
		const FECsSenseActorType& ActorType = Cast<ACsPlayerPawn>(Pawn) ? ECsSenseActorType::Player : ECsSenseActorType::AI;

		FCsSenseInfo& Info	= SenseMap[ActorType].Add(Pawn->UniqueObjectId);
		Info.Id				= UniqueObjectId;
		Info.ObserveeId		= Pawn->UniqueObjectId;
		Info.ActorType		= ActorType;
		Info.Team			= Team;
		Info.Init();

		return &Info;
	}
	return nullptr;
}

bool ACsManager_Sense::CanSense(AActor* Actor)
{
	if (Cast<ACsPawn>(Actor))
		return true;
	return false;
}

bool ACsManager_Sense::IsSensing(AActor* Actor)
{
	if (!CanSense(Actor))
		return false;

	// Player
	if (ACsPlayerPawn* Pawn = Cast<ACsPlayerPawn>(Actor))
	{
		if (SenseMap[ECsSenseActorType::Player].Find(Pawn->UniqueObjectId))
			return true;
	}
	// AI
	if (ACsAIPawn* Pawn = Cast<ACsAIPawn>(Actor))
	{
		if (SenseMap[ECsSenseActorType::AI].Find(Pawn->UniqueObjectId))
			return true;
	}
	return false;
}

void ACsManager_Sense::OnTick(const float &DeltaSeconds)
{
	AActor* Me			  = GetMyOwner();
	FVector OwnerLocation = FVector::ZeroVector;

	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
		OwnerLocation = Pawn->CurrentRootLocation;

	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());

	const float CurrentTimeSeconds = GetWorld()->GetTimeSeconds();

	// Do Sensing (i.e. by Radius, Dot, and/or Trace to body part)
	TArray<FECsSenseActorType> TypeKeys;
	SenseMap.GetKeys(TypeKeys);

	for (const FECsSenseActorType& ActorType : TypeKeys)
	{
		bSeesAnyByRadius[ActorType] = false;
		bSeesAnyByDot[ActorType] = false;

		TMap<uint64, FCsSenseInfo>& Map = SenseMap[ActorType];

		TArray<uint64> IdKeys;
		Map.GetKeys(IdKeys);

		for (const uint64& Id : IdKeys)
		{
			FCsSenseInfo& Info = Map[Id];

			AActor* Actor		  = GameInstance->GetUniqueActorById(Info.ObserveeId);
			FVector ActorLocation = FVector::ZeroVector;

			// Player / AI
			if (Info.ActorType == ECsSenseActorType::Player ||
				Info.ActorType == ECsSenseActorType::AI)
			{
				ACsPawn* Pawn = Cast<ACsPawn>(Actor);
				ActorLocation = Pawn->CurrentRootLocation;

				// Check Pawn is Alive
				if (!Pawn->bSpawnedAndActive)
					continue;
			}
			else
			{
				Actor->GetActorLocation();
			}

			// Check Radius
			if (bRadius)
			{
				const float DistanceSq = (ActorLocation - OwnerLocation).SizeSquared();

				Info.SetSeesActorByRadius(DistanceSq <= RadiusSq);

				if (!Info.bSeesActorByRadius)
					continue;
			}

			bSeesAnyByRadius[ActorType] |= Info.bSeesActorByRadius;

			// Check Dot
			Sense_CheckMeToActorDot(Info);

			if (!Info.bSeesActorByDot)
			{
				Info.SetSeesActor(false);
				Info.SetSeesActorBody(false);
				Info.SetSeesActorHead(false);
				continue;
			}

			bSeesAnyByDot[ActorType] |= Info.bSeesActorByDot;

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

	// Update flags
	for (const FECsSenseActorType& ActorType : TypeKeys)
	{
		// Handle flags set for only ONE frame

			// First Sees
		if (bFirstSeesAnyBody[ActorType])
		{
			bFirstSeesAnyBody[ActorType] = false;

			OnbFirstSeesAnyBody_Event.Broadcast(ActorType, false);
#if WITH_EDITOR
			OnbFirstSeesAnyBody_ScriptEvent.Broadcast(ActorType, false);
#endif // #if WITH_EDITOR
		}

			// First UnSees
		if (bFirstUnSeesAnyBody[ActorType])
		{
			bFirstUnSeesAnyBody[ActorType] = false;

			OnbFirstUnSeesAnyBody_Event.Broadcast(ActorType, false);
#if WITH_EDITOR
			OnbFirstUnSeesAnyBody_ScriptEvent.Broadcast(ActorType, false);
#endif // #if WITH_EDITOR
		}

		// Check ALL Actors for the given ActorType
		bSeesAnyBody[ActorType] = false;

		TMap<uint64, FCsSenseInfo>& Map = SenseMap[ActorType];

		TArray<uint64> IdKeys;
		Map.GetKeys(IdKeys);

		for (const uint64& Id : IdKeys)
		{
			FCsSenseInfo& Info = Map[Id];

			if (Info.bSeesActorBody)
			{
				Info.SeesActorBodyTime	 += DeltaSeconds;
				Info.NotSeesActorBodyTime = 0.0f;
			}
			else
			{
				Info.SeesActorBodyTime     = 0.0f;
				Info.NotSeesActorBodyTime += DeltaSeconds;
			}
			bSeesAnyBody[ActorType] |= Info.bSeesActorBody;
		}

		if (bSeesAnyBody[ActorType])
		{
			SeesAnyBodyTime[ActorType]	 += DeltaSeconds;
			NotSeesAnyBodyTime[ActorType] = 0.0f;
		}
		else
		{
			SeesAnyBodyTime[ActorType]	   = 0.0f;
			NotSeesAnyBodyTime[ActorType] += DeltaSeconds;
		}

		bSeesAndBodyHandle[ActorType].UpdateIsDirty();

		if (bSeesAndBodyHandle[ActorType].HasChanged())
		{
			// First Sees
			if (bSeesAnyBody[ActorType])
			{
				bFirstSeesAnyBody[ActorType] = true;

				OnbFirstSeesAnyBody_Event.Broadcast(ActorType, true);
#if WITH_EDITOR
				OnbFirstSeesAnyBody_ScriptEvent.Broadcast(ActorType, true);
#endif // #if WITH_EDITOR
			}
			// First UnSees
			else
			{
				bFirstUnSeesAnyBody[ActorType] = true;

				OnbFirstUnSeesAnyBody_Event.Broadcast(ActorType, true);
#if WITH_EDITOR
				OnbFirstUnSeesAnyBody_ScriptEvent.Broadcast(ActorType, true);
#endif // #if WITH_EDITOR
			}
			bSeesAndBodyHandle[ActorType].Clear();
		}
	}

	// Draw Radius
	if (bRadius)
	{
		if (bDrawRadius || CsCVarDrawManagerSenseRadius->GetInt() == CS_CVAR_DRAW)
		{
			DrawDebugSphere(GetWorld(), OwnerLocation, Radius, 16.0f, FColor::Green, false, DeltaSeconds + 0.001f, 0, 5.0f);
		}
	}
	// Draw Angle
	if (CsCVarDrawManagerSenseAngle->GetInt() == CS_CVAR_DRAW)
	{
		bool Sees = false;

		TArray<FECsSenseActorType> TypeKeys;
		bSeesAnyByDot.GetKeys(TypeKeys);

		for (const FECsSenseActorType& ActorType : TypeKeys)
		{
			Sees |= bSeesAnyByDot[ActorType];
		}

		const FColor Color = Sees ? FColor::Red : FColor::Green;
		FVector Direction  = FVector::ZeroVector;

		if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
			Direction = Pawn->CurrentViewDirXY;

		const float AngleHeight = 0.0174533f;// FMath::DegreesToRadians(1.0f);

		DrawDebugCone(GetWorld(), OwnerLocation, Direction, Radius, ViewMinRadians, AngleHeight, 16, Color, false, DeltaSeconds + 0.001f, 0, 5.0f);
	}
}

void ACsManager_Sense::Sense_CheckMeToActorDot(FCsSenseInfo& Info)
{
	UCsGameInstance* GameInstance = Cast<UCsGameInstance>(GetGameInstance());
	AActor* Actor				  = GameInstance->GetUniqueActorById(Info.ObserveeId);

	FVector ActorLocation = FVector::ZeroVector;

	// Player / AI
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
	{
		ACsPawn* Pawn = Cast<ACsPawn>(Actor);
		ActorLocation = Pawn->CurrentBodyLocation;
	}
	else
	{
		ActorLocation = Actor->GetActorLocation();
	}

	AActor* Me = GetMyOwner();

	FVector OwnerLocation = FVector::ZeroVector;

	// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		OwnerLocation = Pawn->CurrentBodyLocation;
	}
	else
	{
		OwnerLocation = Me->GetActorLocation();
	}

	// MeToActor

		// XYZ
	const FVector MeToActor = ActorLocation - OwnerLocation;
	Info.MeToActorDistance	= MeToActor.Size();
	Info.MeToActorDistanceSq = Info.MeToActorDistance * Info.MeToActorDistance;
	Info.MeToActorDir		= MeToActor / Info.MeToActorDistance;
	
	Info.MeToActorBodyRotation	  = UCsCommon::AngleClamp360(Info.MeToActorDir.Rotation());
	Info.MeToActorBodyRotation.Roll = 0.0f;
		// XY
	const FVector MeToActorXY	= FVector(MeToActor.X, MeToActor.Y, 0.0f);
	Info.MeToActorDistanceXY	= MeToActorXY.Size();
	Info.MeToActorDistanceXYSq	= Info.MeToActorDistanceXY * Info.MeToActorDistanceXY;
	Info.MeToActorDirXY			= MeToActorXY / Info.MeToActorDistanceXY;

	// ViewToActor

		// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		Info.ViewToActorDir			 = (ActorLocation - Pawn->CurrentViewLocation).GetSafeNormal();
		Info.ViewToActorBodyRotation = Info.ViewToActorDir.Rotation();
	}
	else
	{
		Info.ViewToActorDir			 = Info.MeToActorDir;
		Info.ViewToActorBodyRotation = Info.MeToActorBodyRotation;
	}

	// Dot
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
	Info.MeToActorDot			= FVector::DotProduct(CurrentFaceDirXY, Info.MeToActorDirXY);
	Info.MeToActorAbsDeltaAngle = FMath::Abs(FMath::RadiansToDegrees(FMath::Acos(Info.MeToActorDot)));

		// Player / AI
	if (ACsPawn* Pawn = Cast<ACsPawn>(Me))
	{
		Info.ViewToActorDot = FVector::DotProduct(Pawn->CurrentViewDirXY, Info.MeToActorDirXY);
	}
	else
	{
		Info.ViewToActorDot	= Info.MeToActorDot;
	}

	Info.SetSeesActorByDot(Info.ViewToActorDot >= ViewMinDot);
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

	FVector End = FVector::ZeroVector;

	// Player / AI
	if (Info.ActorType == ECsSenseActorType::Player ||
		Info.ActorType == ECsSenseActorType::AI)
	{
		ACsPawn* Pawn = Cast<ACsPawn>(Actor);
		End			  = Pawn->CurrentBodyLocation;
	}
	else
	{
		End = Actor->GetActorLocation();
	}

	Request->End	= End;
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