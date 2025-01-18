// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Update/CsUpdate.h"
#include "Managers/Time/CsPause.h"
#include "Shutdown/CsShutdown.h"
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
class CSFX_API UCsFXActorPooledImpl : public UObject,
										public ICsOnConstructObject,
										public ICsUpdate,
										public ICsPause,
										public ICsShutdown,
										public ICsPooledObject,
										public ICsFXActorPooled
{
	GENERATED_UCLASS_BODY()

	using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
	using CacheType = NCsPooledObject::NCache::ICache;
	using CacheImplType = NCsFX::NCache::FImpl;
	using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
	using PayloadType = NCsFX::NPayload::IPayload;

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

// ICsPooledObject
#pragma region
public:

	FORCEINLINE CacheType* GetCache() const { return Cache; }
	
	void Allocate(PooledPayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

// PooledObject
#pragma region
protected:

	CacheType* Cache;
	CacheImplType* CacheImpl;

	void ConstructCache();

	uint32 PreserveChangesToDefaultMask;
	uint32 ChangesToDefaultMask;

#pragma endregion PooledObject

// ICsFXActorPooled
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|FX")
	FORCEINLINE ANiagaraActor* GetFX() const { return FX; }

#if !UE_BUILD_SHIPPING
	virtual FString PrintDescription(const int32& Padding) const;
#endif // #if !UE_BUILD_SHIPPING

#pragma endregion ICsFXActorPooled

protected:

	UPROPERTY()
	ANiagaraActor* FX;

	UNiagaraSystem** AssetPropertyPtr;

	void Handle_SetFXSystem(PayloadType* Payload);
	void Log_SetFXSystem(PayloadType* Payload);

	FName AttachToBone;

	void Handle_AttachAndSetTransform(PooledPayloadType* Payload, PayloadType* FXPayload);
	void Log_AttachAndSetTransform(PooledPayloadType* Payload, PayloadType* FXPayload);

	void Handle_ClearFXSystem();
	void WaitForSystemComplete();

	void Handle_ClearAttachAndTransform();

	void LogChangeCounter();
};