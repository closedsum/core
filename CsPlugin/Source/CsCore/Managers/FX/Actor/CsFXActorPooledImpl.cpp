// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsCore.h"

// Library
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_PooledObjectPayload.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"
// FX
#include "Managers/FX/Cache/CsFXPooledCacheImpl.h"
#include "Managers/FX/Payload/CsFXPooledPayload.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"

// Cached
#pragma region

namespace NCsFXActorPooledImplCached
{
	namespace Str
	{
		const FString Allocate = TEXT("UCsFXActorPooledImpl::Allocate");
	}
}

#pragma endregion Cached

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

	checkf(Manager_FX_Actor, TEXT("UCsFXActorPooledImpl::OnConstructObject: Outer for %s is NOT of type: UCsManager_FX_Actor."), *(GetName()));

	UWorld* World = Manager_FX_Actor->GetWorld();

	checkf(World, TEXT("UCsFXActorPooledImpl::OnConstructObject: World is NULL. No World associated with Manager_FX_Actor."));

	FActorSpawnParameters Params;

	FX = World->SpawnActor<ANiagaraActor>(ANiagaraActor::StaticClass(), Params);

	checkf(FX, TEXT("UCsFXActorPooledImpl::OnConstructObject: Failed to spawn FX of type: ANiagaraActor."));
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
	using namespace NCsFXActorPooledImplCached;

	FCsFXPooledCacheImpl* CacheImpl = FCsLibrary_PooledObjectCache::StaticCastChecked<FCsFXPooledCacheImpl>(Str::Allocate, Cache);

	CacheImpl->Allocate(Payload);

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

	checkf(FXComponent, TEXT("%s: NiagaraComponent is NULL for FX Actor: %s."), *(Str::Allocate), *(FX->GetName()));

	CacheImpl->SetFXComponent(FXComponent);

	ICsFXPooledPayload* FXPayload = FCsLibrary_PooledObjectPayload::GetInterfaceChecked<ICsFXPooledPayload>(Str::Allocate, Payload);

	USceneComponent* Parent = Cast<USceneComponent>(Payload->GetParent());

	FX->SetActorTickEnabled(true);
	FX->SetActorHiddenInGame(false);

	//NCsAttachmentTransformRules::ToRule()

	FX->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	FXComponent->SetAsset(FXPayload->GetFXSystem());
	FXComponent->Activate();
}

void UCsFXActorPooledImpl::Deallocate()
{
	FX->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FX->SetActorTickEnabled(false);
	FX->SetActorHiddenInGame(true);

	FX->GetNiagaraComponent()->SetAsset(nullptr);
}

#pragma endregion ICsPooledObject


void UCsFXActorPooledImpl::ConstructCache()
{
	Cache = new FCsFXPooledCacheImpl();
}