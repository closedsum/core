// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Animation/CsAnimInstance.h"
#include "CsCore.h"

// Library
#include "Common/CsCommon_Load.h"
#include "Common/CsCommon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"

// Enums
#pragma region

	// AnimInstanceRoutine
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsAnimInstanceRoutine)

#pragma endregion Enums

UCsAnimInstance::UCsAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	bSetupInGameSimulationHandle.Set(&bSetupInGameSimulation);
	ShowEmitterEditorIconsHandle.Set(&ShowEmitterEditorIcons);
	ShowSoundEditorIconsHandle.Set(&ShowSoundEditorIcons);

	GlobalPlayRate = 1.0f;

	GlobalPlayRateHandle.Set(&GlobalPlayRate);
#endif // #if WITH_EDITOR

	CurrentViewType  = ECsViewType::ThirdPerson;
	DefaultLoadFlags = ECsLoadFlags::All;
}

void UCsAnimInstance::BeginDestroy()
{
	Super::BeginDestroy();

#if WITH_EDITOR 
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// Manager_Time
		if (UCsManager_Time* Manager = UCsManager_Time::Get(this))
			Manager->Shutdown(this);
		// CoroutineScheduler
		if (UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this))
			Scheduler->Shutdown(this);
	}
#endif // #if WITH_EDITOR
}

// Routine
#pragma region

/*static*/ void UCsAnimInstance::AddRoutine(UObject* InAnimInstance, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsAnimInstance>(InAnimInstance)->AddRoutine_Internal(Routine, Type);
}

bool UCsAnimInstance::AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	return false;
}

/*static*/ void UCsAnimInstance::RemoveRoutine(UObject* InAnimInstance, struct FCsRoutine* Routine, const uint8 &Type)
{
	Cast<UCsAnimInstance>(InAnimInstance)->RemoveRoutine_Internal(Routine, Type);
}

bool UCsAnimInstance::RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type)
{
	return false;
}

#pragma endregion Routine

// Init
void UCsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

#if WITH_EDITOR 
	bSetupInGameSimulation = false;
#endif // #if WITH_EDITOR

	OwningPawn = TryGetPawnOwner();
	MyOwningActor = GetOwningActor();
}

APawn* UCsAnimInstance::GetOwningPawn() { return OwningPawn.IsValid() ? OwningPawn.Get() : nullptr; }
AActor* UCsAnimInstance::GetMyOwningActor() { return MyOwningActor.IsValid() ? MyOwningActor.Get() : nullptr; }

USkeletalMeshComponent* UCsAnimInstance::GetSkeletalMeshComponent(){ return GetSkelMeshComponent(); }

// Setup
#pragma region

#if WITH_EDITOR

void UCsAnimInstance::SetupInGameSimulation()
{
	if (!UCsCommon::IsPlayInEditorPreview(GetWorld()))
		return;

	Spawn_Manager_Time();
	Spawn_CoroutineScheduler();
	Spawn_Manager_FX();
	Spawn_Manager_Sound();
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
		if (AICsManager_FX* MyManager_FX = GetManager_FX())
			MyManager_FX->ToggleEmitterEditorIcons(ShowEmitterEditorIcons);
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

void UCsAnimInstance::Spawn_Manager_Time()
{

}

void UCsAnimInstance::Spawn_CoroutineScheduler()
{
	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this);

	if (!Scheduler)
	{
		UCsCoroutineScheduler::Init(this);

		Scheduler = UCsCoroutineScheduler::Get(this);
	}
	Scheduler->MyOwner = this;
}

AICsManager_FX* UCsAnimInstance::GetManager_FX()
{
	return Manager_FX.IsValid() ? Manager_FX.Get() : nullptr;
}

void UCsAnimInstance::Spawn_Manager_FX()
{
	// Check if Manager_FX was already created. This may be the case when Refreshing Nodes for the AnimInstance
	for (TActorIterator<AICsManager_FX> Itr(GetWorld()); Itr; ++Itr)
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

		Manager_FX = GetWorld()->SpawnActor<AICsManager_FX>(SpawnInfo);
		AICsManager_FX::Init(this);
		Manager_FX->CreatePool(4);
		Manager_FX->ToggleEmitterEditorIcons(false);
	}
}

AICsManager_Sound* UCsAnimInstance::GetManager_Sound()
{
	return Manager_Sound.IsValid() ? Manager_Sound.Get() : nullptr;
}

void UCsAnimInstance::Spawn_Manager_Sound()
{
	// Check if Manager_Sound was already created. This may be the case when Refreshing Nodes for the AnimInstance
	for (TActorIterator<AICsManager_Sound> Itr(GetWorld()); Itr; ++Itr)
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

		Manager_Sound = GetWorld()->SpawnActor<AICsManager_Sound>(SpawnInfo);
		AICsManager_Sound::Init(this);

		Manager_Sound->CreatePool(8);
	}
}

