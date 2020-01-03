// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"

// Managers
#include "Managers/Widget/CsPooledWidget.h"

#include "Components/CsWidgetComponent.h"

#include "UI/CsUserWidget.h"

#include "Player/CsPlayerController.h"
#include "Pawn/CsPawn.h"

ACsWidgetActor::ACsWidgetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetComponent = ObjectInitializer.CreateDefaultSubobject<UCsWidgetComponent>(this, TEXT("WidgetComponent"));

	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetHiddenInGame(true);
	WidgetComponent->SetCollisionObjectType(ECC_Visibility);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->SetCastShadow(false);
	WidgetComponent->SetMobility(EComponentMobility::Movable);
	SetRootComponent(WidgetComponent);
	WidgetComponent->Deactivate();
}

void ACsWidgetActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WidgetComponent->SetComponentTickEnabled(false);
}

void ACsWidgetActor::Tick(float DeltaSeconds)
{
	if (!Cache.bAllocated)
		return;

	Cache.ElapsedTime += DeltaSeconds;

	if (Cache.bMinDrawDistance)
		OnTick_Handle_DrawDistance();

	if (Visibility == ECsVisibility::Hidden)
		return;

	if (Cache.ScaleByDistance)
		OnTick_Handle_Scale();

	ACsPlayerController* LocalController = UCsLibrary_Common::GetLocalPlayerController<ACsPlayerController>(GetWorld());

	OnTick_Handle_LocalCamera(LocalController->MinimalViewInfoCache.Location, LocalController->MinimalViewInfoCache.Rotation);

	if (Cache.bMovementFunction)
		OnTick_HandleMovementFunction();
}

void ACsWidgetActor::Init(const int32 &Index, const FECsWidgetActorType &InType)
{
	PoolIndex	= Index;
	Type		= InType;

	Cache.Set(Index, this);
}

// Allocate / DeAllocate
#pragma region

void ACsWidgetActor::Allocate( FCsWidgetActorPayload* Payload)
{
	Cache.Init(Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsLibrary_Common::GetCurrentFrame(GetWorld()));

	Allocate_Internal(Payload);
}

void ACsWidgetActor::Allocate_Internal(FCsWidgetActorPayload* Payload)
{
	if (bCacheWidget)
	{
		Cache.Widget = MyWidget;
	}
	else
	{
		MyWidget = Cache.GetWidget();
		WidgetComponent->SetWidget(MyWidget);
	}

	SetActorTickEnabled(true);
	WidgetComponent->Show();
	Visibility = ECsVisibility::Visible;

	//InWidget->Init();
}

void ACsWidgetActor::DeAllocate()
{
	Super::DeAllocate();

	Cache.Reset();

	Visibility = ECsVisibility::Hidden;
	WidgetComponent->Hide();

	if (!bCacheWidget)
	{
		WidgetComponent->SetWidget(nullptr);

		if (UCsPooledWidget* PooledWidget = Cast<UCsPooledWidget>(MyWidget))
		{
			PooledWidget->Cache.bLifeTime = true;
			PooledWidget->Cache.LifeTime = 0.0f;
		}
		MyWidget = nullptr;
	}
	SetActorTickEnabled(false);
}

#pragma endregion Allocate / DeAllocate

// Camera
#pragma region

void ACsWidgetActor::OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult)
{
#if WITH_EDITOR
	if (Override_OnCalcCamera_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsWidgetActor::OnCalcCamera (%s): Using Override Function."), *GetName());
		}
		Override_OnCalcCamera_ScriptEvent.Broadcast(PoolIndex, MappingId, DeltaTime, OutResult);
		return;
	}
#endif // #if WITH_EDITOR

	if (!Cache.bAllocated)
		return;
	if (Visibility == ECsVisibility::Hidden)
		return;

	OnTick_Handle_LocalCamera(OutResult.Location, OutResult.Rotation);
}

void ACsWidgetActor::OnTick_Handle_LocalCamera(const FVector &ViewLocation, const FRotator &ViewRotation)
{
	FVector CameraLocation = ViewLocation;
	FRotator CameraRotation = ViewRotation;

	if (Cache.FollowCamera)
	{
		if (UCsLibrary_Common::IsVR())
		{
			UCsLibrary_Common::GetHMDWorldViewPoint(GetWorld(), CameraLocation, CameraRotation);
		}
		CameraRotation.Roll = 0.f;

		const FVector Forward = ViewRotation.Vector();
		const FVector Location = ViewLocation + DistanceProjectedOutFromCamera * Forward;

		SetActorLocation(Location);

		FRotator Rotation = (-Forward).Rotation();
		Cache.CameraLockAxes.ApplyLock(Rotation);
		//Rotation.Roll = 0.0f;
		//const FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);

		SetActorRotation(Rotation);
	}
	else
	if (Cache.LookAtCamera)
	{
		FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);
		Cache.CameraLockAxes.ApplyLock(Rotation);

		SetActorRotation(Rotation);
	}
}

