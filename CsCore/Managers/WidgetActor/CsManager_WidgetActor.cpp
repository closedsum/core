// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Managers/WidgetActor/CsWidgetActor.h"

// UI
#include "UI/CsUserWidget.h"
#include "UI/Simple/CsSimpleWidget.h"

#include "Game/CsGameState.h"

// static initializations
TWeakObjectPtr<UObject> ACsManager_WidgetActor::MyOwner;

// Cache
#pragma region

namespace ECsManagerWidgetActorCachedString
{
	namespace Str
	{
		const FString OnTick = TEXT("ACsManager_WidgetActor::OnTick");
		const FString DeAllocate = TEXT("ACsManager_WidgetActor::DeAllocate");
		const FString DeAllocateAll = TEXT("ACsManager_WidgetActor::DeAllocateAll");
		const FString Display = TEXT("ACsManager_WidgetActor::Display");
	}
}

#pragma endregion Cache

ACsManager_WidgetActor::ACsManager_WidgetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetActorTypeToString = nullptr;

	PoolSize = 1;
}

/*static*/ UObject* ACsManager_WidgetActor::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void ACsManager_WidgetActor::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ ACsManager_WidgetActor* ACsManager_WidgetActor::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(InWorld))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_WidgetActor;
	}
	return nullptr;
}

void ACsManager_WidgetActor::SetWidgetActorType(const TCsWidgetActorType &InWidgetActorType_MAX, TCsWidgetActorTypeToString InWidgetActorTypeToString)
{
	WidgetActorType_MAX		= InWidgetActorType_MAX;
	WIDGET_ACTOR_TYPE_MAX   = (uint8)InWidgetActorType_MAX;
	WidgetActorTypeToString = InWidgetActorTypeToString;
}

void ACsManager_WidgetActor::Clear()
{
	Super::Clear();

	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveWidgetActors.Reset();
}

void ACsManager_WidgetActor::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Clear();
}

void ACsManager_WidgetActor::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

void ACsManager_WidgetActor::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size)
{
	const TCsWidgetActorType ClassType = (TCsWidgetActorType)Type;

	PoolSizes.Add(ClassType, Size);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	PoolIndices.Add(ClassType, 0);

	TArray<ACsWidgetActor*> WidgetPool;

	for (int32 I = 0; I < Size; ++I)
	{
		ACsWidgetActor* Widget = GetWorld()->SpawnActor<ACsWidgetActor>(ObjectClass, SpawnInfo);
		Widget->SetReplicates(false);
		Widget->Role = ROLE_None;
		GetWorld()->RemoveNetworkActor(Widget);
		Widget->Init(I, ClassType);
		Pool.Add(Widget);
		WidgetPool.Add(Widget);
	}
	Pools.Add(ClassType, WidgetPool);
}

void ACsManager_WidgetActor::AddToActivePool(UObject* InObject, const uint8& Type)
{
	checkf(InObject, TEXT("ACsManager_WidgetActor::AddToActivePool: InObject is NULL."));

	ACsWidgetActor* Actor = Cast<ACsWidgetActor>(InObject);

	checkf(Actor, TEXT("ACsManager_WidgetActor::AddToActivePool: InObject (%s) is NOT type ACsInteraciveActor."), *InObject->GetClass()->GetName());

	const TCsWidgetActorType ClassType = (TCsWidgetActorType)Type;

	Actor->Cache.IsAllocated = true;

	if (TArray<ACsWidgetActor*>* ActorsPtr = ActiveWidgetActors.Find(ClassType))
	{
		ActorsPtr->Add(Actor);
	}
	else
	{
		TArray<ACsWidgetActor*> Actors;
		Actors.Add(Actor);
		ActiveWidgetActors.Add(ClassType, Actors);
	}
	//Actor->Cache.OnDeAllocate_Event.AddUObject(this, &ACsManager_WidgetActor::OnDeAllocate);
}

