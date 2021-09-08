// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"
// Types
#include "Types/CsTypes_Load.h"
#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Types/Property/Ref/CsProperty_Ref_float.h"
#include "Animation/CsTypes_Anim.h"
#include "Animation/CsTypes_AnimInstance.h"

#include "CsAnimInstance.generated.h"

class UCsManager_Singleton;
class APawn;
class AActor;
class ACsManager_Singleton_Actor;

UCLASS()
class CSCORE_API UCsAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
protected:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// UAnimInstance Interface
#pragma region
public:

	/** Init */
	virtual void NativeInitializeAnimation() override;

	/** Tick */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

#pragma endregion UAnimInstance Interface

// Owner
#pragma region
public:

	TWeakObjectPtr<APawn> OwningPawn;

	APawn* GetOwningPawn();

	template<typename T>
	T* GetOwningPawn() { return Cast<T>(GetOwningPawn()); }

	TWeakObjectPtr<AActor> MyOwningActor;

	AActor* GetMyOwningActor();

	template<typename T>
	T* GetMyOwningActor() { return Cast<T>(GetMyOwningActor()); }

	USkeletalMeshComponent* GetSkeletalMeshComponent();

#pragma endregion Owner

// Manager Singleton
#pragma region
protected:

	UPROPERTY()
	ACsManager_Singleton_Actor* Manager_Singleton_Actor;

	virtual void ConstructManagerSingletonActor(){}

#pragma endregion Manager Singleton

// Event Graph
#pragma region
public:

	// 0 Setup
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool bSetupInGameSimulation;

	TCsBool_Ref bSetupInGameSimulationHandle;

	virtual void SetupInGameSimulation();
	virtual void OnTick_Handle_bSetupInGameSimulation();

	/** Show Emitter Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowEmitterEditorIcons;

	TCsBool_Ref ShowEmitterEditorIconsHandle;

	/** Show Sound Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowSoundEditorIcons;

	TCsBool_Ref ShowSoundEditorIconsHandle;

	virtual void OnTick_Handle_ShowEditorIcons();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	float GlobalPlayRate;

	TCsFloat_Ref GlobalPlayRateHandle;

	virtual void OnTick_Handle_GlobalPlayRate();

#pragma endregion 0 Setup

#pragma endregion Event Graph
};