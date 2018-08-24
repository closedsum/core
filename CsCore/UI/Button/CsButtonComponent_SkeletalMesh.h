#pragma once

#include "Components/CsSkeletalMeshComponent.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_UI.h"
#include "CsButtonComponent_SkeletalMesh.generated.h"

// Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnInteraction, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnInteraction, const uint16&, UObject*);

// FirstHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstHover, const uint16&, UObject*);
// Hover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnHover, const uint16&, UObject*);
// FirstUnHover
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstUnHover, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstUnHover, const uint16&, UObject*);
// FirstPressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstPressed, const uint16&, UObject*);
// Pressed
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnPressed, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnPressed, const uint16&, UObject*);
// FirstReleased
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstReleased, const int32&, Index, UObject*, Instigator);
DECLARE_MULTICAST_DELEGATE_TwoParams(FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstReleased, const uint16&, UObject*);

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsButtonComponent_SkeletalMesh : public USceneComponent
{
	GENERATED_UCLASS_BODY()

	virtual void OnConstructor(const FObjectInitializer& ObjectInitializer);

// State
#pragma region
public:

	UPROPERTY(BlueprintReadWrite, Category = "State")
	ECsButtonState State;

	TMap<TCsButtonState, TArray<TWeakObjectPtr<UObject>>> Instigators;

	UFUNCTION(BlueprintCallable, Category = "State")
	void AddInstigator(const ECsButtonState &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void RemoveInstigator(const ECsButtonState &InState, UObject* InInstigator);
	UFUNCTION(BlueprintCallable, Category = "State")
	void ClearInstigators();

	TArray<TWeakObjectPtr<UObject>>* GetInstigators(const ECsButtonState &InState);

	UFUNCTION(BlueprintCallable, Category = "State")
	void GetInstigators_Script(const ECsButtonState &InState, TArray<UObject*> OutInstigators);

	FBindableEvent_CsButtonComponent_SkeletalMesh_OnInteraction OnInteraction_Event;

	FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstHover OnFirstHover_Event;
	FBindableEvent_CsButtonComponent_SkeletalMesh_OnHover OnHover_Event;
	FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstUnHover OnFirstUnHover_Event;
	FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstPressed OnFirstPressed_Event;
	FBindableEvent_CsButtonComponent_SkeletalMesh_OnPressed OnPressed_Event;
	FBindableEvent_CsButtonComponent_SkeletalMesh_OnFirstReleased OnFirstReleased_Event;

#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnInteraction Override_OnInteraction_ScriptEvent;

	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstHover Override_OnFirstHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnHover Override_OnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstUnHover Override_OnFirstUnHover_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstPressed Override_OnFirstPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnPressed Override_OnPressed_ScriptEvent;
	UPROPERTY(BlueprintAssignable, Category = "State")
	FBindableDynEvent_CsButtonComponent_SkeletalMesh_Override_OnFirstReleased Override_OnFirstReleased_ScriptEvent;
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