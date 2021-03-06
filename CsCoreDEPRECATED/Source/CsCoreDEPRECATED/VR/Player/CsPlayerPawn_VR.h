// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Player/CsPlayerPawn.h"
#include "Types/CsTypes.h"
#include "CsPlayerPawn_VR.generated.h"

class ACsMotionController_DEPRECATED;
class UMotionControllerComponent;

UCLASS(config = Game)
class CSCOREDEPRECATED_API ACsPlayerPawn_VR : public ACsPlayerPawn
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	// Camera
#pragma region
public:

	virtual void LinkHandsToCamera(USceneComponent* CameraViewComponent);

#pragma endregion Camera


// Hands
#pragma region
public:

	TSubclassOf<ACsMotionController_DEPRECATED> MotionControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hands")
	UMotionControllerComponent* MotionControllerComponent_LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands")
	ACsMotionController_DEPRECATED* LeftHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hands")
	UMotionControllerComponent* MotionControllerComponent_RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hands")
	ACsMotionController_DEPRECATED* RightHand;

	void ShowHand(const ECsControllerHand &Hand);
	void ShowHands();

	void HideHand(const ECsControllerHand &Hand);
	void HideHands();

#pragma endregion Hands
};