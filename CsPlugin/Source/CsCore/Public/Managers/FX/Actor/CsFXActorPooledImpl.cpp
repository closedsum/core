// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsCore.h"

// CVar
#include "Managers/FX/CsCVars_FX.h"
// Types
#include "Types/CsTypes_Macro.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_PooledObjectCache.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/FX/CsLibrary_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Cache/CsCache_FXImpl.h"
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "Managers/FX/Params/CsParams_FX.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

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

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetAsset, "UCsFXActorPooledImpl::Allocate_SetAsset");
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

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
void UCsFXActorPooledImpl::OnConstructObject(const ConstructParamsType& Params)
{
#undef ConstructParamsType

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
	typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;

	CacheImplType* CacheImpl = PooledCacheLibrary::PureStaticCastChecked<CacheImplType>(Str::Update, Cache);

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

	const FString& Context = Str::Allocate;

	typedef NCsFX::NCache::FImpl CacheImplType;
	typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;

	// TODO: Add IsValidChecked in PayloadLibrary

	CacheImplType* CacheImpl = PooledCacheLibrary::PureStaticCastChecked<CacheImplType>(Context, Cache);

	CacheImpl->Allocate(Payload);

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

	checkf(FXComponent, TEXT("%s: NiagaraComponent is NULL for FX Actor: %s."), *Context, *(FX->GetName()));

	CacheImpl->SetFXComponent(FXComponent);

	typedef NCsFX::NPayload::IPayload FXPayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	FXPayloadType* FXPayload = PooledPayloadLibrary::GetInterfaceChecked<FXPayloadType>(Context, Payload);

	// If the Parent is set, attach the FX to the Parent
	USceneComponent* Parent = nullptr;

	UObject* Object = Payload->GetParent();

		// SceneComponent
	if (USceneComponent* Component = Cast<USceneComponent>(Object))
		Parent = Component;
		// Actor -> Get RootComponent
	else
	if (AActor* Actor = Cast<AActor>(Object))
		Parent = Actor->GetRootComponent();

	const FTransform& Transform = FXPayload->GetTransform();
	const int32& TransformRules = FXPayload->GetTransformRules();

	if (Parent)
	{
		// TODO: Add check if Bone is Valid for SkeletalMeshComponent
		FX->AttachToComponent(Parent, NCsAttachmentTransformRules::ToRule(FXPayload->GetAttachmentTransformRule()), FXPayload->GetBone());

		NCsTransformRules::SetRelativeTransform(FX, Transform, TransformRules);
	}
	// NO Parent, set the World Transform of the FX
	else
	{
		NCsTransformRules::SetTransform(FX, Transform, TransformRules);
	}

	UNiagaraSystem* FXSystem = FXPayload->GetFXSystem();

	FXComponent->SetAsset(FXSystem);

	// Set Parameters
	typedef NCsFX::NParameter::IParameter ParameterType;
	typedef NCsFX::FLibrary FXLibrary;

	const TArray<ParameterType*>& Parameters = FXPayload->GetParameters();

	for (const ParameterType* Param : Parameters)
	{
		FXLibrary::SetParameterChecked(Context, FXComponent, Param);
	}

	FX->SetActorTickEnabled(true);
	FX->SetActorHiddenInGame(false);

	{
		const FString& ScopeName		   = ScopedTimer::SetAsset;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::FX;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogFXScopedTimerActivate;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		FXComponent->Activate();
	}
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