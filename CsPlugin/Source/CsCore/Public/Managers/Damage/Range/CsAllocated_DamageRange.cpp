// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Range/CsAllocated_DamageRange.h"
#include "CsCore.h"

// Managers
#include "Managers/Damage/CsManager_Damage.h"

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

		void FAllocated::CopyFrom(UObject* InRoot, const IRange* From)
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::CopyFrom;

			checkf(InRoot, TEXT("%s: InRoot is NULL."), *Context);

			checkf(From, TEXT("%s: From is NULL."), *Context);

			Root	  = InRoot;
			Container = UCsManager_Damage::Get(Root)->CreateCopyOfRange(Context, From);
			Range	  = Container->Get();
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
				Container = UCsManager_Damage::Get(Root)->CreateCopyOfRange(Context, From->Container);
				Range	  = Container->Get();
			}
		}

		void FAllocated::Reset()
		{
			using namespace NAllocatedCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				checkf(Root, TEXT("%s: Root is NULL."), *Context);

				UCsManager_Damage::Get(Root)->DeallocateRange(Context, Container);
			}

			Root	  = nullptr;
			Container = nullptr;
			Range	  = nullptr;
		}
	}
}