// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsManager_Damage.h"
#include "CsCore.h"

// CVar
#include "Managers/Damage/CsCVars_Manager_Damage.h"
// Library
#include "Library/CsLibrary_Common.h"
#include "Managers/Damage/Expression/CsLibrary_DamageExpression.h"
// Damage
#include "Managers/Damage/Event/CsDamageEventImpl.h"
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Managers/Damage/Shape/CsDamageShape.h"
// Unique
#include "UniqueObject/CsUniqueObject.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Damage/CsGetManagerDamage.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerDamageCached
{
	namespace Str
	{
		const FString ProcessDamageEvent = TEXT("UCsManager_Damage::ProcessDamageEvent");
		const FString ProcessDamageEventContainer = TEXT("UCsManager_Damage::ProcessDamageEventContainer");
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Damage* UCsManager_Damage::s_Instance;
bool UCsManager_Damage::s_bShutdown = false;

UCsManager_Damage::UCsManager_Damage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Damage* UCsManager_Damage::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Damage::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Damage::Init(UObject* InRoot, TSubclassOf<UCsManager_Damage> ManagerDamageClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDamage* GetManagerDamage = Get_GetManagerDamage(InRoot);

	UCsManager_Damage* Manager_Damage = GetManagerDamage->GetManager_Damage();

	if (!Manager_Damage)
	{
		Manager_Damage = NewObject<UCsManager_Damage>(InOuter ? InOuter : InRoot, ManagerDamageClass, TEXT("Manager_Damage_Singleton"), RF_Transient | RF_Public);

		GetManagerDamage->SetManager_Damage(Manager_Damage);

		Manager_Damage->SetMyRoot(InRoot);
		Manager_Damage->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Damage>(GetTransientPackage(), ManagerDamageClass, TEXT("Manager_Damage_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Damage::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerDamage* GetManagerDamage = Get_GetManagerDamage(InRoot);
	UCsManager_Damage* Manager_Damage	  = GetManagerDamage->GetManager_Damage();
	Manager_Damage->CleanUp();

	GetManagerDamage->SetManager_Damage(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Damage::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerDamage(InRoot)->GetManager_Damage() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerDamage* UCsManager_Damage::Get_GetManagerDamage(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton is NULL."));

	ICsGetManagerDamage* GetManagerDamage = Cast<ICsGetManagerDamage>(Manager_Singleton);

	checkf(GetManagerDamage, TEXT("UCsManager_Damage::Get_GetManagerDamage: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerDamage."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerDamage;
}

/*static*/ ICsGetManagerDamage* UCsManager_Damage::GetSafe_GetManagerDamage(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerDamage>(Manager_Singleton);
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetSafe(UObject* Object)
{
	if (ICsGetManagerDamage* GetManagerDamage = GetSafe_GetManagerDamage(Object))
		return GetManagerDamage->GetManager_Damage();
	return nullptr;
}

/*static*/ UCsManager_Damage* UCsManager_Damage::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_Damage* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Damage from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Damage::Initialize()
{
	// Bind Construct Resource Impl
	Manager_Event.ConstructResourceType_Impl.BindUObject(this, &UCsManager_Damage::ConstructEvent);

	// TODO: Poll config in future

	// Create Pool
	static const int32 PoolSize = 64;

	Manager_Event.CreatePool(PoolSize);

	bInitialized = true;
}

/*static*/ bool UCsManager_Damage::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Damage::CleanUp()
{
	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Damage::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Receive Damage
#pragma region

void UCsManager_Damage::Add(ICsReceiveDamage* Object)
{
	checkf(Object, TEXT("UCsManager_Damage::Add: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsManager_Damage::Add: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsManager_Damage::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsManager_Damage::Add: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveDamageMap.Add(Id, Object);
}

void UCsManager_Damage::Remove(ICsReceiveDamage* Object)
{
	checkf(Object, TEXT("UCsManager_Damage::Remove: Object is NULL."));

	UObject* O = Object->_getUObject();

	checkf(O, TEXT("UCsManager_Damage::Remove: Object is NOT a UObject."));

	UClass* Class = O->GetClass();

	checkf(Class->ImplementsInterface(UCsUniqueObject::StaticClass()), TEXT("UCsManager_Damage::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	// TODO: Need to look at script objects
	ICsUniqueObject* UniqueObject = Cast<ICsUniqueObject>(O);

	checkf(UniqueObject, TEXT("UCsManager_Damage::Remove: Object: %s with Class: %s does NOT implement interface: ICsUniqueObject."), *(O->GetName()), *(Class->GetName()));

	const FCsUniqueObjectId& Id = UniqueObject->GetId();

	ReceiveDamageMap.Remove(Id);
}

#pragma endregion Receive Damage

// Event
#pragma region

ICsDamageEvent* UCsManager_Damage::ConstructEvent()
{
	return new FCsDamageEventImpl();
}

FCsResource_DamageEvent* UCsManager_Damage::AllocateEvent()
{
	return Manager_Event.Allocate();
}

void UCsManager_Damage::ProcessDamageEvent(const ICsDamageEvent* Event)
{
	using namespace NCsManagerDamageCached;

	const FString& Context = Str::ProcessDamageEvent;

	checkf(Event, TEXT("%s: Event is NULL."), *Context);

	ICsDamageExpression* Expression = Event->GetExpression();

	checkf(Expression, TEXT("%s: Expression is NULL. No Damage Expression found for Event."), *Context);

	Local_Recievers.Reset(Local_Recievers.Max());

	// ICsDamageShape
	if (ICsDamageShape* Shape = FCsLibrary_DamageExpression::GetSafeInterfaceChecked<ICsDamageShape>(Context, Expression))
	{

	}
	// Point
	else
	{
		const FHitResult& HitResult = Event->GetHitResult();
		
		// Actor
		if (AActor* Actor = HitResult.GetActor())
		{
			// Check if Actor implements interface: ICsReceiveDamage
			UClass* Class = Actor->GetClass();
			
			if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
			{
				Local_Recievers.AddDefaulted();
				Local_Recievers.Last().SetObject(Actor);
			}
		}
		// Component
		if (UPrimitiveComponent* Component = HitResult.GetComponent())
		{
			// Check if Component implements interface: ICsReceiveDamage
			UClass* Class = Component->GetClass();

			if (Class->ImplementsInterface(UCsReceiveDamage::StaticClass()))
			{
				Local_Recievers.AddDefaulted();
				Local_Recievers.Last().SetObject(Component);
			}
		}
	}

	for (FCsReceiveDamage& Receiver : Local_Recievers)
	{
		Receiver.Damage(Event);

#if !UE_BUILD_SHIPPING
		LogEventPoint(Event);
#endif // #if !UE_BUILD_SHIPPING
		OnProcessDamageEvent_Event.Broadcast(Event);
	}
}


void UCsManager_Damage::ProcessDamageEventContainer(const FCsResource_DamageEvent* Event)
{
	using namespace NCsManagerDamageCached;

	check(Manager_Event.IsValidChecked(Str::ProcessDamageEventContainer, Event));

	const ICsDamageEvent* IEvent = Event->Get();

	ProcessDamageEvent(IEvent);

	Manager_Event.Deallocate(const_cast<FCsResource_DamageEvent*>(Event));
}

#pragma endregion Event

// Log
#pragma region

void UCsManager_Damage::LogEventPoint(const ICsDamageEvent* Event)
{
	ICsDamageExpression* Expression = Event->GetExpression();

	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogManagerDamageEvents))
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::ProcessDamageEvent:"));
		// Expression
		UE_LOG(LogCs, Warning, TEXT("- Expression: Point"));
		UE_LOG(LogCs, Warning, TEXT("-- Damage: %f"), Expression->GetDamage());
		UE_LOG(LogCs, Warning, TEXT("-- Type: %s"), Expression->GetType().ToChar());
		// Instigator
		UE_LOG(LogCs, Warning, TEXT("- Instigator: %s"), Event->GetInstigator() ? *(Event->GetInstigator()->GetName()) : TEXT("None"));
		// Causer
		UE_LOG(LogCs, Warning, TEXT("- Causer: %s"), Event->GetCauser() ? *(Event->GetCauser()->GetName()) : TEXT("None"));
		// HitResult
		const FHitResult& HitResult = Event->GetHitResult();

		UE_LOG(LogCs, Warning, TEXT("- HitResult"));
		UE_LOG(LogCs, Warning, TEXT("-- bBlockingHit: %s"), HitResult.bBlockingHit ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- bStartPenetrating"), HitResult.bStartPenetrating ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCs, Warning, TEXT("-- Time: %f"), HitResult.Time);
		UE_LOG(LogCs, Warning, TEXT("-- Location: %s"), *(HitResult.Location.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- ImpactPoint: %s"), *(HitResult.ImpactPoint.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- Normal: %s"), *(HitResult.Normal.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- ImpactNormal: %s"), *(HitResult.ImpactNormal.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- TraceStart: %s"), *(HitResult.TraceStart.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- TraceEnd: %s"), *(HitResult.TraceEnd.ToString()));
		UE_LOG(LogCs, Warning, TEXT("-- PenetrationDepth: %f"), HitResult.PenetrationDepth);
		UE_LOG(LogCs, Warning, TEXT("-- Item: %d"), HitResult.Item);
		UE_LOG(LogCs, Warning, TEXT("-- PhysMaterial: %s"), HitResult.PhysMaterial.IsValid() ? *(HitResult.PhysMaterial->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- Actor: %s"), HitResult.Actor.IsValid() ? *(HitResult.Actor->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- Component: %s"), HitResult.Component.IsValid() ? *(HitResult.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- BoneName: %s"), HitResult.BoneName.IsValid() ? *(HitResult.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCs, Warning, TEXT("-- FaceIndex: %d"), HitResult.FaceIndex);
	}
}

#pragma endregion Log