void ACsManager_WidgetActor::OnTick(const float &DeltaSeconds)
{
	const int32 PoolCount = ActiveWidgetActors.Num();

	for (int32 I = PoolCount - 1; I >= 0; --I)
	{
		const TCsWidgetActorType Type	   = (TCsWidgetActorType)I;
		TArray<ACsWidgetActor*>* ActorsPtr = ActiveWidgetActors.Find(Type);

		const int32 ActorCount = ActorsPtr->Num();
		int32 EarliestIndex    = ActorCount;

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			ACsWidgetActor* Actor = (*ActorsPtr)[J];

			// Check if InteractiveActor was DeAllocated NOT in a normal way (i.e. Out of Bounds)

			if (!Actor->Cache.IsAllocated)
			{
				UE_LOG(LogCs, Warning, TEXT("ACsManager_WidgetActor::OnTick: WidgetActor: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Actor->GetName()), Actor->Cache.Index);

				LogTransaction(ECsManagerWidgetActorCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Actor);

				ActorsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
				continue;
			}

			if (!Actor->Cache.bLifeTime)
				continue;

			if (GetWorld()->GetTimeSeconds() - Actor->Cache.Time > Actor->Cache.LifeTime)
			{
				LogTransaction(ECsManagerWidgetActorCachedString::Str::OnTick, ECsPoolTransaction::Deallocate, Actor);

				Actor->DeAllocate();
				ActorsPtr->RemoveAt(J);

				if (J < EarliestIndex)
					EarliestIndex = J;
			}
		}

		// Update ActiveIndex
		if (EarliestIndex != ActorCount)
		{
			const uint16 Max = ActorsPtr->Num();

			for (uint16 J = EarliestIndex; J < Max; J++)
			{
				ACsWidgetActor* Actor = (*ActorsPtr)[J];
				Actor->Cache.SetActiveIndex(J);
			}
		}
	}
}

int32 ACsManager_WidgetActor::GetActivePoolSize(const uint8 &Type)
{
	TArray<ACsWidgetActor*>* ActorsPtr = ActiveWidgetActors.Find((TCsWidgetActorType)Type);

	if (!ActorsPtr)
		return CS_EMPTY;
	return ActorsPtr->Num();
}

bool ACsManager_WidgetActor::IsExhausted(const uint8 &Type)
{
	const TCsWidgetActorType ClassType = (TCsWidgetActorType)Type;

	TArray<ACsWidgetActor*>* PoolPtr = Pools.Find(ClassType);

	if (!PoolPtr)
		return true;

	return GetActivePoolSize(Type) >= PoolPtr->Num();
}

void ACsManager_WidgetActor::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject)
{
	if (CsCVarLogManagerWidgetActorTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		ACsWidgetActor* Actor = Cast<ACsWidgetActor>(InObject);

		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString ActorName		= Actor->GetName();
		const FString TypeAsString	= (*WidgetActorTypeToString)((TCsWidgetActorType)Actor->Cache.Type);
		const float CurrentTime		= GetWorld()->GetTimeSeconds();
		const UObject* ActorOwner	= Actor->Cache.GetOwner();
		const FString OwnerName		= ActorOwner ? ActorOwner->GetName() : ECsCachedString::Str::None;
		const UObject* Parent		= Actor->Cache.GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : ECsCachedString::Str::None;

		if (ActorOwner && Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s InteractiveActor: %s of Type: %s at %f for %s attached to %s."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime, *OwnerName, *ParentName);
		}
		else
		if (ActorOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s WidgetActor: %s of Type: %s at %f for %s."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime, *OwnerName);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s WidgetActor: %s of Type: %s at %f attached to %s."), *TransactionAsString, *FunctionName, *ActorName, *TypeAsString, CurrentTime, *ParentName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s WidgetActor: %s of Type: %s at %f."), *FunctionName, *TransactionAsString, *ActorName, *TypeAsString, CurrentTime);
		}
	}
}

// Allocate / DeAllocate
#pragma region

ACsWidgetActor* ACsManager_WidgetActor::Allocate(const TCsWidgetActorType &ClassType)
{
	TArray<ACsWidgetActor*>* WidgetPool = Pools.Find(ClassType);
	const uint8 Size					= *(PoolSizes.Find(ClassType));

	for (uint8 I = 0; I < Size; ++I)
	{
		uint8* PoolIndexPtr    = (PoolIndices.Find(ClassType));
		*PoolIndexPtr	       = (*PoolIndexPtr + I) % Size;
		ACsWidgetActor* Widget = (*WidgetPool)[*PoolIndexPtr];

		if (!Widget->Cache.IsAllocated)
		{
			Widget->Cache.IsAllocated = true;
			return Widget;
		}
	}
	checkf(0, TEXT("ACsManager_WidgetActor::Allocate: Pool: %s is exhausted"), *(*WidgetActorTypeToString(ClassType)));
	return nullptr;
}

