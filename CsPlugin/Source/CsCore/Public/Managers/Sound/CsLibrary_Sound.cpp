// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsLibrary_Sound.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Sound/CsManager_Sound.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Audio
#include "AudioDeviceManager.h"
#include "AudioDevice.h"
// World
#include "Engine/World.h"

namespace NCsSound
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::FLibrary, Spawn_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsSound::FLibrary, Spawn_Internal);
			}
		}
	}

	FLibrary::FLibrary() :
		Manager_SpawnParams()
	{
	}

	FLibrary::~FLibrary()
	{
		Manager_SpawnParams.Shutdown();
	}

	// Load
	#pragma region

	USoundBase* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<USoundBase>(Context, Path, Log);
	}

	USoundBase* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<USoundBase>(Context, Path, Log);
	}

	#pragma endregion Load

	// Spawn
	#pragma region

	#define ParamsResourceType NCsSound::NSpawn::NParams::FResource
	#define ParamsType NCsSound::NSpawn::NParams::FParams

	FCsRoutineHandle FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params)
	{
		using namespace NCsSound::NLibrary::NCached;

		check(Get().Manager_SpawnParams.ContainsChecked(Context, Params));

		check(Params->Get()->IsValidChecked(Context));

		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

		UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
		const FECsUpdateGroup& UpdateGroup = Params->Get()->Group;

		typedef NCsCoroutine::NPayload::FImpl PayloadType;

		PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

		#define COROUTINE Spawn_Internal

		Payload->CoroutineImpl.BindStatic(&NCsSound::FLibrary::COROUTINE);
		Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
		Payload->Owner.SetObject(WorldContext);
		Payload->SetName(Str::COROUTINE);
		Payload->SetFName(Name::COROUTINE);

		#undef COROUTINE

		// Set End callback (to free any allocated references)
		typedef NCsCoroutine::FOnEnd OnEndType;

		Payload->OnEnds.AddDefaulted();
		OnEndType& OnEnd = Payload->OnEnds.Last();
		OnEnd.BindStatic(&FLibrary::Spawn_Internal_OnEnd);

		static const int32 RESOURCE = 0;
		Payload->SetValue_Void(RESOURCE, Params);

		ParamsType* P = Params->Get();
		P->Update();
	
		typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;

		const FrequencyParamsType& FrequencyParams = Params->Get()->FrequencyParams;
		const float TotalTime = FrequencyParams.CalculateTotalTime();

		static const int32 TOTAL_TIME = 0;
		Payload->SetValue_Float(TOTAL_TIME, TotalTime);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check to get Context Root for Manager_Sound
		{
			typedef NCsSound::NManager::FLibrary SoundManagerLibrary;

			UObject* ContextRoot = SoundManagerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}

		// Check Params are Valid.
		if (!Params)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params is NULL."), *Context));
			return FCsRoutineHandle::Invalid;
		}
		// Check Params's Resource is Valid.
		if (!Params->Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params's Resource is NULL."), *Context));
			return FCsRoutineHandle::Invalid;
		}

		if (!Params->Get()->IsValid(Context))
			return FCsRoutineHandle::Invalid;

		if (!Get().Manager_SpawnParams.Contains(Params))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params has NOT been allocated from pool. Use the method that passes by const reference."), *Context));
			return FCsRoutineHandle::Invalid;
		}
		
		// Check to get Context Root for CoroutineScheduler
		{
			typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

			UObject* ContextRoot = CoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}

		return SpawnChecked(Context, WorldContext, Params);
	}

	char FLibrary::Spawn_Internal(FCsRoutine* R)
	{
		using namespace NCsSound::NLibrary::NCached;

		const FString& Context = Str::Spawn_Internal;

		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();

		typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
		typedef NCsSpawner::EFrequency FrequencyType;

		const FrequencyParamsType& FrequencyParams = Params->FrequencyParams;
		const FrequencyType& FreqType = FrequencyParams.GetType();

		static const int32 CAN_SPAWN = 0;
		bool& CanSpawn				 = R->GetValue_Flag(CAN_SPAWN);

		static const int32 HAS_SPAWN_INTERVAL = 1;
		bool& HasSpawnInterval				  = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

		static const int32 SPAWN_COUNT = 0;
		int32& SpawnCount			   = R->GetValue_Int(SPAWN_COUNT);

		static const int32 TOTAL_TIME = 0;
		const float& TotalTime		  = R->GetValue_Float(TOTAL_TIME);

		FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
		ElapsedTime += R->DeltaTime;

		CS_COROUTINE_BEGIN(R)

		do
		{
			{
				ElapsedTime.Reset();

				// Spawn FX
				{
					typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
					typedef NCsSound::NPayload::FImpl PayloadImplType;

					UObject* Owner = R->GetOwnerAsObject();

					PayloadImplType Payload;
					Payload.Instigator		 = Owner;
					Payload.Parent			 = Params->GetObject();
					Payload.Sound			 = Params->Sound.GetChecked(Context);
					Payload.VolumeMultiplier = Params->VolumeMultiplier;
					Payload.PitchMultiplier  = Params->PitchMultiplier;

					SoundManagerLibrary::SpawnChecked(Context, R->GetOwnerAsObject(), Params->Sound.Type, &Payload);
				}

				++SpawnCount;

				// Once
				if (FreqType == FrequencyType::Once)
				{
					 // Do Nothing 
				}
				// Count | TimeCount | TimeInterval
				else
				if (FreqType == FrequencyType::Count ||
					FreqType == FrequencyType::TimeCount ||
					FreqType == FrequencyType::TimeInterval)
				{
					CanSpawn		 = SpawnCount < FrequencyParams.GetCount();
					HasSpawnInterval = CanSpawn && FrequencyParams.GetInterval() > 0.0f;
				}
				// Infinite
				else
				if (FreqType == FrequencyType::Infinite)
				{
					CanSpawn		 = true;
					HasSpawnInterval = true;
				}

				if (HasSpawnInterval)
				{
					CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams.GetInterval());
				}
			}
		} while (CanSpawn);

		CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= TotalTime);

		CS_COROUTINE_END(R)
	}

	void FLibrary::Spawn_Internal_OnEnd(FCsRoutine* R)
	{
		static const int32 RESOURCE  = 0;
		ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		ParamsType* Params			 = Resource->Get();
		Params->Reset();

		Get().Manager_SpawnParams.Deallocate(Resource);
	}

	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Spawn

	bool FLibrary::CanPlayChecked(const FString& Context, const UObject* WorldContext)
	{
		return true;
	}

	bool FLibrary::CanPlay(const UObject* WorldContext)
	{
		if (!WorldContext)
			return false;

		if (!GEngine)
			return false;

		if (!GEngine->UseSound())
			return false;

		UWorld* World = WorldContext->GetWorld();

		if (!World)
			return false;

		if (!World->bAllowAudioPlayback)
			return false;

		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		if (!AudioDevice.IsValid())
			return false;
		return true;
	}

	void FLibrary::SetMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume /*=1.0f*/, const float& Pitch /*=1.0f*/, const float& FadeInTime /*=1.0f*/, bool bApplyToChildren /*=true*/)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)
		
		CS_IS_PTR_NULL_CHECKED(SoundClass)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, Volume, Pitch, FadeInTime, bApplyToChildren);
	}

	void FLibrary::PushMixModifierChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->PushSoundMixModifier(SoundMix);
	}
		
	void FLibrary::SetAndPushMixClassOverrideChecked(const FString& Context, const UObject* WorldContext, USoundMix* SoundMix, USoundClass* SoundClass, const float& Volume /*=1.0f*/, const float& Pitch /*=1.0f*/, const float& FadeInTime /*=1.0f*/, bool bApplyToChildren /*=true*/)
	{
		check(CanPlayChecked(Context, WorldContext));

		CS_IS_PTR_NULL_CHECKED(SoundMix)

		CS_IS_PTR_NULL_CHECKED(SoundClass)

		UWorld* World				   = WorldContext->GetWorld();
		FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, Volume, Pitch, FadeInTime, bApplyToChildren);
		AudioDevice->PushSoundMixModifier(SoundMix);
	}
}