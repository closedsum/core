// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "CsCore.h"
#include "Common/CsCommon.h"
#include "Managers/WidgetActor/CsWidgetActor.h"
#include "UI/CsUserWidget.h"
#include "Game/CsGameState.h"

// static initializations
TWeakObjectPtr<UObject> ACsManager_WidgetActor::MyOwner;

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

void ACsManager_WidgetActor::SetWidgetActorType(TCsWidgetActorTypeToString InWidgetActorTypeToString)
{
	WidgetActorTypeToString = InWidgetActorTypeToString;
}

void ACsManager_WidgetActor::Shutdown()
{
	Super::Shutdown();

	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveWidgetActors.Reset();
}

void ACsManager_WidgetActor::Destroyed()
{
	const int32 Count = Pool.Num();

	for (int32 I = 0; I < Count; I++)
	{
		if (Pool[I] && !Pool[I]->IsPendingKill())
			Pool[I]->Destroy(true);
	}
	Pool.Reset();
	Pools.Reset();
	PoolSizes.Reset();
	PoolIndices.Reset();
	ActiveWidgetActors.Reset();

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

	for (int32 I = 0; I < Size; I++)
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

void ACsManager_WidgetActor::OnTick(const float &DeltaSeconds)
{
	/*
	const uint8 Count = ActiveWidgetActors.Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsWidgetActor* Widget = ActiveWidgetActors[I];

		if (GetWorld()->TimeSeconds - Sound->Cache.Time > Sound->Cache.Duration)
		{
			Widget->DeAllocate();
			ActiveWidgetActors.RemoveAt(I);
		}
	}
	*/
}

int32 ACsManager_WidgetActor::GetActivePoolSize(const uint8 &Type)
{
	TArray<ACsWidgetActor*>* ActorsPtr = ActiveWidgetActors.Find((TCsWidgetActorType)Type);

	if (!ActorsPtr)
		return CS_EMPTY;
	return ActorsPtr->Num();
}

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

	TArray<ACsWidgetActor*>* WidgetActors = ActiveWidgetActors.Find(ClassType);

	if (!WidgetActors)
	{
		UE_LOG(LogCs, Warning, TEXT("ACsManager_WidgetActor::DeAllocate: WidgetActor of Type: %s at Index: %d is already deallocated."), *((*WidgetActorTypeToString)(ClassType)), Index);
		return;
	}

	const uint8 Count = WidgetActors->Num();

	for (int32 I = Count - 1; I >= 0; I--)
	{
		ACsWidgetActor* Widget = (*WidgetActors)[I];

		if (Widget->PoolIndex == Index)
		{
			Widget->DeAllocate();
			WidgetActors->RemoveAt(I);
			return;
		}
	}
	UE_LOG(LogCs, Warning, TEXT("ACsManager_WidgetActor::DeAllocate: WidgetActor of Type: %s at Index: %d is already deallocated."), *((*WidgetActorTypeToString)(ClassType)), Index);
}

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, UCsUserWidget* InWidget, UObject* InOwner, UObject* Parent)
{
	ACsWidgetActor* Widget = Allocate(ClassType);

	InWidget->SetIsEnabled(true);
	InWidget->SetVisibility(ESlateVisibility::Visible);
	Widget->Allocate(GetActivePoolSize((uint8)ClassType), InWidget, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent);

	if (TArray<ACsWidgetActor*>* WidgetActors = ActiveWidgetActors.Find(ClassType))
	{
		WidgetActors->Add(Widget);
	}
	else
	{
		TArray<ACsWidgetActor*> Actors;
		Actors.Add(Widget);
		ActiveWidgetActors.Add(ClassType, Actors);
	}
	return Widget;
}

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, UCsUserWidget* InWidget, UObject* InOwner)
{
	return Display(ClassType, InWidget, InOwner, nullptr);
}

ACsWidgetActor* ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, UCsUserWidget* InWidget)
{
	return Display(ClassType, InWidget, nullptr, nullptr);
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, ACsWidgetActor* OutWidgetActor, UCsUserWidget* InWidget, UObject* InOwner, UObject* Parent, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	OutWidgetActor = Allocate(ClassType);

	InWidget->SetIsEnabled(true);
	InWidget->SetVisibility(ESlateVisibility::Visible);
	OutWidgetActor->Allocate<T>(GetActivePoolSize((uint8)ClassType), InWidget, GetWorld()->TimeSeconds, GetWorld()->RealTimeSeconds, 0, InOwner, Parent, InObject, OnDeAllocate);

	if (TArray<ACsWidgetActor*>* WidgetActors = ActiveWidgetActors.Find(ClassType))
	{
		WidgetActors->Add(Widget);
	}
	else
	{
		TArray<ACsWidgetActor*> Actors;
		Actors.Add(Widget);
		ActiveWidgetActors.Add(ClassType, Actors);
	}
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, ACsWidgetActor* OutWidgetActor, UCsUserWidget* InWidget, UObject* InOwner, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Display<T>(ClassType, OutWidgetActor, InWidget, nullptr, InOwner, InObject, OnDeAllocate);
}

template<typename T>
void ACsManager_WidgetActor::Display(const TCsWidgetActorType &ClassType, ACsWidgetActor* OutWidgetActor, UCsUserWidget* InWidget, T* InObject, void (T::*OnDeAllocate)(const uint16&, const uint16&, const uint8&))
{
	Display<T>(ClassType, OutWidgetActor, InWidget, nullptr, nullptr, InObject, OnDeAllocate);
}