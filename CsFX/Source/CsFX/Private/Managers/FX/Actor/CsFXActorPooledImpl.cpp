// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsFXActorPooledImpl.h"
#include "CsFX.h"

// CVar
#include "Managers/FX/CsCVars_FX.h"
// Types
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Cache/CsLibrary_Cache_PooledObject.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/FX/CsLibrary_FX.h"
#include "Library/CsLibrary_World.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// Pooled Object
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// FX
#include "Managers/FX/Cache/CsCache_FXImpl.h"
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "Managers/FX/Params/CsParams_FX.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "NiagaraSystemSimulation.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameInstance.h"
#endif // #if WITH_EDITOR

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, Handle_SetFXSystem);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, Handle_ClearFXSystem);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsFXActorPooledImpl, WaitForSystemComplete);
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

UCsFXActorPooledImpl::UCsFXActorPooledImpl(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	// Shutdown
	bShutdown(false),
	Cache(nullptr),
	CacheImpl(nullptr),
	PreserveChangesToDefaultMask(0),
	ChangesToDefaultMask(0),
	FX(nullptr),
	AssetPropertyPtr(nullptr),
	AttachToBone(NAME_None)
{
}

// UObject Interface
#pragma region

void UCsFXActorPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Shutdown();
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

	UCsManager_FX* Manager_FX = Cast<UCsManager_FX>(MyOuter);

	checkf(Manager_FX, TEXT("%s: Outer for %s is NOT of type: UCsManager_FX."), *Context, *(GetName()));

	UWorld* World = Manager_FX->GetMyRoot()->GetWorld();

	checkf(World, TEXT("%s: World is NULL. No World associated with Manager_FX."), *Context);

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

	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsPause
#pragma region

void UCsFXActorPooledImpl::Pause(bool bPaused)
{
	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

	checkf(FXComponent, TEXT("UCsFXActorPooledImpl::Pause: NiagaraComponent is NULL for FX Actor: %s."), *(FX->GetName()));

	FXComponent->SetPaused(bPaused);
}

#pragma endregion ICsPause

// ICsShutdown
#pragma region

void UCsFXActorPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}

	FX = nullptr;
	bShutdown = true;
}

#pragma endregion ICsShutdown

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void UCsFXActorPooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsFXActorPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	typedef NCsFX::NCache::FImpl CacheImplType;
	typedef NCsPooledObject::NCache::FLibrary PooledCacheLibrary;

	CacheImpl->Allocate(Payload);

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

	checkf(FXComponent, TEXT("%s: NiagaraComponent is NULL for FX Actor: %s."), *Context, *(FX->GetName()));

	CacheImpl->SetFXComponent(FXComponent);

	PreserveChangesToDefaultMask = Payload->GetPreserveChangesFromDefaultMask();

	typedef NCsFX::NPayload::IPayload FXPayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	FXPayloadType* FXPayload = PooledPayloadLibrary::GetInterfaceChecked<FXPayloadType>(Context, Payload);

	// Attach and set Transform
	Handle_AttachAndSetTransform(Payload, FXPayload);
	// Set FX System
	Handle_SetFXSystem(FXPayload);

	// TODO: Change for Parameters

	// Set Parameters
	typedef NCsFX::FLibrary FXLibrary;
	typedef NCsFX::NParameter::IParameter ParameterType;
	typedef NCsFX::NParameter::NScaled::IScaled ScaledParameterType;
	typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType SkeletalMeshParameterType;
	
		// Value
	const TArray<ParameterType*>& Parameters = FXPayload->GetParameters();

	for (const ParameterType* Param : Parameters)
	{
		FXLibrary::SetParameterChecked(Context, FXComponent, Param);
	}
		// Scaled
	const TArray<ScaledParameterType*>& ScaledParameters = FXPayload->GetScaledParameters();

	float Scale = FXPayload->ShouldApplyTransformScale() ? 1.0f : FXPayload->GetTransform().GetScale3D().GetMax();

	for (const ScaledParameterType* Param : ScaledParameters)
	{
		FXLibrary::SetParameterChecked(Context, FXComponent, Param, Scale);
	}
		// Data Interface

			// Skeletal
	const TArray<SkeletalMeshParameterType*>& SkeletalMeshParameters = FXPayload->GetSkeletalMeshParameters();

	for (const SkeletalMeshParameterType* Param : SkeletalMeshParameters)
	{
		FXLibrary::SetParameterChecked(Context, FXComponent, Param);
	}

	FX->SetActorTickEnabled(true);
	FXComponent->SetHiddenInGame(false);
	FX->SetActorHiddenInGame(false);

	{
		const FString& ScopeName		   = ScopedTimer::SetAsset;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::FX;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogFXScopedTimerActivate;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		FXComponent->Activate();
	}

	CS_NON_SHIPPING_EXPR(LogChangeCounter());
}

