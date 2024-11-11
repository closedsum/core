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
		namespace NImpl
		{
			using PayloadType = NCsRunnable::NPayload::FImpl;

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
		}
	}
}

// TaskInfo
namespace NCsRunnable
{
	namespace NTask
	{
		namespace NInfo
		{
			using InfoType = NCsRunnable::NTask::NInfo::FInfo;

			/**
			* Container for holding a reference to a InfoType (NCsRunnable::NTask::NInfo::Info).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSTHREAD_API FResource : public TCsResourceContainer<InfoType>
			{
			};

			/**
			* A manager handling allocating and deallocating of a InfoType (NCsRunnable::NTask::NInfo::Info) and
			* are wrapped in the container: FResource.
			*/
			struct CSTHREAD_API FManager : public NCsResource::NManager::NValue::TFixed<InfoType, FResource, 0>
			{
			};
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
			using PayloadType = NCsRunnable::NTask::NPayload::FImpl;

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
		}
	}
}

#pragma endregion Structs

class ICsGetManagerRunnable;

UCLASS(transient)
class CSTHREAD_API UCsManager_Runnable : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using RunnableManagerType = NCsRunnable::FManager;
	using PayloadType = NCsRunnable::NPayload::FImpl;
	using PayloadManagerType = NCsRunnable::NPayload::NImpl::FManager;
	using TaskPayloadType = NCsRunnable::NTask::NPayload::FImpl;
	using TaskPayloadManagerType = NCsRunnable::NTask::NPayload::FManager;
	using TaskInfoManagerType = NCsRunnable::NTask::NInfo::FManager;

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

private:

	PayloadManagerType Manager_Payload;

public:

	FORCEINLINE PayloadType* AllocatePayload()
	{
		return Manager_Payload.AllocateResource();
	}

private:

	RunnableManagerType Manager_Internal;

public:

	FCsRunnable* Start(PayloadType* Payload);

#pragma endregion Payload

	// Task
#pragma region

private:

	FCsRunnable* Runnable;

	TaskPayloadManagerType Manager_TaskPayload;

public:

	FORCEINLINE TaskPayloadType* AllocateTaskPayload()
	{
		return Manager_TaskPayload.AllocateResource();
	}

private:

	TaskInfoManagerType Manager_TaskInfo;

public:


	FCsRunnableHandle StartTask(TaskPayloadType* Payload);

	bool StopQueuedTask(const FCsRunnableHandle& Handle);

#pragma endregion Task

private:

	//void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, FCsRunnable_Delegate* Runnable);

};