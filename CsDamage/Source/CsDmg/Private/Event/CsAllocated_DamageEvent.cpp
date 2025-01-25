// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/CsAllocated_DamageEvent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h" // TODO: Fix: Potentially put resources into separate file?

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NEvent, Allocated)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NEvent::FAllocated, Set);
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NEvent::FAllocated, Copy);
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NEvent::FAllocated, Reset);
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsDamage
{
	namespace NEvent
	{
		using ResourceType = NCsDamage::NEvent::FResource;
		using EventType =  NCsDamage::NEvent::IEvent;
			
		void FAllocated::Set(UObject* InRoot, ResourceType* InContainer)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Set);

			CS_IS_PENDING_KILL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(InContainer)

			checkf(!Container, TEXT("NCsDamage::NEvent::FAllocated::Set: Container is already SET."));

			Root	  = InRoot;
			Container = InContainer;
			Event	  = Container->Get();
		}

		void FAllocated::Copy(UObject* InRoot, const EventType* From)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

			CS_IS_PTR_NULL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = InRoot;
			Container = CsDamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From);
			Event	  = Container->Get();
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

			CS_IS_PTR_NULL_CHECKED(From.Root)

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				Root	  = From.Root;
				Container = CsDamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From.Container->Get());
				Event	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Reset);

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(Root)

				CsDamageManagerLibrary::DeallocateEventChecked(Context, Root, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Event	  = nullptr;
		}
	}
}