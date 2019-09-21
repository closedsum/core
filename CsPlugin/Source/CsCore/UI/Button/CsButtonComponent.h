#pragma once

#include "../Engine/Classes/Components/SceneComponent.h"
#include "Types/CsTypes.h"
#include "UI/CsTypes_UI.h"
#include "CsButtonComponent.generated.h"

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnInteraction, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnInteraction, const uint16&, UObject*);

// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnFirstHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnFirstHover, const uint16&, UObject*);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnHover, const uint16&, UObject*);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnFirstUnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnFirstUnHover, const uint16&, UObject*);
// FirstPressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnFirstPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnFirstPressed, const uint16&, UObject*);
// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnPressed, const uint16&, UObject*);
// FirstReleased
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_Override_OnFirstReleased, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_OnFirstReleased, const uint16&, UObject*);

UCLASS()
class CSCORE_API UCsButtonComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()

	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Button")
	class UPrimitiveComponent* VisualComponent;

protected:
	bool UseWidget;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Button")
	class UCsWidgetComponent* WidgetComponent;
protected:
	bool UseSkeletalMesh;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Button")
	class UCsSkeletalMeshComponent* SkeletalMeshComponent;
protected:
	bool UseStaticMesh;
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Button")
	class UCsStaticMeshComponent* StaticMeshComponent;

// State
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECsButtonState State;

	TMap<ECsButtonState, TArray<TWeakObjectPtr<UObject>>> Instigators;

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddInstigator(const ECsButtonState &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveInstigator(const ECsButtonState &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ClearInstigators();

	TArray<TWeakObjectPtr<UObject>>* GetInstigators(const ECsButtonState &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetInstigators_Script(const ECsButtonState &InState, TArray<UObject*> OutInstigators);

	FBindableEvent_CsButtonComponent_OnInteraction OnInteraction_Event;

	FBindableEvent_CsButtonComponent_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsButtonComponent_OnHover OnHover_Event;
	FBindableEvent_CsButtonComponent_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsButtonComponent_OnFirstPressed OnFirstPressed_Event;
	FBindableEvent_CsButtonComponent_OnPressed OnPressed_Event;
	FBindableEvent_CsButtonComponent_OnFirstReleased OnFirstReleased_Event;

#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnFirstPressed Override_OnFirstPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnPressed Override_OnPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_Override_OnFirstReleased Override_OnFirstReleased_ScriptEvent;
#endif // #if WITH_EDITORONLY_DATA

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnInteraction_Script(const ECsButtonState &InState, UObject* InInstigator);

	virtual void OnInteraction(UObject* InInstigator);

	virtual void OnFirstHover(UObject* InInstigator);
	virtual void OnHover(UObject* InInstigator);
	virtual void OnFirstUnHover(UObject* InInstigator);
	virtual void OnFirstPressed(UObject* InInstigator);
	virtual void OnPressed(UObject* InInstigator);
	virtual void OnFirstReleased(UObject* InInstigator);

	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeState(const ECsButtonState &FromState, const ECsButtonState &ToState);
	UFUNCTION(BlueprintCallable = Category = "State")
	virtual bool CanChangeFromAnyState(const TArray<ECsButtonState> &FromStates, const ECsButtonState &ToState);

#pragma endregion State

	virtual void Show();
	virtual void Hide();
};