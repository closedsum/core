#pragma once

#include "GameFramework/Actor.h"
#include "Types/R6Types_Input.h"
#include "R6Manager_Input.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_OnAction, const FECsInputAction&, Action, const ECsInputEvent&, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_OnAxis, const FECsInputAction&, Action, const float&, Value);

#pragma endregion Delegates

class APlayerController;

UCLASS()
class CSCORE_API ACsManager_Input : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	APlayerController* MyOwner;

	virtual void Init();

	virtual void SetupInputCompoonet();

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused);

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float CurrentDeltaTime;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	int32 CurrentInputFrameIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FCsInputFrame CurrentInputFrame;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	TArray<FCsInput> QueuedInputsForNextFrame;

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void QueueInput(FECsInputAction Action, ECsInputEvent Event, float Value = 0.0f, FVector Location = FVector::ZeroVector, FRotator Rotation = FRotator::ZeroRotator);

	bool TryAddInput(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value = 0.0f, const FVector& Location = FVector::ZeroVector, const FRotator& Rotation = FRotator::ZeroRotator);

	bool CanAddInput(const FECsInputAction& Action);

	ECsInputEvent ProcessInputEvent(const ECsInputType& Type, const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value, const FVector& Location, const FRotator& Rotation);

	virtual void AddInput(const FECsInputAction& Action, const ECsInputEvent& Event, const float& Value=0.0f, const FVector& Location=FVector::ZeroVector, const FRotator& Rotation=FRotator::ZeroRotator);

// Action Map
#pragma region
public:

	TMap<FECsInputAction, FCsInputEventInfo> InputActionEventInfoMap;

	void SetupInputActionEventInfoMap();

	TMap<FECsInputActionMap, TSet<FECsInputAction>> InputActionMappings;

	void SetupInputActionMapping();

	UFUNCTION(BlueprintNativeEvent, Category = "Action Map")
	void BP_GetInputActionNamesFromMapping(const FECsInputActionMap& Map, TArray<FName>& OutNames);

	UPROPERTY(BlueprintReadOnly, Category = "Action Map")
	TMap<FECsInputAction, int32> InputActionMapping;

	UPROPERTY(BlueprintReadWrite, Category = "Action Map")
	int32 CurrentInputActionMap;

	UFUNCTION(BlueprintCallable, Category = "Action Map")
	void SetInputActionMappingByMap(FECsInputActionMap Map);

#pragma endregion Action Map

// Actions
#pragma region
public:

	// Action

	UPROPERTY(BlueprintAssignable, Category = "Actions")
	FBindableDynEvent_CsManagerInput_OnAction OnAction_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAction, const FECsInputAction&, const ECsInputEvent&);

	FOnAction OnAction_Event;

	// Axis

	UPROPERTY(BlueprintAssignable, Category = "Actions")
	FBindableDynEvent_CsManagerInput_OnAxis OnAxis_ScriptEvent;

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAxis, const FECsInputAction&, const float&);

	FOnAxis OnAxis_Event;

#pragma endregion Actions

// Events
#pragma region
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TMap<FECsGameEvent, FCsInputSentence> GameEventDefinitions;

	void SetupGameEventDefinitions();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Events")
	void BP_GetGameEventDefinitionSimpleFromGameEvent(const FECsGameEvent& Event, FCsGameEventDefinitionSimpleInfo& Def);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<FECsGameEvent> GameEventPriorityList;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TMap<FECsGameEvent, int32> GameEventPriorityMap;

	TArray<FCsGameEventInfo> CurrentGameEventInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TArray<FCsGameEventInfo> CurrentValidGameEventInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Events")
	TArray<FCsGameEventInfo> QueuedGameEventInfosForNextFrame;

#if WITH_EDITOR
	void LogProcessGameEventDefinition(const FString& FunctionName, const FECsGameEvent& Event, const FCsInputSentence& Sentence);
#endif // #if WITH_EDITOR

	virtual void QueueGameEvent(const FECsGameEvent& Event);

#pragma endregion Events
};
