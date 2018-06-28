// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"
#include "Types/CsTypes_Anim.h"
#include "Types/CsTypes_AnimInstance.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsAnimInstance.generated.h"

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsAnimInstanceRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsAnimInstanceRoutine() {}
	FECsAnimInstanceRoutine(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsAnimInstanceRoutine(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsAnimInstanceRoutine() {}

	FORCEINLINE virtual FString ToString() const override { return FECsEnum_uint8::ToString(); }
};

FORCEINLINE uint32 GetTypeHash(const FECsAnimInstanceRoutine& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsAnimInstanceRoutine : public TCsEnumStructMap<FECsAnimInstanceRoutine, uint8>
{
protected:
	EMCsAnimInstanceRoutine() {}
	EMCsAnimInstanceRoutine(const EMCsAnimInstanceRoutine &) = delete;
	EMCsAnimInstanceRoutine(EMCsAnimInstanceRoutine &&) = delete;
public:
	~EMCsAnimInstanceRoutine() {}
private:
	static EMCsAnimInstanceRoutine* Instance;

public:
	static EMCsAnimInstanceRoutine& Get();
};

namespace ECsAnimInstanceRoutine
{
}

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

	virtual void BeginDestroy() override;

// Routine
#pragma region
public:

	static void AddRoutine(UObject* InAnimInstance, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InAnimInstance, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

#pragma endregion Routine

// Event Graph
#pragma region
public:

	/** Init */
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
	TWeakObjectPtr<class APawn> OwningPawn;

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	class APawn* GetOwningPawn();

	template<typename T>
	T* GetOwningPawn()
	{
		return Cast<T>(GetOwningPawn());
	}

	UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
	TWeakObjectPtr<class AActor> MyOwningActor;

	UFUNCTION(BlueprintCallable, Category = "AnimInstance")
	class AActor* GetMyOwningActor();

	template<typename T>
	T* GetMyOwningActor()
	{
		return Cast<T>(GetMyOwningActor());
	}

	USkeletalMeshComponent* GetSkeletalMeshComponent();

	// 0 Setup
#pragma region
public:

#if WITH_EDITOR
	virtual void SetupInGameSimulation();
	virtual void OnTick_Handle_SetupInGameSimulation();
#endif // #if WITH_EDITOR

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool DoSetupInGameSimulation;
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITOR
	TCsBool_Ref DoSetupInGameSimulationHandle;
#endif // #if WITH_EDITOR

#if WITH_EDITORONLY_DATA
	/** Show Emitter Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowEmitterEditorIcons;
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITOR
	TCsBool_Ref ShowEmitterEditorIconsHandle;
#endif // #if WITH_EDITOR

#if WITH_EDITORONLY_DATA
	/** Show Sound Editor Icons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool ShowSoundEditorIcons;
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITOR
	TCsBool_Ref ShowSoundEditorIconsHandle;

	virtual void OnTick_Handle_ShowEditorIcons();
#endif // #if WITH_EDITOR

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	float GlobalPlayRate;
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITOR

	TCsFloat_Ref GlobalPlayRateHandle;

	float Last_GlobalPlayRate;

	virtual void OnTick_Handle_GlobalPlayRate();

#endif // #if WITH_EDITOR

	TCsViewType CurrentViewType;

#if WITH_EDITOR
	// Coroutine Scheduler

	void Spawn_CoroutineScheduler();

	// Manager FX

	TWeakObjectPtr<class AICsManager_FX> Manager_FX;

	class AICsManager_FX* GetManager_FX();

	void Spawn_Manager_FX();

	// Manager Sound

	TWeakObjectPtr<class AICsManager_Sound> Manager_Sound;

	class AICsManager_Sound* GetManager_Sound();

	void Spawn_Manager_Sound();

#endif // #if WITH_EDITOR

#pragma endregion 0 Setup

	/** Tick */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Anims
#pragma region
public:

	ECsLoadFlags DefaultLoadFlags;

	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimSequence &Anim, FCsAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimMontage &Anim, FCsAnimMontage* DataAnim);
	void LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimSequence &Anim, FCsFpvAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimMontage &Anim, FCsFpvAnimMontage* DataAnim);

	void LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace1D &Blend, FCsBlendSpace1D* DataBlend);
	void LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace &Blend, FCsBlendSpace* DataBlend);
	void LoadBlendSpace(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_BlendSpace1D &Blend, FCsFpvBlendSpace1D* DataBlend);
	void LoadBlendSpace(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_BlendSpace &Blend, FCsFpvBlendSpace* DataBlend);

#pragma endregion Anims

#pragma endregion Event Graph
};