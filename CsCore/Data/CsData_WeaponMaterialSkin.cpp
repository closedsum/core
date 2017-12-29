// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_WeaponMaterialSkin.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Runtime/Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_WeaponMaterialSkin::ACsData_WeaponMaterialSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Skin
#pragma region

TArray<class UMaterialInstanceConstant*>* ACsData_WeaponMaterialSkin::GetMaterials(const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	return nullptr;
}

void ACsData_WeaponMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	UCsCommon::SetMaterials(InMesh, *GetMaterials(ViewType, IsLow));
}

void ACsData_WeaponMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetMaterials(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_WeaponMaterialSkin::SetMaterials(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh, ViewType, IsLow);
	else
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

#pragma region Skin