// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Process/CsManager_Process.h"
#include "CsCore.h"

// Internal
#pragma region

CsManager_Process::~CsManager_Process(){}

UCsProcess* CsManager_Process::ConstructObject(const FECsProcess& e)
{
	return NewObject<UCsProcess>(GetCurrentWorld(), UCsProcess::StaticClass());
}

const FString& CsManager_Process::EnumTypeToString(const FECsProcess &e)
{
	return e.Name;
}

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
	Internal = new CsManager_Process();
}

void UICsManager_Process::CleanUp()
{
	delete Internal;
}

void UICsManager_Process::Clear()
{
	Internal->Clear();
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