void UCsFXActorPooledImpl::Deallocate()
{
	using namespace NCsFXActorPooledImpl::NCached;

	// Check if beginning Shutdown
	UCsManager_FX* Manager_FX = Cast<UCsManager_FX>(GetOuter());
	const bool IsBeginningShutdown		  = Manager_FX->IsBeginningShutdown();

	if (IsBeginningShutdown)
	{
		ChangesToDefaultMask = 0;
		PreserveChangesToDefaultMask = 0;
	}

	Handle_ClearAttachAndTransform();

	FX->SetActorTickEnabled(false);
	FX->SetActorHiddenInGame(true);

	Handle_ClearFXSystem();

	PreserveChangesToDefaultMask = 0;

	CS_NON_SHIPPING_EXPR(LogChangeCounter());

	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledObject
#pragma region

void UCsFXActorPooledImpl::ConstructCache()
{
	typedef NCsFX::NCache::FImpl CacheImplType;

	Cache	  = new CacheImplType();
	CacheImpl = (CacheImplType*)Cache;
}

#pragma endregion PooledObject

// ICsFXActorPooled
#pragma region

#if !UE_BUILD_SHIPPING

FString UCsFXActorPooledImpl::PrintDescription(const int32& Padding) const
{
	FString Desc;

	FString Pad;

	for (int32 I = 0; I < Padding; ++I)
	{
		Pad += TEXT(" ");
	}

	Desc += Pad + GetName();
	Desc += TEXT("\n");
	Desc += Pad + FString::Printf(TEXT(" Index: %d"), Cache->GetIndex());
	Desc += TEXT("\n");
	Desc += Pad + FString::Printf(TEXT(" bAllocated: %s"), Cache->IsAllocated() ? TEXT("True") : TEXT("False"));

	if (Cache->IsAllocated())
	{
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" State: %s"), NCsPooledObject::EMState::Get().ToChar(Cache->GetState()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" UpdateType: %s"), NCsPooledObject::EMUpdate::Get().ToChar(Cache->GetUpdateType()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" Instigator: %s"), Cache->GetInstigator() ? *(Cache->GetInstigator()->GetName()) : TEXT("NULL"));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" Owner: %s"), Cache->GetOwner() ? *(Cache->GetOwner()->GetName()) : TEXT("NULL"));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" Parent: %s"), Cache->GetParent() ? *(Cache->GetParent()->GetName()) : TEXT("NULL"));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" WarmUpTime: %f"), Cache->GetWarmUpTime());
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" LifeTime: %f"), Cache->GetLifeTime());
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" StartTime: %s"), *(Cache->GetStartTime().ToCompactString()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" ElapsedTime: %s"), *(Cache->GetElapsedTime().ToCompactString()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" FXComponent: %s"), *(CacheImpl->GetFXComponent()->GetName()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" FXSystem: %s"), CacheImpl->GetFXComponent()->GetAsset() ? *(CacheImpl->GetFXComponent()->GetAsset()->GetName()) : TEXT("NULL"));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" DeallocateMethod: %s"), NCsFX::EMDeallocateMethod::Get().ToChar(CacheImpl->GetDeallocateMethod()));
		Desc += TEXT("\n");
		Desc += Pad + FString::Printf(TEXT(" DeallocateState: %s"), NCsFX::EMDeallocateState::Get().ToChar(CacheImpl->GetDeallocateState()));
	}
	return Desc;
}

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion ICsFXActorPooled

#define FXPayloadType NCsFX::NPayload::IPayload

