// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "CsPlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerPawn_OnTick, const uint8&, MappingId, const float&, DeltaSeconds);

UCLASS(config = Game)
class CSCORE_API ACsPlayerPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerPawn_OnTick OnTick_ScriptEvent;

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

// Camera
#pragma region
public:

	float EyeHeight;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	virtual FRotator GetViewRotation() const override;
	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// View
#pragma region

	virtual void RecordView() override;

#pragma endregion View
};