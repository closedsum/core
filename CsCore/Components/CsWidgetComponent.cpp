// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsWidgetComponent.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "Common/CsCommon.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Pawn/CsPawn.h"
#include "Player/CsPlayerController.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bOnCalcCamera)
		return;

	ACsPlayerController* LocalController = UCsCommon::GetLocalPlayerController<ACsPlayerController>(GetWorld());

	OnTick_Handle_LocalCamera(LocalController->MinimalViewInfoCache.Location, LocalController->MinimalViewInfoCache.Rotation);
}

UUserWidget* UCsWidgetComponent::GetWidget()
{
	return Widget;
}

void UCsWidgetComponent::OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult)
{
	OnTick_Handle_LocalCamera(OutResult.Location, OutResult.Rotation);
}
																			  
void UCsWidgetComponent::OnTick_Handle_LocalCamera(const FVector &ViewLocation, const FRotator &ViewRotation)
{
	if (bHiddenInGame || !bVisible)
		return;
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
	
	DistanceProjectedOutFromCamera = Info.DistanceProjectedOutFromCamera;
	CameraLockAxes				   = Info.LockAxes;
}

void UCsWidgetComponent::SetInfo(const FCsWidgetActorInfo &Info)
{
	SetInfo(Info.DrawSize, Info.Transform, false, false);
}

void UCsWidgetComponent::Show()
{
	Widget->SetIsEnabled(true);
	Widget->SetVisibility(ESlateVisibility::Visible);
	Activate();
	SetComponentTickEnabled(true);
	SetHiddenInGame(false);
	SetVisibility(true);
}

void UCsWidgetComponent::Hide()
{
	Widget->SetIsEnabled(false);
	Widget->SetVisibility(ESlateVisibility::Hidden);
	SetVisibility(false);
	SetHiddenInGame(true);
	SetComponentTickEnabled(false);
	Deactivate();
}