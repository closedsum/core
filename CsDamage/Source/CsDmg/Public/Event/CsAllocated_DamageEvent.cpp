// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/CsAllocated_DamageEvent.h"
#include "CsDmg.h"

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FAllocated, Reset);
				}
			}
		}

		void FAllocated::Set(UObject* InRoot, FResource* InContainer)
		{
			checkf(InRoot, TEXT("NCsDamage::NEvent::FAllocated::Set: InRoot is NULL."));

			checkf(InContainer, TEXT("NCsDamage::NEvent::FAllocated::Set: From is NULL."));

			checkf(!Container, TEXT("NCsDamage::NEvent::FAllocated::Set: Container is already SET."));

			Root	  = InRoot;
			Container = InContainer;
			Event	  = Container->Get();
		}

		void FAllocated::Copy(UObject* InRoot, const IEvent* From)
		{
			using namespace NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From);
			Event	  = Container->Get();
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			using namespace NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From.Root)

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				Root	  = From.Root;
				Container = DamageManagerLibrary::CreateCopyOfEventChecked(Context, Root, From.Container->Get());
				Event	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			using namespace NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(Root)

				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				DamageManagerLibrary::DeallocateEventChecked(Context, Root, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Event	  = nullptr;
		}
	}
}