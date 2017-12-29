// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_AnimInstance.h"
#include "CsAnimInstance.generated.h"

UCLASS()
class CSCORE_API UCsAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

// Event Graph
#pragma region
public:

	virtual void BeginDestroy() override;

	/** Init */
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
	TWeakObjectPtr<class APawn> OwningPawn;

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	class APawn* GetOwningPawn();

	USkeletalMeshComponent* GetSkeletalMeshComponent();

	// 0 Setup
#pragma region
public:

	virtual void SetupInGameSimulation();
	virtual void OnTick_HandleSetupInGameSimulation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool DoSetupInGameSimulation;

	bool Last_DoSetupInGameSimulation;

	/** Show Emitter Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowEmitterEditorIcons;

	bool Last_ShowEmitterEditorIcons;

	/** Show Sound Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowSoundEditorIcons;

	bool Last_ShowSoundEditorIcons;

	virtual void OnTick_HandleEditorIcons();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	float GlobalPlayRate;

	float Last_GlobalPlayRate;

	virtual void OnTick_HandleGlobalPlayRate();

	TCsViewType CurrentViewType;

#if WITH_EDITOR

	// Coroutine Scheduler

	void Spawn_CoroutineScheduler();

	// Manager FX

	TWeakObjectPtr<class ACsManager_FX> Manager_FX;

	class ACsManager_FX* GetManager_FX();

	void Spawn_Manager_FX();

	// Manager Sound

	TWeakObjectPtr<class ACsManager_Sound> Manager_Sound;

	class ACsManager_Sound* GetManager_Sound();

	void Spawn_Manager_Sound();

#endif // #if WITH_EDITOR

#pragma endregion 0 Setup

	/** Tick */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Anims
#pragma region

	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimSequence &Anim, FCsAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimMontage &Anim, FCsAnimMontage* DataAnim);
	void LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimSequence &Anim, FCsFpsAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimMontage &Anim, FCsFpsAnimMontage* DataAnim);

#pragma endregion Anims

#pragma endregion Event Graph
};