void UCsFXActorPooledImpl::Handle_SetFXSystem(FXPayloadType* Payload)
{
	CS_NON_SHIPPING_EXPR(Log_SetFXSystem(Payload));

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();
	UNiagaraSystem* FXSystem	   = Payload->GetFXSystem();

	typedef NCsFX::NPayload::EChange ChangeType;
	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

	// If ALREADY set FXSystem and the trying to the SAME FXSystem, Do Nothing
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::FXSystem) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::FXSystem))
	{
		if (FXComponent->GetAsset() != FXSystem)
		{
			FXComponent->SetAsset(FXSystem);
			ChangeCounter::Get().AddChanged();
		}
		else
		{
			ChangeCounter::Get().AddPreserved();
		}
	}
	else
	{
		FXComponent->SetAsset(FXSystem);
		ChangeCounter::Get().AddChanged();
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::FXSystem);
}

void UCsFXActorPooledImpl::Log_SetFXSystem(FXPayloadType* Payload)
{
	using namespace NCsFXActorPooledImpl::NCached;

	const FString& Context = Str::Handle_SetFXSystem;

	if (CS_CVAR_LOG_IS_SHOWING(LogFXPooledChange) ||
		CS_CVAR_LOG_IS_SHOWING(LogFXPooledChangeSet))
	{
		UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();
		UNiagaraSystem* FXSystem	   = Payload->GetFXSystem();

		typedef NCsFX::NPayload::EChange ChangeType;
		typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

		// Check if FX System should be PRESERVED
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::FXSystem))
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: %s"), *Context, *(ChangeCounter::Get().ToString()));

			// Check if the FX System changed
			if (FXComponent->GetAsset() != FXSystem)
			{
				if (CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::FXSystem))
				{
					UE_LOG(LogCsFX, Warning, TEXT(" %s -> %s."), *(FXComponent->GetAsset()->GetName()), *(FXSystem->GetName()));
				}
				else
				{
					UE_LOG(LogCsFX, Warning, TEXT(" NULL -> %s."), *(FXSystem->GetName()));
				}
			}
			else
			{
				UE_LOG(LogCsFX, Warning, TEXT(" (PRESERVED) %s."), *(FXComponent->GetAsset()->GetName()));
			}
		}
	}
}

#define PooledPayloadType NCsPooledObject::NPayload::IPayload

void UCsFXActorPooledImpl::Handle_AttachAndSetTransform(PooledPayloadType* Payload, FXPayloadType* FXPayload)
{
	CS_NON_SHIPPING_EXPR(Log_AttachAndSetTransform(Payload, FXPayload));

	UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

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

	FTransform3f Transform = FXPayload->GetTransform();

	if (!FXPayload->ShouldApplyTransformScale())
	{
		Transform.SetScale3D(FVector3f::OneVector);
	}

	const int32& TransformRules = FXPayload->GetTransformRules();
	
	typedef NCsFX::NPayload::EChange ChangeType;
	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsFX::NPayload::NChange

	if (Parent)
	{
		const FAttachmentTransformRules& Rule = FXPayload->GetAttachmentTransformRule();
		const FName& Bone					  = FXPayload->GetBone();

		bool PerformAttach = true;
		bool IsPreserved = false;

		// If Attach and Transform are the SAME, Do Nothing
		if (FXComponent->GetAttachParent() == Parent &&
			AttachToBone == Bone)
		{
			// Check Attachment Rule
			IsPreserved   = ChangeHelper::HasAttach(PreserveChangesToDefaultMask & ChangesToDefaultMask, Rule);
			PerformAttach = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		// Attach
		if (PerformAttach)
		{
			AttachToBone = Bone;

			FXComponent->SetUsingAbsoluteLocation(FXPayload->GetbAbsoluteLocation());
			FXComponent->SetUsingAbsoluteRotation(FXPayload->GetbAbsoluteRotation());
			FXComponent->SetUsingAbsoluteScale(FXPayload->GetbAbsoluteScale());
			FXComponent->AttachToComponent(Parent, Rule, Bone);
			ChangeCounter::Get().AddChanged();
		}

		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeHelper::FromTransformAttachmentRule(Rule));

		bool PerformTransform = true;
		IsPreserved			  = false;

		// If Transform has NOT changed, don't update it.
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Transform) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Transform))
		{
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(FXComponent->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		// Set Transform
		if (PerformTransform)
		{
			NCsTransformRules::SetRelativeTransform(FXComponent, Transform, TransformRules);
			ChangeCounter::Get().AddChanged();
		}
		CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
	}
	// NO Parent, set the World Transform of the FX Component
	else
	{
		bool PerformTransform = true;
		bool IsPreserved	  = false;

		// If Transform has NOT changed, don't update it.
		if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::Transform) &&
			CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::Transform))
		{
			IsPreserved		 = NCsTransformRules::AreTransformsEqual(FXComponent->GetRelativeTransform(), Transform, TransformRules);
			PerformTransform = !IsPreserved;

			if (IsPreserved)
				ChangeCounter::Get().AddPreserved();
		}

		if (PerformTransform)
		{
			NCsTransformRules::SetTransform(FX, Transform, TransformRules);
			ChangeCounter::Get().AddChanged();
		}

		AttachToBone = NAME_None;
	}
	CS_SET_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);

	#undef ChangeHelper
}

