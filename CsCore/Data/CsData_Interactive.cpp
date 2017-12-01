// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Interactive.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

ACsData_Interactive::ACsData_Interactive(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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