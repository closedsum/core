// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Interactive.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

ACsData_Interactive::ACsData_Interactive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const float& ACsData_Interactive::GetWarmUpTime() { return ECsCachedReferences::Ref::Float; }
const float& ACsData_Interactive::GetLifeTime() { return ECsCachedReferences::Ref::Float; }

const FVector& ACsData_Interactive::GetScale() { return FVector::OneVector; }

#pragma endregion Stats

// Mesh
#pragma region

UStaticMesh* ACsData_Interactive::GetStaticMesh() { return nullptr; }
USkeletalMesh* ACsData_Interactive::GetSkeletalMesh() { return nullptr; }

void ACsData_Interactive::SetMeshAndMaterials(UStaticMeshComponent* InMesh)
{
	InMesh->SetStaticMesh(GetStaticMesh());
	UCsCommon::SetMaterials(InMesh, *GetMaterials());
}

void ACsData_Interactive::SetMeshAndMaterials(USkeletalMeshComponent* InMesh)
{
	InMesh->SetSkeletalMesh(GetSkeletalMesh());
	UCsCommon::SetMaterials(InMesh, *GetMaterials());
}

TArray<UMaterialInstanceConstant*>* ACsData_Interactive::GetMaterials() { return nullptr; }

#pragma endregion Mesh

// Collision
#pragma region

const bool& ACsData_Interactive::UseWorldCollisionPreset() { return ECsCachedReferences::Ref::False; }
void ACsData_Interactive::SetWorldCollisionFromPreset(UPrimitiveComponent* InComponent) {}
const float& ACsData_Interactive::GetInteractiveCollisionRadius() { return ECsCachedReferences::Ref::Float; }
const float& ACsData_Interactive::GetInteractiveCollisionRadiusSq() { return ECsCachedReferences::Ref::Float; }

#pragma endregion Collision

// Movement
#pragma region

const bool& ACsData_Interactive::UsePhysicsPreset(){ return ECsCachedReferences::Ref::False; }
void ACsData_Interactive::SetPhysicsFromPreset(UPrimitiveComponent* InComponent) {}
const bool& ACsData_Interactive::UseSpawnPhysicsImpulse() { return ECsCachedReferences::Ref::False; }
void ACsData_Interactive::ApplySpawnPhysicsImpulse(UPrimitiveComponent* InComponent){}

#pragma endregion Movement

// UI
#pragma region

const bool& ACsData_Interactive::OnSpawnSpawnWidget() { return ECsCachedReferences::Ref::False; }
const FString& ACsData_Interactive::GetDisplayName() { return ECsCachedString::Str::Empty; }
void ACsData_Interactive::GetScreenSpaceOffset(FIntPoint &OutPoint){ OutPoint = FIntPoint::ZeroValue; }

#pragma endregion UI