void UCsFXActorPooledImpl::Log_AttachAndSetTransform(PooledPayloadType* Payload, FXPayloadType* FXPayload)
{
}

#undef PooledPayloadType

#undef FXPayloadType

void UCsFXActorPooledImpl::Handle_ClearFXSystem()
{
	using namespace NCsFXActorPooledImpl::NCached;

	const FString& Context = Str::Handle_ClearFXSystem;

	typedef NCsFX::FLibrary FXLibrary;
	typedef NCsFX::NPayload::EChange ChangeType;
	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

	// If FX System is SET and meant to be PRESERVED, Deactivate
	if (CS_TEST_BITFLAG(PreserveChangesToDefaultMask, ChangeType::FXSystem) &&
		CS_TEST_BITFLAG(ChangesToDefaultMask, ChangeType::FXSystem))
	{
		FX->GetNiagaraComponent()->Deactivate();
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		// NOTE: 4.25. Currently there is a BUG at Runtime when calling UNiagaraComponent->SetAsset(nullptr) where
		//			   some code runs assuming the Asset is valid. The work around is to manually
		//			   call DestroyInstance() and then "null" out the Asset member on UNiagaraComponent.
		// NOTE: 4.26.2. Still occurs.

#if WITH_EDITOR
		// NOTE: 4.26.2. When exiting the game, need to wait for any async threads (render/gpu) to complete.
		//				 During the game, this shouldn't be an issue since the FX should deallocate gracefully.
		typedef NCsWorld::FLibrary WorldLibrary;
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		UCsManager_FX* Manager_FX = Cast<UCsManager_FX>(GetOuter());
		UObject* OuterRoot					  = Manager_FX->GetMyRoot();

		if (WorldLibrary::IsPlayInGameOrPIE(OuterRoot) &&
			GameInstanceLibrary::IsStandaloneFromEditorChecked(Context, OuterRoot))
		{
			FX->GetNiagaraComponent()->DeactivateImmediate();
			*AssetPropertyPtr = nullptr;
			WaitForSystemComplete();
			FX->GetNiagaraComponent()->DestroyInstance();
		}
		else
		{
			FX->GetNiagaraComponent()->SetAsset(nullptr);
		}
#else
		FX->GetNiagaraComponent()->DeactivateImmediate();

		*AssetPropertyPtr = nullptr;

		// NOTE: 4.26.2. When exiting the game, need to wait for any async threads (render/gpu) to complete.
		//				 During the game, this shouldn't be an issue since the FX should deallocate gracefully.
		WaitForSystemComplete();

		FX->GetNiagaraComponent()->DestroyInstance();

#endif // #if WITH_EDITOR
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::FXSystem);
		ChangeCounter::Get().AddCleared();
	}
}

