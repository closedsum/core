// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Types/CsTypes.h" 
#include "Types/CsTypes_Input.h"
#include "CsUI.generated.h"

// Update
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnUpdate, const float&, DeltaSeconds);
// Last Tick
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnLastTick, const float&, DeltaSeconds);
// Widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnAddWidget, class UCsUserWidget*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnAddWidgetActor, class ACsWidgetActor*, WidgetActor);

UCLASS()
class CSCORE_API ACsUI : public AHUD
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Destroyed() override;

	virtual void OnUpdate(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnUpdate OnUpdate_ScriptEvent;

	virtual void OnLastTick(const float &DeltaSeconds);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnLastTick OnLastTick_ScriptEvent;

	UPROPERTY()
	TArray<class UCsUserWidget*> Widgets;

	TArray<class UCsUserWidget*> ActiveWidgets;

	TCsWidgetTypeToString WidgetTypeToString;
	TCsStringToWidgetType StringToWidgetType;

	virtual void AddWidget(const TCsWidgetType &WidgetType);

	virtual class UCsUserWidget* GetWidget(const TCsWidgetType &WidgetType);
	virtual class UCsUserWidget* GetActiveWidget(const TCsWidgetType &WidgetType);

	UPROPERTY()
	TArray<TWeakObjectPtr<class ACsWidgetActor>> WidgetActors;

	TArray<TWeakObjectPtr<class ACsWidgetActor>> ActiveWidgetActors;

	TCsWidgetActorTypeToString WidgetActorTypeToString;
	TCsStringToWidgetActorType StringToWidgetActorType;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidget OnAddWidget_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidgetActor OnAddWidgetActor_ScriptEvent;

	virtual bool HasWidgetInitialized(const TCsWidgetType &WidgetType);

	virtual void Open(const TCsWidgetType &WidgetType);
	virtual bool IsOpened(const TCsWidgetType &WidgetType);
	virtual bool IsOpenedAndFocused(const TCsWidgetType &WidgetType);

	virtual void SetFocus(const TCsWidgetType &WidgetType, const int32 &Focus);
	virtual void SetFocus(const TCsWidgetType &WidgetType, const ECsWidgetFocus &Focus);

	virtual void Close(const TCsWidgetType &WidgetType);
	virtual bool IsClosed(const TCsWidgetType &WidgetType);

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent);
};