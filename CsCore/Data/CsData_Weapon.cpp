// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "CsCore.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_Weapon::ACsData_Weapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Mesh
#pragma region

USkeletalMesh* ACsData_Weapon::GetMesh(const TCsViewType &ViewType, const bool &IsLow /*=false*/){ return nullptr; }
USkeletalMesh* ACsData_Weapon::GetMesh() { return nullptr; }

void ACsData_Weapon::SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	InMesh->SetSkeletalMesh(GetMesh(ViewType, IsLow));
}

void ACsData_Weapon::SetMesh(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_Weapon::SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType, IsLow);
}

void ACsData_Weapon::SetMesh(USkeletalMeshComponent* InMesh)
{
	InMesh->SetSkeletalMesh(GetMesh());
}

void ACsData_Weapon::SetMesh(ASkeletalMeshActor* InActor)
{
	SetMesh(InActor->GetSkeletalMeshComponent());
}

void ACsData_Weapon::SetMesh(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor);
}

void ACsData_Weapon::GetDefaultMaterials(TArray<UMaterialInstanceConstant*> &OutMaterials, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	USkeletalMesh* InMesh = GetMesh(ViewType, IsLow);

	OutMaterials.Reset();

	const int32 Count = InMesh->Materials.Num();

	for (int32 I = 0; I < Count; ++I)
	{
		OutMaterials.Add(Cast<UMaterialInstanceConstant>(InMesh->Materials[I].MaterialInterface->GetMaterial()));
	}
}

void ACsData_Weapon::GetDefaultMaterials(TArray<UMaterialInstanceConstant*> &OutMaterials)
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

void ACsData_Weapon::SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/){}

void ACsData_Weapon::SetAnimBlueprint(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_Weapon::SetAnimBlueprint(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor, ViewType, IsLow);
}

void ACsData_Weapon::SetAnimBlueprint(USkeletalMeshComponent* InMesh) {}

void ACsData_Weapon::SetAnimBlueprint(ASkeletalMeshActor* InActor)
{
	SetAnimBlueprint(InActor->GetSkeletalMeshComponent());
}

void ACsData_Weapon::SetAnimBlueprint(UObject* InObject)
{
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetAnimBlueprint(InMesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetAnimBlueprint(Actor);
}

#pragma endregion Anims