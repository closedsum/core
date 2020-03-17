#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "CsSkeletalMeshComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCOREDEPRECATED_API UCsSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
};