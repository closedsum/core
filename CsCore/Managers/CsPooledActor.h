// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsTypes.h"
#include "CsPooledActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPooledActor_Override_OnTick, const int32&, Index, const float&, DeltaSeconds);

UCLASS()
class CSCORE_API ACsPooledActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	virtual void OutsideWorldBounds() override;

	FString Warning_FellOutOfWorld;
	FString Warning_OutsideWorldBounds;

	UPROPERTY(BlueprintAssignable, Category = "Pool")
	FBindableDynEvent_CsPooledActor_Override_OnTick Override_OnTick_ScriptEvent;

	virtual void OnTick(const float &DeltaSeconds);
	virtual void OnTick_CheckCVars(const float &DeltaSeconds);

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	int32 PoolIndex;

	virtual void DeAllocate();

	UPROPERTY(BlueprintReadWrite, Category = "Pool")
	bool IsAllocated;

	virtual void OnCreatePool();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	bool IsPlaceable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pool")
	TEnumAsByte<ECsVisibility::Type> Visibility;

	virtual void Show();
	virtual void Hide();
};