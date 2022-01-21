// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsAllocated_DamageModifier.h"
#include "CsDmg.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Modifier/CsResource_DamageModifier.h"

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FAllocated, CopyFrom);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NModifier::FAllocated, Reset);
				}
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::CopyFrom(UObject* InRoot, const IModifier* From)
		{
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::CopyFrom;

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfModifierChecked(Context, InRoot, From);
			Modifier  = Container->Get();
			Type	  = DamageManagerLibrary::GetModifierTypeChecked(Context, InRoot, Modifier);
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::CopyFrom;

			CS_IS_PTR_NULL_CHECKED(From->GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->Container)
			{
				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				Root	  = From->GetRoot();
				Container = DamageManagerLibrary::CreateCopyOfModifierChecked(Context, GetRoot(), From->Container);
				Modifier  = Container->Get();
				Type	  = DamageManagerLibrary::GetModifierTypeChecked(Context, GetRoot(), Modifier);
			}
		}

		void FAllocated::Reset()
		{
			using namespace NCsDamage::NModifier::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				DamageManagerLibrary::DeallocateModifierChecked(Context, GetRoot(), Type, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Modifier  = nullptr;
			Type	  = EMCsDamageModifier::Get().GetMAX();
		}
	}
}