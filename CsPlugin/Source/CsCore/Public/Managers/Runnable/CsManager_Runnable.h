// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Runnable
#include "Managers/Runnable/CsRunnable.h"
#include "Managers/Runnable/Payload/CsRunnablePayload.h"
#include "Managers/Runnable/Task/CsRunnableTaskInfo.h"
#include "Managers/Runnable/Task/CsRunnableTaskPayload.h"
// Types
#include "Managers/Runnable/CsTypes_Runnable.h"

#include "CsManager_Runnable.generated.h"

#define CS_RUNNABLE_DELEGATE_POOL_SIZE 32		

// Structs
#pragma region

	// Runnable

/**
* Container for holding a reference to a FCsRunnable.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_Runnable : public TCsResourceContainer<FCsRunnable>
{
};

/**
* A manager handling allocating and deallocating of a FCsRunnable and
* are wrapped in the container: FCsResource_Runnable.
*/
struct CSCORE_API FCsManager_Runnable_Internal : public TCsManager_ResourceValueType_Fixed<FCsRunnable, FCsResource_Runnable, 0>
{
};

	// RunnablePayload

/**
* Container for holding a reference to a FCsRunnablePayload.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_RunnablePayload : public TCsResourceContainer<FCsRunnablePayload>
{
};

/**
* A manager handling allocating and deallocating of a FCsRunnablePayload and
* are wrapped in the container: FCsResource_RunnablePayload.
*/
struct CSCORE_API FCsManager_RunnablePayload : public TCsManager_ResourceValueType_Fixed<FCsRunnablePayload, FCsResource_RunnablePayload, 0>
{
};

	// RunnableTaskInfo

/**
* Container for holding a reference to a FCsRunnableTaskInfo.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_RunnableTaskInfo : public TCsResourceContainer<FCsRunnableTaskInfo>
{
};

/**
* A manager handling allocating and deallocating of a FCsRunnableTaskInfo and
* are wrapped in the container: FCsResource_RunnableTaskInfo.
*/
struct CSCORE_API FCsManager_RunnableTaskInfo : public TCsManager_ResourceValueType_Fixed<FCsRunnableTaskInfo, FCsResource_RunnableTaskInfo, 0>
{
};

	// RunnableTaskPayload

/**
* Container for holding a reference to a FCsRunnableTaskPayload.
* This serves as an easy way for a Manager Resource to keep track of the resource.
*/
struct CSCORE_API FCsResource_RunnableTaskPayload : public TCsResourceContainer<FCsRunnableTaskPayload>
{
};

/**
* A manager handling allocating and deallocating of a FCsRunnableTaskPayload and
* are wrapped in the container: FCsResource_RunnableTaskPayload.
*/
struct CSCORE_API FCsManager_RunnableTaskPayload : public TCsManager_ResourceValueType_Fixed<FCsRunnableTaskPayload, FCsResource_RunnableTaskPayload, 0>
{
};

#pragma endregion Structs

class ICsGetManagerRunnable;
struct FCsRunnableTaskPayload;

UCLASS(transient)
class CSCORE_API UCsManager_Runnable : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Runnable* Get(UObject* InRoot = nullptr);

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

	static UCsManager_Runnable* GetFromWorldContextObject(const UObject* WorldContextObject);

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

	FCsManager_RunnablePayload Manager_Payload;

public:

	FORCEINLINE FCsRunnablePayload* AllocatePayload()
	{
		return Manager_Payload.AllocateResource();
	}

private:

	FCsManager_Runnable_Internal Manager_Internal;

public:

	FCsRunnable* Start(FCsRunnablePayload* Payload);

#pragma endregion Payload

	// Task
#pragma region
private:

	FCsRunnable* Runnable;

	FCsManager_RunnableTaskPayload Manager_TaskPayload;

public:

	FORCEINLINE FCsRunnableTaskPayload* AllocateTaskPayload()
	{
		return Manager_TaskPayload.AllocateResource();
	}

private:

	FCsManager_RunnableTaskInfo Manager_TaskInfo;

public:

	FCsRunnableHandle StartTask(FCsRunnableTaskPayload* Payload);

	bool StopQueuedTask(const FCsRunnableHandle& Handle);

#pragma endregion Task

private:

	//void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, FCsRunnable_Delegate* Runnable);

};