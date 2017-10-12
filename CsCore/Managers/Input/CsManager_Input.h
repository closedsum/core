// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "Types/CsTypes_Input.h"
#include "CsManager_Input.generated.h"

#define CS_INPUT_POOL_SIZE 65535
#define CS_MAX_INPUT_FRAMES 300

// TODO: Future: It doesn't seem necessary to have a "generic" call back that takes in the action and event at this point

// Input Delegates
#pragma region

	// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput, const uint8&, Action, const TEnumAsByte<ECsInputEvent::Type>&, Event);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput, AActor*, const uint8&, const TEnumAsByte<ECsInputEvent::Type>&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_FirstPressed, const uint8&, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_Pressed, const uint8&, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_FirstReleased, const uint8&, Action);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_FirstPressed, AActor*, const uint8&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_Pressed, AActor*, const uint8&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_FirstReleased, AActor*, const uint8&);

	// Axis
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManagerInput_Axis, const uint8&, Action, const TEnumAsByte<ECsInputEvent::Type>&, Event, const float&, Val);
DECLARE_MULTICAST_DELEGATE_FourParams(FBindableEvent_CsManagerInput_Axis, AActor*, const uint8&, const TEnumAsByte<ECsInputEvent::Type>&, const float&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Axis_FirstMoved, const uint8&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Axis_Moved, const uint8&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Axis_FirstStationary, const uint8&, Action, const float&, Val);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Axis_Stationary, const uint8&, Action, const float&, Val);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Axis_FirstMoved, AActor*, const uint8&, const float&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Axis_Moved, AActor*, const uint8&, const float&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Axis_FirstStationary, AActor*, const uint8&, const float&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Axis_Stationary, AActor*, const uint8&, const float&);

	// Location
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManagerInput_Location, const uint8&, Action, const TEnumAsByte<ECsInputEvent::Type>&, Event, const FVector&, Location);
DECLARE_MULTICAST_DELEGATE_FourParams(FBindableEvent_CsManagerInput_Location, AActor*, const uint8&, const TEnumAsByte<ECsInputEvent::Type>&, const FVector&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Location_FirstMoved, const uint8&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Location_Moved, const uint8&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Location_FirstStationary, const uint8&, Action, const FVector&, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Location_Stationary, const uint8&, Action, const FVector&, Location);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Location_FirstMoved, AActor*, const uint8&, const FVector&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Location_Moved, AActor*, const uint8&, const FVector&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Location_FirstStationary, AActor*, const uint8&, const FVector&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Location_Stationary, AActor*, const uint8&, const FVector&);

DECLARE_DELEGATE_OneParam(FBindableCall_CsManagerInput_Location_Raw, const FVector&);

	// Rotation
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBindableDynEvent_CsManagerInput_Rotation, const uint8&, Action, const TEnumAsByte<ECsInputEvent::Type>&, Event, const FRotator&, Rotation);
DECLARE_MULTICAST_DELEGATE_FourParams(FBindableEvent_CsManagerInput_Rotation, AActor*, const uint8&, const TEnumAsByte<ECsInputEvent::Type>&, const FRotator&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Rotation_FirstMoved, const uint8&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Rotation_Moved, const uint8&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Rotation_FirstStationary, const uint8&, Action, const FRotator&, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsManagerInput_Rotation_Stationary, const uint8&, Action, const FRotator&, Rotation);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Rotation_FirstMoved, AActor*, const uint8&, const FRotator&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Rotation_Moved, AActor*, const uint8&, const FRotator&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Rotation_FirstStationary, AActor*, const uint8&, const FRotator&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FBindableEvent_CsManagerInput_Rotation_Stationary, AActor*, const uint8&, const FRotator&);

DECLARE_DELEGATE_OneParam(FBindableCall_CsManagerInput_Rotation_Raw, const FRotator&);

// Macros - Should ONLY be used for testing
#pragma region

