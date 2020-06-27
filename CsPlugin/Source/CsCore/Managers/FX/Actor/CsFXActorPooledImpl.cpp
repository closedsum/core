// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsCore.h"

// FX
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"

UCsFXActorPooledImpl::UCsFXActorPooledImpl(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region
void UCsFXActorPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
	}
}

#pragma endregion UObject Interface

// ICsOnConstructObject
#pragma region

void UCsFXActorPooledImpl::OnConstructObject()
{
	ConstructCache();
}

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region

void UCsFXActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{

}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

ICsPooledObjectCache* UCsFXActorPooledImpl::GetCache() const
{
	return Cache;
}

void UCsFXActorPooledImpl::Allocate(ICsPooledObjectPayload* Payload)
{

}

void UCsFXActorPooledImpl::Deallocate()
{

}

#pragma endregion ICsPooledObject


void UCsFXActorPooledImpl::ConstructCache()
{
	Cache = new FCsFXPooledCacheImpl();
}