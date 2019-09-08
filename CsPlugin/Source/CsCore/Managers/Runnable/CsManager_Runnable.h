// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/Core/Public/Containers/Ticker.h"
#include "Runtime/Core/Public/Delegates/IDelegateInstance.h"
#include "Managers/Runnable/CsRunnable_Delegate.h"
#include "Types/CsTypes_Runnable.h"
#include "Types/CsTypes_Pool.h"
#include "CsManager_Runnable.generated.h"

#define CS_RUNNABLE_DELEGATE_POOL_SIZE 32		

UCLASS(transient)
class CSCORE_API UCsManager_Runnable : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	static UCsManager_Runnable* Get();
	static void Init();
	static void Shutdown();

	TWeakObjectPtr<UWorld> CurrentWorld;
	
	UWorld* GetCurrentWorld();
	
	/** Delegate for callbacks to Tick */
	FTickerDelegate	TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle	TickDelegateHandle;

	bool Tick(float DeltaSeconds);			

protected:

	void Initialize();
	void CleanUp();

// Payload
#pragma region
private:

	FCsRunnablePayload Payloads[CS_RUNNABLE_DELEGATE_POOL_SIZE];

	uint8 PayloadIndex;

public:

	FCsRunnablePayload* AllocatePayload();

#pragma endregion Payload

private:

	FCsRunnable_Delegate Pool[CS_RUNNABLE_DELEGATE_POOL_SIZE];

	uint8 PoolIndex;

	TMap<uint8, FCsRunnable_Delegate*> ActiveRunnables;

public:

	void LogTransaction(const FString& FunctionName, const ECsPoolTransaction& Transaction, FCsRunnable_Delegate* Runnable);

protected:

	FCsRunnable_Delegate* Allocate();

public:

	FCsRunnable_Delegate * Prep(FCsRunnablePayload* Payload);

private:
	// Singleton data
	static UCsManager_Runnable* s_managerRunnableSingleton;
	static bool s_bManagerHasShutdown;
};