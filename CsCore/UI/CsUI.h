// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Types/CsTypes.h" 
#include "Types/CsTypes_UI.h"
#include "Types/CsTypes_Input.h"
#include "CsUI.generated.h"

// Update
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnUpdate, const float&, DeltaSeconds);
// PostProcessInput
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnPostProcessInput, const float&, DeltaTime);
// Last Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnLastTick, const float&, DeltaSeconds);
// Widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnAddWidget, class UCsUserWidget*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnAddWidgetActor, class ACsWidgetActor*, WidgetActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnOpen, const FECsWidgetType&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUI_OnOpen, const FECsWidgetType&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnClose, const FECsWidgetType&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUI_OnClose, const FECsWidgetType&);
// ProcessGameEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_Override_ProcessGameEvent, const uint8&, GameEvent);

UCLASS()
class CSCORE_API ACsUI : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Destroyed() override;

	virtual void OnUpdate(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnUpdate OnUpdate_ScriptEvent;

	virtual void OnPostProcessInput(const float &DeltaTime);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnPostProcessInput OnPostProcessInput_ScriptEvent;

	virtual void OnLastTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnLastTick OnLastTick_ScriptEvent;

	TWeakObjectPtr<AActor> MyOwner;

	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetMyOwner();

	template<typename T>
	T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

	TArray<FECsWidgetType> WidgetTypes;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<class UCsUserWidget*> Widgets;

	TMap<FECsWidgetType, TArray<class UCsUserWidget*>> WidgetsMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<class UCsUserWidget*> ActiveWidgets;

	TMap<FECsWidgetType, TArray<class UCsUserWidget*>> ActiveWidgetsMap;

// Add
#pragma region
public:

	virtual void AddWidget(const FECsWidgetType &WidgetType);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidget OnAddWidget_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddWidget_Script(const uint8 &WidgetType);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidgetActor OnAddWidgetActor_ScriptEvent;

#pragma endregion Add

// Get
#pragma region
public:

	virtual class UCsUserWidget* GetWidget(const FECsWidgetType &WidgetType);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual class UCsUserWidget* GetWidget_Script(const uint8 &WidgetType);

	virtual class UCsUserWidget* GetActiveWidget(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual class UCsUserWidget* GetActiveWidget_Script(const uint8 &WidgetType);

#pragma endregion Get


// WidgetActor
#pragma region
public:

	TArray<TWeakObjectPtr<class ACsWidgetActor>> WidgetActors;
	TArray<TWeakObjectPtr<class ACsWidgetActor>> ActiveWidgetActors;

#pragma endregion WidgetActor

	virtual bool HasWidgetInitialized(const FECsWidgetType &WidgetType);

	virtual void SetFocus(const FECsWidgetType &WidgetType, const int32 &Focus);
	virtual void SetFocus(const FECsWidgetType &WidgetType, const ECsWidgetFocus &Focus);

	void SetFocusAll(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetFocusAll_Script(const uint8 &WidgetType);

// Open / Close
#pragma region
public:

	virtual void Open(const FECsWidgetType &WidgetType);

	FBindableEvent_CsUI_OnOpen OnOpen_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnOpen OnOpen_ScriptEvent;

	virtual bool IsOpened(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsOpened_Script(const uint8 &WidgetType);

	virtual bool IsOpenedAndFocused(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsOpenedAndFocused_Script(const uint8 &WidgetType);

	virtual void Close(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Close_Script(const uint8 &WidgetType);

	UFUNCTION()
	virtual void CloseAll();

	FBindableEvent_CsUI_OnClose OnClose_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnClose OnClose_ScriptEvent;

	virtual bool IsClosed(const FECsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsClosed_Script(const uint8 &WidgetType);

#pragma endregion Open / Close

// Raw Inputs
#pragma region
public:

	virtual bool ProcessInputFrame(FCsInputFrame &InputFrame);

#pragma endregion Raw Inputs

// Game Event
#pragma region
public:

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_Override_ProcessGameEvent Override_ProcessGameEvent_ScriptEvent;

#pragma endregion Game Event
};