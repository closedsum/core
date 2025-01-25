// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/CsAllocated_DamageValue.h"

// Types
#include "CsMacro_Misc.h"
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

		#define USING_NS_CACHED using namespace NCsDamage::NValue::NAllocated::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsDamage::NValue::NAllocated::NCached; \
			const FString& Context = Str::__FunctionName
		#define DamageValueLibrary NCsDamage::NValue::FLibrary

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::CopyFrom(const FString& Context, UObject* InRoot, const IValue* From)
		{
			CS_IS_PTR_NULL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = InRoot;
			Container = CsDamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), From);
			Value	  = Container->Get();
			Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
		}

		#define DataType NCsDamage::NData::IData
		void FAllocated::CopyFrom(const FString& Context, UObject* InRoot, const DataType* Data)
		{
		#undef DataType

			CS_IS_PTR_NULL_CHECKED(InRoot)
			CS_IS_PTR_NULL_CHECKED(Data)

			Root	  = InRoot;
			Container = CsDamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), Data->GetValue());
			Value	  = Container->Get();
			Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			SET_CONTEXT(CopyFrom);

			CS_IS_PTR_NULL_CHECKED(From->GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->GetContainer())
			{
				Root	  = From->Root;
				Container = CsDamageManagerLibrary::CreateCopyOfValueChecked(Context, GetRoot(), From->GetContainer());
				Value	  = Container->Get();
				Type	  = DamageValueLibrary::GetTypeChecked(Context, Value);
			}
		}

		void FAllocated::Reset()
		{
			SET_CONTEXT(Reset);

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				CsDamageManagerLibrary::DeallocateValueChecked(Context, GetRoot(), Type, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Value	  = nullptr;
			Type	  = EMCsDamageValue::Get().GetMAX();
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef DamageValueLibrary
	}
}