/*
#define CS_DECLARE_INPUT_AXIS_DELEGATES(INPUT)	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_On##INPUT##_FirstMoved, const float&, Val) \
												DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_On##INPUT##_Moved, const float&, Val); \
												DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_On##INPUT##_FirstStationary, const float&, Val); \
												DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsManagerInput_On##INPUT##_Stationary, const float&, Val); \
												DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_On##INPUT##_FirstMoved, AActor*, const float&); \
												DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_On##INPUT##_Moved, AActor*, const float&); \
												DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_On##INPUT##_FirstStationary, AActor*, const float&); \
												DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsManagerInput_On##INPUT##_Stationary, AActor*, const float&);
*/

/*
// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_DECLARE_INPUT_AXIS_MEMBERS(CLASS, INPUT)	FCsInput Input_Last_##INPUT; \
													void INPUT##_Raw(float Val); \
													void INPUT##_FirstMoved(const float &Val); \
													UPROPERTY(BlueprintAssignable, Category = "Input") \
													FBindableDynEvent_##CLASS##_On##INPUT##_FirstMoved On##INPUT##_FirstMoved_ScriptEvent; \
													FBindableEvent_##CLASS##_On##INPUT##_FirstMoved On##INPUT##_FirstMoved_Event; \
													void INPUT##_Moved(const float &Val); \
													UPROPERTY(BlueprintAssignable, Category = "Input") \
													FBindableDynEvent_##CLASS##_On##INPUT##_Moved On##INPUT##_Moved_ScriptEvent; \
													FBindableEvent_##CLASS##_On##INPUT##_Moved On##INPUT##_Moved_Event; \
													void INPUT##_FirstStationary(const float &Val); \
													UPROPERTY(BlueprintAssignable, Category = "Input") \
													FBindableDynEvent_##CLASS##_On##INPUT##_FirstStationary On##INPUT##_FirstStationary_ScriptEvent; \
													FBindableEvent_##CLASS##_On##INPUT##_FirstStationary On##INPUT##_FirstStationary_Event; \
													void INPUT##_Stationary(const float &Val); \
													UPROPERTY(BlueprintAssignable, Category = "Input") \
													FBindableDynEvent_##CLASS##_On##INPUT##_Stationary On##INPUT##_Stationary_ScriptEvent; \
													FBindableEvent_##CLASS##_On##INPUT##_Stationary On##INPUT##_Stationary_Event; \
*/

#define CS_INPUT_DEFINE_TYPES	InputActionToString = &ECsInputAction::ToString; \
								StringToInputAction = &ECsInputAction::ToType; \
								InputAction_MAX = ECsInputAction::ECsInputAction_MAX; \
								InputActionMapToString = &ECsInputActionMap::ToString; \
								StringToInputActionMap = &ECsInputActionMap::ToBitMask;

// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_DECLARE_INPUT_ACTION_MEMBERS(INPUT)	FCsInputInfo INPUT; \
												void INPUT##_FirstPressed(); \
												void INPUT##_Pressed(); \
												void INPUT##_FirstReleased();

#define CS_DEFINE_INPUT_ACTION_VALUES(INPUT) Infos[ECsInputAction::INPUT] = &INPUT; \
											 INPUT.Type = ECsInputType::Action; \
											 INPUT.ValueType = ECsInputValue::Void; \
											 Actions[ECsInputAction::INPUT] = &INPUT.Event; \
											 INPUT.Event = ECsInputEvent::Released; \
											 Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
											 INPUT.Last_Event = ECsInputEvent::Released; \
											 
// Example: CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_DEFINE_INPUT_ACTION_MEMBERS(CLASS, INPUT, MAP)	void CLASS::INPUT##_FirstPressed() \
															{ \
																if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																	return; \
																INPUT.Event = ECsInputEvent::FirstPressed; \
																AddInput(ECsInputAction::INPUT, ECsInputEvent::FirstPressed); \
															} \
															void CLASS::INPUT##_Pressed() \
															{ \
																if (INPUT.Last_Event == ECsInputEvent::FirstPressed) \
																	INPUT.Event = ECsInputEvent::Pressed; \
																AddInput(ECsInputAction::INPUT, ECsInputEvent::Pressed); \
															} \
															void CLASS::INPUT##_FirstReleased() \
															{ \
																if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																	return; \
																INPUT.Event = ECsInputEvent::FirstReleased; \
																AddInput(ECsInputAction::INPUT, ECsInputEvent::FirstReleased); \
															}

