// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsAllocated_DamageModifier.h"
#include "CsDmg.h"

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

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(const UObject* WorldContext, const IModifier* From)
		{
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NManager::FLibrary DmgManagerLibrary;
			typedef NCsDamage::NManager::NModifier::FLibrary ModifierLibrary;

			Root	  = DmgManagerLibrary::GetContextRootChecked(Context, WorldContext);
			Container = ModifierLibrary::CopyChecked(Context, WorldContext, From);
			Modifier  = Container->Get();
			Type	  = ModifierLibrary::GetTypeChecked(Context, WorldContext, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_EDITOR_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				typedef NCsDamage::NManager::NModifier::FLibrary ModifierLibrary;

				Root	  = From.GetRoot();
				Container = ModifierLibrary::CopyChecked(Context, GetRoot(), From.Container);
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
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::Transfer;

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
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_EDITOR_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsDamage::NManager::NModifier::FLibrary ModifierLibrary;

				ModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}
	}
}