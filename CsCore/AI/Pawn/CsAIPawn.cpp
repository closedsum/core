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
// Game
#include "Game/CsGameState.h"
// Player
#include "Player/CsPlayerState.h"
#include "Player/CsPlayerPawn.h"
// UI
//#include "Components/CsWidgetComponent.h"
//#include "UI/Simple/CsWidget_ProgressBar.h"

ACsAIPawn::ACsAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationYaw = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI	  = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACsAIController::StaticClass();

	bPlayerSeesBodyHandle.Set(&bPlayerSeesBody);
	bPlayerSeesBodyHandle.OnChange_Event.AddUObject(this, &ACsAIPawn::OnChange_bPlayerSeesBody);

	PlayerSeesBodyAngle			= 70.0f;
	PlayerSeesBodyMinDot		= FMath::Cos(FMath::DegreesToRadians(70.0f));
	CheckPlayerSeesBodyInterval = 0.1f;
}

void ACsAIPawn::Init(const int32 &Index, const FECsAIType &InType)
{
	PoolIndex	= Index;
	Type		= InType;

	Cache.Set(Index, this);
}

void ACsAIPawn::OnCreatePool()
{
	SetActorHiddenInGame(true);

	// Populate SenseInfos
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	TArray<uint8> Keys;
	GameState->PlayerStateMappings.GetKeys(Keys);

	const uint8 Count = Keys.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		PlayerSenseInfos.AddDefaulted();
		PlayerSenseInfos[I].PlayerMappingId = Keys[I];
	}
}

void ACsAIPawn::OnPostCreatePool(){}

void ACsAIPawn::Allocate(const int32 &ActiveIndex, FCsAIPawnPayload* Payload)
{
	Cache.Init(ActiveIndex, Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
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

void ACsAIPawn::OnTick_HandleCVars(const float &DeltaSeconds){}

// State
#pragma region

void ACsAIPawn::OnChange_Health(const float &Value)
{
	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);

	OnChange_Health_Event.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#if WITH_EDITOR
	OnChange_Health_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, Health, MaxHealth);
#endif // #if WITH_EDITOR
}

#pragma endregion State

// Player
#pragma region

void ACsAIPawn::OnTick_CheckSenses()
{
	ACsGameState* GameState = GetWorld()->GetGameState<ACsGameState>();

	for (FCsAISenseInfo_Player& Info : PlayerSenseInfos)
	{
		ACsPlayerState* PlayerState = GameState->GetPlayerState(Info.PlayerMappingId);

		if (!PlayerState->IsOnBoardCompleted_Game())
			continue;

		ACsPawn* Pawn = PlayerState->GetMyPawn();

		// Check to start any Sensing
		const float DistanceSq = (GetActorLocation() - Pawn->GetActorLocation()).SizeSquared2D();

		if (DistanceSq > SenseRadiusSq)
			continue;

		OnTick_CalculateMeToPlayerDot(Info);
	}
}

void ACsAIPawn::OnTick_CalculateMeToPlayerDot(FCsAISenseInfo_Player& Info)
{
	ACsGameState* GameState		= GetWorld()->GetGameState<ACsGameState>();
	ACsPlayerState* PlayerState = GameState->GetPlayerState(Info.PlayerMappingId);
	ACsPawn* Pawn				= PlayerState->GetMyPawn();

	const FVector MeToPlayer = (Pawn->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	Info.MeToPlayerDot		 = FVector::DotProduct(CurrentRootDirXY, MeToPlayer);
}

void ACsAIPawn::OnTick_CheckSeesPlayer(FCsAISenseInfo_Player& Info)
{

}

void ACsAIPawn::OnTick_CheckSeesPlayerBody(FCsAISenseInfo_Player& Info)
{

}

void ACsAIPawn::OnTick_CheckSeesPlayerHead(FCsAISenseInfo_Player& Info)
{

}

void ACsAIPawn::OnTick_CalculatePlayerToMeDot()
{
	ACsPawn* LocalPawn		 = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());
	const FVector PlayerToMe = (GetActorLocation() - LocalPawn->GetActorLocation()).GetSafeNormal2D();
	PlayerToMeDot			 = FVector::DotProduct(LocalPawn->CurrentRootDirXY, PlayerToMe);
}

void ACsAIPawn::SetPlayerSeesBody(const bool &Value)
{
	bPlayerSeesBody = Value;

	bPlayerSeesBodyHandle.UpdateIsDirty();

	if (bPlayerSeesBodyHandle.HasChanged())
	{
		bPlayerSeesBodyHandle.Clear();
	}
}

void ACsAIPawn::OnChange_bPlayerSeesBody(const bool &Value)
{
	ACsAIPlayerState* MyPlayerState = Cast<ACsAIPlayerState>(PlayerState);

	OnPlayerSeesBody_Event.Broadcast(MyPlayerState->UniqueMappingId, Value);
#if WITH_EDITOR
	OnPlayerSeesBody_ScriptEvent.Broadcast(MyPlayerState->UniqueMappingId, Value);
#endif // #if WITH_EDITOR
}

void ACsAIPawn::OnTick_CheckPlayerSeesBody()
{
	if (PlayerToMeDot < PlayerSeesBodyMinDot)
	{
		SetPlayerSeesBody(false);
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

	Manager_Trace->Trace(Request);
}

void ACsAIPawn::CheckPlayerSeesBody_Response(FCsTraceResponse* Response)
{
	if (PlayerToMeDot < PlayerSeesBodyMinDot)
	{
		SetPlayerSeesBody(false);
		return;
	}

	if (!Response->bResult)
	{
		return;
	}

	ACsPawn* LocalPawn = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());

	const uint8 Count = Response->OutHits.Num();

	for (uint8 I = 0; I < Count; ++I)
	{
		ACsPawn* Pawn = Cast<ACsPawn>(Response->OutHits[I].GetActor());

		if (LocalPawn == Pawn)
		{
			SetPlayerSeesBody(true);
			return;
		}
	}
}

#pragma endregion Player