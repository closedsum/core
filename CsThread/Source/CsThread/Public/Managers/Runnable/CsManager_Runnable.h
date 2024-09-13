// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Runnable
#include "Managers/Runnable/CsRunnable.h"
#include "Managers/Runnable/Payload/CsPayload_Runnable.h"
#include "Managers/Runnable/Task/CsRunnableTaskInfo.h"
#include "Managers/Runnable/Task/CsPayload_RunnableTask.h"
// Types
#include "Managers/Runnable/CsTypes_Runnable.h"

#include "CsManager_Runnable.generated.h"

#define CS_RUNNABLE_DELEGATE_POOL_SIZE 32		

// Structs
#pragma region

// Runnable
namespace NCsRunnable
{
	/**
	* Container for holding a reference to a FCsRunnable.
	* This serves as an easy way for a Manager Resource to keep track of the resource.
	*/
	struct CSTHREAD_API FResource : public TCsResourceContainer<FCsRunnable>
	{
	};

	/**
	* A manager handling allocating and deallocating of a FCsRunnable and
	* are wrapped in the container: FResource.
	*/
	struct CSTHREAD_API FManager : public NCsResource::NManager::NValue::TFixed<FCsRunnable, FResource, 0>
	{
	};
}

// Payload
namespace NCsRunnable
{
	namespace NPayload
	{
	#define PayloadType NCsRunnable::NPayload::FImpl

		/**
		* Container for holding a reference to a PayloadType (NCsRunnable::NPayload::FImpl).
		* This serves as an easy way for a Manager Resource to keep track of the resource.
		*/
		struct CSTHREAD_API FResource : public TCsResourceContainer<PayloadType>
		{
		};

		/**
		* A manager handling allocating and deallocating of a PayloadType (NCsRunnable::NPayload::FImpl) and
		* are wrapped in the container: FResource.
		*/
		struct CSTHREAD_API FManager : public NCsResource::NManager::NValue::TFixed<PayloadType, FResource, 0>
		{
		};

	#undef PayloadType
	}
}

// TaskInfo
namespace NCsRunnable
{
	namespace NTask
	{
		namespace NInfo
		{
		#define CsRunnableTaskInfoType NCsRunnable::NTask::NInfo::FInfo

			/**
			* Container for holding a reference to a InfoType (NCsRunnable::NTask::NInfo::Info).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSTHREAD_API FResource : public TCsResourceContainer<CsRunnableTaskInfoType>
			{
			};

			/**
			* A manager handling allocating and deallocating of a InfoType (NCsRunnable::NTask::NInfo::Info) and
			* are wrapped in the container: FResource.
			*/
			struct CSTHREAD_API FManager : public NCsResource::NManager::NValue::TFixed<CsRunnableTaskInfoType, FResource, 0>
			{
			};

		#undef CsRunnableTaskInfoType
		}
	}
}

// TaskPayload
namespace NCsRunnable
{
	namespace NTask
	{
		namespace NPayload
		{
		#define PayloadType NCsRunnable::NTask::NPayload::FImpl

			/**
			* Container for holding a reference to a PayloadType (NCsRunnable::NTask::NPayload::FImpl).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSTHREAD_API FResource : public TCsResourceContainer<PayloadType>
			{
			};

			/**
			* A manager handling allocating and deallocating of a PayloadType (NCsRunnable::NTask::NPayload::FImpl) and
			* are wrapped in the container: FResource.
			*/
			struct CSTHREAD_API FManager : public NCsResource::NManager::NValue::TFixed<PayloadType, FResource, 0>
			{
			};

		#undef PayloadType
		}
	}
}

#pragma endregion Structs

class ICsGetManagerRunnable;

UCLASS(transient)
class CSTHREAD_API UCsManager_Runnable : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Runnable* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Runnable* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

	static void Shutdown();

#if WITH_EDITOR
protected:

	static ICsGetManagerRunnable* Get_GetManagerRunnable(UObject* InRoot);
	static ICsGetManagerRunnable* GetSafe_GetManagerRunnable(UObject* Object);

	static UCsManager_Runnable* GetSafe(UObject* Object);

public:

	static UCsManager_Runnable* GetFromWorldContextObject(UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	void CleanUp();

private:
	// Singleton data
	static UCsManager_Runnable* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	void Update(const FCsDeltaTime& DeltaTime);

	// Runnable
#pragma region

#define PayloadType NCsRunnable::NPayload::FImpl
#define PayloadManagerType NCsRunnable::NPayload::FManager

private:

	PayloadManagerType Manager_Payload;

public:

	FORCEINLINE PayloadType* AllocatePayload()
	{
		return Manager_Payload.AllocateResource();
	}

private:

#define RunnableManagerType NCsRunnable::FManager
	RunnableManagerType Manager_Internal;
#undef RunnableManagerType

public:

	FCsRunnable* Start(PayloadType* Payload);

#undef PayloadType
#undef PayloadManagerType

#pragma endregion Payload

	// Task
#pragma region

#define TaskPayloadType NCsRunnable::NTask::NPayload::FImpl
#define TaskPayloadManagerType NCsRunnable::NTask::NPayload::FManager

private:

	FCsRunnable* Runnable;

	TaskPayloadManagerType Manager_TaskPayload;

public:

	FORCEINLINE TaskPayloadType* AllocateTaskPayload()
	{
		return Manager_TaskPayload.AllocateResource();
	}

private:

#define TaskInfoManagerType NCsRunnable::NTask::NInfo::FManager
	TaskInfoManagerType Manager_TaskInfo;
#undef TaskInfoManagerType

public:


	FCsRunnableHandle StartTask(TaskPayloadType* Payload);

	bool StopQueuedTask(const FCsRunnableHandle& Handle);

#undef TaskPayloadType
#undef TaskPayloadManagerType

#pragma endregion Task

private:

	//void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, FCsRunnable_Delegate* Runnable);

};