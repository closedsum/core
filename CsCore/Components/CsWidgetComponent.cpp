// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsWidgetComponent.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "Common/CsCommon.h"

// UI
#include "UI/CsUserWidget.h"
#include "UI/Simple/CsSimpleWidget.h"

#include "Pawn/CsPawn.h"
#include "Player/CsPlayerController.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bMinDrawDistance)
		OnTick_Handle_DrawDistance();

	if (Visibility == ECsVisibility::Hidden)
		return;

	if (ScaleByDistance)
		OnTick_Handle_Scale();

	if (!bOnCalcCamera)
	{
		ACsPlayerController* LocalController = UCsCommon::GetLocalPlayerController<ACsPlayerController>(GetWorld());

		OnTick_Handle_LocalCamera(LocalController->MinimalViewInfoCache.Location, LocalController->MinimalViewInfoCache.Rotation);
	}

	if (!FollowLocalCamera && FollowOwner)
		OnTick_Handle_Movement();
}

UUserWidget* UCsWidgetComponent::GetWidget()
{
	return Widget;
}

// Camera
#pragma region

void UCsWidgetComponent::OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult)
{
	if (Visibility == ECsVisibility::Hidden)
		return;

	OnTick_Handle_LocalCamera(OutResult.Location, OutResult.Rotation);
}
																			  
void UCsWidgetComponent::OnTick_Handle_LocalCamera(const FVector &ViewLocation, const FRotator &ViewRotation)
{
	if (!FollowLocalCamera && !LookAtLocalCamera)
		return;

	FVector CameraLocation = ViewLocation;
	FRotator CameraRotation = ViewRotation;

	if (FollowLocalCamera)
	{
		if (UCsCommon::IsVR())
		{
			UCsCommon::GetHMDWorldViewPoint(GetWorld(), CameraLocation, CameraRotation);
		}
		CameraRotation.Roll = 0.f;

		const FVector Forward = ViewRotation.Vector();
		const FVector Location = ViewLocation + DistanceProjectedOutFromCamera * Forward;

		SetWorldLocation(Location);

		FRotator Rotation = (-Forward).Rotation();
		CameraLockAxes.ApplyLock(Rotation);
		//Rotation.Roll = 0.0f;
		//const FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);

		SetWorldRotation(Rotation);
	}
	else
	if (LookAtLocalCamera)
	{
		//ViewRotation.Roll = 0.f;
		FRotator Rotation = FRotator(-ViewRotation.Pitch, ViewRotation.Yaw + 180.0f, 0.0f);
		CameraLockAxes.ApplyLock(Rotation);

		SetWorldRotation(Rotation);
	}
}

#pragma endregion Camera

// Info
#pragma region

void UCsWidgetComponent::SetInfo(const FVector2D &Size, const FTransform &Transform, const bool &InFollowLocalCamera, const bool &InLookAtLocalCamera)
{
	SetDrawSize(Size);
	SetRelativeTransform(Transform);

	FollowLocalCamera = InFollowLocalCamera;
	LookAtLocalCamera = InLookAtLocalCamera;
}

void UCsWidgetComponent::SetInfo(const FCsWidgetComponentInfo &Info)
{
	SetInfo(Info.DrawSize, Info.Transform, Info.FollowCamera, Info.LookAtCamera);
	
	DistanceProjectedOutFromCamera	= Info.DistanceProjectedOutFromCamera;
	CameraLockAxes					= Info.LockAxes;
	bMinDrawDistance				= Info.bMinDrawDistance;
	MyMinDrawDistance				= Info.MinDrawDistance;
	ScaleByDistance					= Info.ScaleByDistance;
	FollowOwner						= Info.FollowOwner;
	LocationOffset					= Info.Transform.GetTranslation();
}

void UCsWidgetComponent::SetInfo(const FCsWidgetActorInfo &Info)
{
	SetInfo(Info.DrawSize, Info.Transform, false, false);
}

#pragma endregion Info

// Visibility
#pragma region

void UCsWidgetComponent::Show()
{
	Visibility = ECsVisibility::Visible;

	if (UCsUserWidget* UserWidget = Cast<UCsUserWidget>(Widget))
	{
		UserWidget->Show();
	}
	else
	if (UCsSimpleWidget* SimpleWidget = Cast<UCsSimpleWidget>(Widget))
	{
		SimpleWidget->Show();
	}
	else
	if (Widget)
	{
		Widget->SetIsEnabled(true);
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
	Activate();
	SetComponentTickEnabled(true);
	SetHiddenInGame(false);
	SetVisibility(true);
}

void UCsWidgetComponent::Hide()
{
	Visibility = ECsVisibility::Hidden;

	if (UCsUserWidget* UserWidget = Cast<UCsUserWidget>(Widget))
	{
		UserWidget->Hide();
	}
	else
	if (UCsSimpleWidget* SimpleWidget = Cast<UCsSimpleWidget>(Widget))
	{
		SimpleWidget->Hide();
	}
	else
	if (Widget)
	{
		Widget->SetIsEnabled(false);
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
	SetVisibility(false);
	SetHiddenInGame(true);
	SetComponentTickEnabled(false);
	Deactivate();
}

void UCsWidgetComponent::OnTick_Handle_Scale()
{
	ACsPawn* LocalPawn	 = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());
	const float Distance = (LocalPawn->GetActorLocation() - GetComponentLocation()).Size2D();
	const float Scale	 = MyMinDrawDistance.Distance > 0 ? Distance / MyMinDrawDistance.Distance : 1.0f;

	SetRelativeScale3D(Scale * FVector::OneVector);
}

void UCsWidgetComponent::OnTick_Handle_DrawDistance()
{
	ACsPawn* LocalPawn	   = UCsCommon::GetLocalPawn<ACsPawn>(GetWorld());
	const float DistanceSq = (LocalPawn->GetActorLocation() - GetComponentLocation()).SizeSquared2D();

	if (DistanceSq < MyMinDrawDistance.DistanceSq)
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

#pragma endregion Visibility

// Movement
#pragma region

void UCsWidgetComponent::OnTick_Handle_Movement()
{
	const FVector Location = GetOwner()->GetActorLocation() + LocationOffset;

	SetWorldLocation(Location);
}

#pragma endregion Movement