#pragma endregion Camera

// State
#pragma region

void ACsWidgetActor::OnInteraction_Script(const TEnumAsByte<ECsInteractiveState::Type> &InState, const FCsInteractedActorInfo &Info)
{
	if (InState == ECsInteractiveState::FirstFreeze) { OnFirstFreeze(Info); return; }
	if (InState == ECsInteractiveState::Freeze) { OnFreeze(Info); return; }
	if (InState == ECsInteractiveState::FirstUnFreeze) { OnFirstUnFreeze(Info); return; }
	if (InState == ECsInteractiveState::FirstHold) { OnFirstHold(Info); return; }
	if (InState == ECsInteractiveState::Hold) { OnHold(Info); return; }
	if (InState == ECsInteractiveState::Release) { OnRelease(Info); return; }
	if (InState == ECsInteractiveState::FirstTouch) { OnFirstTouch(Info); return; }
	if (InState == ECsInteractiveState::Touch) { OnTouch(Info); return; }
	if (InState == ECsInteractiveState::FirstHover) { OnFirstHover(Info); return; }
	if (InState == ECsInteractiveState::Hover) { OnHover(Info); return; }
	if (InState == ECsInteractiveState::FirstUnHover) { OnFirstUnHover(Info); return; }
	if (InState == ECsInteractiveState::FirstCollide) { OnFirstCollide(Info); return; }
	if (InState == ECsInteractiveState::Collide) { OnCollide(Info); return; }
	if (InState == ECsInteractiveState::FirstUnCollide) { OnFirstUnCollide(Info); return; }
	if (InState == ECsInteractiveState::Remove) { OnRemove(Info); return; }
}

void ACsWidgetActor::OnInteraction(const FCsInteractedActorInfo &Info)
{
}

void ACsWidgetActor::OnFirstFreeze(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstFreeze;
}

void ACsWidgetActor::OnFreeze(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Freeze;
}

void ACsWidgetActor::OnFirstUnFreeze(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstUnFreeze;
}

void ACsWidgetActor::OnFirstHold(const FCsInteractedActorInfo &Info)
{
	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::FirstHold;
}

void ACsWidgetActor::OnHold(const FCsInteractedActorInfo &Info)
{
	if (State != ECsInteractiveState::FirstCollide && State != ECsInteractiveState::Collide)
		State = ECsInteractiveState::Hold;
}

void ACsWidgetActor::OnRelease(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Release;
}

void ACsWidgetActor::OnFirstTouch(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstTouch;
}

void ACsWidgetActor::OnTouch(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Touch;
}

void ACsWidgetActor::OnFirstHover(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstHover;
}

void ACsWidgetActor::OnHover(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Hover;
}

void ACsWidgetActor::OnFirstUnHover(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstUnHover;
}

void ACsWidgetActor::OnFirstCollide(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstCollide;
}

void ACsWidgetActor::OnCollide(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Collide;
}

void ACsWidgetActor::OnFirstUnCollide(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::FirstUnCollide;
}

void ACsWidgetActor::OnRemove(const FCsInteractedActorInfo &Info)
{
	State = ECsInteractiveState::Remove;
}

void ACsWidgetActor::OnTick_Handle_Scale()
{
	ACsPawn* LocalPawn   = UCsLibrary_Common::GetLocalPawn<ACsPawn>(GetWorld());
	const float Distance = (LocalPawn->GetActorLocation() - GetActorLocation()).Size2D();
	const float Scale	 = Cache.MinDrawDistance.Distance > 0 ? Distance / Cache.MinDrawDistance.Distance : 1.0f;

	SetActorScale3D(Scale * Cache.Scale);
}

#pragma endregion State

// Visibility
#pragma region

void ACsWidgetActor::Show()
{
	Super::Show();

	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	WidgetComponent->Show();
}

void ACsWidgetActor::Hide()
{
	Super::Hide();

	WidgetComponent->Hide();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ACsWidgetActor::OnTick_Handle_DrawDistance()
{
	ACsPawn* LocalPawn	   = UCsLibrary_Common::GetLocalPawn<ACsPawn>(GetWorld());
	const float DistanceSq = (LocalPawn->GetActorLocation() - GetActorLocation()).SizeSquared2D();

	if (DistanceSq < Cache.MinDrawDistance.DistanceSq)
	{
		if (Visibility == ECsVisibility::Visible)
			Hide();
	}
	else
	{
		if (Visibility == ECsVisibility::Hidden)
			Show();
	}
}

#pragma endregion Visiblity

// Movement
#pragma region

void ACsWidgetActor::OnTick_HandleMovementFunction()
{
	const float Percent = Cache.LifeTime > 0.0f ? Cache.ElapsedTime / Cache.LifeTime : 1.0f;
	FVector Location	= Cache.MovementFunction.Evaluate(Percent, Cache.Location, FTransform::Identity);

	SetActorLocation(Location);
}

#pragma endregion Movement