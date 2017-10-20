// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Types/CsTypes.h" 
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnOpen, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUI_OnOpen, const TEnumAsByte<ECsWidgetType::Type>&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnClose, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUI_OnClose, const TEnumAsByte<ECsWidgetType::Type>&);
// ProcessGameEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_Override_ProcessGameEvent, const uint8&, GameEvent);

#define CS_UI_DEFINE_TYPE	WidgetType_MAX = ECsWidgetType::ECsWidgetType_MAX; \
							WidgetTypeToString = &ECsWidgetType::ToString; \
							StringToWidgetType = &ECsWidgetType::ToType;

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

	TArray<TCsWidgetType> WidgetTypes;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<class UCsUserWidget*> Widgets;

	TMap<TCsWidgetType, TArray<class UCsUserWidget*>> WidgetsMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<class UCsUserWidget*> ActiveWidgets;

	TMap<TCsWidgetType, TArray<class UCsUserWidget*>> ActiveWidgetsMap;

	TCsWidgetType WidgetType_MAX;

	TCsWidgetTypeToString WidgetTypeToString;
	TCsStringToWidgetType StringToWidgetType;

// Add
#pragma region

	virtual void AddWidget(const TCsWidgetType &WidgetType);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidget OnAddWidget_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void AddWidget_Script(const uint8 &WidgetType);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidgetActor OnAddWidgetActor_ScriptEvent;

#pragma endregion Add

// Get
#pragma region

	virtual class UCsUserWidget* GetWidget(const TCsWidgetType &WidgetType);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual class UCsUserWidget* GetWidget_Script(const uint8 &WidgetType);

	virtual class UCsUserWidget* GetActiveWidget(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual class UCsUserWidget* GetActiveWidget_Script(const uint8 &WidgetType);

#pragma endregion Get


// WidgetActor
#pragma region

	TArray<TWeakObjectPtr<class ACsWidgetActor>> WidgetActors;
	TArray<TWeakObjectPtr<class ACsWidgetActor>> ActiveWidgetActors;

	TCsWidgetActorTypeToString WidgetActorTypeToString;
	TCsStringToWidgetActorType StringToWidgetActorType;

#pragma endregion WidgetActor

	virtual bool HasWidgetInitialized(const TCsWidgetType &WidgetType);

	virtual void SetFocus(const TCsWidgetType &WidgetType, const int32 &Focus);
	virtual void SetFocus(const TCsWidgetType &WidgetType, const ECsWidgetFocus &Focus);

	void SetFocusAll(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetFocusAll_Script(const uint8 &WidgetType);

// Open / Close
#pragma region

	virtual void Open(const TCsWidgetType &WidgetType);

	FBindableEvent_CsUI_OnOpen OnOpen_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnOpen OnOpen_ScriptEvent;

	virtual bool IsOpened(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsOpened_Script(const uint8 &WidgetType);

	virtual bool IsOpenedAndFocused(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsOpenedAndFocused_Script(const uint8 &WidgetType);

	virtual void Close(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Close_Script(const uint8 &WidgetType);

	UFUNCTION()
	virtual void CloseAll();

	FBindableEvent_CsUI_OnClose OnClose_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnClose OnClose_ScriptEvent;

	virtual bool IsClosed(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsClosed_Script(const uint8 &WidgetType);

#pragma endregion Open / Close

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_Override_ProcessGameEvent Override_ProcessGameEvent_ScriptEvent;
};