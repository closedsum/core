// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/CsAllocated_DamageValue.h"
#include "CsDmg.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Value/CsLibrary_DamageValue.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Value/CsResource_DamageValue.h"

namespace NCsDamage 
{
	namespace NValue
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::FAllocated, CopyFrom);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::FAllocated, Reset);
				}
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::CopyFrom(const FString& Context, UObject* InRoot, const IValue* From)
		{
			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NValue::FLibrary DamageValueLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), From);
			Value	  = Container->Get();
			Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
		}

		#define DataType NCsDamage::NData::IData
		void FAllocated::CopyFrom(const FString& Context, UObject* InRoot, const DataType* Data)
		{
		#undef DataType

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(Data)

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
			typedef NCsDamage::NValue::FLibrary DamageValueLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), Data->GetValue());
			Value	  = Container->Get();
			Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			using namespace NCsDamage::NValue::NAllocated::NCached;

			const FString& Context = Str::CopyFrom;

			CS_IS_PTR_NULL_CHECKED(From->GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->GetContainer())
			{
				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;
				typedef NCsDamage::NValue::FLibrary DamageValueLibrary;

				Root	  = From->Root;
				Container = DamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), From->GetContainer());
				Value	  = Container->Get();
				Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
			}
		}

		void FAllocated::Reset()
		{
			using namespace NCsDamage::NValue::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				DamageManagerLibrary::DeallocateValueChecked(Context, GetRoot(), Type, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Value	  = nullptr;
			Type	  = EMCsDamageValue::Get().GetMAX();
		}
	}
}