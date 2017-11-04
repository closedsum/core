// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"
#include "Types/CsTypes.h"
#include "CsAnimInstance.generated.h"

// Structs
#pragma region

USTRUCT(BlueprintType)
struct FCsAnimInstance_AnimSequence
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UAnimSequence> Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimSequence> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimSequence()
	{
		UseDataValueAsDefault = true;
	}

	UAnimSequence* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FCsAnimInstance_AnimSequence& operator=(const FCsAnimInstance_AnimSequence& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_AnimSequence& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_AnimSequence& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsAnimInstance_AnimMontage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<UAnimMontage> Anim;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	TWeakObjectPtr<UAnimMontage> Anim_Internal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool UseDataValueAsDefault;

public:

	FCsAnimInstance_AnimMontage()
	{
		UseDataValueAsDefault = true;
	}

	UAnimMontage* Get() const
	{
		return Anim_Internal.IsValid() ? Anim_Internal.Get() : nullptr;
	}

	FCsAnimInstance_AnimMontage& operator=(const FCsAnimInstance_AnimMontage& B)
	{
		Anim = B.Anim;
		Anim_Internal = B.Anim_Internal;
		UseDataValueAsDefault = B.UseDataValueAsDefault;
		return *this;
	}

	bool operator==(const FCsAnimInstance_AnimMontage& B) const
	{
		return Anim == B.Anim && Anim_Internal == B.Anim_Internal && UseDataValueAsDefault == B.UseDataValueAsDefault;
	}

	bool operator!=(const FCsAnimInstance_AnimMontage& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Structs

USTRUCT(BlueprintType)
struct FCsAnimInstance_Blueprint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TAssetPtr<class UBlueprint> Blueprint;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Animation)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:

	UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}

	FCsAnimInstance_Blueprint& operator=(const FCsAnimInstance_Blueprint& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_Internal = B.Blueprint_Internal;
		return *this;
	}

	bool operator==(const FCsAnimInstance_Blueprint& B) const
	{
		return Blueprint == B.Blueprint && Blueprint_Internal == B.Blueprint_Internal;
	}

	bool operator!=(const FCsAnimInstance_Blueprint& B) const
	{
		return !(*this == B);
	}
};

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