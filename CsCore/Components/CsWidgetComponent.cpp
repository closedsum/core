// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsWidgetComponent.h"
#include "CsCore.h"
#include "Types/CsTypes.h"
#include "UI/CsUserWidget.h"

UCsWidgetComponent::UCsWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsWidgetComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bOnCalcCamera)
		return;
	OnTick_Handle_LocalCamera();
}

UCsUserWidget* UCsWidgetComponent::GetWidget()
{
	return Cast<UCsUserWidget>(Widget);
}

void UCsWidgetComponent::OnCalcCamera(const uint8 &MappingId, const float &DeltaTime, const struct FMinimalViewInfo &OutResult)
{
	OnTick_Handle_LocalCamera();
}

void UCsWidgetComponent::OnTick_Handle_LocalCamera()
{
	if (bHiddenInGame || !bVisible)
		return;
	if (!FollowLocalCamera && !LookAtLocalCamera)
		return;
}

void UCsWidgetComponent::SetInfo(const FVector2D &Size, const FTransform &Transform, const bool &InFollowLocalCamera, const bool &InLookAtLocalCamera)
{
	SetDrawSize(DrawSize);
	SetRelativeTransform(Transform);

	FollowLocalCamera = InFollowLocalCamera;
	LookAtLocalCamera = InLookAtLocalCamera;
}

void UCsWidgetComponent::SetInfo(const FCsWidgetComponentInfo &Info)
{
	SetInfo(Info.DrawSize, Info.Transform, Info.FollowCamera, Info.LookAtCamera);
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