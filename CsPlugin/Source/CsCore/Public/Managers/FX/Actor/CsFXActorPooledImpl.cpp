// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Cache/CsCache_FXImpl.h"
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"

// Cached
#pragma region

namespace NCsFXActorPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, OnConstructObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, Update);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, Allocate);
		}

		namespace Name
		{
			const FName Asset = FName("Asset");
		}
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

void UCsFXActorPooledImpl::OnConstructObject(const FCsManagerPooledObjectConstructParams& Params)
{
	using namespace NCsFXActorPooledImpl::NCached;

	const FString& Context = Str::OnConstructObject;

	ConstructCache();
	
	// Create the FX Actor
	UObject* MyOuter = GetOuter();

	checkf(MyOuter, TEXT("%s: Outer is NULL. No Outer set for %s."), *Context, *(GetName()));

	UCsManager_FX_Actor* Manager_FX_Actor = Cast<UCsManager_FX_Actor>(MyOuter);

	checkf(Manager_FX_Actor, TEXT("%s: Outer for %s is NOT of type: UCsManager_FX_Actor."), *Context, *(GetName()));

	UWorld* World = Manager_FX_Actor->GetMyRoot()->GetWorld();

	checkf(World, TEXT("%s: World is NULL. No World associated with Manager_FX_Actor."), *Context);

	FActorSpawnParameters SpawnParams;

	FX = World->SpawnActor<ANiagaraActor>(ANiagaraActor::StaticClass(), SpawnParams);

	checkf(FX, TEXT("%s: Failed to spawn FX of type: ANiagaraActor."), *Context);

	// Cache the FProperty for UNiagaraComponent->Asset
	UNiagaraComponent* Component = FX->GetNiagaraComponent();
	FProperty* Property			 = Component->GetClass()->FindPropertyByName(Name::Asset);
	
	checkf(Property, TEXT("%s: Failed to find FProperty with Name: %s from UNiagaraComponent."), *Context, *(Name::Asset.ToString()));
	
	AssetPropertyPtr = Property->ContainerPtrToValuePtr<UNiagaraSystem*>(Component);
	
	checkf(AssetPropertyPtr, TEXT("%s: Failed to get pointer to type: UNiagaraSystem from Property: UNiagaraComponent.Asset."), *Context);
}

#pragma endregion ICsOnConstructObject

// ICsUpdate
#pragma region

void UCsFXActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsFXActorPooledImpl::NCached;

	typedef NCsFX::NCache::FImpl CacheImplType;

	CacheImplType* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<CacheImplType>(Str::Update, Cache);

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPooledObject
#pragma region

#define CacheType NCsPooledObject::NCache::ICache
CacheType* UCsFXActorPooledImpl::GetCache() const
{
#undef CacheType

	return Cache;
}

#define PayloadType NCsPooledObject::NPayload::IPayload
void UCsFXActorPooledImpl::Allocate(PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsFXActorPooledImpl::NCached;

	typedef NCsFX::NCache::FImpl CacheImplType;

	CacheImplType* CacheImpl = FCsLibrary_PooledObjectCache::PureStaticCastChecked<CacheImplType>(Str::Allocate, Cache);

	CacheImpl->Allocate(Payload);

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

	checkf(FXComponent, TEXT("%s: NiagaraComponent is NULL for FX Actor: %s."), *(Str::Allocate), *(FX->GetName()));

	CacheImpl->SetFXComponent(FXComponent);

	typedef NCsFX::NPayload::IPayload FXPayloadType;

	FXPayloadType* FXPayload = FCsLibrary_Payload_PooledObject::GetInterfaceChecked<FXPayloadType>(Str::Allocate, Payload);

	FX->SetActorTickEnabled(true);
	FX->SetActorHiddenInGame(false);

	// If the Parent is set, attach the FX to the Parent
	if (USceneComponent* Parent = Cast<USceneComponent>(Payload->GetParent()))
	{
		FX->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(FXPayload->GetAttachmentTransformRule()), FXPayload->GetBone());

		const FTransform& Transform = FXPayload->GetTransform();
		const int32& TransformRules = FXPayload->GetTransformRules();
		
		// Location | Rotation | Scale
		if (TransformRules == NCsTransformRules::All)
		{
			FX->SetActorRelativeTransform(Transform);
		}
		else
		{
			// Location
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Location))
			{
				FX->SetActorRelativeLocation(Transform.GetLocation());
			}
			// Rotation
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Rotation))
			{
				FX->SetActorRelativeRotation(Transform.GetRotation().Rotator());
			}
			// Scale
			if (CS_TEST_BLUEPRINT_BITFLAG(TransformRules, ECsTransformRules::Scale))
			{
				FX->SetActorRelativeScale3D(Transform.GetScale3D());
			}
		}
	}
	// NO Parent, set the World Transform of the FX
	else
	{
		FX->SetActorTransform(FXPayload->GetTransform());
	}

	FXComponent->SetAsset(FXPayload->GetFXSystem());
	FXComponent->Activate();
}

void UCsFXActorPooledImpl::Deallocate()
{
	using namespace NCsFXActorPooledImpl::NCached;

	FX->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	FX->SetActorTickEnabled(false);
	FX->SetActorHiddenInGame(true);

	// NOTE: 4.25. Currently there is a BUG at Runtime when calling UNiagaraComponent->SetAsset(nullptr) where
	//			   some code runs assuming the Asset is valid. The work around is to manually
	//			   call DestroyInstanc() and then "null" out the Asset member on UNiagaraComponent.
#if WITH_EDITOR
	FX->GetNiagaraComponent()->SetAsset(nullptr);
#else
	*AssetPropertyPtr = nullptr;

	FX->GetNiagaraComponent()->DestroyInstance();
#endif // #if WITH_EDITOR

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject


void UCsFXActorPooledImpl::ConstructCache()
{
	typedef NCsFX::NCache::FImpl CacheImplType;

	Cache = new CacheImplType();
}