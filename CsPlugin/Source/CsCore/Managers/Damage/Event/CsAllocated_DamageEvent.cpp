// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsAllocated_DamageEvent.h"
#include "CsCore.h"

// Managers
#include "Managers/Damage/CsManager_Damage.h"

// Cached
#pragma region

namespace NCsAllocatedDamageEventCached
{
	namespace Str
	{
		const FString CopyFrom = TEXT("FCsAllocated_DamageEvent::CopyFrom");
		const FString Reset = TEXT("FCsAllocated_DamageEvent::Reset");
	}
}

#pragma endregion Cached

void FCsAllocated_DamageEvent::CopyFrom(UObject* InRoot, const ICsDamageEvent* From)
{
	using namespace NCsAllocatedDamageEventCached;

	const FString& Context = Str::CopyFrom;

	checkf(InRoot, TEXT("%s: InRoot is NULL."), *Context);

	checkf(From, TEXT("%s: From is NULL."), *Context);

	Root	  = InRoot;
	Container = UCsManager_Damage::Get(Root)->CreateCopyOfEvent(Context, From);
	Event	  = Container->Get();
}

void FCsAllocated_DamageEvent::CopyFrom(const FCsAllocated_DamageEvent* From)
{
	using namespace NCsAllocatedDamageEventCached;

	const FString& Context = Str::CopyFrom;

	checkf(From->Root, TEXT("&s: From->Root is NULL."), *Context);

	checkf(Container, TEXT("%s: Container is already SET."), *Context);

	if (From->Container)
	{
		Root	  = From->Root;
		Container = UCsManager_Damage::Get(Root)->CreateCopyOfEvent(Context, From->Container);
		Event	  = Container->Get();
	}
}

void FCsAllocated_DamageEvent::Reset()
{
	using namespace NCsAllocatedDamageEventCached;

	const FString& Context = Str::Reset;

	if (Container)
	{
		checkf(Root, TEXT("%s: Root is NULL."), *Context);

		UCsManager_Damage::Get(Root)->DeallocateEvent(Context, Container);
	}

	Root	  = nullptr;
	Container = nullptr;
	Event	  = nullptr;
}