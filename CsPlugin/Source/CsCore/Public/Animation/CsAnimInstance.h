// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Animation/AnimInstance.h"
// Types
#include "Types/Property/Ref/CsProperty_Ref_bool.h"
#include "Types/Property/Ref/CsProperty_Ref_float.h"
#include "Animation/CsTypes_Anim.h"
#include "Types/CsTypes_AnimInstance.h"
#include "Coroutine/CsTypes_Coroutine.h"
#include "CsAnimInstance.generated.h"

// Enums
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsAnimInstanceRoutine : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAnimInstanceRoutine)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAnimInstanceRoutine)

struct CSCORE_API EMCsAnimInstanceRoutine : public TCsEnumStructMap<FECsAnimInstanceRoutine, uint8>
{
	CS_DECLARE_ENUM_STRUCT_MAP_BODY(EMCsAnimInstanceRoutine)
};

namespace ECsAnimInstanceRoutine
{
}

#pragma endregion Enums

//class AICsManager_FX;
//class AICsManager_Sound;

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

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "0 Setup")
	bool bSetupInGameSimulation;
#endif // #if WITH_EDITORONLY_DATA

#if WITH_EDITOR
	TCsBool_Ref bSetupInGameSimulationHandle;

	virtual void SetupInGameSimulation();
	virtual void OnTick_Handle_bSetupInGameSimulation();
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

	ECsViewType CurrentViewType;

#if WITH_EDITOR

	// Manager Time

	void Spawn_Manager_Time();

	// Coroutine Scheduler

	void Spawn_CoroutineScheduler();

	// Manager FX

	//TWeakObjectPtr<AICsManager_FX> Manager_FX;

	//AICsManager_FX* GetManager_FX();

	void Spawn_Manager_FX();

	// Manager Sound

	//TWeakObjectPtr<AICsManager_Sound> Manager_Sound;

	//AICsManager_Sound* GetManager_Sound();

	void Spawn_Manager_Sound();

#endif // #if WITH_EDITOR

#pragma endregion 0 Setup

	/** Tick */
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	// Anims
#pragma region
public:

	ECsLoadFlags DefaultLoadFlags;

	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimSequence& Anim, FCsAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, FCsAnimInstance_AnimMontage& Anim, FCsAnimMontage* DataAnim);
	void LoadAnim(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AnimSequence& Anim, FCsFpvAnimSequence* DataAnim);
	void LoadAnim(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AnimMontage& Anim, FCsFpvAnimMontage* DataAnim);

	void LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace1D& Blend, FCsBlendSpace1D* DataBlend);
	void LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace& Blend, FCsBlendSpace* DataBlend);
	void LoadBlendSpace(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_BlendSpace1D& Blend, FCsFpvBlendSpace1D* DataBlend);
	void LoadBlendSpace(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_BlendSpace& Blend, FCsFpvBlendSpace* DataBlend);

	void LoadAimOffset(const FString& MemberName, FCsAnimInstance_AimOffset& Blend, FCsAimOffset* DataBlend);
	void LoadAimOffset(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AimOffset& Blend, FCsFpvAimOffset* DataBlend);

#pragma endregion Anims

#pragma endregion Event Graph
};