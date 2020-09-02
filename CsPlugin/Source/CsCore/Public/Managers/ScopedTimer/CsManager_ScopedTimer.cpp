// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"
#include "CsCore.h"

// CVars
#include "CsCVars.h"

FCsManager_ScopedTimer::FCsManager_ScopedTimer() :
	Internal(),
	GroupTimers()
{
	// Set Index values for Resources
	for (FCsResource_ScopedTimer* Container : Internal.GetPool())
	{
		FCsScopedTimer* Resource = Container->Get();
		Resource->Handle.Index   = Container->GetIndex();
	}
	// Initialize GroupTimers
	{
		const int32& Count = EMCsScopedGroup::Get().Num();

		GroupTimers.Reserve(Count);

		for (int32 I = 0; I < Count; ++I)
		{
			GroupTimers.AddDefaulted();
			GroupTimers.Last().Init(&(EMCsScopedGroup::Get().GetEnumAt(I)));
		}
	}
}

FCsManager_ScopedTimer::~FCsManager_ScopedTimer()
{

}

/*static*/ FCsManager_ScopedTimer& FCsManager_ScopedTimer::Get()
{
	static FCsManager_ScopedTimer Instance;
	return Instance;
}

void FCsManager_ScopedTimer::Update(const FCsDeltaTime& DeltaTime)
{
	// Scope Timers
	TCsDoubleLinkedList<FCsResource_ScopedTimer*>* Current = Internal.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_ScopedTimer*>* Next	   = Current;

	while (Next)
	{
		Current							   = Next;
		FCsResource_ScopedTimer* Container = **Current;
		Next							   = Current->GetNextLink();

		FCsScopedTimer* R = Container->Get();

		if (R->IsDirty())
		{
			R->Log();
			R->ClearDirty();

			// Update Group Timer
			const FECsScopedGroup& Group = R->GetGroup();

			GroupTimers[Group.GetValue()].AddTime(*R);
		}
	}

	// Group Timers
	for (FCsScopedGroupTimer& G : GroupTimers)
	{
		if (G.IsDirty())
		{
			G.Resolve();
			G.Log();
			G.ClearDirty();
		}
	}
}

const FCsScopedTimerHandle& FCsManager_ScopedTimer::GetHandle(const FString* Name, const FECsScopedGroup* Group, const FECsCVarLog* CVar)
{
	checkf(Name, TEXT("FCsManager_ScopedTimer::GetHandle: Name is NULL."));

	checkf(!Name->IsEmpty(), TEXT("FCsManager_ScopedTimer::GetHandle: Name is Empty."));

	checkf(Group, TEXT("FCsManager_ScopedTimer::GetHandle: Group is NULL."));

	checkf(CVar, TEXT("FCsManager_ScopedTimer::GetHandle: CVar is NULL."));

	FCsScopedTimer* ScopedTimer = Internal.AllocateResource();

	ScopedTimer->Init(Name, Group, CVar);

	return ScopedTimer->Handle;
}

void FCsManager_ScopedTimer::ClearHandle(const FCsScopedTimerHandle& Handle)
{
	if (!Handle.IsValid())
	{
		UE_LOG(LogCs, Warning, TEXT("FCsManager_ScopedTimer::ClearHandle: Handle is NOT Valid."));
		return;
	}

	if (Handle.GetIndex() >= Internal.GetPoolSize())
	{
		UE_LOG(LogCs, Warning, TEXT("FCsManager_ScopedTimer::ClearHandle: Handle's Index >= Internal.GetPoolSize() (%d >= %d)."), Handle.GetIndex(), Internal.GetPoolSize());
		return;
	}

	FCsResource_ScopedTimer* Resource = Internal.GetAt(Handle.GetIndex());

	checkf(Resource, TEXT("FCsManager_ScopedTimer::ClearHandle: Resource is NULL."));

	FCsScopedTimer* ScopedTimer = Resource->Get();

	checkf(ScopedTimer, TEXT("FCsManager_ScopedTimer::ClearHandle: ScopedTimer is NULL."));

	if (Handle != ScopedTimer->Handle)
	{
		UE_LOG(LogCs, Warning, TEXT("FCsManager_ScopedTimer::ClearHandle: ScopedTimer with Index: %d does NOT match Handle."), Handle.Index);
		return;
	}

	Internal.Deallocate(Resource);
}

void FCsManager_ScopedTimer::UpdateHandle(FCsScopedTimerHandle& Handle, double Time)
{
	checkf(Handle.IsValid(), TEXT("FCsManager_ScopedTimer::UpdateHandle: Handle is NOT Valid."));

	FCsScopedTimer* ScopedTimer = Internal.GetResourceAt(Handle.GetIndex());

	checkf(ScopedTimer, TEXT("FCsManager_ScopedTimer::UpdateHandle: ScopedTimer is NULL."));

	ScopedTimer->SetTime(Time);
	ScopedTimer->MarkDirty();
}