// Example: THIS = this, CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = Fire
#define CS_BIND_ACTION_INPUT(THIS, CLASS, INPUT) 	InputComponent->BindAction(#INPUT, IE_Pressed, this, &CLASS::INPUT##_FirstPressed).bConsumeInput = false; \
													InputComponent->BindAction(#INPUT, IE_Released, this, &CLASS::INPUT##_FirstReleased).bConsumeInput = false;

#define CS_IS_INPUT_ACTION_FIRST_PRESSED(Input, ACTION) Input->Action == ECsInputAction::ACTION && Input->Event == ECsInputEvent::FirstPressed

// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_DECLARE_INPUT_AXIS_MEMBERS(INPUT)	FCsInputInfo INPUT; \
												FCsInput Input_Last_##INPUT; \
												void INPUT##_Raw(float Val); \
												void INPUT##_FirstMoved(const float &Val); \
												void INPUT##_Moved(const float &Val); \
												void INPUT##_FirstStationary(const float &Val); \
												void INPUT##_Stationary(const float &Val);

#define CS_DEFINE_INPUT_AXIS_VALUES(INPUT)	Infos[ECsInputAction::INPUT] = &INPUT; \
											INPUT.Type = ECsInputType::Axis; \
											INPUT.ValueType = ECsInputValue::Float; \
											Actions[ECsInputAction::INPUT] = &INPUT.Event; \
											INPUT.Event = ECsInputEvent::Stationary; \
											Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
											INPUT.Last_Event = ECsInputEvent::Stationary; \

// Example: CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_DEFINE_INPUT_AXIS_MEMBERS(CLASS, INPUT, MAP)	void CLASS::INPUT##_Raw(float Val) \
														{ \
															if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																return; \
															if (Val != 0.0f && INPUT.Value == 0.0f) \
																INPUT##_FirstMoved(Val); \
															else \
															if (Val != 0.0f && INPUT.Value != 0.0f) \
																INPUT##_Moved(Val); \
															else \
															if (Val == 0.0f && INPUT.Value != 0.0f) \
																INPUT##_FirstStationary(Val); \
															else \
															if (Val == 0.0f && INPUT.Value == 0.0f) \
																INPUT##_Stationary(Val); \
														} \
														void CLASS::INPUT##_FirstMoved(const float &Val) \
														{ \
															INPUT.Set(ECsInputEvent::FirstMoved, Val); \
															AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
														} \
														void CLASS::INPUT##_Moved(const float &Val) \
														{ \
															INPUT.Set(ECsInputEvent::Moved, Val); \
															AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
														} \
														void CLASS::INPUT##_FirstStationary(const float &Val) \
														{ \
															INPUT.Set(ECsInputEvent::FirstStationary, Val); \
															AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
														} \
														void CLASS::INPUT##_Stationary(const float &Val) \
														{ \
															INPUT.Set(ECsInputEvent::Stationary, Val); \
															AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
														}

// Example: THIS = this, CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = TurnAtRate
#define CS_BIND_AXIS_INPUT(THIS, CLASS, INPUT) InputComponent->BindAxis(#INPUT, THIS, &CLASS::INPUT##_Raw).bConsumeInput = false;

// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = LeftTrigger
#define CS_DECLARE_INPUT_TRIGGER_MEMBERS(INPUT)	FCsInputInfo INPUT; \
												void INPUT##_Raw(float Val); \
												void INPUT##_FirstMoved(const float &Val); \
												void INPUT##_Moved(const float &Val); \
												void INPUT##_FirstStationary(const float &Val); \
												void INPUT##_Stationary(const float &Val);

#define CS_DEFINE_INPUT_TRIGGER_VALUES(INPUT)	Infos[ECsInputAction::INPUT] = &INPUT; \
												INPUT.Type = ECsInputType::Trigger; \
												INPUT.ValueType = ECsInputValue::Float; \
												Actions[ECsInputAction::INPUT] = &INPUT.Event; \
												INPUT.Event = ECsInputEvent::Stationary; \
												Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
												INPUT.Last_Event = ECsInputEvent::Stationary; \

// Example: CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = LeftTrigger
#define CS_DEFINE_INPUT_TRIGGER_MEMBERS(CLASS, INPUT, MAP)	void CLASS::INPUT##_Raw(float Val) \
															{ \
																if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																	return; \
																FCsInput* Input	= GetPreviousPreviousInputAction(ECsInputAction::INPUT); \
																\
																if (!Input && INPUT.Value != Val) \
																	INPUT##_FirstMoved(Val); \
																else \
																if (INPUT.Value != Val) \
																	INPUT##_Moved(Val); \
																else \
																if ((!Input && INPUT.Value == Val) || (Input && Input->Val != INPUT.Value && INPUT.Value == Val)) \
																	INPUT##_FirstStationary(Val); \
																else \
																if (INPUT.Value == Val) \
																	INPUT##_Stationary(Val); \
															} \
															void CLASS::INPUT##_FirstMoved(const float &Val) \
															{ \
																INPUT.Set(ECsInputEvent::FirstMoved, Val); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
															} \
															void CLASS::INPUT##_Moved(const float &Val) \
															{ \
																INPUT.Set(ECsInputEvent::Moved, Val); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
															} \
															void CLASS::INPUT##_FirstStationary(const float &Val) \
															{ \
																INPUT.Set(ECsInputEvent::FirstStationary, Val); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
															} \
															void CLASS::INPUT##_Stationary(const float &Val) \
															{ \
																INPUT.Set(ECsInputEvent::Stationary, Val); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, Val); \
															}

