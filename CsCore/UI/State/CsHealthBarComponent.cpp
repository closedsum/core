// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/State/CsHealthBarComponent.h"
#include "CsCore.h"

#include "UI/State/CsWidget_HealthBar.h"

UCsHealthBarComponent::UCsHealthBarComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCsHealthBarComponent::OnChange_Health(const uint8 &MappingId, const float &CurrentHealth, const float &CurrentMaxHealth)
{
	const float Percent = CurrentHealth / CurrentMaxHealth;

	GetWidget<UCsWidget_HealthBar>()->SetPercent(Percent);
}

void UCsHealthBarComponent::OnLocalClientSeesMe(const uint64 &ObserverId, const uint64& ObserveeId, const bool& Value)
{
	if (Value)
		Show();
	else
		Hide();
}