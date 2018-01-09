// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Engine/StaticMeshActor.h"
#include "Types/CsTypes.h"
#include "CsAnim_Control.generated.h"

DECLARE_DELEGATE_OneParam(FBindableEvent_CsAnimControl_OnControlNameChanged, const int32&);

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsAnim_Control : public AStaticMeshActor
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;

#if WITH_EDITOR

	virtual void OnTick_Editor(const float &DeltaSeconds);

#endif // #if WITH_EDITOR

	bool HasTickedInEditor;
	/* Control Name */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	FString Control;

	TCsFString ControlName;

#if WITH_EDITOR

	virtual void OnControlNameChanged();

	FBindableEvent_CsAnimControl_OnControlNameChanged OnControlNameChanged_Event;

	void SetControlName(const FString &InName);

#endif // #if WITH_EDITOR

	/* Index in Control Array in PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	int32 ControlIndex;
	/* Reference to PoseableMeshActor */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	AActor* Root;
	/* Reference to Anchor for Control */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "00 Control")
	AActor* Anchor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool ResetToAnchor;

	bool ForceUpdateTransform;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockTransform;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "00 Control")
	bool LockScale;

	bool RecordTransform;
	bool RecordLocation;
	bool RecordRotation;
	bool RecordScale;

	TCsFVector RelativeLocation;
	TCsFRotator RelativeRotation;
	TCsFVector RelativeScale;

	TCsFVector Location;
	TCsFRotator Rotation;
	TCsFVector Scale;
	
	UFUNCTION(BlueprintCallable, Category = "Control")
	bool HasTransformChanged();
	UFUNCTION(BlueprintCallable, Category = "Control")
	bool HasRelativeTransformMemberChanged(const TEnumAsByte<ECsTransformMember::Type> &Member, const int32 &Axes);
	UFUNCTION(BlueprintCallable, Category = "Control")
	bool HasTransformMemberChanged(const TEnumAsByte<ECsTransformMember::Type> &Member, const int32 &Axes);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
};