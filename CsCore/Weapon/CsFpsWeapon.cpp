// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsFpsWeapon.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "Animation/CsAnimInstance.h"

// Data
#include "Data/CsData_WeaponMaterialSkin.h"

ACsFpsWeapon::ACsFpsWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh1P"));
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetHiddenInGame(true);
	Mesh1P->SetVisibility(false);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(false);
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh1P->SetRenderCustomDepth(true);
	Mesh1P->Deactivate();
	Mesh1P->PrimaryComponentTick.bStartWithTickEnabled = false;
	RootComponent = Mesh1P;

	Mesh3P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh3P"));
	Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->CastShadow = false;
	Mesh3P->bCastDynamicShadow = false;
	Mesh3P->SetHiddenInGame(true);
	Mesh3P->SetVisibility(false);
	Mesh3P->SetOnlyOwnerSee(false);
	Mesh3P->SetOwnerNoSee(true);
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh3P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh3P->SetRenderCustomDepth(true);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	//Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	Mesh3P->Deactivate();
	Mesh3P->SetupAttachment(Mesh1P);
	Mesh3P->PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Data
#pragma region

ACsData_WeaponMaterialSkin* ACsFpsWeapon::GetMyData_WeaponMaterialSkin()
{
	return MyData_WeaponMaterialSkin.IsValid() ? MyData_WeaponMaterialSkin.Get() : nullptr;
}

#pragma endregion Data

// Mesh
#pragma region

void ACsFpsWeapon::SetMesh1P()
{
	Mesh1P->SetAnimInstanceClass(nullptr);

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
		{
			USkeletalMeshComponent* Mesh = AnimInstance->GetSkeletalMeshComponent();

			if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
			{
				Skin->SetMaterials(Mesh, ECsViewType::FirstPerson);
				UCsCommon::SetMIDs(Mesh, MeshMIDs1P, *Skin->GetMaterials(ECsViewType::FirstPerson));
			}
			else
			{
				TArray<UMaterialInstanceConstant*> Materials;
				Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::FirstPerson);

				UCsCommon::SetMIDs(Mesh, MeshMIDs1P, Materials);
			}
			return;
		}
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh1P, ECsViewType::FirstPerson);
		Data_Weapon->SetAnimBlueprint(Mesh1P, ECsViewType::FirstPerson);

		if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh1P, ECsViewType::FirstPerson);
			UCsCommon::SetMIDs(Mesh1P, MeshMIDs1P, *Skin->GetMaterials(ECsViewType::FirstPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::FirstPerson);

			UCsCommon::SetMIDs(Mesh1P, MeshMIDs1P, Materials);
		}
		//Mesh1P->SetRelativeScale3D(Data_Weapon->Mesh1PScale);
	}
}

void ACsFpsWeapon::SetMesh3P()
{
	Mesh3P->SetAnimInstanceClass(nullptr);

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
		{
			USkeletalMeshComponent* Mesh = AnimInstance->GetSkeletalMeshComponent();

			if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
			{
				Skin->SetMaterials(Mesh, ECsViewType::ThirdPerson);
				UCsCommon::SetMIDs(Mesh, MeshMIDs3P, *Skin->GetMaterials(ECsViewType::ThirdPerson));
			}
			else
			{
				TArray<UMaterialInstanceConstant*> Materials;
				Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::ThirdPerson);

				UCsCommon::SetMIDs(Mesh, MeshMIDs3P, Materials);
			}
			return;
		}
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);
		Data_Weapon->SetAnimBlueprint(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);

		if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh3P, ECsViewType::ThirdPerson);
			UCsCommon::SetMIDs(Mesh3P, MeshMIDs3P, *Skin->GetMaterials(ECsViewType::ThirdPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::ThirdPerson);

			UCsCommon::SetMIDs(Mesh3P, MeshMIDs3P, Materials);
		}
		//Mesh3P->SetRelativeScale3D(WeaponData->Mesh3PScale);
		Mesh3P->SetCastShadow(false);
	}
}

USkeletalMeshComponent* ACsFpsWeapon::GetMesh(const TCsViewType &ViewType)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// 1P / 3P
		if (UCsAnimInstance* AnimInstance = Cast<UCsAnimInstance>(GetMyOwner()))
			return AnimInstance->GetSkeletalMeshComponent();
	}
#endif // #if WITH_EDITOR
	if (IsValidOwnerTypeInGame())
	{
		if (ViewType == ECsViewType::FirstPerson)
			return Mesh1P;
		if (ViewType == ECsViewType::ThirdPerson)
			return Mesh3P;
	}
	return nullptr;
}

USkeletalMeshComponent* ACsFpsWeapon::GetCurrentMesh()
{
	return GetMesh(GetCurrentViewType());
}

#pragma endregion Mesh