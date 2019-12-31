// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Interactive.h"
#include "CsCore.h"

// Library
#include "Common/CsCommon.h"

UCsData_Interactive::UCsData_Interactive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const FECsInteractiveType& UCsData_Interactive::GetInteractiveType() { return EMCsInteractiveType::Get().GetMAX(); }

const float& UCsData_Interactive::GetWarmUpTime() { return NCsCached::Ref::Float; }
const float& UCsData_Interactive::GetLifeTime() { return NCsCached::Ref::Float; }

const FVector& UCsData_Interactive::GetScale() { return FVector::OneVector; }

#pragma endregion Stats

// Mesh
#pragma region

UStaticMesh* UCsData_Interactive::GetStaticMesh() { return nullptr; }
USkeletalMesh* UCsData_Interactive::GetSkeletalMesh() { return nullptr; }

void UCsData_Interactive::SetMeshAndMaterials(UStaticMeshComponent* InMesh)
{
	InMesh->SetStaticMesh(GetStaticMesh());
	UCsCommon::SetMaterials(InMesh, *GetMaterials());
}

void UCsData_Interactive::SetMeshAndMaterials(USkeletalMeshComponent* InMesh)
{
	InMesh->SetSkeletalMesh(GetSkeletalMesh());
	UCsCommon::SetMaterials(InMesh, *GetMaterials());
}

TArray<UMaterialInstanceConstant*>* UCsData_Interactive::GetMaterials() { return nullptr; }

#pragma endregion Mesh

// Collision
#pragma region

const bool& UCsData_Interactive::UseWorldCollisionPreset() { return NCsCached::Ref::False; }
void UCsData_Interactive::SetWorldCollisionFromPreset(UPrimitiveComponent* InComponent) {}
const float& UCsData_Interactive::GetInteractiveCollisionRadius() { return NCsCached::Ref::Float; }
const float& UCsData_Interactive::GetInteractiveCollisionRadiusSq() { return NCsCached::Ref::Float; }

#pragma endregion Collision

// Movement
#pragma region

const bool& UCsData_Interactive::UsePhysicsPreset(){ return NCsCached::Ref::False; }
void UCsData_Interactive::SetPhysicsFromPreset(UPrimitiveComponent* InComponent) {}
const bool& UCsData_Interactive::SimulatePhysics() { return NCsCached::Ref::False; }
void UCsData_Interactive::ToggleWorldCollisionAndPhysics(UPrimitiveComponent* InComponent, const bool& Toggle){}
const bool& UCsData_Interactive::UseSpawnPhysicsImpulse() { return NCsCached::Ref::False; }
void UCsData_Interactive::ApplySpawnPhysicsImpulse(UPrimitiveComponent* InComponent, const bool& bSeed /*=true*/){}

#pragma endregion Movement

// UI
#pragma region

const bool& UCsData_Interactive::OnSpawnSpawnWidget() { return NCsCached::Ref::False; }
const FString& UCsData_Interactive::GetDisplayName() { return NCsCached::Str::Empty; }
void UCsData_Interactive::GetScreenSpaceOffset(FIntPoint &OutPoint){ OutPoint = FIntPoint::ZeroValue; }

#pragma endregion UI