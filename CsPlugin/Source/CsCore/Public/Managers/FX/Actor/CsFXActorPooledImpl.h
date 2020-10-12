// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Managers/Pool/CsOnConstructObject.h"
#include "Managers/Time/CsUpdate.h"
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/FX/Actor/CsFXActorPooled.h"

#include "CsFXActorPooledImpl.generated.h"

struct FCsFXActorPooled;

// NCsPooledObject::NCache::ICache
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NCache, ICache)
// NCsPooledObject::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPooledObject, NPayload, IPayload)

class ANiagaraActor;
class UNiagaraSystem;

UCLASS()
class CSCORE_API UCsFXActorPooledImpl : public UObject,
										public ICsOnConstructObject,
										public ICsUpdate,
										public ICsPooledObject,
										public ICsFXActorPooled
{
	GENERATED_UCLASS_BODY()

#define CacheType NCsPooledObject::NCache::ICache
#define PayloadType NCsPooledObject::NPayload::IPayload
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

// ICsPooledObject
#pragma region
public:

	CacheType* GetCache() const;
	
	void Allocate(PayloadType* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	CacheType* Cache;

	void ConstructCache();

// ICsFXActorPooled
#pragma region
public:

	FORCEINLINE ANiagaraActor* GetFX() const 
	{
		return FX;
	}

#pragma endregion ICsFXActorPooled

protected:

	UPROPERTY()
	ANiagaraActor* FX;

	UNiagaraSystem** AssetPropertyPtr;

#undef CacheType
#undef PayloadType
#undef ConstructParamsType
};