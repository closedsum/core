// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Animation/CsAnimInstance.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Library/CsLibrary_World.h"
// Singleton
#include "Singleton/CsManager_Singleton_Actor.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
//#include "Managers/FX/Actor/CsManager_FX.h"
//#include "Managers/Sound/CsManager_Sound.h"
// Pawn
#include "GameFramework/Pawn.h"
// Components
#include "Components/SkeletalMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsAnimInstance)

UCsAnimInstance::UCsAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bSetupInGameSimulationHandle.Set(&bSetupInGameSimulation);
	ShowEmitterEditorIconsHandle.Set(&ShowEmitterEditorIcons);
	ShowSoundEditorIconsHandle.Set(&ShowSoundEditorIcons);

	GlobalPlayRate = 1.0f;

	GlobalPlayRateHandle.Set(&GlobalPlayRate);
}

// UObject Interface
#pragma region

void UCsAnimInstance::BeginDestroy()
{
	Super::BeginDestroy();
}

#pragma endregion UObject Interface

// UAnimInstance Interface
#pragma region

// Init
void UCsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	bSetupInGameSimulation = false;

	OwningPawn    = TryGetPawnOwner();
	MyOwningActor = GetOwningActor();
}

// Tick
void UCsAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

#if WITH_EDITOR
	if (CsWorldLibrary::IsPlayInEditorPreview(GetWorld()))
	{
		OnTick_Handle_bSetupInGameSimulation();
		OnTick_Handle_ShowEditorIcons();
		OnTick_Handle_GlobalPlayRate();

		if (Manager_Singleton_Actor)
		{
			UCsManager_Time* Manager_Time = UCsManager_Time::Get(GEngine);

			const FECsUpdateGroup& Group  = NCsUpdateGroup::EditorEngine;
			const FCsDeltaTime& DeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			UCsCoroutineScheduler::Get(GEngine)->Update(Group, DeltaTime);

			//UCsManager_FX::Get(Manager_Singleton_Actor)->Update(DeltaTime);
			//UCsManager_Sound::Get(Manager_Singleton_Actor)->Update(DeltaTime);
		}
	}
#endif // #if WITH_EDITOR
}

#pragma endregion UAnimInstance Interface

APawn* UCsAnimInstance::GetOwningPawn() { return OwningPawn.IsValid() ? OwningPawn.Get() : nullptr; }
AActor* UCsAnimInstance::GetMyOwningActor() { return MyOwningActor.IsValid() ? MyOwningActor.Get() : nullptr; }

USkeletalMeshComponent* UCsAnimInstance::GetSkeletalMeshComponent(){ return GetSkelMeshComponent(); }

// Setup
#pragma region

void UCsAnimInstance::SetupInGameSimulation()
{
}

void UCsAnimInstance::OnTick_Handle_bSetupInGameSimulation()
{
	bSetupInGameSimulationHandle.UpdateIsDirty();

	if (bSetupInGameSimulationHandle.HasChanged())
	{
		if (bSetupInGameSimulation)
		{
			SetupInGameSimulation();

			bSetupInGameSimulationHandle = false;
			bSetupInGameSimulationHandle.Clear();
		}
	}
}

void UCsAnimInstance::OnTick_Handle_ShowEditorIcons()
{
	ShowEmitterEditorIconsHandle.UpdateIsDirty();

	if (ShowEmitterEditorIconsHandle.HasChanged())
	{
		//if (AICsManager_FX* MyManager_FX = GetManager_FX())
		//	MyManager_FX->ToggleEmitterEditorIcons(ShowEmitterEditorIcons);
		ShowEmitterEditorIconsHandle.Clear();
	}
}

void UCsAnimInstance::OnTick_Handle_GlobalPlayRate()
{
	GlobalPlayRateHandle.UpdateIsDirty();

	if (GlobalPlayRateHandle.HasChanged())
	{
		USkeletalMeshComponent* Mesh = GetSkeletalMeshComponent();
		Mesh->GlobalAnimRateScale    = GlobalPlayRate;

		GlobalPlayRateHandle.Clear();
	}
}

#pragma endregion Setup