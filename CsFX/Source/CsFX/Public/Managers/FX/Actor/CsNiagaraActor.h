// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "NiagaraActor.h"

#include "CsNiagaraActor.generated.h"

UCLASS()
class CSFX_API ACsNiagaraActor : public ANiagaraActor
{
	GENERATED_UCLASS_BODY()

// AActor Interface
#pragma region
public:

	virtual void PostRegisterAllComponents() override;

	virtual bool ShouldTickIfViewportsOnly() const override;

#if WITH_EDITOR
	virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;
#endif // #if WITH_EDITOR

#pragma endregion AActor Interface

private:

	/** True for this actor to self-destruct when the Niagara system finishes, false otherwise */
	UPROPERTY()
	uint32 bDestroyOnSystemFinish2 : 1;

	/** Callback when Niagara system finishes. */
	UFUNCTION(CallInEditor)
	void OnNiagaraSystemFinished2(UNiagaraComponent* FinishedComponent);
};