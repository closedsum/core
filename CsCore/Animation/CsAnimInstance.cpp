// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.

#include "Animation/CsAnimInstance.h"
#include "CsCore.h"
#include "CsCommon.h"
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"


UCsAnimInstance::UCsAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GlobalPlayRate = 1.0f;
}

void UCsAnimInstance::BeginDestroy()
{
	Super::BeginDestroy();

#if WITH_EDITOR 
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get())
		{
			Scheduler->Shutdown();
		}
	}
#endif // #if WITH_EDITOR
}

// Init
void UCsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

#if WITH_EDITOR 
	DoSetupInGameSimulation = false;
#endif // #if WITH_EDITOR

	OwningPawn = TryGetPawnOwner();
}

APawn* UCsAnimInstance::GetOwningPawn() { return OwningPawn.IsValid() ? OwningPawn.Get() : nullptr; }

USkeletalMeshComponent* UCsAnimInstance::GetSkeletalMeshComponent(){ return GetSkelMeshComponent(); }

// Setup
#pragma region

void UCsAnimInstance::SetupInGameSimulation()
{
#if WITH_EDITOR
	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	Spawn_CoroutineScheduler();
	Spawn_Manager_FX();
	Spawn_Manager_Sound();
#endif // #if WITH_EDITOR
}

void UCsAnimInstance::OnTick_HandleSetupInGameSimulation()
{
	if (DoSetupInGameSimulation && !Last_DoSetupInGameSimulation)
	{
		SetupInGameSimulation();

		DoSetupInGameSimulation = false;
	}
	Last_DoSetupInGameSimulation = DoSetupInGameSimulation;
}

void UCsAnimInstance::OnTick_HandleEditorIcons()
{
#if WITH_EDITOR
	
	if (ShowEmitterEditorIcons != Last_ShowEmitterEditorIcons)
	{
		if (ACsManager_FX* MyManager_FX = GetManager_FX())
			MyManager_FX->ToggleEmitterEditorIcons(ShowEmitterEditorIcons);
	}
	Last_ShowEmitterEditorIcons = ShowEmitterEditorIcons;
#endif // #if WITH_EDITOR
}

void UCsAnimInstance::OnTick_HandleGlobalPlayRate()
{
	if (GlobalPlayRate != Last_GlobalPlayRate)
	{
		USkeletalMeshComponent* Mesh = GetSkeletalMeshComponent();
		Mesh->GlobalAnimRateScale    = GlobalPlayRate;
	}
	Last_GlobalPlayRate = GlobalPlayRate;
}

#if WITH_EDITOR

void UCsAnimInstance::Spawn_CoroutineScheduler()
{
	// Check if CoroutineScheduler was already created. This may be the case when Refreshing Nodes for the AnimInstance

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get();

	if (!Scheduler)
	{
		UCsCoroutineScheduler::Init();

		Scheduler = UCsCoroutineScheduler::Get();
	}

	Scheduler->MyOwner = this;

	/*
	for (TActorIterator<ACsCoroutineScheduler> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr &&
			Itr->GetMyOwner() == this)
		{
			CoroutineScheduler = *Itr;
			break;
		}
	}

	if (!CoroutineScheduler)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;

		CoroutineScheduler = GetWorld()->SpawnActor<ACsCoroutineScheduler>(SpawnInfo);
		CoroutineScheduler->MyOwner = this;
	}
	*/
}

ACsManager_FX* UCsAnimInstance::GetManager_FX()
{
	return Manager_FX.IsValid() ? Manager_FX.Get() : nullptr;
}

void UCsAnimInstance::Spawn_Manager_FX()
{
	// Check if Manager_FX was already created. This may be the case when Refreshing Nodes for the AnimInstance
	for (TActorIterator<ACsManager_FX> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr)
		{
			Manager_FX = *Itr;
			break;
		}
	}

	if (!GetManager_FX())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;

		Manager_FX = GetWorld()->SpawnActor<ACsManager_FX>(SpawnInfo);
		Manager_FX->CreatePool(4);
		Manager_FX->ToggleEmitterEditorIcons(false);
	}
}

