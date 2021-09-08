// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Time/CsTypes_Time.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

class UObject;

// NCsRunnable::NTask::ITask
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NTask, ITask)

namespace NCsRunnable
{
	namespace NPayload
	{
		/**
		*/
		struct CSCORE_API FImpl
		{
		private:

			int32 Index;

		public:

			TWeakObjectPtr<UObject> Owner;

			FCsTime Time;

			uint32 StackSize;

			EThreadPriority ThreadPriority;

		#define TaskType NCsRunnable::NTask::ITask
			TaskType* Task;
		#undef TaskType

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