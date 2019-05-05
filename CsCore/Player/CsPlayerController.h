// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/CsTypes_Input.h"
#include "CsPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsPlayerController_OnTickActor, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsPlayerController_OnCalcCamera, const uint8&, MappingId, const float&, DeltaTime, const struct FMinimalViewInfo&, ViewInfo);

class UCsManager_Input;

UCLASS()
class CSCORE_API ACsPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	virtual void Destroyed() override;

	UPROPERTY(BlueprintAssignable, Category = "Tick")
	FBindableDynEvent_CsPlayerController_OnTickActor OnTickActor_ScriptEvent;

	virtual void OnTickActor_HandleCVars();

// Camera
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCalcCamera, const uint8&, const float&, const struct FMinimalViewInfo&);

	FOnCalcCamera OnCalcCamera_Event;

	UPROPERTY(BlueprintAssignable, Category = "Camera")
	FBindableDynEvent_CsPlayerController_OnCalcCamera OnCalcCamera_ScriptEvent;

	UPROPERTY()
	FMinimalViewInfo MinimalViewInfoCache;

	TCsFRotator ViewRotation;
	TCsFVector ViewLocation;

	UFUNCTION(BlueprintCallable, Category = "Caemra")
	virtual void SetTargetActor(AActor* InActor);

	TWeakObjectPtr<AActor> TargetActor;

	UFUNCTION(BlueprintCallable, Category = "Camera")
	AActor* GetTargetActor();

	template<typename T>
	T* GetTargetActor()
	{
		return Cast<T>(GetTargetActor());
	}

#pragma endregion Camera

// Input
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSubclassOf<UCsManager_Input> ManagerInputClass;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	UCsManager_Input* Manager_Input;

	UFUNCTION(BlueprintCallable, Category = "Input")
	int32 GetCurrentInputActionMap();
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm="ActionMap"))
	void SetCurrentInputActionMap(const FECsInputActionMap& ActionMap);
	void SetCurrentInputActionMap(const int32& ActionMap);
	UFUNCTION(BlueprintCallable, Category = "Input", meta = (AutoCreateRefTerm = "ActionMap"))
	void ClearCurrentInputActionMap(const FECsInputActionMap& ActionMap);
	void ClearCurrentInputActionMap(const int32& ActionMap);

	virtual void InitInputSystem() override;
	virtual void BindDelegatesToInputManager();
	virtual void UnBindPawnDelegatesFromInputManager();

	virtual void BuildInputStack(TArray<UInputComponent*>& InputStack) override;

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual bool CanPostProcessInput();

	TArray<FCsGameEventInfo> GameEventInfoPriorityList;

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