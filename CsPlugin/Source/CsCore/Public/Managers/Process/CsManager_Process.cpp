// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsManager_Process.h"
#include "CsCore.h"
#include "CsCVars.h"

// Internal
#pragma region

FCsManager_Process::~FCsManager_Process(){}

	// Interface
#pragma region

void FCsManager_Process::DeconstructObject(UCsProcess* o)
{
	if (o && !o->IsPendingKill())
	{
		o->RemoveFromRoot();
		o->ConditionalBeginDestroy();
	}
}

UCsProcess* FCsManager_Process::ConstructObject(const FECsProcess& e)
{
	UCsProcess* process = NewObject<UCsProcess>(GetTransientPackage(), UCsProcess::StaticClass());
	process->AddToRoot();
	return process;
}

FString FCsManager_Process::GetObjectName(UCsProcess* p)
{
	return p->GetName();
}

const FString& FCsManager_Process::EnumTypeToString(const FECsProcess &e)
{
	return e.GetName();
}

const FString& FCsManager_Process::EnumTypeToString(const int32 &index)
{
	return EMCsProcess::Get().GetEnumAt(index).GetName();
}

void FCsManager_Process::Log(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

#pragma endregion Interface

#pragma endregion // Internal

// static initializations
UICsManager_Process* UICsManager_Process::s_managerProcessSingleton;
bool UICsManager_Process::s_bManagerProcessHasShutdown = false;

UICsManager_Process::UICsManager_Process(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

/*static*/ UICsManager_Process* UICsManager_Process::Get()
{
	if (s_bManagerProcessHasShutdown)
		return nullptr;

	if (!s_managerProcessSingleton)
	{
		s_managerProcessSingleton = NewObject<UICsManager_Process>(GetTransientPackage(), UICsManager_Process::StaticClass(), TEXT("Manager_Process_Singleton"), RF_Transient | RF_Public);
		s_managerProcessSingleton->AddToRoot();
		s_managerProcessSingleton->Initialize();
	}

	return s_managerProcessSingleton;
}

/*static*/ void UICsManager_Process::Init()
{
	s_bManagerProcessHasShutdown = false;
	UICsManager_Process::Get();
}

/*static*/ void UICsManager_Process::Shutdown()
{
	if (!s_managerProcessSingleton)
		return;

	s_managerProcessSingleton->CleanUp();
	s_managerProcessSingleton->RemoveFromRoot();
	s_managerProcessSingleton = nullptr;
	s_bManagerProcessHasShutdown = true;
}

void UICsManager_Process::Initialize()
{
	Internal = new FCsManager_Process();
	Internal->Init(TEXT("CsManager_Process"), TEXT("UCsProcess"), nullptr, &CsCVarLogManagerProcessTransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &UICsManager_Process::ConstructObject);
}

void UICsManager_Process::CleanUp()
{
	Internal->Shutdown();
	delete Internal;
}

void UICsManager_Process::Clear()
{
	Internal->Clear();
}

UCsProcess* UICsManager_Process::ConstructObject(const FECsProcess &Type)
{
	UCsProcess* Process = NewObject<UCsProcess>(GetTransientPackage(), UCsProcess::StaticClass());
	Process->AddToRoot();
	return Process;
}

void UICsManager_Process::CreatePool(const FECsProcess &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void UICsManager_Process::AddToPool(const FECsProcess &Type, UCsProcess* Process)
{
	Internal->AddToPool(Type, Process);
}

void UICsManager_Process::AddToActivePool(const FECsProcess &Type, UCsProcess* Process)
{
	Internal->AddToActivePool(Type, Process);
}

void UICsManager_Process::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

int32 UICsManager_Process::GetActivePoolSize(const FECsProcess &Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool UICsManager_Process::IsExhausted(const FECsProcess &Type)
{
	return Internal->IsExhausted(Type);
}

bool UICsManager_Process::DeAllocate(const FECsProcess &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void UICsManager_Process::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsProcessPayload* UICsManager_Process::AllocatePayload()
{
	return Internal->AllocatePayload();
}

UCsProcess* UICsManager_Process::Spawn(const FECsProcess &Type, FCsProcessPayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

UCsProcess* UICsManager_Process::Spawn(const FECsProcess &Type, FCsProcessPayload* Payload)
{
	return Internal->Spawn(Type, Payload);
}