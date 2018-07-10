// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "CsPlayerPawn.generated.h"

// Enums
#pragma region

#pragma endregion Enums

UCLASS(config = Game)
class CSCORE_API ACsPlayerPawn : public ACsPawn
{
	GENERATED_UCLASS_BODY()

	virtual void OnTickActor_HandleCVars(const float &DeltaSeconds);

// Camera
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	float EyeHeight;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	virtual void OnCalcCamera_Trace(const float &DeltaTime, const struct FMinimalViewInfo& ViewResult);

	virtual FRotator GetViewRotation() const override;
	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// View
#pragma region
public:

	virtual void PerformViewTrace_Response(const uint8 &RequestId, FCsTraceResponse* Response) override;
	virtual void RecordView() override;

#pragma endregion View

// Managers
#pragma region
public:

	virtual class ACsManager_Inventory* GetMyManager_Inventory() override;

#pragma endregion Managers
};