// Example: THIS = this, CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = LeftTrigger
#define CS_BIND_TRIGGER_INPUT(THIS, CLASS, INPUT) InputComponent->BindAxis(#INPUT, THIS, &CLASS::INPUT##_Raw).bConsumeInput = false;

// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = RightHandMove
#define CS_DECLARE_INPUT_LOCATION_MEMBERS(INPUT)	FCsInputInfo INPUT; \
													void INPUT##_Raw(const FVector &Location); \
													void INPUT##_FirstMoved(const FVector &Location); \
													void INPUT##_Moved(const FVector &Location); \
													void INPUT##_FirstStationary(const FVector &Location); \
													void INPUT##_Stationary(const FVector &Location);

#define CS_DEFINE_INPUT_LOCATION_VALUES(INPUT)	Infos[ECsInputAction::INPUT] = &INPUT; \
												INPUT.Type = ECsInputType::Location; \
												INPUT.ValueType = ECsInputValue::Vector; \
												Actions[ECsInputAction::INPUT] = &INPUT.Event; \
												INPUT.Event = ECsInputEvent::Stationary; \
												Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
												INPUT.Last_Event = ECsInputEvent::Stationary; \

// Example: CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = RightHandMove
#define CS_DEFINE_INPUT_LOCATION_MEMBERS(CLASS, INPUT, MAP)	void CLASS::INPUT##_Raw(const FVector &Location) \
															{ \
																if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																	return; \
																\
																FCsInput* Input	= GetPreviousPreviousInputAction(ECsInputAction::INPUT); \
																\
																if (!Input && INPUT.Location != Location) \
																	INPUT##_FirstMoved(Location); \
																else \
																if (INPUT.Location != Location) \
																	INPUT##_Moved(Location); \
																else \
																if ((!Input && INPUT.Location == Location) || (Input && Input->Location != INPUT.Location && INPUT.Location == Location)) \
																	INPUT##_FirstStationary(Location); \
																else \
																if (INPUT.Location == Location) \
																	INPUT##_Stationary(Location); \
															} \
															void CLASS::INPUT##_FirstMoved(const FVector &Location) \
															{ \
																INPUT.Set(ECsInputEvent::FirstMoved, Location); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, Location); \
															} \
															void CLASS::INPUT##_Moved(const FVector &Location) \
															{ \
																INPUT.Set(ECsInputEvent::Moved, Location); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, Location); \
															} \
															void CLASS::INPUT##_FirstStationary(const FVector &Location) \
															{ \
																INPUT.Set(ECsInputEvent::FirstStationary, Location); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, Location); \
															} \
															void CLASS::INPUT##_Stationary(const FVector &Location) \
															{ \
																INPUT.Set(ECsInputEvent::Stationary, Location); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, Location); \
															}