void UCsFXActorPooledImpl::WaitForSystemComplete()
{
	using namespace NCsFXActorPooledImpl::NCached;

	const FString& Context = Str::WaitForSystemComplete;

	// Check to Wait for System to "complete"
	UCsManager_FX* Manager_FX = Cast<UCsManager_FX>(GetOuter());
	const bool IsBeginningShutdown		  = Manager_FX->IsBeginningShutdown();

	typedef NCsFX::FLibrary FXLibrary;

	FNiagaraSystemInstance* System = FXLibrary::GetSafeSystemInstance(Context, FX->GetNiagaraComponent(), nullptr);

	bool WaitForSystem = false;
	
	if (IsBeginningShutdown)
	{
		if (System)
		{
#if !UE_BUILD_SHIPPING
			if (CS_CVAR_LOG_IS_SHOWING(LogFXPooledWaitForSystemComplete))
			{
				if (UNiagaraSystem* NS = System->GetSystem())
				{
					UE_LOG(LogCsFX, Warning, TEXT("%s: IsBeginningShutdown and System != NULL. NiagaraSystem: %s. Set WaitForSystem = true."), *Context, *(NS->GetName()));
				}
				else
				{
					UE_LOG(LogCsFX, Warning, TEXT("%s: IsBeginningShutdown and System != NULL. Set WaitForSystem = true."), *Context);
				}
			}
#endif // #if !UE_BUILD_SHIPPING
			WaitForSystem = true;
		}
	}
	else
	{
		WaitForSystem = System != nullptr && System->GetSystemInstanceIndex() != INDEX_NONE && System->GetSystem() != nullptr;// && !System->HandleCompletion();

#if !UE_BUILD_SHIPPING
		if (WaitForSystem &&
			CS_CVAR_LOG_IS_SHOWING(LogFXPooledWaitForSystemComplete))
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: System != NULL. NiagaraSystem: %s. Set WaitForSystem = true."), *Context, *(System->GetSystem()->GetName()));
		}
#endif // #if !UE_BUILD_SHIPPING
	}

	if (WaitForSystem)
	{
		System->WaitForConcurrentTickDoNotFinalize(false);
	}

	TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> Simulation = FXLibrary::GetSafeSystemSimulation(Context, FX->GetNiagaraComponent(), nullptr);

#if WITH_EDITOR
	/*
	while (Simulation.IsValid())
	{
		FPlatformProcess::SleepNoStats(0.001f);
	}
	*/
#else
	if (WaitForSystem &&
		Simulation.IsValid())
	{
#if !UE_BUILD_SHIPPING
		if (CS_CVAR_LOG_IS_SHOWING(LogFXPooledWaitForSystemComplete))
		{
			UE_LOG(LogCsFX, Warning, TEXT("UCsFXActorPooledImpl::WaitForSystemComplete: Waiting for Simulation."), *(System->GetSystem()->GetName()));
		}
#endif // #if !UE_BUILD_SHIPPING

		Simulation->WaitForInstancesTickComplete(false);
	}
#endif // #if WITH_EDITOR
}

void UCsFXActorPooledImpl::Handle_ClearAttachAndTransform()
{
	typedef NCsFX::NPayload::EChange ChangeType;
	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;
	#define ChangeHelper NCsFX::NPayload::NChange
	
	const uint32 Mask = PreserveChangesToDefaultMask & ChangesToDefaultMask;

	// If Attached, check if the Attach should be PERSERVED
	if (FX->GetNiagaraComponent()->GetAttachParent())
	{
		if (ChangeHelper::HasAttach(Mask))
		{
			// Do Nothing
			ChangeCounter::Get().AddPreserved();
			ChangeCounter::Get().AddPreserved();
		}
		else
		{
			UNiagaraComponent* FXComponent = FX->GetNiagaraComponent();

			FXComponent->SetUsingAbsoluteLocation(false);
			FXComponent->SetUsingAbsoluteRotation(false);
			FXComponent->SetUsingAbsoluteScale(false);

			FX->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			FX->SetActorRelativeTransform(FTransform3d::Identity);
			CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeHelper::GetAttachAsMask(Mask));
			CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
			AttachToBone = NAME_None;
			ChangeCounter::Get().AddCleared();
			ChangeCounter::Get().AddCleared();
		}
	}
	// If NOT Attached, check if Transform should be PRESERVED
	else
	if (CS_TEST_BITFLAG(Mask, ChangeType::Transform))
	{
		// Do Nothing	
		ChangeCounter::Get().AddPreserved();
	}
	else
	{
		FX->SetActorRelativeTransform(FTransform3d::Identity);
		CS_CLEAR_BITFLAG(ChangesToDefaultMask, ChangeType::Transform);
		ChangeCounter::Get().AddCleared();
	}

	#undef ChangeHelper
}

void UCsFXActorPooledImpl::LogChangeCounter()
{
	if (CS_CVAR_LOG_IS_SHOWING(LogFXPooledChangeCounter))
	{
		typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

		UE_LOG(LogCsFX, Warning, TEXT("UCsFXActorPooledImpl::LogChangeCounter: %s."), *(ChangeCounter::Get().ToString()));
	}
}