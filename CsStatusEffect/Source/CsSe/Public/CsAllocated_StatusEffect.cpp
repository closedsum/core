// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "CsAllocated_StatusEffect.h"

// Types
#include "CsMacro_Misc.h"
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
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::FAllocated, Copy);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::FAllocated, Reset);
			}
		}
	}

	FAllocated::~FAllocated()
	{
		Reset();
	}

	UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

	void FAllocated::Copy(UObject* InRoot, const StatusEffectType* From)
	{
		using namespace NCsStatusEffect::NAllocated::NCached;

		const FString& Context = Str::Copy;

		CS_IS_PTR_NULL_CHECKED(InRoot)

		CS_IS_PTR_NULL_CHECKED(From)

		typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;
		
		Root		 = InRoot;
		Container	 = SeCoordinatorLibrary::CreateCopyOfStatusEffectChecked(Context, InRoot, From);
		StatusEffect = Container->Get();
		ImplType	 = SeCoordinatorLibrary::GetStatusEffectImplTypeChecked(Context, InRoot, StatusEffect);
	}

	void FAllocated::Copy(const FAllocated& From)
	{
		using namespace NCsStatusEffect::NAllocated::NCached;

		const FString& Context = Str::Copy;

		CS_IS_PTR_NULL_CHECKED(From.GetRoot())

		checkf(!Container, TEXT("%s: Container is already SET."), *Context);

		if (From.Container)
		{
			typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;
			
			Root		 = From.GetRoot();
			Container	 = SeCoordinatorLibrary::CreateCopyOfStatusEffectChecked(Context, GetRoot(), From.Container);
			StatusEffect = Container->Get();
			Type		 = From.Type;
			ImplType	 = From.ImplType;
		}
		else 
		{
			StatusEffect = From.StatusEffect;
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

			SeCoordinatorLibrary::DeallocateStatusEffectChecked(Context, GetRoot(), ImplType, Container);
		}
		Clear();
	}
}