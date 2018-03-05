// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Pawn/CsPawn.h"
#include "CsPlayerPawn.generated.h"

USTRUCT(BlueprintType)
struct FCsPlayerPawnCalcCameraTraceInfo
{
	GENERATED_USTRUCT_BODY()

	FCollisionQueryParams QueryParams;

	TArray<TWeakObjectPtr<AActor>> IgnoreActors;

	FCollisionObjectQueryParams ObjectParams;

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float Range;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	float RangeSq;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	FVector HitLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	FHitResult HitResult;

	UPROPERTY(BlueprintReadWrite, Category = "Trace")
	TArray<FHitResult> OutHits;
};

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

	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	bool bOnCalcCamera_Trace;

	virtual void OnCalcCamera_Trace(const float &DeltaTime, const struct FMinimalViewInfo& ViewResult);

	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	FCsPlayerPawnCalcCameraTraceInfo CalcCameraTraceInfo;

	virtual FRotator GetViewRotation() const override;
	virtual FVector GetPawnViewLocation() const override;

	virtual FVector GetFeetLocation() const;

#pragma endregion Camera

// View
#pragma region

	virtual void RecordView() override;

#pragma endregion View

// Managers
#pragma region

	virtual class ACsManager_Inventory* GetMyManager_Inventory() override;

#pragma endregion Managers
};