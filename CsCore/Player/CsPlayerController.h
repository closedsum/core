// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "CsPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerController_OnTickActor, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsPlayerController_OnCalcCamera, const uint8&, const float&, const struct FMinimalViewInfo&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPlayerController_OnCalcCamera, const uint8&, MappingId, const float&, DeltaTime, const struct FMinimalViewInfo&, ViewInfo);

UCLASS()
class CSCORE_API ACsPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerController_OnTickActor OnTickActor_ScriptEvent;

	virtual void OnTickActor_CheckCVars();

// Camera
#pragma region
public:

	FBindableEvent_CsPlayerController_OnCalcCamera OnCalcCamera_Event;

	UPROPERTY(BlueprintAssignable, Category = "Camera")
	FBindableDynEvent_CsPlayerController_OnCalcCamera OnCalcCamera_ScriptEvent;

	UPROPERTY()
	FMinimalViewInfo MinimalViewInfoCache;

#pragma endregion Camera

// Input
#pragma region
public:

	UPROPERTY()
	class ACsManager_Input* Manager_Input;
	
	virtual void BuildInputStack(TArray<UInputComponent*>& InputStack) override;

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

#if WITH_EDITOR

	// Editor - Game
#pragma region
public:

	bool HasBoundEditorGameInputCallbacks;

#pragma endregion Editor - Game

#endif // #if WITH_EDITOR

#pragma endregion Input
};