// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"

class UObject;

// NCsRunnable::NTask::ITask
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsRunnable, NTask, ITask)

namespace NCsRunnable
{
	namespace NTask
	{
		namespace NInfo
		{
			/**
			*/
			struct CSTHREAD_API FInfo
			{
			private:

				using TaskType = NCsRunnable::NTask::ITask;

				int32 Index;

			public:

				FString* Name;

				TWeakObjectPtr<UObject> Owner;

				TaskType* Task;

				FCsRunnableHandle Handle;

				FInfo() :
					Index(INDEX_NONE),
					Name(nullptr),
					Owner(nullptr),
					Task(nullptr),
					Handle()
				{
				}

				FORCEINLINE const int32& GetIndex() const
				{
					return Index;
				}

				FORCEINLINE void SetIndex(const int32& InIndex)
				{
					Index = InIndex;
				}

				void Reset()
				{
					Name = nullptr;
					Owner.Reset();
					Owner = nullptr;
					Task = nullptr;
					Handle = FCsRunnableHandle::Invalid;
				}

				UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	
				template<typename T>
				T* GetOwner() { return Cast<T>(GetOwner()); }
			};
		}
	}
}

using CsRunnableTaskInfoType = NCsRunnable::NTask::NInfo::FInfo;