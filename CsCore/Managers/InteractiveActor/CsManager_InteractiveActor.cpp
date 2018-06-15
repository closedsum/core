// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/InteractiveActor/CsManager_InteractiveActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Managers/InteractiveActor/CsInteractiveActor.h"
#include "Game/CsGameState.h"

// Data
#include "Data/CsData_Interactive.h"

// Internal
#pragma region

FCsManager_InteractiveActor::~FCsManager_InteractiveActor() {}

void FCsManager_InteractiveActor::DeconstructObject(ACsInteractiveActor* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

FString FCsManager_InteractiveActor::GetObjectName(ACsInteractiveActor* a)
{
	return a->GetName();
}

const FString& FCsManager_InteractiveActor::EnumTypeToString(const FECsInteractiveType &e)
{
	return e.Name;
}

const FString& FCsManager_InteractiveActor::EnumTypeToString(const int32 &index)
{
	return EMCsInteractiveType::Get().GetEnumAt(index).Name;
}

void FCsManager_InteractiveActor::LogTransaction_Internal(const FString& outLog)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *outLog);
}

#pragma endregion // Internal

AICsManager_InteractiveActor::AICsManager_InteractiveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Internal = new FCsManager_InteractiveActor();
	Internal->Init(TEXT("CsManager_InteractiveActor"), TEXT("ACsInteractiveActor"), nullptr, &CsCVarLogManagerInteractiveActorTransactions);
	Internal->CsConstructObject.Unbind();
	Internal->CsConstructObject.BindUObject(this, &AICsManager_InteractiveActor::ConstructObject);
}

/*static*/ AICsManager_InteractiveActor* AICsManager_InteractiveActor::Get(UWorld* InWorld)
{
	return InWorld->GetGameState<ACsGameState>()->Manager_InteractiveActor;
}

void AICsManager_InteractiveActor::Clear()
{
	Internal->Clear();
}

void AICsManager_InteractiveActor::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_InteractiveActor::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsInteractiveActor* AICsManager_InteractiveActor::ConstructObject(const FECsInteractiveType &Type)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsInteractiveActor* Actor = GetWorld()->SpawnActor<ACsInteractiveActor>(ACsInteractiveActor::StaticClass(), SpawnInfo);
	Actor->SetReplicates(false);
	Actor->Role = ROLE_None;
	GetWorld()->RemoveNetworkActor(Actor);
	return Actor;
}

void AICsManager_InteractiveActor::CreatePool(const FECsInteractiveType &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void AICsManager_InteractiveActor::AddToPool(const FECsInteractiveType &Type, ACsInteractiveActor* Actor)
{
	Internal->AddToPool(Type, Actor);
}

void AICsManager_InteractiveActor::AddToActivePool(const FECsInteractiveType &Type, ACsInteractiveActor* Actor)
{
	Internal->AddToActivePool(Type, Actor);
}

void AICsManager_InteractiveActor::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

void AICsManager_InteractiveActor::GetAllActiveActors(TArray<ACsInteractiveActor*> &OutActors)
{
	Internal->GetAllActiveObjects(OutActors);
}

const TArray<class ACsInteractiveActor*>* AICsManager_InteractiveActor::GetActors(const FECsInteractiveType& Type)
{
	return Internal->GetObjects(Type);
}

int32 AICsManager_InteractiveActor::GetActivePoolSize(const FECsInteractiveType &Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool AICsManager_InteractiveActor::IsExhausted(const FECsInteractiveType &Type)
{
	return Internal->IsExhausted(Type);
}

bool AICsManager_InteractiveActor::DeAllocate(const FECsInteractiveType &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void AICsManager_InteractiveActor::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsInteractiveActorPayload* AICsManager_InteractiveActor::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsInteractiveActor* AICsManager_InteractiveActor::Spawn(const FECsInteractiveType &Type, FCsInteractiveActorPayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

ACsInteractiveActor* AICsManager_InteractiveActor::Spawn(const FECsInteractiveType &Type, FCsInteractiveActorPayload *Payload)
{
	return Internal->Spawn(Type, Payload);
}