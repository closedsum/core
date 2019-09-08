#pragma once

#include "Components/StaticMeshComponent.h"
#include "CsStaticMeshComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
};