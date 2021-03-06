// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformAffinity.h"
#include "Managers/Runnable/CsTypes_Runnable.h"
#pragma once

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
			struct CSCORE_API FInfo
			{
			private:

				int32 Index;

			public:

				FString* Name;

				TWeakObjectPtr<UObject> Owner;

			#define TaskType NCsRunnable::NTask::ITask
				TaskType* Task;
			#undef TaskType

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