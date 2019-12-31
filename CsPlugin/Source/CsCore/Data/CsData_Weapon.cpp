// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "CsCore.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"

UCsData_Weapon::UCsData_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Stats
#pragma region

const FName& UCsData_Weapon::GetItemShortCode() { return NCsCached::Ref::Name; }
const bool& UCsData_Weapon::UseInventory() { return NCsCached::Ref::False; }

#pragma endregion Stats

// Mesh
#pragma region

const bool& UCsData_Weapon::UseMesh() { return NCsCached::Ref::True; }

USkeletalMesh* UCsData_Weapon::GetMesh(const TCsViewType& ViewType, const bool& IsLow /*=false*/){ return nullptr; }
USkeletalMesh* UCsData_Weapon::GetMesh(const TEnumAsByte<ECsViewType::Type>& ViewType, const bool& IsLow /*=false*/) { return GetMesh((TCsViewType)ViewType, IsLow); }
USkeletalMesh* UCsData_Weapon::GetMesh() { return nullptr; }

void UCsData_Weapon::SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	InMesh->SetSkeletalMesh(GetMesh(ViewType, IsLow));
}

void UCsData_Weapon::SetMesh(ASkeletalMeshActor* InActor, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_Weapon::SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type>& ViewType, const bool& IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, (TCsViewType)ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, (TCsViewType)ViewType, IsLow);
}

void UCsData_Weapon::SetMesh(USkeletalMeshComponent* InMesh)
{
	InMesh->SetSkeletalMesh(GetMesh());
}

void UCsData_Weapon::SetMesh(ASkeletalMeshActor* InActor)
{
	SetMesh(InActor->GetSkeletalMeshComponent());
}

void UCsData_Weapon::SetMesh(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor);
}

void UCsData_Weapon::GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	USkeletalMesh* InMesh = GetMesh(ViewType, IsLow);

	OutMaterials.Reset();

	const int32 Count = InMesh->Materials.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutMaterials.Add(Cast<UMaterialInstanceConstant>(InMesh->Materials[I].MaterialInterface->GetMaterial()));
	}
}

void UCsData_Weapon::GetDefaultMaterials(TArray<UMaterialInstanceConstant*>& OutMaterials)
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

void UCsData_Weapon::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType& ViewType, const bool& IsLow /*=false*/){}

void UCsData_Weapon::SetAnimBlueprint(ASkeletalMeshActor* InActor, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_Weapon::SetAnimBlueprint(UObject* InObject, const TEnumAsByte<ECsViewType::Type>& ViewType, const bool& IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh, (TCsViewType)ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, (TCsViewType)ViewType, IsLow);
}

void UCsData_Weapon::SetAnimBlueprint(USkeletalMeshComponent* InMesh) {}

void UCsData_Weapon::SetAnimBlueprint(ASkeletalMeshActor* InActor)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent());
}

void UCsData_Weapon::SetAnimBlueprint(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor);
}

#pragma endregion Anims