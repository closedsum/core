// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsPlayerPawn.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// Managers
#include "Managers/Inventory/CsManager_Inventory.h"
#include "Managers/Trace/CsManager_Trace.h"
// Game
#include "Game/CsGameState.h"
// Player
#include "Player/CsPlayerState.h"
// AI
#include "AI/CsAIPlayerState.h"
#include "AI/Pawn/CsAIPawn.h"

ACsPlayerPawn::ACsPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = true;

	/*
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->SetHiddenInGame(true);
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	GetMesh()->ClothTickFunction.bCanEverTick = true;
	GetMesh()->bGenerateOverlapEvents = false;
	GetMesh()->Deactivate();

	GetMesh()->ClothTickFunction.bStartWithTickEnabled = false;
	GetCharacterMovement()->PrimaryComponentTick.bStartWithTickEnabled = false;
	GetCharacterMovement()->bAutoActivate = false;
	*/
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	/*
	bAlwaysRelevant		   = true;
	NetDormancy			   = ENetDormancy::DORM_Never;
	NetCullDistanceSquared = FMath::Square(100000);
	*/

	EyeHeight = 192.0f;

	bOnCalcCamera_Trace = false;

	CalcCameraTraceInfo.QueryParams.TraceTag = FName("OnCalcCamera_Trace");
	CalcCameraTraceInfo.IgnoreActors.Add(this);
	CalcCameraTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	CalcCameraTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	CalcCameraTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	CalcCameraTraceInfo.ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	CalcCameraTraceInfo.Range = 30000.0f;
	CalcCameraTraceInfo.RangeSq = CalcCameraTraceInfo.Range * CalcCameraTraceInfo.Range;
}

void ACsPlayerPawn::OnTickActor_HandleCVars(const float &DeltaSeconds)
{
	Super::OnTickActor_HandleCVars(DeltaSeconds);

	// View
	{
		// Forward
		if (CsCVarDrawPlayerViewForward->GetInt() == CS_CVAR_DRAW)
		{
			const FVector Start	  = GetActorLocation();
			const float Length	  = FMath::Max(CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_LENGTH, CsCVarDrawPlayerViewForwardLength->GetFloat());
			const FVector End	  = Start + Length * CurrentViewDir;
			const float Thickness = FMath::Max(CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_THICKNESS, CsCVarDrawPlayerViewForwardThickness->GetFloat());

			DrawDebugDirectionalArrow(GetWorld(), Start, End, 10.0f, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
		}
		// Right
		if (CsCVarDrawPlayerViewRight->GetInt() == CS_CVAR_DRAW)
		{
			const FVector Start	  = GetActorLocation();
			const float Length	  = FMath::Max(CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_LENGTH, CsCVarDrawPlayerViewRightLength->GetFloat());
			const FVector End	  = Start + Length * CurrentViewRight;
			const float Thickness = FMath::Max(CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_THICKNESS, CsCVarDrawPlayerViewRightThickness->GetFloat());

			DrawDebugDirectionalArrow(GetWorld(), Start, End, 10.0f, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);
		}
	}
	// Pawn
	{
		// Forward
		if (CsCVarDrawPlayerPawnForward->GetInt() == CS_CVAR_DRAW)
		{
			const FVector Start	  = GetActorLocation();
			const float Length	  = FMath::Max(CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_LENGTH, CsCVarDrawPlayerPawnForwardLength->GetFloat());
			const FVector End	  = Start + Length * CurrentCapsuleVelocityDir;
			const float Thickness = FMath::Max(CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_THICKNESS, CsCVarDrawPlayerPawnForwardThickness->GetFloat());

			DrawDebugDirectionalArrow(GetWorld(), Start, End, 10.0f, FColor::Red, false, DeltaSeconds + 0.005f, 0, Thickness);
		}
		// Right
		if (CsCVarDrawPlayerPawnRight->GetInt() == CS_CVAR_DRAW)
		{
			const FVector Start	  = GetActorLocation();
			const float Length	  = FMath::Max(CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_LENGTH, CsCVarDrawPlayerPawnRightLength->GetFloat());
			const FVector End	  = Start + Length * CurrentCapsuleVelocityRight;
			const float Thickness = FMath::Max(CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_THICKNESS, CsCVarDrawPlayerPawnRightThickness->GetFloat());

			DrawDebugDirectionalArrow(GetWorld(), Start, End, 10.0f, FColor::Green, false, DeltaSeconds + 0.005f, 0, Thickness);
		}
	}
}

// Camera
#pragma region

void ACsPlayerPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	// TODO: This should allow another client to look at another clients view point

	AController* ViewingController = Controller;

	if (!ViewingController)
		return;
	ViewingController->CalcCamera(DeltaTime, OutResult);
	OnCalcCamera_Trace(DeltaTime, OutResult);
	RecordView();
}