void ACsManager_WidgetActor::DeAllocate(const uint8 &Type, const int32 &Index)
{
	const TCsWidgetActorType ClassType = (TCsWidgetActorType)Type;

	TArray<ACsWidgetActor*>* Actors = ActiveWidgetActors.Find(ClassType);

	if (!Actors)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_WidgetActor::DeAllocate: WidgetActor of Type: %s at PoolIndex: %d is already deallocated."), *((*WidgetActorTypeToString)(ClassType)), Index);
		return;
	}

	const uint8 Count = Actors->Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		ACsWidgetActor* Actor = (*Actors)[I];

		// Update ActiveIndex
		if (I > CS_FIRST)
		{
			Actor->Cache.DecrementActiveIndex();
		}

		if (Actor->Cache.Index == Index)
		{
			LogTransaction(ECsManagerWidgetActorCachedString::Str::DeAllocate, ECsPoolTransaction::Deallocate, Actor);

			Actor->DeAllocate();
			Actors->RemoveAt(I);

#if WITH_EDITOR
			OnDeAllocateEX_ScriptEvent.Broadcast(Index, I, Actor->Cache.Type);
#endif // #if WITH_EDITOR
			OnDeAllocateEX_Event.Broadcast(Index, I, (TCsWidgetActorType)Actor->Cache.Type);
			return;
		}
	}

	// Correct on Cache "Miss"
	for (int32 I = 1; I < Count; ++I)
	{
		ACsWidgetActor* Actor = (*Actors)[I];
		// Reset ActiveIndex
		Actor->Cache.SetActiveIndex(I);
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_WidgetActor::DeAllocate: WidgetActor of Type: %s at PoolIndex: %d is already deallocated."), *((*WidgetActorTypeToString)(ClassType)), Index);
}

void ACsManager_WidgetActor::DeAllocateAll()
{
	const uint8 Count = (uint8)WidgetActorType_MAX;

	for (uint8 I = 0; I < WIDGET_ACTOR_TYPE_MAX; ++I)
	{
		const TCsWidgetActorType Type = (TCsWidgetActorType)I;

		TArray<ACsWidgetActor*>* Actors = ActiveWidgetActors.Find(Type);

		if (!Actors)
			continue;

		const int32 ActorCount = Actors->Num();

		for (int32 J = ActorCount - 1; J >= 0; --J)
		{
			LogTransaction(ECsManagerWidgetActorCachedString::Str::DeAllocateAll, ECsPoolTransaction::Deallocate, (*Actors)[J]);

			(*Actors)[J]->DeAllocate();
			Actors->RemoveAt(J);
		}
	}
}

#pragma endregion Allocate / DeAllocate

// Display
#pragma region

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent)
{
	ACsWidgetActor* Widget = Allocate(Type);

	Widget->Allocate(GetActivePoolSize((uint8)Type), Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, Parent);
	
	LogTransaction(ECsManagerWidgetActorCachedString::Str::Display, ECsPoolTransaction::Allocate, Widget);

	AddToActivePool(Widget, (uint8)Type);
	return Widget;
}

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload, UObject* InOwner)
{
	return Display(Type, Payload, InOwner, nullptr);
}

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, FCsWidgetActorPayload* Payload)
{
	return Display(Type, Payload, nullptr, nullptr);
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutWidgetActor = Allocate(Type);

	OutWidgetActor->Allocate<T>(GetActivePoolSize((uint8)Type), Payload, GetWorld()->GetTimeSeconds(), GetWorld()->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(GetWorld()), InOwner, Parent, InObject, OnDeAllocate);

	LogTransaction(ECsManagerWidgetActorCachedString::Str::Display, ECsPoolTransaction::Allocate, OutWidgetActor);

	AddToActivePool(Widget, (uint8)Type);
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Display<T>(Type, OutWidgetActor, Payload, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &Type, ACsWidgetActor* OutWidgetActor, FCsWidgetActorPayload* Payload, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Display<T>(Type, OutWidgetActor, Payload, nullptr, nullptr, InObject, OnDeAllocate);
}

#pragma endregion Display