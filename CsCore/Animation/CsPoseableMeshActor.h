// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "GameFramework/Actor.h"
#include "CsPoseableMeshActor.generated.h"


USTRUCT()
struct FCsBoneActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	FName Bone;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bone")
	class ACsBoneActor* Actor;

	FCsBoneActorInfo()
	{
		Bone = NAME_None;
		Actor = nullptr;
	}
};

UCLASS()
class CSCORE_API ACsPoseableMeshActor : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void OnTick_Editor(const float &DeltaSeconds);

	bool HasTickedInEditor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PoseableMesh")
	class UCsPoseableMeshComponent* PoseableMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PoseableMesh")
	class USkeletalMesh* Last_SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PoseableMesh")
	TArray<FCsBoneActorInfo> Bones;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

	virtual void GenerateBones();
	virtual void ClearBones();

#endif // #if WITH_EDITOR
};