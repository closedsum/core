// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/CsAllocated_DamageModifier.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Modifier/CsResource_DamageModifier.h"

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NModifier, Allocated)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::FAllocated, Copy)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::FAllocated, Transfer)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NModifier::FAllocated, Reset)
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsDamage 
{
	namespace NModifier
	{
		using DamageModifierLibrary = NCsDamage::NManager::NModifier::FLibrary;

		FAllocated::~FAllocated()
		{
			Reset();
		}

		using ModifierType = NCsDamage::NModifier::IModifier;

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(const UObject* WorldContext, const ModifierType* From)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = CsDamageManagerLibrary::GetContextRootChecked(Context, WorldContext);
			Container = DamageModifierLibrary::CopyChecked(Context, WorldContext, From);
			Modifier  = Container->Get();
			Type	  = DamageModifierLibrary::GetTypeChecked(Context, WorldContext, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

			CS_EDITOR_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				Root	  = From.GetRoot();
				Container = DamageModifierLibrary::CopyChecked(Context, GetRoot(), From.Container);
				Modifier  = Container->Get();
				Type	  = From.Type;
			}
			else
			{
				Modifier = From.Modifier;
			}
		}

		void FAllocated::Transfer(FAllocated& To)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Transfer);

			checkf(!To.Container, TEXT("%s: Container is already SET."), *Context);

			if (Container)
			{
				CS_EDITOR_IS_PTR_NULL_CHECKED(GetRoot())

				To.Root		  = GetRoot();
				To.Container  = Container;
				To.Modifier   = Modifier;
				To.Type		  = Type;
			}
			else
			{
				To.Modifier = Modifier;
			}
			Clear();
		}

		void FAllocated::Reset()
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(Reset);

			if (Container)
			{
				CS_EDITOR_IS_PTR_NULL_CHECKED(GetRoot())

				DamageModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}
	}
}