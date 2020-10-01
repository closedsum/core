// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsAllocated_DamageValue.h"
#include "CsCore.h"

// Managers
#include "Managers/Damage/CsManager_Damage.h"

namespace NCsDamage 
{
	namespace NValue
	{
		namespace NAllocatedCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::FAllocated, CopyFrom);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::FAllocated, Reset);
			}
		}

		void FAllocated::CopyFrom(UObject* InRoot, const IValue* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			checkf(InRoot, TEXT("%s: InRoot is NULL."), *Context);

			checkf(From, TEXT("%s: From is NULL."), *Context);

			Root	  = InRoot;
			Container = UCsManager_Damage::Get(Root)->CreateCopyOfValue(Context, From);
			Value	  = Container->Get();
			Type	  = UCsManager_Damage::Get(Root)->GetValueType(Context, Value);
		}

		void FAllocated::CopyFrom(const FAllocated* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			checkf(From->Root, TEXT("&s: From->Root is NULL."), *Context);

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From->Container)
			{
				Root	  = From->Root;
				Container = UCsManager_Damage::Get(Root)->CreateCopyOfValue(Context, From->Container);
				Value	  = Container->Get();
				Type	  = UCsManager_Damage::Get(Root)->GetValueType(Context, Value);
			}
		}

		void FAllocated::Reset()
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				checkf(Root, TEXT("%s: Root is NULL."), *Context);

				UCsManager_Damage::Get(Root)->DeallocateValue(Context, Type, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Value	  = nullptr;
			Type	  = EMCsDamageValue::Get().GetMAX();
		}
	}
}