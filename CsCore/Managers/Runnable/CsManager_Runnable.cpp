// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Runnable/CsManager_Runnable.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

// static initializations
UCsManager_Runnable* UCsManager_Runnable::s_managerRunnableSingleton;
bool UCsManager_Runnable::s_bManagerHasShutdown = false;

// Cache
#pragma region

namespace ECsManagerRunnableCached
{
	namespace Str
	{
		const FString OnTick = TEXT("UCsManager_Runnable::OnTick");
		const FString Prep = TEXT("UCsManager_Runnable::Prep");
	}
}

#pragma endregion Cache

UCsManager_Runnable::UCsManager_Runnable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	for (uint8 I = 0; I < CS_RUNNABLE_DELEGATE_POOL_SIZE; ++I)
	{
		Pool[I].Setup(I);
	}
}

/*static*/ UCsManager_Runnable* UCsManager_Runnable::Get()
{
	if (s_bManagerHasShutdown)
		return nullptr;

	if (!s_managerRunnableSingleton)
	{
		s_managerRunnableSingleton = NewObject<UCsManager_Runnable>(GetTransientPackage(), UCsManager_Runnable::StaticClass(), TEXT("Manager_Runnable_Singleton"), RF_Transient | RF_Public);
		s_managerRunnableSingleton->AddToRoot();
		s_managerRunnableSingleton->Initialize();
	}

	return s_managerRunnableSingleton;
}

/*static*/ void UCsManager_Runnable::Init()
{
	s_bManagerHasShutdown = false;
	UCsManager_Runnable::Get();
}

/*static*/ void UCsManager_Runnable::Shutdown()
{
	if (!s_managerRunnableSingleton)
		return;

	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(s_managerRunnableSingleton->TickDelegateHandle);

	s_managerRunnableSingleton->CleanUp();
	s_managerRunnableSingleton->RemoveFromRoot();
	s_managerRunnableSingleton = nullptr;
	s_bManagerHasShutdown = true;
}

UWorld* UCsManager_Runnable::GetCurrentWorld()
{
	return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
}

bool UCsManager_Runnable::Tick(float DeltaSeconds)
{
	const int32 Count	= ActiveRunnables.Num();
	uint8 EarliestIndex = Count;

	for (int32 I = Count - 1; I >= 0; --I)
	{
		FCsRunnable_Delegate* Runnable = ActiveRunnables[I];

		// Check if Runnable was DeAllocated NOT in a normal way
		if (!Runnable->Cache.bAllocated)
		{
			UE_LOG(LogCs, Warning, TEXT("UCsManager_Runnable::OnTick: Runnable: %s at PoolIndex: %s was prematurely deallocted NOT in a normal way."), *(Runnable->Cache.Name), Runnable->Cache.Index);

			LogTransaction(ECsManagerRunnableCached::Str::OnTick, ECsPoolTransaction::Deallocate, Runnable);

			ActiveRunnables.Remove(Runnable->Cache.Index);
			continue;
		}

		if (Runnable->bExit)
		{
			LogTransaction(ECsManagerRunnableCached::Str::OnTick, ECsPoolTransaction::Deallocate, Runnable);

			Runnable->DeAllocate();
			ActiveRunnables.Remove(Runnable->Cache.Index);
			continue;
		}
	}
	return true;
}

void UCsManager_Runnable::Initialize()
{
	// Register delegate for ticker callback
	TickDelegate	   = FTickerDelegate::CreateUObject(this, &UCsManager_Runnable::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

void UCsManager_Runnable::CleanUp()
{
	for (uint8 I = 0; I < CS_RUNNABLE_DELEGATE_POOL_SIZE; ++I)
	{
		Pool[I].DeAllocate();
	}
	ActiveRunnables.Reset();
}

// Payload
#pragma region

FCsRunnablePayload* UCsManager_Runnable::AllocatePayload()
{
	for (uint8 I = 0; I < CS_RUNNABLE_DELEGATE_POOL_SIZE; ++I)
	{
		const uint8 Index			= (PayloadIndex + I) % CS_RUNNABLE_DELEGATE_POOL_SIZE;
		FCsRunnablePayload* Payload = &(Payloads[Index]);

		if (!Payload->bAllocated)
		{
			Payload->bAllocated = true;
			return Payload;
		}
	}
	checkf(0, TEXT("UCsManager_Runnable::AllocatePayload: Pool is exhausted"));
	return nullptr;
}

#pragma endregion Payload


void UCsManager_Runnable::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, FCsRunnable_Delegate* Runnable)
{
	if (CsCVarLogManagerRunnableTransactions->GetInt() == CS_CVAR_SHOW_LOG)
	{
		const FString& TransactionAsString = ECsPoolTransaction::ToActionString(Transaction);

		const FString& RunnableName  = Runnable->Cache.Name;
		const float CurrentTime		 = GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : UCsCommon::GetCurrentDateTimeSeconds();
		const UObject* RunnableOwner = Runnable->Cache.GetOwner();
		const FString OwnerName		 = RunnableOwner ? RunnableOwner->GetName() : ECsCached::Str::None;

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

FCsRunnable_Delegate* UCsManager_Runnable::Allocate()
{
	for (uint8 I = 0; I < CS_RUNNABLE_DELEGATE_POOL_SIZE; ++I)
	{
		PoolIndex					   = (PoolIndex + I) % CS_RUNNABLE_DELEGATE_POOL_SIZE;
		FCsRunnable_Delegate* Runnable = &(Pool[PoolIndex]);

		if (!Runnable->Cache.bAllocated)
		{
			Runnable->Cache.bAllocated = true;
			return Runnable;
		}
	}
	checkf(0, TEXT("UCsManager_Runnable::Allocate: Pool is exhausted"));
	return nullptr;
}

FCsRunnable_Delegate * UCsManager_Runnable::Prep(FCsRunnablePayload* Payload)
{
	FCsRunnable_Delegate* Runnable = Allocate();
	ActiveRunnables.Add(Runnable->Cache.Index, Runnable);

	if (UWorld* World = GetCurrentWorld())
		Runnable->Allocate(Payload, World->GetTimeSeconds(), World->GetRealTimeSeconds(), UCsCommon::GetCurrentFrame(World));
	else
		Runnable->Allocate(Payload, UCsCommon::GetCurrentDateTimeSeconds(), UCsCommon::GetCurrentDateTimeSeconds(), 0);

	LogTransaction(ECsManagerRunnableCached::Str::Prep, ECsPoolTransaction::Allocate, Runnable);
	Payload->Reset();
	return Runnable;
}