// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsAllocated_DamageEvent.h"
#include "CsCore.h"

// Managers
#include "Managers/Damage/CsManager_Damage.h"

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NAllocatedCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, CopyFrom);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Reset);
			}
		}

		void FAllocated::Set(UObject* InRoot, FCsResource_DamageEvent* InContainer)
		{
			checkf(InRoot, TEXT("NCsDamage::NEvent::FAllocated::Set: InRoot is NULL."));

			checkf(InContainer, TEXT("NCsDamage::NEvent::FAllocated::Set: From is NULL."));

			checkf(!Container, TEXT("NCsDamage::NEvent::FAllocated::Set: Container is already SET."));

			Root	  = InRoot;
			Container = InContainer;
			Event	  = Container->Get();
		}

		void FAllocated::CopyFrom(UObject* InRoot, const IEvent* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			checkf(InRoot, TEXT("%s: InRoot is NULL."), *Context);

			checkf(From, TEXT("%s: From is NULL."), *Context);

			Root	  = InRoot;
			Container = UCsManager_Damage::Get(Root)->CreateCopyOfEvent(Context, From);
			Event	  = Container->Get();
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			checkf(From->Root, TEXT("%s: From->Root is NULL."), *Context);

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->Container)
			{
				Root	  = From->Root;
				Container = UCsManager_Damage::Get(Root)->CreateCopyOfEvent(Context, From->Container);
				Event	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			using namespace NAllocatedCached;

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
	}
}