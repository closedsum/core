// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Range/CsAllocated_DamageRange.h"
#include "CsDmg.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"

namespace NCsDamage
{
	namespace NRange
	{
		namespace NAllocatedCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NRange::FAllocated, CopyFrom);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NRange::FAllocated, Reset);
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::CopyFrom(const FString& Context, UObject* InRoot, const IRange* From)
		{
			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfRangeChecked(Context, GetRoot(), From);
			Range	  = Container->Get();
		}

		#define DataType NCsDamage::NData::IData
		void FAllocated::SafeCopyFrom(const FString& Context, UObject* InRoot, const DataType* Data, void(*Log)(const FString&) /*=nullptr*/)
		{
		#undef DataType

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_EXIT(Data)

			typedef NCsDamage::NData::FLibrary DamageDataLibrary;
			typedef NCsDamage::NData::NShape::IShape ShapeDataType;

			const ShapeDataType* From = DamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data);

			if (!From)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data does NOT implement the interface: %s."), *Context, *(ShapeDataType::Name.ToString())));
				return;
			}

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			Root	  = InRoot;
			Container = DamageManagerLibrary::CreateCopyOfRangeChecked(Context, GetRoot(), From->GetRange());
			Range	  = Container->Get();
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			CS_IS_PTR_NULL_CHECKED(From->GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->GetContainer())
			{
				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				Root	  = From->GetRoot();
				Container = DamageManagerLibrary::CreateCopyOfRangeChecked(Context, GetRoot(), From->GetContainer());
				Range	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

				DamageManagerLibrary::DeallocateRangeChecked(Context, GetRoot(), Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Range	  = nullptr;
		}
	}
}