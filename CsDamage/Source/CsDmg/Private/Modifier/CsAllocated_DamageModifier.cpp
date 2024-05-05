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

namespace NCsDamage 
{
	namespace NModifier
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FAllocated, Transfer);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FAllocated, Reset);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsDamage::NModifier::NAllocated::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsDamage::NModifier::NAllocated::NCached; \
			const FString& Context = Str::__FunctionName
		#define DamageManagerLibrary NCsDamage::NManager::FLibrary
		#define DamageModifierLibrary NCsDamage::NManager::NModifier::FLibrary

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(const UObject* WorldContext, const IModifier* From)
		{
			SET_CONTEXT(Copy);

			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = DamageManagerLibrary::GetContextRootChecked(Context, WorldContext);
			Container = DamageModifierLibrary::CopyChecked(Context, WorldContext, From);
			Modifier  = Container->Get();
			Type	  = DamageModifierLibrary::GetTypeChecked(Context, WorldContext, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			SET_CONTEXT(Copy);

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
			SET_CONTEXT(Transfer);

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
			SET_CONTEXT(Reset);

			if (Container)
			{
				CS_EDITOR_IS_PTR_NULL_CHECKED(GetRoot())

				DamageModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef DamageManagerLibrary
		#undef DamageModifierLibrary
	}
}