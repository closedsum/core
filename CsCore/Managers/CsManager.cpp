// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/CsManager.h"
#include "CsCore.h"

ACsManager::ACsManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick		   = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	bReplicateMovement = false;
}

void ACsManager::Clear(){}
void ACsManager::Shutdown(){}

void ACsManager::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size){}
void ACsManager::CreatePool(const TSubclassOf<class UObject> &ObjectClass, const int32 &Size) {}
void ACsManager::CreatePool(const int32 &Size){}
void ACsManager::CreatePool_Script(const int32 &Size) { CreatePool(Size); }
void ACsManager::AddToPool(UObject* InObject, const uint8 &Type){}
void ACsManager::AddToPool(const TSubclassOf<class UObject> &ObjectClass, const uint8 &Type, const int32 &Size) {}
void ACsManager::AddToActivePool(UObject* InObject, const uint8 &Type) {}
int32 ACsManager::GetActivePoolSize(const uint8& Type) { return 0; }
bool ACsManager::IsExhausted(const uint8 &Type) { return true; }
void ACsManager::OnTick(const float &DeltaSeconds){}
void ACsManager::LogTransaction(const FString &FunctionName, const TEnumAsByte<ECsPoolTransaction::Type> &Transaction, UObject* InObject){}
void ACsManager::DeAllocate(const int32 &Index){}
void ACsManager::DeAllocate_Script(const int32 &Index) { DeAllocate(Index); }
void ACsManager::DeAllocate(const uint8 &Type, const int32 &Index){}
void ACsManager::DeAllocateAll() {}

void ACsManager::DeAllocateAll_Script()
{
	DeAllocateAll();
}