// Example: CLASS = CsManagerInput (if class is ACsManager_Input), INPUT = RightHandRotate
#define CS_DECLARE_INPUT_ROTATION_MEMBERS(INPUT)	FCsInputInfo INPUT; \
													void INPUT##_Raw(const FRotator &Rotation); \
													void INPUT##_FirstMoved(const FRotator &Rotation); \
													void INPUT##_Moved(const FRotator &Rotation); \
													void INPUT##_FirstStationary(const FRotator &Rotation); \
													void INPUT##_Stationary(const FRotator &Rotation);

#define CS_DEFINE_INPUT_ROTATION_VALUES(INPUT)	Infos[ECsInputAction::INPUT] = &INPUT; \
												INPUT.Type = ECsInputType::Rotation; \
												INPUT.ValueType = ECsInputValue::Rotator; \
												Actions[ECsInputAction::INPUT] = &INPUT.Event; \
												INPUT.Event = ECsInputEvent::Stationary; \
												Last_Actions[ECsInputAction::INPUT] = &INPUT.Last_Event; \
												INPUT.Last_Event = ECsInputEvent::Stationary; \

// Example: CLASS = ACsManager_Input (if class is ACsManager_Input), INPUT = RightHandRotate
#define CS_DEFINE_INPUT_ROTATION_MEMBERS(CLASS, INPUT, MAP)	void CLASS::INPUT##_Raw(const FRotator &Rotation) \
															{ \
																if (((MAP) & CurrentInputActionMap) != CurrentInputActionMap) \
																	return; \
																\
																FCsInput* Input	= GetPreviousPreviousInputAction(ECsInputAction::INPUT); \
																\
																if (!Input && INPUT.Rotation != Rotation) \
																	INPUT##_FirstMoved(Rotation); \
																else \
																if (INPUT.Rotation != Rotation) \
																	INPUT##_Moved(Rotation); \
																else \
																if ((!Input && INPUT.Rotation == Rotation) || (Input && Input->Rotation != INPUT.Rotation && INPUT.Rotation == Rotation)) \
																	INPUT##_FirstStationary(Rotation); \
																else \
																if (INPUT.Rotation == Rotation) \
																	INPUT##_Stationary(Rotation); \
															} \
															void CLASS::INPUT##_FirstMoved(const FRotator &Rotation) \
															{ \
																INPUT.Set(ECsInputEvent::FirstMoved, Rotation); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, FVector::ZeroVector, Rotation); \
															} \
															void CLASS::INPUT##_Moved(const FRotator &Rotation) \
															{ \
																INPUT.Set(ECsInputEvent::Moved, Rotation); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, FVector::ZeroVector, Rotation); \
															} \
															void CLASS::INPUT##_FirstStationary(const FRotator &Rotation) \
															{ \
																INPUT.Set(ECsInputEvent::FirstStationary, Rotation); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, FVector::ZeroVector, Rotation); \
															} \
															void CLASS::INPUT##_Stationary(const FRotator &Rotation) \
															{ \
																INPUT.Set(ECsInputEvent::Stationary, Rotation); \
																AddInput(ECsInputAction::INPUT, INPUT.Event, 0.0f, FVector::ZeroVector, Rotation); \
															}

#pragma endregion Macros

#if WITH_EDITOR

DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsManagerInput_RunEditorGameBatchConsoleCommands_FirstPressed);
DECLARE_MULTICAST_DELEGATE(FBindableEvent_CsManagerInput_RunEditorGameJavascriptFile_FirstPressed);

#endif // #if WITH_EDITOR

#pragma endregion Input Delegates

// Game Action Delegates

UCLASS()
class CSCORE_API ACsManager_Input : public AActor
{
	GENERATED_UCLASS_BODY()

	static ACsManager_Input* Get(UWorld* InWorld, const int32 &Id = INDEX_NONE);

	TWeakObjectPtr<AActor> InputOwner;

	virtual AActor* GetInputOwner();

	int32 ControllerId;

	virtual void SetupInputComponent();

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused);
	virtual void ProcessInput(AActor* ActionOwner, const struct FCsInput* PreviousInput, const struct FCsInput* CurrentInput, const float DeltaTime);

	float CurrentDeltaTime;

	uint64 CurrentGameFrame;

	FCsInput InputPool[CS_INPUT_POOL_SIZE];

	FCsInput* AllocateInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator);

	virtual void AddInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value=0.0f, const FVector &Location=FVector::ZeroVector, const FRotator &Rotation=FRotator::ZeroRotator);

	TArray<FCsInput*> QueuedInputsForNextFrame;

	virtual void QueueInput(const TCsInputAction &Action, const TCsInputEvent &Event, const float &Value = 0.0f, const FVector &Location = FVector::ZeroVector, const FRotator &Rotation = FRotator::ZeroRotator);

	uint16 CurrentInputPoolIndex;

	FCsInputFrame InputFrames[CS_MAX_INPUT_FRAMES];

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	int32 CurrentInputFrameIndex;

	FCsInputFrame CurrentInputFrame;

	TCsInputActionMap CurrentInputActionMap;

	TCsInputActionMapToString InputActionMapToString;
	TCsStringToInputActionMap StringToInputActionMap;

	TArray<FKey> PressedKeys;

	FCsInput* GetPreviousInputAction(const TCsInputAction &Action);
	FCsInput* GetPreviousInputAction(const TCsInputAction &Action, const TCsInputEvent &Event);
	FCsInput* GetPreviousInputAction(const TCsInputAction &Action, const TArray<TCsInputEvent> &Events);
	FCsInput* GetPreviousPreviousInputAction(const TCsInputAction &Action);

	TArray<TCsGameEvent> QueuedGameEventsForNextFrame;

	virtual void QueueGameEvent(const TCsGameEvent &Event);

	void ClearQueuedGameEvents();

	virtual void DetermineGameEvents(const TArray<FCsInput*> &Inputs);

	bool HasActionEventOccured(const TCsInputAction &Action, const TCsInputEvent &Event);

	float GetInputValue(const TCsInputAction &Action);
	FVector GetInputLocation(const TCsInputAction &Action);
	TCsInputEvent GetInputEvent(const TCsInputAction& Action);

	UFUNCTION(BlueprintCallable, Category = "Input")
	TEnumAsByte<ECsInputEvent::Type> GetInputEvent_Script(const uint8& Action);

	float GetInputDuration(const TCsInputAction &Action);

	virtual bool CanSaveInputActionMapping(const TCsInputDevice &Device, const TCsInputAction &Action);

	FCsInputProfile InputProfile;

	void SaveInputProfile();
	void LoadDefaultInputProfile();
	void LoadInputProfile();

	bool IsValidKey(const TCsInputDevice &Device, const FKey &Key);

	struct FKey GetKey(const FString &KeyName);
	
	TCsInputAction GetActionFromKey(const TCsInputDevice &Device, const FKey &Key);

	void UnbindActionMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);
	void UnbindAxisMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);
	void UnbindMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);

	void RebindActionMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);
	void RebindAxisMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);
	void RebindMapping(const TCsInputDevice &Device, const TCsInputAction &Action, const FKey &Key);

#if WITH_EDITOR

