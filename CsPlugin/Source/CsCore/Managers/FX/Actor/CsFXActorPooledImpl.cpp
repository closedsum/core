// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsCore.h"

// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
// FX
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"
#include "Managers/FX/Payload/CsFXPooledPayload.h"
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

	UObject* MyOuter = GetOuter();

	checkf(MyOuter, TEXT("UCsFXActorPooledImpl::OnConstructObject: Outer is NULL. No Outer set for %s."), *(GetName()));

	UCsManager_FX_Actor* Manager_FX_Actor = Cast<UCsManager_FX_Actor>(MyOuter);

	checkf(Manager_FX_Actor, TEXT(""));
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
	FCsInterfaceMap* InterfaceMap = Payload->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsFXActorPooledImpl::Allocate: InterfaceMap is NULL. Payload failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));

	ICsFXPooledPayload* FXPayload = InterfaceMap->Get<ICsFXPooledPayload>();
}

void UCsFXActorPooledImpl::Deallocate()
{

}

#pragma endregion ICsPooledObject


void UCsFXActorPooledImpl::ConstructCache()
{
	Cache = new FCsFXPooledCacheImpl();
}