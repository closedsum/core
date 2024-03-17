// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Managers/Time/CsTypes_Time.h"
#include "GenericPlatform/GenericPlatformAffinity.h"

class UObject;

// NCsRunnable::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NPayload, FImpl)

namespace NCsRunnable
{
	/**
	*/
	struct CSTHREAD_API FCache
	{
	public:

		int32 Index;

		bool bAllocated;

		bool bQueueDeallocate;

		TWeakObjectPtr<UObject> Owner;

		FCsTime Time;

		uint32 StackSize;

		EThreadPriority ThreadPriority;

	public:

		FCache() :
			Index(INDEX_NONE),
			bAllocated(false),
			bQueueDeallocate(false),
			Owner(nullptr),
			Time(),
			StackSize(0),
			ThreadPriority(EThreadPriority::TPri_Normal)
		{
		}

		virtual ~FCache() {}

		void Init(const int32& InIndex) { Index = InIndex; }

		FORCEINLINE const int32& GetIndex() const { return Index; }
		FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

		#define PayloadType NCsRunnable::NPayload::FImpl
		void Allocate(PayloadType* Payload);
		#undef PayloadType

		FORCEINLINE const bool& IsAllocated() const { return bAllocated; }

		FORCEINLINE void Deallocate()
		{
			Reset();
		}

		FORCEINLINE void QueueDeallocate() { bQueueDeallocate = true; }
		FORCEINLINE bool ShouldDeallocate() const { return bQueueDeallocate; }

		UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }

		template<typename T>
		T* GetOwner() { return Cast<T>(GetOwner()); }

		void Reset()
		{
			bAllocated = false;
			bQueueDeallocate = false;

			Owner.Reset();
			Owner = nullptr;
			Time.Reset();
			StackSize = 0;
			ThreadPriority = EThreadPriority::TPri_Normal;
		}
	};
}