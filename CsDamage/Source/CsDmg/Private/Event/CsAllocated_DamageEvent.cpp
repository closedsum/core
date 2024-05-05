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

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Set);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Reset);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsDamage::NEvent::NAllocated::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsDamage::NEvent::NAllocated::NCached; \
			const FString& Context = Str::__FunctionName
		#define DamageManagerLibrary NCsDamage::NManager::FLibrary

		void FAllocated::Set(UObject* InRoot, FResource* InContainer)
		{
			SET_CONTEXT(Set);

			CS_IS_PENDING_KILL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(InContainer)

			checkf(!Container, TEXT("NCsDamage::NEvent::FAllocated::Set: Container is already SET."));

			Root	  = InRoot;
			Container = InContainer;
			Event	  = Container->Get();
		}

		void FAllocated::Copy(UObject* InRoot, const IEvent* From)
		{
			SET_CONTEXT(Copy);

			CS_IS_PTR_NULL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From);
			Event	  = Container->Get();
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			SET_CONTEXT(Copy);

			CS_IS_PTR_NULL_CHECKED(From.Root)

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				Root	  = From.Root;
				Container = DamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From.Container->Get());
				Event	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			SET_CONTEXT(Reset);

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(Root)

				DamageManagerLibrary::DeallocateEventChecked(Context, Root, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Event	  = nullptr;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef DamageManagerLibrary
	}
}