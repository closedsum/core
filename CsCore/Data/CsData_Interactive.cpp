// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Interactive.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

ACsData_Interactive::ACsData_Interactive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const FECsInteractiveType& ACsData_Interactive::GetInteractiveType() { return EMCsInteractiveType::Get().GetMAX(); }

const float& ACsData_Interactive::GetWarmUpTime() { return NCsCached::Ref::Float; }
const float& ACsData_Interactive::GetLifeTime() { return NCsCached::Ref::Float; }

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

const bool& ACsData_Interactive::UseWorldCollisionPreset() { return NCsCached::Ref::False; }
void ACsData_Interactive::SetWorldCollisionFromPreset(UPrimitiveComponent* InComponent) {}
const float& ACsData_Interactive::GetInteractiveCollisionRadius() { return NCsCached::Ref::Float; }
const float& ACsData_Interactive::GetInteractiveCollisionRadiusSq() { return NCsCached::Ref::Float; }

#pragma endregion Collision

// Movement
#pragma region

const bool& ACsData_Interactive::UsePhysicsPreset(){ return NCsCached::Ref::False; }
void ACsData_Interactive::SetPhysicsFromPreset(UPrimitiveComponent* InComponent) {}
const bool& ACsData_Interactive::SimulatePhysics() { return NCsCached::Ref::False; }
void ACsData_Interactive::ToggleWorldCollisionAndPhysics(UPrimitiveComponent* InComponent, const bool& Toggle){}
const bool& ACsData_Interactive::UseSpawnPhysicsImpulse() { return NCsCached::Ref::False; }
void ACsData_Interactive::ApplySpawnPhysicsImpulse(UPrimitiveComponent* InComponent, const bool& bSeed /*=true*/){}

#pragma endregion Movement

// UI
#pragma region

const bool& ACsData_Interactive::OnSpawnSpawnWidget() { return NCsCached::Ref::False; }
const FString& ACsData_Interactive::GetDisplayName() { return NCsCached::Str::Empty; }
void ACsData_Interactive::GetScreenSpaceOffset(FIntPoint &OutPoint){ OutPoint = FIntPoint::ZeroValue; }

#pragma endregion UI