// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "UI/CsUserWidget.h"
#include "Common/CsCommon.h"

ACsWidgetActor::ACsWidgetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetComponent = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent>(this, TEXT("WidgetComponent"));

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
	if (!Cache.IsAllocated)
		return;
}

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

	if (!Cache.IsAllocated)
		return;

	if (Visibility == ECsVisibility::Hidden)
		return;

	if (FollowLocalCamera)
	{
		FVector ViewLocation  = OutResult.Location;
		FRotator ViewRotation = OutResult.Rotation;
		
		if (UCsCommon::IsVR())
		{
			UCsCommon::GetHMDWorldViewPoint(GetWorld(), ViewLocation, ViewRotation);
		}
		ViewRotation.Roll = 0.f;

		const FVector Forward = ViewRotation.Vector();
		const FVector Location = ViewLocation + DistanceProjectedOutFromCamera * Forward;

		SetActorLocation(Location);

		FRotator Rotation = (-Forward).Rotation();
		Rotation.Roll     = 0.0f;
		//const FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);

		SetActorRotation(Rotation);
	}

	if (LookAtLocalCamera)
	{
		FRotator ViewRotation   = OutResult.Rotation;
		ViewRotation.Roll	    = 0.f;
		const FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);

		SetActorRotation(Rotation);
	}
}

void ACsWidgetActor::Init(const int32 &Index, const TCsWidgetActorType &InType)
{
	PoolIndex	= Index;
	Type		= InType;
	Type_Script = (uint8)Type;

	Cache.Set(Index, this);
}

template<typename T>
void ACsWidgetActor::Allocate(const uint16 &ActiveIndex, UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InWidget, Time, RealTime, Frame, InOwner, InParent, InObject, OnDeAllocate);

	Allocate_Internal(InWidget);
}

template<typename T>
void ACsWidgetActor::Allocate(const uint16 &ActiveIndex, UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Cache.Init<T>(ActiveIndex, InWidget, Time, RealTime, Frame, InObject, OnDeAllocate);

	Allocate_Internal(InWidget);
}

void ACsWidgetActor::Allocate(const uint16 &ActiveIndex, UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Cache.Init(ActiveIndex, InWidget, Time, RealTime, Frame, InOwner, InParent);

	Allocate_Internal(InWidget);
}

void ACsWidgetActor::Allocate(const uint16 &ActiveIndex, UCsUserWidget* InWidget, const float &Time, const float &RealTime, const uint64 &Frame)
{
	Cache.Init(ActiveIndex, InWidget, Time, RealTime, Frame);

	Allocate_Internal(InWidget);
}

void ACsWidgetActor::Allocate_Internal(class UCsUserWidget* InWidget)
{
	SetActorTickEnabled(true);
	WidgetComponent->Activate();
	WidgetComponent->SetComponentTickEnabled(true);
	WidgetComponent->SetWidget(InWidget);
	WidgetComponent->SetHiddenInGame(false);
	WidgetComponent->SetVisibility(true);
	Visibility = ECsVisibility::Visible;

	InWidget->Init();
}

void ACsWidgetActor::DeAllocate()
{
	Super::DeAllocate();

	UCsUserWidget* Widget = Cache.GetWidget();
	Widget->SetVisibility(ESlateVisibility::Hidden);
	Widget->SetIsEnabled(false);

	Cache.Reset();

	Visibility = ECsVisibility::Hidden;
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetHiddenInGame(true);
	WidgetComponent->SetComponentTickEnabled(false);
	WidgetComponent->Deactivate();
	WidgetComponent->SetWidget(nullptr);
	SetActorTickEnabled(false);
}

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

#pragma endregion State

void ACsWidgetActor::Show()
{
	Super::Show();

	SetActorTickEnabled(true);

	UCsUserWidget* Widget = Cache.GetWidget();

	Widget->SetIsEnabled(true);
	Widget->SetVisibility(ESlateVisibility::Visible);
	WidgetComponent->Activate();
	WidgetComponent->SetComponentTickEnabled(true);
	WidgetComponent->SetHiddenInGame(false);
	WidgetComponent->SetVisibility(true);
}

void ACsWidgetActor::Hide()
{
	Super::Hide();

	UCsUserWidget* Widget = Cache.GetWidget();

	Widget->SetIsEnabled(false);
	Widget->SetVisibility(ESlateVisibility::Hidden);
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetHiddenInGame(true);
	WidgetComponent->SetComponentTickEnabled(false);
	WidgetComponent->Deactivate();
	SetActorTickEnabled(false);
}