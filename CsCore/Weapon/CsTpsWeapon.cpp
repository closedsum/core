// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsTpsWeapon.h"
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

ACsTpsWeapon::ACsTpsWeapon(const FObjectInitializer& ObjectInitializer)
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

// Data
#pragma region

void ACsTpsWeapon::ApplyData_Weapon(const TCsWeaponSlot &Slot, class ACsData_Weapon* InData, class ACsData_WeaponMaterialSkin* InSkin, const bool &Equipped /*=true*/){}

#pragma endregion Data

// State
#pragma region

void ACsTpsWeapon::OnTick(const float &DeltaSeconds)
{
#if WITH_EDITOR 
	if (Override_OnTick_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsTpsWeapon::OnTick (%s): Using Override Function."), *GetName());
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

void ACsTpsWeapon::Show()
{
	Mesh->SetHiddenInGame(false);
	Mesh->SetComponentTickEnabled(true);
	Mesh->Activate();
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	Mesh->UpdateComponentToWorld();
}

void ACsTpsWeapon::Hide()
{
	Mesh->SetHiddenInGame(true);
	Mesh->Deactivate();
	Mesh->SetComponentTickEnabled(false);
	Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
}

#pragma endregion State

// Mesh
#pragma region

void ACsTpsWeapon::SetMesh()
{
	Mesh->SetAnimInstanceClass(nullptr);

	ACsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<ACsData_ProjectileWeapon>();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		USkeletalMeshComponent* AltMesh = nullptr;

		// Character
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
		{
			AltMesh = Mesh;

			Data_Weapon->SetMesh(AltMesh);
			Data_Weapon->SetAnimBlueprint(AltMesh);
		}
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = GetMyOwner<UCsAnimInstance_Weapon>())
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
		//Mesh->SetRelativeScale3D(Data_Weapon->MeshScale);
		Mesh->SetCastShadow(false);
	}
}

USkeletalMeshComponent* ACsTpsWeapon::GetMesh()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		// Character
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
			return Mesh;
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = GetMyOwner<UCsAnimInstance_Weapon>())
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

FVector ACsTpsWeapon::GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode)
{
	return GetMyData_Weapon<ACsData_ProjectileWeapon>()->GetMuzzleLocation(GetMesh(), FireMode, CurrentProjectilePerShotIndex.Get(FireMode));
}

#pragma endregion Firing