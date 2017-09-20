#pragma once

#include "Components/PoseableMeshComponent.h"
#include "CsPoseableMeshComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class CSCORE_API UCsPoseableMeshComponent : public UPoseableMeshComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMesh* Last_SkeletalMesh;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
};