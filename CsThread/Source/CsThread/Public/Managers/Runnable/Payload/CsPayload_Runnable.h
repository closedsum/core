// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Time/CsTypes_Time.h"
#include "GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"

class UObject;

// NCsRunnable::NTask::ITask
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NTask, ITask)

namespace NCsRunnable
{
	namespace NPayload
	{
		/**
		*/
		struct CSTHREAD_API FImpl
		{
		private:

			using TaskType = NCsRunnable::NTask::ITask;

			int32 Index;

		public:

			TWeakObjectPtr<UObject> Owner;

			FCsTime Time;

			uint32 StackSize;

			EThreadPriority ThreadPriority;

			TaskType* Task;

			FImpl() :
				Index(INDEX_NONE),
				Owner(nullptr),
				Time(),
				StackSize(0),
				ThreadPriority(EThreadPriority::TPri_Normal),
				Task(nullptr)
			{
			}
	
			FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

			FORCEINLINE const int32 GetIndex() const { return Index; }

			FORCEINLINE bool IsPooled() const { return Index != INDEX_NONE; }

			void Reset()
			{
				Owner.Reset();
				Owner = nullptr;
				Time.Reset();
				StackSize = 0;
				ThreadPriority = EThreadPriority::TPri_Normal;
				Task = nullptr;
			}

			UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	
			template<typename T>
			T* GetOwner() { return Cast<T>(GetOwner()); }
		};
	}
}

using CsRunnablePayloadImplType = NCsRunnable::NPayload::FImpl;