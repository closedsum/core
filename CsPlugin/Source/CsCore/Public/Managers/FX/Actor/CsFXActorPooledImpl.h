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
struct ICsPooledObjectCache;
struct ICsPayload_PooledObject;
class ANiagaraActor;

UCLASS()
class CSCORE_API UCsFXActorPooledImpl : public UObject,
										public ICsOnConstructObject,
										public ICsUpdate,
										public ICsPooledObject,
										public ICsFXActorPooled
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region
public:

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region
public:

	void OnConstructObject(const FCsManagerPooledObjectConstructParams& Params);

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region
public:

	ICsPooledObjectCache* GetCache() const;
	
	void Allocate(ICsPayload_PooledObject* Payload);

	void Deallocate();

#pragma endregion ICsPooledObject

protected:

	ICsPooledObjectCache* Cache;

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
};