#endif // #if WITH_EDITOR

#pragma endregion Setup

// Tick
void UCsAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

#if WITH_EDITOR
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		OnTick_Handle_bSetupInGameSimulation();
		OnTick_Handle_ShowEditorIcons();
		OnTick_Handle_GlobalPlayRate();

		if (UCsManager_Time* Manager_Time = UCsManager_Time::Get(this))
		{
			const FECsUpdateGroup& Group = NCsUpdateGroup::GameState;

			Manager_Time->Update(Group, DeltaTimeX);

			const FCsDeltaTime& DeltaTime = Manager_Time->GetScaledDeltaTime(Group);

			// CoroutineScheduler
			if (UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(this))
				Scheduler->Update(Group, DeltaTime);
			// Manager_FX
			if (AICsManager_FX* MyManager_FX = GetManager_FX())
				MyManager_FX->OnTick(DeltaTimeX);
			// Manager_Sound
			if (AICsManager_Sound* MyManager_Sound = GetManager_Sound())
				MyManager_Sound->OnTick(DeltaTimeX);
		}
	}
#endif // #if WITH_EDITOR
}

// Anims
#pragma region

void UCsAnimInstance::LoadAnim(const FString& MemberName, FCsAnimInstance_AnimSequence &Anim, FCsAnimSequence* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsAnimSequence(MemberName, DataAnim, DefaultLoadFlags);

		if (UAnimSequence* Seq = DataAnim->Get())
		{
			Anim.Anim		   = DataAnim->Anim;
			Anim.Anim_Internal = Seq;
		}
		else
		{
			//																					    TEXT("AnimSequence"), TEXT("Anim Sequence")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimSequence, NCsAnimCached::Str::Anim_Sequence);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Anim.Anim.ToString() != NCsAnimCached::Str::Empty)
		{
			//																						TEXT("AnimSequence"), TEXT("Anim Sequence")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimSequence, NCsAnimCached::Str::Anim_Sequence);
		}
	}
	Anim.Update();
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, FCsAnimInstance_AnimMontage &Anim, FCsAnimMontage* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsAnimMontage(MemberName, DataAnim, DefaultLoadFlags);

		if (UAnimMontage* Seq = DataAnim->Get())
		{
			Anim.Anim		   = DataAnim->Anim;
			Anim.Anim_Internal = Seq;
		}
		else
		{
			//																					   TEXT("AnimMontage"), TEXT("Anim Montage")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimMontage, NCsAnimCached::Str::Anim_Montage);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Anim.Anim.ToString() != NCsAnimCached::Str::Empty)
		{
			//																					   TEXT("AnimMontage"), TEXT("Anim Montage")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimMontage, NCsAnimCached::Str::Anim_Montage);
		}
	}
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AnimSequence& Anim, FCsFpvAnimSequence* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsFpvAnimSequence(MemberName, DataAnim, ViewType);

		if (UAnimSequence* Seq = DataAnim->Get(ViewType))
		{
			Anim.Anim		   = DataAnim->GeTSoftObjectPtr(ViewType);
			Anim.Anim_Internal = Seq;
		}
		else
		{
			//																					    TEXT("AnimSequence"), TEXT("Anim Sequence")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimSequence, NCsAnimCached::Str::Anim_Sequence);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Anim.Anim.ToString() != NCsAnimCached::Str::Empty)
		{
			//																					    TEXT("AnimSequence"), TEXT("Anim Sequence")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimSequence>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimSequence, NCsAnimCached::Str::Anim_Sequence);
		}
	}
}

void UCsAnimInstance::LoadAnim(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AnimMontage& Anim, FCsFpvAnimMontage* DataAnim)
{
	if (DataAnim &&
		Anim.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsFpvAnimMontage(MemberName, DataAnim, ViewType);

		if (UAnimMontage* Seq = DataAnim->Get(ViewType))
		{
			Anim.Anim		   = DataAnim->GeTSoftObjectPtr(ViewType);
			Anim.Anim_Internal = Seq;
		}
		else
		{
			//																					   TEXT("AnimMontage"), TEXT("Anim Montage")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimMontage, NCsAnimCached::Str::Anim_Montage);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Anim.Anim.ToString() != NCsAnimCached::Str::Empty)
		{
			//																					   TEXT("AnimMontage"), TEXT("Anim Montage")
			UCsCommon_Load::LoadTSoftObjectPtr<UAnimMontage>(MemberName, Anim.Anim, Anim.Anim_Internal, NCsAnimCached::Str::AnimMontage, NCsAnimCached::Str::Anim_Montage);
		}
	}
}

void UCsAnimInstance::LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace1D &Blend, FCsBlendSpace1D* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsBlendSpace1D(MemberName, DataBlend, DefaultLoadFlags);

		if (UBlendSpace1D* Space = DataBlend->Get())
		{
			Blend.Blend = DataBlend->Blend;
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																							TEXT("BlendSpace1D"), TEXT("Blend Space 1D")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace1D>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace1D, NCsAnimCached::Str::Blend_Space_1D);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																							TEXT("BlendSpace1D"), TEXT("Blend Space 1D")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace1D>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace1D, NCsAnimCached::Str::Blend_Space_1D);
		}
	}
	Blend.Update();
}

