// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GameFramework/Actor.h"
// Interfaces
#include "Update/CsUpdate.h"
#include "Managers/Time/CsPause.h"
#include "Shutdown/CsShutdown.h"
#include "Managers/Pool/CsPooledObject.h"
// Types
#include "Managers/Sound/CsSoundPooled.h"
#include "Managers/Sound/CsTypes_SoundPooled.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"

#include "CsSoundPooledImpl.generated.h"

class UAudioComponent;
class UDamageType;

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsSound::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSound, NPayload, IPayload)
// NCsSound::NCache::NImpl::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSound, NCache, NImpl, FImpl)

struct FCsRoutine;

/**
* 
*/
UCLASS()
class CSSOUND_API ACsSoundPooledImpl : public AActor,
									  public ICsUpdate,
									  public ICsPause,
									  public ICsShutdown,
									  public ICsPooledObject,
									  public ICsSoundPooled
{
	GENERATED_UCLASS_BODY()

using CacheType = NCsPooledObject::NCache::ICache;
using CacheImplType = NCsSound::NCache::NImpl::FImpl;
using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
using SoundPayloadType = NCsSound::NPayload::IPayload;

public:

	UPROPERTY(Category = Sound, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sound,Audio,Audio|Components|Audio"))
	UAudioComponent* AudioComponent;

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// AActor Interface
#pragma region
public:

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void FellOutOfWorld(const UDamageType& DmgType) override;
	virtual void OutsideWorldBounds() override;

#pragma endregion AActor Interface

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPause
#pragma region
public:

	void Pause(bool bPaused);

#pragma endregion ICsPause

// ICsShutdown
#pragma region
public:

	void Shutdown();

	FORCEINLINE bool HasShutdown() const { return bShutdown; }

#pragma endregion ICsShutdown

// Shutdown
#pragma region
private:

	bool bShutdown;

#pragma endregion Shutdown

protected:

	CacheType* Cache;
	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;

// ICsPooledObject
#pragma region
public:

	CacheType* GetCache() const;

	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// ICsSoundPooled
#pragma region
public:

	FORCEINLINE UAudioComponent* GetAudioComponent() const { return AudioComponent; }

	UFUNCTION(BlueprintCallable, Category = "CsCore|Sound", meta = (AutoCreateRefTerm = "FadeOutTime"))
	void Stop(const float& FadeOutTime = 0.0f);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Sound", meta = (AutoCreateRefTerm = "Duration"))
	void FadeIn(const float& Duration);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Sound", meta = (AutoCreateRefTerm = "Duration"))
	void FadeOut(const float& Duration);

#pragma endregion ICsSoundPooled

// Sound Pooled
#pragma region
private:

	char Stop_Internal(FCsRoutine* R);

	FCsRoutineHandle StopHandle;

#pragma endregion SoundPooled

public:

	UPROPERTY(BlueprintReadWrite, Category = "Sound")
	FECsSound Type;

	void Play(SoundPayloadType* Payload);

public:

	float InitialVolume;

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PooledPayloadType* Payload, SoundPayloadType* SoundPayload);
	void Log_AttachAndSetTransform(PooledPayloadType* Payload, SoundPayloadType* SoundPayload);

	void Handle_ClearAttachAndTransform();

	void LogChangeCounter();
};