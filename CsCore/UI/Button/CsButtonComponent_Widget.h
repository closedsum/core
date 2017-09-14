#pragma once

#include "Components/CsWidgetComponent.h"
#include "CsTypes.h"
#include "CsButtonComponent_Widget.generated.h"

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnInteraction, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnInteraction, const uint16&, UObject*);

// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnFirstHover, const uint16&, UObject*);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnHover, const uint16&, UObject*);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstUnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnFirstUnHover, const uint16&, UObject*);
// FirstPressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnFirstPressed, const uint16&, UObject*);
// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnPressed, const uint16&, UObject*);
// FirstReleased
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstReleased, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_Widget_OnFirstReleased, const uint16&, UObject*);

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsButtonComponent_Widget : public UCsWidgetComponent
{
	GENERATED_UCLASS_BODY()

	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);

// State
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	TEnumAsByte<ECsButtonState::Type> State;

	TMap<TCsButtonState, TArray<TWeakObjectPtr<UObject>>> Instigators;

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveInstigator(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ClearInstigators();

	TArray<TWeakObjectPtr<UObject>>* GetInstigators(const TEnumAsByte<ECsButtonState::Type> &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetInstigators_Script(const TEnumAsByte<ECsButtonState::Type> &InState, TArray<UObject*> OutInstigators);

	FBindableEvent_CsButtonComponent_Widget_OnInteraction OnInteraction_Event;

	FBindableEvent_CsButtonComponent_Widget_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsButtonComponent_Widget_OnHover OnHover_Event;
	FBindableEvent_CsButtonComponent_Widget_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsButtonComponent_Widget_OnFirstPressed OnFirstPressed_Event;
	FBindableEvent_CsButtonComponent_Widget_OnPressed OnPressed_Event;
	FBindableEvent_CsButtonComponent_Widget_OnFirstReleased OnFirstReleased_Event;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstPressed Override_OnFirstPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnPressed Override_OnPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Widget_Override_OnFirstReleased Override_OnFirstReleased_ScriptEvent;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnInteraction_Script(const TEnumAsByte<ECsButtonState::Type> &InState, UObject* InInstigator);

	virtual void OnInteraction(UObject* InInstigator);

	virtual void OnFirstHover(UObject* InInstigator);
	virtual void OnHover(UObject* InInstigator);
	virtual void OnFirstUnHover(UObject* InInstigator);
	virtual void OnFirstPressed(UObject* InInstigator);
	virtual void OnPressed(UObject* InInstigator);
	virtual void OnFirstReleased(UObject* InInstigator);

	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeState(const TEnumAsByte<ECsButtonState::Type> &FromState, const TEnumAsByte<ECsButtonState::Type> &ToState);
	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeFromAnyState(const TArray<TEnumAsByte<ECsButtonState::Type>> &FromStates, const TEnumAsByte<ECsButtonState::Type> &ToState);

#pragma endregion State

	virtual void Show();
	virtual void Hide();
};