ACsManager_Sound* UCsAnimInstance::GetManager_Sound()
{
	return Manager_Sound.IsValid() ? Manager_Sound.Get() : nullptr;
}

void UCsAnimInstance::Spawn_Manager_Sound()
{
	// Check if Manager_Sound was already created. This may be the case when Refreshing Nodes for the AnimInstance
	for (TActorIterator<ACsManager_Sound> Itr(GetWorld()); Itr; ++Itr)
	{
		if (Itr)
		{
			Manager_Sound = *Itr;
			break;
		}
	}

	if (!GetManager_Sound())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;

		Manager_Sound = GetWorld()->SpawnActor<ACsManager_Sound>(SpawnInfo);
		Manager_Sound->CreatePool(2);
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Setup

// Tick
void UCsAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		OnTick_HandleSetupInGameSimulation();
		OnTick_HandleEditorIcons();
		OnTick_HandleGlobalPlayRate();

		if (ACsManager_FX* MyManager_FX = GetManager_FX())
			MyManager_FX->OnTick(DeltaTimeX);

		//if (CoroutineScheduler)
		//	CoroutineScheduler->OnTick_Update(DeltaTimeX);
	}
#endif // #if WITH_EDITOR

	Super::NativeUpdateAnimation(DeltaTimeX);
}

// Anims
#pragma region

void UCsAnimInstance::LoadAnim(const FString& MemberName, FCsAnimInstance_AnimSequence &Anim, FCsAnimSequence* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon::LoadFCsAnimSequence(MemberName, DataAnim);

		if (UAnimSequence* Seq = DataAnim->Get())
			Anim.Anim_Internal = Seq;
		else
			UCsCommon::LoadTAssetPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimSequence"), TEXT("Anim Sequence"));
	}
	else
	{
		if (Anim.Anim.ToString() != TEXT(""))
			UCsCommon::LoadTAssetPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimSequence"), TEXT("Anim Sequence"));
	}
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, FCsAnimInstance_AnimMontage &Anim, FCsAnimMontage* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon::LoadFCsAnimMontage(MemberName, DataAnim);

		if (UAnimMontage* Seq = DataAnim->Get())
			Anim.Anim_Internal = Seq;
		else
			UCsCommon::LoadTAssetPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimMontage"), TEXT("Anim Montage"));
	}
	else
	{
		if (Anim.Anim.ToString() != TEXT(""))
			UCsCommon::LoadTAssetPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimMontage"), TEXT("Anim Montage"));
	}
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimSequence &Anim, FCsFpsAnimSequence* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon::LoadFCsFpsAnimSequence(MemberName, DataAnim, ViewType);

		if (UAnimSequence* Seq = DataAnim->Get(ViewType))
			Anim.Anim_Internal = Seq;
		else
			UCsCommon::LoadTAssetPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimSequence"), TEXT("Anim Sequence"));
	}
	else
	{
		if (Anim.Anim.ToString() != TEXT(""))
			UCsCommon::LoadTAssetPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimSequence"), TEXT("Anim Sequence"));
	}
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, const TCsViewType &ViewType, FCsAnimInstance_AnimMontage &Anim, FCsFpsAnimMontage* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon::LoadFCsFpsAnimMontage(MemberName, DataAnim, ViewType);

		if (UAnimMontage* Seq = DataAnim->Get(ViewType))
			Anim.Anim_Internal = Seq;
		else
			UCsCommon::LoadTAssetPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimMontage"), TEXT("Anim Montage"));
	}
	else
	{
		if (Anim.Anim.ToString() != TEXT(""))
			UCsCommon::LoadTAssetPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, TEXT("AnimMontage"), TEXT("Anim Montage"));
	}
}

#pragma endregion Anims