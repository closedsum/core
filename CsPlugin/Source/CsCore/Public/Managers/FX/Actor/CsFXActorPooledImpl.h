// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Time/CsPause.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/FX/Actor/CsFXActorPooled.h"

#include "CsFXActorPooledImpl.generated.h"

struct FCsFXActorPooled;

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsFX::NCache::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NCache, FImpl)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)
// NCsFX::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsFX, NPayload, IPayload)

class ANiagaraActor;
class UNiagaraSystem;

UCLASS()
class CSCORE_API UCsFXActorPooledImpl : public UObject,
										public ICsOnConstructObject,
										public ICsUpdate,
										public ICsPause,
										public ICsPooledObject,
										public ICsFXActorPooled
{
	GENERATED_UCLASS_BODY()

#define CacheType NCsPooledObject::NCache::ICache
#define CacheImplType NCsFX::NCache::FImpl
#define PooledPayloadType NCsPooledObject::NPayload::IPayload
#define FXPayloadType NCsFX::NPayload::IPayload
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const ConstructParamsType& Params);

#pragma endregion ICsOnConstructObject

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

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const { return Cache; }
	
	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	CacheType* Cache;
	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;

// ICsFXActorPooled
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|FX")
	FORCEINLINE ANiagaraActor* GetFX() const { return FX; }

#pragma endregion ICsFXActorPooled

protected:

	UPROPERTY()
	ANiagaraActor* FX;

	UNiagaraSystem** AssetPropertyPtr;

	void Handle_SetFXSystem(FXPayloadType* Payload);
	void Log_SetFXSystem(FXPayloadType* Payload);

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PooledPayloadType* Payload, FXPayloadType* FXPayload);
	void Log_AttachAndSetTransform(PooledPayloadType* Payload, FXPayloadType* FXPayload);

	void Handle_ClearFXSystem();
	void WaitForSystemComplete();

	void Handle_ClearAttachAndTransform();

	void LogChangeCounter();

#undef CacheType
#undef CacheImplType
#undef PooledPayloadType
#undef FXPayloadType
#undef ConstructParamsType
};