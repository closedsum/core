// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/CsManager_Runnable.h"
#include "CsCore.h"

// CVar
#include "CsCVars.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Task
#include "Managers/Runnable/Task/CsRunnableTask.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Runnable/CsGetManagerRunnable.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_Runnable* UCsManager_Runnable::s_Instance;
bool UCsManager_Runnable::s_bShutdown = false;

// Cache
#pragma region

namespace NCsManagerRunnableCached
{
	namespace Str
	{
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Runnable, OnTick);
		CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_Runnable, Prep);
	}
}

#pragma endregion Cache

UCsManager_Runnable::UCsManager_Runnable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_Runnable* UCsManager_Runnable::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerRunnable(InRoot)->GetManager_Runnable();
#else
	if (s_bShutdown)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::Get: Manager has already shutdown."));
		return nullptr;
	}
	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Runnable::IsValid(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerRunnable(InRoot)->GetManager_Runnable() != nullptr;
#else
	return s_Instance != nullptr;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Runnable::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerRunnable* GetManagerRunnable = Get_GetManagerRunnable(InRoot);

	UCsManager_Runnable* Manager_Runnable = GetManagerRunnable->GetManager_Runnable();

	if (!Manager_Runnable)
	{
		Manager_Runnable = NewObject<UCsManager_Runnable>(InRoot, UCsManager_Runnable::StaticClass(), TEXT("Manager_Runnable_Singleton"), RF_Transient | RF_Public);

		GetManagerRunnable->SetManager_Runnable(Manager_Runnable);

		Manager_Runnable->SetMyRoot(InRoot);
		Manager_Runnable->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Runnable>(GetTransientPackage(), UCsManager_Runnable::StaticClass(), TEXT("Manager_Runnable_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Runnable::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerRunnable* GetManagerRunnable = Get_GetManagerRunnable(InRoot);
	UCsManager_Runnable* Manager_Runnable	  = GetManagerRunnable->GetManager_Runnable();
	Manager_Runnable->CleanUp();

	GetManagerRunnable->SetManager_Runnable(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Runnable::HasShutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerRunnable(InRoot)->GetManager_Runnable() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerRunnable* UCsManager_Runnable::Get_GetManagerRunnable(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Runnable::Get_GetManagerRunnable: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Runnable::Get_GetManagerRunnable: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Runnable::Get_GetManagerRunnable: Manager_Singleton is NULL."));

	ICsGetManagerRunnable* GetManagerRunnable = Cast<ICsGetManagerRunnable>(Manager_Singleton);

	checkf(GetManagerRunnable, TEXT("UCsManager_Runnable::Get_GetManagerRunnable: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerRunnable."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerRunnable;
}

/*static*/ ICsGetManagerRunnable* UCsManager_Runnable::GetSafe_GetManagerRunnable(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::GetSafe_GetManagerRunnable: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::GetSafe_GetManagerRunnable: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::GetSafe_GetManagerRunnable: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerRunnable>(Manager_Singleton);
}

/*static*/ UCsManager_Runnable* UCsManager_Runnable::GetSafe(UObject* Object)
{
	if (ICsGetManagerRunnable* GetManagerRunnable = GetSafe_GetManagerRunnable(Object))
		return GetManagerRunnable->GetManager_Runnable();
	return nullptr;
}

/*static*/ UCsManager_Runnable* UCsManager_Runnable::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsManager_Runnable* Manager = GetSafe(World->GetGameInstance()))
			return Manager;

		UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::GetFromWorldContextObject: Failed to Manager Item of type UCsManager_Runnable from GameInstance."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_Runnable::Initialize()
{
	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	// Delegate
	{
		// Delegate
		{
			checkf(Settings->Manager_Runnable.RunnablePoolSize >= 1, TEXT("UCsManager_Runnable::Initialize: UCsDeveloperSettings.Manager_Runnable.RunnablePoolSize should be >= 1."));

			Manager_Internal.CreatePool(Settings->Manager_Runnable.RunnablePoolSize);

			const TArray<FCsResource_Runnable*>& Pool = Manager_Internal.GetPool();

			for (FCsResource_Runnable* Container : Pool)
			{
				FCsRunnable* R		= Container->Get();
				const int32& Index	= R->GetCache()->GetIndex();
				R->GetCache()->SetIndex(Index);
			}
		}
		// Payload
		{
			checkf(Settings->Manager_Runnable.RunnablePayloadSize >= 1, TEXT("UCsManager_Runnable::Initialize: UCsDeveloperSettings.Manager_Runnable.RunnablePayloadSize should be >= 1."));

			Manager_Payload.CreatePool(Settings->Manager_Runnable.RunnablePayloadSize);

			const TArray<FCsResource_RunnablePayload*>& Pool = Manager_Payload.GetPool();

			for (FCsResource_RunnablePayload* Container : Pool)
			{
				FCsRunnablePayload* R = Container->Get();
				const int32& Index	  = R->GetIndex();
				R->SetIndex(Index);
			}
		}
	}
	// Task
	{
		// Info
		{
			checkf(Settings->Manager_Runnable.TaskPoolSize >= 4, TEXT("UCsManager_Runnable::Initialize: UCsDeveloperSettings.Manager_Runnable.TaskPoolSize should be >= 4."));

			Manager_TaskInfo.CreatePool(Settings->Manager_Runnable.TaskPoolSize);

			const TArray<FCsResource_RunnableTaskInfo*>& Pool = Manager_TaskInfo.GetPool();

			for (FCsResource_RunnableTaskInfo* Container : Pool)
			{
				FCsRunnableTaskInfo* R = Container->Get();
				const int32& Index	   = R->GetIndex();
				R->SetIndex(Index);
			}
		}
		// Payload
		{
			checkf(Settings->Manager_Runnable.TaskPayloadSize >= 4, TEXT("UCsManager_Runnable::Initialize: UCsDeveloperSettings.Manager_Runnable.TaskPayloadSize should be >= 4."));

			Manager_TaskPayload.CreatePool(Settings->Manager_Runnable.TaskPayloadSize);

			const TArray<FCsResource_RunnableTaskPayload*>& Pool = Manager_TaskPayload.GetPool();

			for (FCsResource_RunnableTaskPayload* Container : Pool)
			{
				FCsRunnableTaskPayload* R = Container->Get();
				const int32& Index	      = R->GetIndex();
				R->SetIndex(Index);
			}
		}
	}

	Runnable = new FCsRunnable();
	Runnable->SetIndex(0);
	Runnable->StartThread();

	bInitialized = true;
}

/*static*/ bool UCsManager_Runnable::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Runnable::CleanUp()
{
	delete Runnable;
	Runnable = nullptr;

	Manager_Internal.Shutdown();
	Manager_Payload.Shutdown();
	Manager_TaskInfo.Shutdown();
	Manager_TaskPayload.Shutdown();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Runnable::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

void UCsManager_Runnable::Update(const FCsDeltaTime& DeltaTime)
{
	// Task
	{
		// if Tasks Queued, process Task
		if (TCsDoubleLinkedList<FCsResource_RunnableTaskInfo*>* Current = Manager_TaskInfo.GetAllocatedHead())
		{
			FCsRunnableTaskInfo* Info = nullptr;

			// Complete
			if (Runnable->IsTaskComplete())
			{
				for (FCsOnRunnableTaskComplete& OnComplete : Runnable->GetTask()->GetOnComplete_Events())
				{
					OnComplete.Execute();
				}

				FCsResource_RunnableTaskInfo* CurrentContainer = **Current;
				FCsRunnableTaskInfo* CurrentInfo			   = CurrentContainer->Get();

				CurrentInfo->Reset();
				Manager_TaskInfo.DeallocateHead();

				// Process Next Task
				if (TCsDoubleLinkedList<FCsResource_RunnableTaskInfo*>* Next = Manager_TaskInfo.GetAllocatedHead())
				{
					FCsResource_RunnableTaskInfo* Container = **Next;
					Info									= Container->Get();
				}
				// If NO Queued Task, Mark Ready
				else
				{
					Runnable->ReadyForTask();
				}
			}
			// Ready
			else
			if (Runnable->IsReadyForTask())
			{
				FCsResource_RunnableTaskInfo* Container = **Current;
				Info									= Container->Get();
			}

			// Start Task
			if (Info &&
				Info->GetOwner())
			{
				// Copy Payload from Info
				FCsRunnableTaskPayload* Payload = Manager_TaskPayload.AllocateResource();

				Payload->Owner = Info->Owner;
				Payload->Task  = Info->Task;
				Payload->Handle = Info->Handle;

				Runnable->StartTask(Payload);
				Payload->Reset();
				Manager_TaskPayload.DeallocateAt(Payload->GetIndex());
			}
		}
		// If NO Tasks in Queue, Mark Ready
		else
		{
			Runnable->ReadyForTask();
		}
	}
	// Runnables
	{
		TCsDoubleLinkedList<FCsResource_Runnable*>* Current = Manager_Internal.GetAllocatedHead();
		TCsDoubleLinkedList<FCsResource_Runnable*>* Next    = Current;

		while (Next)
		{
			Current							= Next;
			FCsResource_Runnable* Container = **Current;
			Next							= Current->GetNextLink();

			FCsRunnable* R = Container->Get();

			if (R->GetCache()->ShouldDeallocate())
			{
				R->Deallocate();
				Manager_Internal.Deallocate(Container);
			}
		}
	}
}

// Delegate
#pragma region

FCsRunnableHandle UCsManager_Runnable::Start(FCsRunnablePayload* Payload)
{
	checkf(Payload, TEXT("UCsManager_Runnable::Start: Payload is NULL."));

	FCsRunnable* R = Manager_Internal.AllocateResource();

	R->StartThread();
	R->Allocate(Payload);

	if (Payload->IsPooled())
	{
		Payload->Reset();
		Manager_Payload.DeallocateAt(Payload->GetIndex());
	}
	return R->GetHandle();
}

#pragma endregion Payload

	// Task
#pragma region

FCsRunnableHandle UCsManager_Runnable::StartTask(FCsRunnableTaskPayload* Payload)
{
	checkf(Payload, TEXT("UCsManager_Runnable::StartTask: Payload is NULL."));

	FCsRunnableTaskInfo* Info = Manager_TaskInfo.AllocateResource();

	Info->Owner = Payload->Owner;
	Info->Task  = Payload->Task;

	Info->Handle = Runnable->GetHandle();
	Info->Handle.New();

	return Info->Handle;
}

bool UCsManager_Runnable::StopQueuedTask(const FCsRunnableHandle& Handle)
{
	if (Runnable->GetHandle() == Handle)
		return false;

	TCsDoubleLinkedList<FCsResource_RunnableTaskInfo*>* Current = Manager_TaskInfo.GetAllocatedHead();
	TCsDoubleLinkedList<FCsResource_RunnableTaskInfo*>* Next	= Current;

	while (Next)
	{
		Current									= Next;
		FCsResource_RunnableTaskInfo* Container = **Current;
		Next									= Current->GetNextLink();

		FCsRunnableTaskInfo* R = Container->Get();

		if (R->Handle == Handle)
		{
			R->Reset();
			Manager_TaskInfo.Deallocate(Container);
			return true;
		}
	}
	return false;
}

#pragma endregion Task

/*
void UCsManager_Runnable::LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, FCsRunnable_Delegate* Runnable)
{
	if (CsCVarLogManagerRunnableTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& TransactionAsString = NCsPoolTransaction::ToActionString(Transaction);

		const FString& RunnableName  = Runnable->Cache.Name;
		const float CurrentTime		 = GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();
		const UObject* RunnableOwner = Runnable->Cache.GetOwner();
		const FString OwnerName		 = RunnableOwner ? RunnableOwner->GetName() : NCsCached::Str::None;

		if (RunnableOwner)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Runnable: %s at %f for %s."), *FunctionName, *TransactionAsString, *RunnableName, CurrentTime, *OwnerName);
		}
		else
		{
			UE_LOG(LogCs, Warning, TEXT("%s: %s Runnable: %s at %f."), *FunctionName, *TransactionAsString, *RunnableName, CurrentTime);
		}
	}
}
*/