void ACsPlayerPawn::OnCalcCamera_Trace(const float &DeltaTime, const struct FMinimalViewInfo& ViewResult)
{
	if (!bOnCalcCamera_Trace)
		return;

	TArray<FHitResult>& OutHits = CalcCameraTraceInfo.OutHits;
	OutHits.Reset();

	const FVector Start = ViewResult.Location;
	const FVector Dir	= ViewResult.Rotation.Vector();
	const FVector End	= Start + CalcCameraTraceInfo.Range * Dir;

	CalcCameraTraceInfo.HitResult.Reset(0.0f, false);

	const bool HasHitSomething = GetWorld()->LineTraceMultiByObjectType(OutHits, Start, End, CalcCameraTraceInfo.ObjectParams, CalcCameraTraceInfo.QueryParams);

	if (HasHitSomething)
	{
		float ClosestDistanceSq = CalcCameraTraceInfo.RangeSq;
		int32 ClosestIndex		= INDEX_NONE;
		bool IgnoreActor		= false;

		const int32 HitCount = OutHits.Num();

		for (int32 Index = 0; Index < HitCount; ++Index)
		{
			IgnoreActor = false;

			if (!IgnoreActor)
			{
				float DistanceSq = FVector::DistSquared(Start, OutHits[Index].Location);

				if (DistanceSq > 0.0f && 
					DistanceSq < ClosestDistanceSq)
				{
					ClosestIndex	  = Index;
					ClosestDistanceSq = DistanceSq;
				}
			}
		}

		if (ClosestIndex != INDEX_NONE)
		{
			CalcCameraTraceInfo.HitLocation = OutHits[ClosestIndex].Location;
			
			UCsCommon::CopyHitResult(OutHits[ClosestIndex], CalcCameraTraceInfo.HitResult);
		}
		else
		{
			CalcCameraTraceInfo.HitLocation = End;
		}
	}
	else
	{
		CalcCameraTraceInfo.HitLocation = End;
	}

	if (CsCVarDrawPlayerCalcCameraTraceHitLocation->GetInt() == CS_CVAR_DRAW)
	{
		DrawDebugSphere(GetWorld(), CalcCameraTraceInfo.HitLocation, 32.0f, 16, FColor::Green, false, DeltaTime + 0.005f, 0, 1.0f);
	}
}

FRotator ACsPlayerPawn::GetViewRotation() const
{
	return Super::GetViewRotation();
}

FVector ACsPlayerPawn::GetPawnViewLocation() const
{
	if (UCsCommon::IsVive())
		return Super::GetPawnViewLocation() + FVector(0.0f, 0.0f, -2.0f * GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	return GetFeetLocation() + FVector(0.0f, 0.0f, EyeHeight);
}

FVector ACsPlayerPawn::GetFeetLocation() const
{
	return GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

#pragma endregion Camera

// View
#pragma region

void ACsPlayerPawn::RecordView()
{
	const FRotator Last_CurrentViewRotation = CurrentViewRotation;

	CurrentViewRotation		 = GetViewRotation();
	CurrentViewRotationDelta = UCsCommon::GetAngleDelta(Last_CurrentViewRotation, CurrentViewRotation);

	CurrentViewLocation = GetPawnViewLocation();
	CurrentViewDir		= CurrentViewRotation.Vector();
	CurrentViewDirXY	= FRotator(0.0f, CurrentViewRotation.Yaw, 0.0f).Vector();

	FRotator Rotation = CurrentViewRotation;

	FRotationMatrix Matrix = FRotationMatrix(Rotation);
	CurrentViewRight	   = Matrix.GetScaledAxis(EAxis::Y);
		
	Rotation = FRotator(0.0f, CurrentViewRotation.Yaw, 0.0f);

	Matrix				= FRotationMatrix(Rotation);
	CurrentViewRightXY	= Matrix.GetScaledAxis(EAxis::Y);
}

#pragma endregion View

// Managers
#pragma region

ACsManager_Inventory* ACsPlayerPawn::GetMyManager_Inventory()
{  
	ACsPlayerState* MyPlayerState = Cast<ACsPlayerState>(PlayerState);
	
	return MyPlayerState->Manager_Inventory;
}

#pragma endregion Managers