// Editor Game
#pragma region
public:

	FBindableEvent_CsManagerInput_RunEditorGameBatchConsoleCommands_FirstPressed OnRunEditorGameBatchConsoleCommands_FirstPressed_Event;

	void RunEditorGameBatchConsoleCommands_FirstPressed();

	FBindableEvent_CsManagerInput_RunEditorGameJavascriptFile_FirstPressed OnRunEditorGameJavascriptFile_FirstPressed_Event;

	void RunEditorGameJavascriptFile_FirstPressed();

#pragma endregion Editor Game

#endif // #if WITH_EDITOR

// Actions
#pragma region
protected:

	TCsInputAction InputAction_MAX;

	TCsInputActionToString InputActionToString;
	TCsStringToInputAction StringToInputAction;

	TArray<FCsInputInfo*> Infos;

	TArray<TCsInputEvent*> Actions;
	TArray<TCsInputEvent*> Last_Actions;

	// Pressed Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput Default_ScriptEvent;

	FBindableEvent_CsManagerInput Default_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_FirstPressed FirstPressed_ScriptEvent;

	FBindableEvent_CsManagerInput_FirstPressed FirstPressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Pressed Pressed_ScriptEvent;

	FBindableEvent_CsManagerInput_Pressed Pressed_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_FirstReleased FirstReleased_ScriptEvent;

	FBindableEvent_CsManagerInput_FirstReleased FirstReleased_Event;

#pragma endregion

	// Axis Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Axis Axis_ScriptEvent;

	FBindableEvent_CsManagerInput_Axis Axis_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Axis_FirstMoved Axis_FirstMoved_ScriptEvent;

	FBindableEvent_CsManagerInput_Axis_FirstMoved Axis_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Axis_Moved Axis_Moved_ScriptEvent;

	FBindableEvent_CsManagerInput_Axis_Moved Axis_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Axis_FirstStationary Axis_FirstStationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Axis_FirstStationary Axis_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Axis_Stationary Axis_Stationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Axis_Stationary Axis_Stationary_Event;

#pragma endregion Axis Events

	// Location Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Location Location_ScriptEvent;

	FBindableEvent_CsManagerInput_Location Location_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Location_FirstMoved Location_FirstMoved_ScriptEvent;

	FBindableEvent_CsManagerInput_Location_FirstMoved Location_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Location_Moved Location_Moved_ScriptEvent;

	FBindableEvent_CsManagerInput_Location_Moved Location_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Location_FirstStationary Location_FirstStationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Location_FirstStationary Location_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Location_Stationary Location_Stationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Location_Stationary Location_Stationary_Event;

	// VR

	FBindableCall_CsManagerInput_Location_Raw HMD_Location_Raw;
	FBindableCall_CsManagerInput_Location_Raw LeftHand_Location_Raw;
	FBindableCall_CsManagerInput_Location_Raw RightHand_Location_Raw;

#pragma endregion Location Events

	// Rotation Events
#pragma region
public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Rotation Rotation_ScriptEvent;

	FBindableEvent_CsManagerInput_Rotation Rotation_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Rotation_FirstMoved Rotation_FirstMoved_ScriptEvent;

	FBindableEvent_CsManagerInput_Rotation_FirstMoved Rotation_FirstMoved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Rotation_Moved Rotation_Moved_ScriptEvent;

	FBindableEvent_CsManagerInput_Rotation_Moved Rotation_Moved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Rotation_FirstStationary Rotation_FirstStationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Rotation_FirstStationary Rotation_FirstStationary_Event;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FBindableDynEvent_CsManagerInput_Rotation_Stationary Rotation_Stationary_ScriptEvent;

	FBindableEvent_CsManagerInput_Rotation_Stationary Rotation_Stationary_Event;

	// VR

	FBindableCall_CsManagerInput_Rotation_Raw HMD_Rotation_Raw;
	FBindableCall_CsManagerInput_Rotation_Raw LeftHand_Rotation_Raw;
	FBindableCall_CsManagerInput_Rotation_Raw RightHand_Rotation_Raw;

#pragma endregion Rotation Events

#pragma endregion Actions
};