// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsGunWeapon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Pawn/CsPawn.h"
#include "Animation/CsAnimInstance_Character.h"
#include "Animation/CsAnimInstance_Weapon.h"

// Data
#include "Data/CsData_ProjectileWeapon.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_WeaponMaterialSkin.h"

ACsGunWeapon::ACsGunWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = false;
	Mesh->SetHiddenInGame(true);
	Mesh->SetVisibility(false);
	Mesh->SetOnlyOwnerSee(true);
	Mesh->SetOwnerNoSee(false);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetRenderCustomDepth(true);
	Mesh->Deactivate();
	Mesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	RootComponent = Mesh;
}

// Members
#pragma region

	// Set
#pragma region

#pragma endregion Set

	// Get
#pragma region

#pragma endregion Get

#pragma endregion Members

// Data
#pragma region

void ACsGunWeapon::ApplyData_Weapon(const TCsWeaponSlot &Slot, class ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped /*=true*/){}

ACsData_WeaponMaterialSkin* ACsGunWeapon::GetMyData_WeaponMaterialSkin()
{
	return MyData_WeaponMaterialSkin.IsValid() ? MyData_WeaponMaterialSkin.Get() : nullptr;
}

ACsData_Character* ACsGunWeapon::GetMyData_Character()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// Character
		if (UCsAnimInstance_Character* AnimInstance = Cast<UCsAnimInstance_Character>(GetMyOwner()))
			return AnimInstance->GetData();
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
		if (MyOwnerType == PawnWeaponOwner)
			return GetMyPawn()->GetMyData_Character();
	}
	return nullptr;
}

#pragma endregion Data

// State
#pragma region

void ACsGunWeapon::OnTick(const float &DeltaSeconds)
{
#if WITH_EDITOR 
	if (Override_OnTick_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsGunWeapon::OnTick (%s): Using Override Function."), *GetName());
		}
		Override_OnTick_ScriptEvent.Broadcast(WeaponIndex, DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponIndex, DeltaSeconds);
#endif // #if WITH_EDITOR

	OnTick_HandleStates();

	Last_IsFirePressed = IsFirePressed;
}

void ACsGunWeapon::Show()
{
	Mesh->SetHiddenInGame(false);
	Mesh->SetComponentTickEnabled(true);
	Mesh->Activate();
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	Mesh->UpdateComponentToWorld();
}

void ACsGunWeapon::Hide()
{
	Mesh->SetHiddenInGame(true);
	Mesh->Deactivate();
	Mesh->SetComponentTickEnabled(false);
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
}

#pragma endregion State

// Mesh
#pragma region

void ACsGunWeapon::SetMesh()
{
	Mesh->SetAnimInstanceClass(nullptr);

	ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		USkeletalMeshComponent* AltMesh = nullptr;

		// Character
		if (UCsAnimInstance_Character* AnimInstance = Cast<UCsAnimInstance_Character>(GetMyOwner()))
		{
			AltMesh = Mesh;

			Data_Weapon->SetMesh(AltMesh);
			Data_Weapon->SetAnimBlueprint(AltMesh);
		}
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = Cast<UCsAnimInstance_Weapon>(GetMyOwner()))
			AltMesh = AnimInstance->GetSkeletalMeshComponent();

		if (!AltMesh)
			return;

		if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(AltMesh, ECsViewType::ThirdPerson);
			UCsCommon::SetMIDs(AltMesh, MeshMIDs, *Skin->GetMaterials());
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials);

			UCsCommon::SetMIDs(AltMesh, MeshMIDs, Materials);
		}
		return;
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh);
		Data_Weapon->SetAnimBlueprint(Mesh);

		if (ACsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh);
			UCsCommon::SetMIDs(Mesh, MeshMIDs, *Skin->GetMaterials());
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials);

			UCsCommon::SetMIDs(Mesh, MeshMIDs, Materials);
		}
		//Mesh->SetRelativeScale3D(WeaponData->Mesh3PScale);
		Mesh->SetCastShadow(false);
	}
}

USkeletalMeshComponent* ACsGunWeapon::GetMesh()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// Character
		if (UCsAnimInstance_Character* AnimInstance = Cast<UCsAnimInstance_Character>(GetMyOwner()))
			return Mesh;
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = Cast<UCsAnimInstance_Weapon>(GetMyOwner()))
			return AnimInstance->GetSkeletalMeshComponent();
	}
#endif // #if WITH_EDITOR
	if (IsValidOwnerTypeInGame())
		return Mesh;
	return nullptr;
}

#pragma endregion Mesh

// Firing
#pragma region

FVector ACsGunWeapon::GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode)
{
	return GetMyData_Weapon<ACsData_ProjectileWeapon>()->GetMuzzleLocation(GetMesh(), FireMode, CurrentProjectilePerShotIndex.Get(FireMode));
}

#pragma endregion Firing