void UCsAnimInstance::LoadBlendSpace(const FString& MemberName, FCsAnimInstance_BlendSpace &Blend, FCsBlendSpace* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsBlendSpace(MemberName, DataBlend, DefaultLoadFlags);

		if (UBlendSpace* Space = DataBlend->Get())
		{
			Blend.Blend = DataBlend->Blend;
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																						  TEXT("BlendSpace"), TEXT("Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace, NCsAnimCached::Str::Blend_Space);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																						  TEXT("BlendSpace"), TEXT("Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace, NCsAnimCached::Str::Blend_Space);
		}
	}
}

void UCsAnimInstance::LoadBlendSpace(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_BlendSpace1D& Blend, FCsFpvBlendSpace1D* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsFpvBlendSpace1D(MemberName, DataBlend, ViewType);

		if (UBlendSpace1D* Space = DataBlend->Get(ViewType))
		{
			Blend.Blend			 = DataBlend->GeTSoftObjectPtr(ViewType);
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																							TEXT("BlendSpace1D"), TEXT("Blend Space 1D")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace1D>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace1D, NCsAnimCached::Str::Blend_Space_1D);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																							TEXT("BlendSpace1D"), TEXT("Anim Sequence")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace1D>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace1D, NCsAnimCached::Str::Blend_Space_1D);
		}
	}
}

void UCsAnimInstance::LoadBlendSpace(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_BlendSpace& Blend, FCsFpvBlendSpace* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsFpvBlendSpace(MemberName, DataBlend, ViewType);

		if (UBlendSpace* Space = DataBlend->Get(ViewType))
		{
			Blend.Blend			 = DataBlend->GeTSoftObjectPtr(ViewType);
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																						  TEXT("BlendSpace"), TEXT("Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace, NCsAnimCached::Str::Blend_Space);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																					      TEXT("BlendSpace"), TEXT("Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::BlendSpace, NCsAnimCached::Str::Blend_Space);
		}
	}
}

void UCsAnimInstance::LoadAimOffset(const FString& MemberName, FCsAnimInstance_AimOffset &Blend, FCsAimOffset* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsAimOffset(MemberName, DataBlend, DefaultLoadFlags);

		if (UAimOffsetBlendSpace* Space = DataBlend->Get())
		{
			Blend.Blend = DataBlend->Blend;
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																									    TEXT("AimOffsetBlendSpace"), TEXT("Aim Offset Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UAimOffsetBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::AimOffsetBlendSpace, NCsAnimCached::Str::Aim_Offset_Blend_Space);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																										TEXT("AimOffsetBlendSpace"), TEXT("Aim Offset Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UAimOffsetBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::AimOffsetBlendSpace, NCsAnimCached::Str::Aim_Offset_Blend_Space);
		}
	}
}

void UCsAnimInstance::LoadAimOffset(const FString& MemberName, const ECsViewType& ViewType, FCsAnimInstance_AimOffset& Blend, FCsFpvAimOffset* DataBlend)
{
	if (DataBlend &&
		Blend.UseDataValueAsDefault)
	{
		UCsCommon_Load::LoadFCsFpvAimOffset(MemberName, DataBlend, ViewType);

		if (UAimOffsetBlendSpace* Space = DataBlend->Get(ViewType))
		{
			Blend.Blend = DataBlend->GeTSoftObjectPtr(ViewType);
			Blend.Blend_Internal = Space;
		}
		else
		{
			//																										TEXT("AimOffsetBlendSpace"), TEXT("Aim Offset Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UAimOffsetBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::AimOffsetBlendSpace, NCsAnimCached::Str::Aim_Offset_Blend_Space);
		}
	}
	else
	{
		//						 != TEXT("")
		if (Blend.Blend.ToString() != NCsAnimCached::Str::Empty)
		{
			//																									   TEXT("AimOffsetBlendSpace"), TEXT("Aim Offset Blend Space")
			UCsCommon_Load::LoadTSoftObjectPtr<UAimOffsetBlendSpace>(MemberName, Blend.Blend, Blend.Blend_Internal, NCsAnimCached::Str::AimOffsetBlendSpace, NCsAnimCached::Str::Aim_Offset_Blend_Space);
		}
	}
}

#pragma endregion Anims