// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "CsTypes.h" 
#include "CsUI.generated.h"

// Update
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUI_OnUpdate, const float&, DeltaSeconds);
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

	UPROPERTY()
	TArray<class UCsUserWidget*> Widgets;

	TArray<class UCsUserWidget*> ActiveWidgets;

	virtual void AddWidget(const TCsWidgetType &WidgetType);

	virtual class UCsUserWidget* GetWidget(const TCsWidgetType &WidgetType);
	virtual class UCsUserWidget* GetActiveWidget(const TCsWidgetType &WidgetType);

	UPROPERTY()
	TArray<TWeakObjectPtr<class ACsWidgetActor>> WidgetActors;

	TArray<TWeakObjectPtr<class ACsWidgetActor>> ActiveWidgetActors;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidget OnAddWidget_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUI_OnAddWidgetActor OnAddWidgetActor_ScriptEvent;

	virtual bool HasWidgetInitialized(const TCsWidgetType &WidgetType);

	virtual void Open(const TCsWidgetType &WidgetType);
	virtual void Close(const TCsWidgetType &WidgetType);
};