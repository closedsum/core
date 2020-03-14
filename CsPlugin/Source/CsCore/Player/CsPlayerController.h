// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "Types/CsTypes_Primitive.h"
#include "Types/Property/Value/CsProperty_Rotator.h"
#include "Types/Property/Value/CsProperty_Vector.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsPlayerController_OnTickActor, const uint8&, MappingId, const float&, DeltaSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsPlayerController_OnCalcCamera, const uint8&, MappingId, const float&, DeltaTime, const struct FMinimalViewInfo&, ViewInfo);

class UCsManager_Input;

UCLASS()
class CSCORE_API ACsPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	virtual void Destroyed() override;

	UPROPERTY(BlueprintAssignable, Category = "Player|Tick")
	FCsPlayerController_OnTickActor OnTickActor_ScriptEvent;

	virtual void OnTickActor_HandleCVars();

// Camera
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCalcCamera, const uint8&, const float&, const struct FMinimalViewInfo&);

	FOnCalcCamera OnCalcCamera_Event;

	UPROPERTY(BlueprintAssignable, Category = "Player|Camera")
	FCsPlayerController_OnCalcCamera OnCalcCamera_ScriptEvent;

	UPROPERTY()
	FMinimalViewInfo MinimalViewInfoCache;

	TCsFRotator ViewRotation;
	TCsFVector ViewLocation;

	UFUNCTION(BlueprintCallable, Category = "Player|Caemra")
	virtual void SetTargetActor(AActor* InActor);

	TWeakObjectPtr<AActor> TargetActor;

	UFUNCTION(BlueprintCallable, Category = "Player|Camera")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player|Input")
	TSubclassOf<UCsManager_Input> ManagerInputClass;

	UPROPERTY()
	UCsManager_Input* Manager_Input;

	UFUNCTION(BlueprintCallable, Category = "Player|Input")
	int32 GetCurrentInputActionMap();
	UFUNCTION(BlueprintCallable, Category = "Player|Input", meta = (AutoCreateRefTerm="ActionMap"))
	void SetCurrentInputActionMap(const FECsInputActionMap& ActionMap);
	void SetCurrentInputActionMap(const int32& ActionMap);
	UFUNCTION(BlueprintCallable, Category = "Player|Input", meta = (AutoCreateRefTerm = "ActionMap"))
	void ClearCurrentInputActionMap(const FECsInputActionMap& ActionMap);
	void ClearCurrentInputActionMap(const int32& ActionMap);

	virtual void InitInputSystem() override;

#if WITH_EDITOR

	// Editor - Game
#pragma region
public:

	bool HasBoundEditorGameInputCallbacks;

#pragma endregion Editor - Game

#endif // #if WITH_EDITOR

#pragma endregion Input
};