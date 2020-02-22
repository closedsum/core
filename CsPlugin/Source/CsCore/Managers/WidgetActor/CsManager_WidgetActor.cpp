// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsManager_WidgetActor.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"

// UI
#include "UI/CsUserWidget.h"
#include "UI/Simple/CsSimpleWidget.h"

#include "Game/CsGameState.h"

// static initializations
TWeakObjectPtr<UObject> AICsManager_WidgetActor::MyOwner;

// Internal
#pragma region

FCsManager_WidgetActor::~FCsManager_WidgetActor() {}

void FCsManager_WidgetActor::DeconstructObject(ACsWidgetActor* a)
{
	if (a && !a->IsPendingKill())
		a->Destroy(true);
}

FString FCsManager_WidgetActor::GetObjectName(ACsWidgetActor* a)
{
	return a->GetName();
}

const FString& FCsManager_WidgetActor::EnumTypeToString(const FECsWidgetActorType &e)
{
	return e.Name;
}

const FString& FCsManager_WidgetActor::EnumTypeToString(const int32 &index)
{
	return EMCsWidgetActorType::Get().GetEnumAt(index).Name;
}

void FCsManager_WidgetActor::Log(const FString& log)
{
	UE_LOG(LogCs, Warning, TEXT("%s"), *log);
}

#pragma endregion // Internal

AICsManager_WidgetActor::AICsManager_WidgetActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Internal = new FCsManager_WidgetActor();
	Internal->Init(TEXT("AICsManager_WidgetActor"), TEXT("ACsWidgetActor"), nullptr, &CsCVarLogManagerWidgetActorTransactions);
	Internal->ConstructObject_Call.Unbind();
	Internal->ConstructObject_Call.BindUObject(this, &AICsManager_WidgetActor::ConstructObject);
}

void AICsManager_WidgetActor::PostActorCreated()
{
	Super::PostActorCreated();

	Internal->CurrentWorld = GetWorld();
}

/*static*/ UObject* AICsManager_WidgetActor::GetMyOwner() { return MyOwner.IsValid() ? MyOwner.Get() : nullptr; }

/*static*/ void AICsManager_WidgetActor::Init(UObject* InOwner)
{
	MyOwner = InOwner;
}

/*static*/ AICsManager_WidgetActor* AICsManager_WidgetActor::Get(UWorld* InWorld)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(InWorld))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		return Cast<ACsGameState>(GetMyOwner())->Manager_WidgetActor;
	}
	return nullptr;
}

void AICsManager_WidgetActor::Clear()
{
	Internal->Clear();
}

void AICsManager_WidgetActor::Shutdown()
{
	Clear();
	Internal->Shutdown();
	delete Internal;
}

void AICsManager_WidgetActor::Destroyed()
{
	Shutdown();

	Super::Destroyed();
}

ACsWidgetActor* AICsManager_WidgetActor::ConstructObject(const FECsWidgetActorType &Type)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.ObjectFlags |= RF_Transient;

	ACsWidgetActor* Actor = GetWorld()->SpawnActor<ACsWidgetActor>(ClassMap.Find(Type) ? ClassMap[Type] : ACsWidgetActor::StaticClass(), SpawnInfo);
	Actor->SetReplicates(false);
	Actor->SetRole(ROLE_None);
	GetWorld()->RemoveNetworkActor(Actor);
	return Actor;
}

void AICsManager_WidgetActor::CreatePool(const FECsWidgetActorType &Type, const int32 &Size)
{
	Internal->CreatePool(Type, Size);
}

void AICsManager_WidgetActor::AddToPool(const FECsWidgetActorType &Type, ACsWidgetActor* Actor)
{
	Internal->AddToPool(Type, Actor);
}

void AICsManager_WidgetActor::AddToActivePool(const FECsWidgetActorType &Type, ACsWidgetActor* Actor)
{
	Internal->AddToActivePool(Type, Actor);
}

void AICsManager_WidgetActor::OnTick(const float &DeltaTime)
{
	Internal->OnTick(DeltaTime);
}

void AICsManager_WidgetActor::GetAllActiveActors(TArray<ACsWidgetActor*> &OutActors)
{
	Internal->GetAllActiveObjects(OutActors);
}

const TArray<class ACsWidgetActor*>* AICsManager_WidgetActor::GetActors(const FECsWidgetActorType& Type)
{
	return Internal->GetObjects(Type);
}

int32 AICsManager_WidgetActor::GetActivePoolSize(const FECsWidgetActorType &Type)
{
	return Internal->GetActivePoolSize(Type);
}

bool AICsManager_WidgetActor::IsExhausted(const FECsWidgetActorType &Type)
{
	return Internal->IsExhausted(Type);
}

bool AICsManager_WidgetActor::DeAllocate(const FECsWidgetActorType &Type, const int32 &Index)
{
	return Internal->DeAllocate(Type, Index);
}

void AICsManager_WidgetActor::DeAllocateAll()
{
	return Internal->DeAllocateAll();
}

FCsWidgetActorPayload* AICsManager_WidgetActor::AllocatePayload()
{
	return Internal->AllocatePayload();
}

ACsWidgetActor* AICsManager_WidgetActor::Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload &Payload)
{
	return Internal->Spawn(Type, &Payload);
}

ACsWidgetActor* AICsManager_WidgetActor::Display(const FECsWidgetActorType &Type, FCsWidgetActorPayload *Payload)
{
	return Internal->Spawn(Type, Payload);
}