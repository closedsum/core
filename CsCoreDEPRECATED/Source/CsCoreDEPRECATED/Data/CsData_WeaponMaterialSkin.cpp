// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponMaterialSkin.h"
#include "CsCoreDEPRECATED.h"

// Librarys
#include "Library/CsLibrary_Common.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"

UCsData_WeaponMaterialSkin::UCsData_WeaponMaterialSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Skin
#pragma region

TArray<UMaterialInstanceConstant*>* UCsData_WeaponMaterialSkin::GetMaterials(const ECsViewType& ViewType, const bool& IsLow /*=false*/){ return nullptr; }
TArray<UMaterialInstanceConstant*>* UCsData_WeaponMaterialSkin::GetMaterials() { return nullptr; }

void UCsData_WeaponMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	UCsLibrary_Common::SetMaterials(InMesh, *GetMaterials(ViewType, IsLow));
}

void UCsData_WeaponMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMaterials(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_WeaponMaterialSkin::SetMaterials(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_WeaponMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh)
{
	UCsLibrary_Common::SetMaterials(InMesh, *GetMaterials());
}

void UCsData_WeaponMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor)
{
	SetMaterials(InActor->GetSkeletalMeshComponent());
}

void UCsData_WeaponMaterialSkin::SetMaterials(UObject* InObject)
{
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor->GetSkeletalMeshComponent());
}

#pragma region Skin