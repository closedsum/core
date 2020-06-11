// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon_DEPRECATED.h"
#include "CsCoreDEPRECATED.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Engine/Classes/Materials/MaterialInstanceConstant.h"

UCsData_Weapon_DEPRECATED::UCsData_Weapon_DEPRECATED(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const FName& UCsData_Weapon_DEPRECATED::GetItemShortCode() { return NCsCached::Ref::Name; }
const bool& UCsData_Weapon_DEPRECATED::UseInventory() { return NCsCached::Ref::False; }

#pragma endregion Stats

// Mesh
#pragma region

const bool& UCsData_Weapon_DEPRECATED::UseMesh() { return NCsCached::Ref::True; }

USkeletalMesh* UCsData_Weapon_DEPRECATED::GetMesh(const ECsViewType& ViewType, const bool& IsLow /*=false*/){ return nullptr; }
USkeletalMesh* UCsData_Weapon_DEPRECATED::GetMesh() { return nullptr; }

void UCsData_Weapon_DEPRECATED::SetMesh(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	InMesh->SetSkeletalMesh(GetMesh(ViewType, IsLow));
}

void UCsData_Weapon_DEPRECATED::SetMesh(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_Weapon_DEPRECATED::SetMesh(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType, IsLow);
}

void UCsData_Weapon_DEPRECATED::SetMesh(USkeletalMeshComponent* InMesh)
{
	InMesh->SetSkeletalMesh(GetMesh());
}

void UCsData_Weapon_DEPRECATED::SetMesh(ASkeletalMeshActor* InActor)
{
	SetMesh(InActor->GetSkeletalMeshComponent());
}

void UCsData_Weapon_DEPRECATED::SetMesh(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor);
}

void UCsData_Weapon_DEPRECATED::GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	USkeletalMesh* InMesh = GetMesh(ViewType, IsLow);

	OutMaterials.Reset();

	const int32 Count = InMesh->Materials.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutMaterials.Add(Cast<UMaterialInstanceConstant>(InMesh->Materials[I].MaterialInterface->GetMaterial()));
	}
}

void UCsData_Weapon_DEPRECATED::GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials)
{
	USkeletalMesh* InMesh = GetMesh();

	OutMaterials.Reset();

	const int32 Count = InMesh->Materials.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutMaterials.Add(Cast<UMaterialInstanceConstant>(InMesh->Materials[I].MaterialInterface->GetMaterial()));
	}
}

#pragma endregion Mesh

// Anims
#pragma region

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow /*=false*/){}

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, IsLow);
}

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(USkeletalMeshComponent* InMesh) {}

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(ASkeletalMeshActor* InActor)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent());
}

void UCsData_Weapon_DEPRECATED::SetAnimBlueprint(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor);
}

#pragma endregion Anims