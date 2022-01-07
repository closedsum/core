// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "CsAllocated_StatusEffect.h"
#include "CsSe.h"

// Library
#include "Coordinators/StatusEffect/CsLibrary_Coordinator_StatusEffect.h"
#include "Library/CsLibrary_Valid.h"
// StatusEffect
#include "CsResource_StatusEffect.h"

namespace NCsStatusEffect 
{
	namespace NAllocated
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::FAllocated, CopyFrom);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::FAllocated, Reset);
			}
		}
	}

	FAllocated::~FAllocated()
	{
		Reset();
	}

	UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

	void FAllocated::CopyFrom(UObject* InRoot, const StatusEffectType* From)
	{
		using namespace NCsStatusEffect::NAllocated::NCached;

		const FString& Context = Str::CopyFrom;

		CS_IS_PTR_NULL_CHECKED(InRoot)

		CS_IS_PTR_NULL_CHECKED(From)

		typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;
		/*
		Root	  = InRoot;
		Container = SeCoordinatorLibrary::CreateCopyOfModifierChecked(Context, InRoot, From);
		Modifier  = Container->Get();
		Type	  = SeCoordinatorLibrary::GetModifierTypeChecked(Context, InRoot, Modifier);
		*/
	}

	void FAllocated::CopyFrom(const FAllocated* From)
	{
		using namespace NCsStatusEffect::NAllocated::NCached;

		const FString& Context = Str::CopyFrom;

		CS_IS_PTR_NULL_CHECKED(From->GetRoot())

		checkf(!Container, TEXT("%s: Container is already SET."), *Context);

		if (From->Container)
		{
			typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;
			/*
			Root	  = From->GetRoot();
			Container = SeCoordinatorLibrary::CreateCopyOfModifierChecked(Context, GetRoot(), From->Container);
			Modifier  = Container->Get();
			Type	  = SeCoordinatorLibrary::GetModifierTypeChecked(Context, GetRoot(), Modifier);
			*/
		}
	}

	void FAllocated::Reset()
	{
		using namespace NCsStatusEffect::NAllocated::NCached;

		const FString& Context = Str::Reset;

		if (Container)
		{
			CS_IS_PTR_NULL_CHECKED(GetRoot())

			typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;

			//SeCoordinatorLibrary::DeallocateModifierChecked(Context, GetRoot(), Type, Container);
		}
		Clear();
	}
}