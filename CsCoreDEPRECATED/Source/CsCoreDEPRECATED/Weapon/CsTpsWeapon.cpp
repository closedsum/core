// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsTpsWeapon.h"
#include "CsCoreDEPRECATED.h"
#include "CsCVars.h"

// Library
#include "Library/CsLibrary_Common.h"
// Pawn
#include "Pawn/CsPawn.h"
// Anim
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
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = false;
	Mesh->SetHiddenInGame(true);
	Mesh->SetVisibility(false);
	Mesh->SetOnlyOwnerSee(false);
	Mesh->SetOwnerNoSee(true);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetRenderCustomDepth(true);
	Mesh->Deactivate();
	Mesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	RootComponent = Mesh;
}

void ACsTpsWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Mesh->SetComponentTickEnabled(false);
}

// Owner
#pragma region

void ACsTpsWeapon::AttachMeshToPawn()
{
	UCsData_Character* Data_Character	  = nullptr;
	USkeletalMeshComponent* CharacterMesh = GetCharacterMesh();

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
			Data_Character = AnimInstance->GetData();
	}
	else
#endif // #if WITH_EDITOR
	{
		if (MyOwnerType == PawnWeaponOwner)
			Data_Character = GetMyPawn()->GetMyData_Character();
	}

	if (!Data_Character)
		return;

	const FName WeaponBone = Data_Character->GetBoneToAttachWeaponTo();
	//const FName MeleeBone = Data_Character->BoneToAttachMeleeItemTo;

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
		Mesh->SetOnlyOwnerSee(false);
		Mesh->SetOwnerNoSee(false);
	}
#endif // #if WITH_EDITOR

	if (IsEquipped)
	{
		Mesh->SetHiddenInGame(false);
		Mesh->SetVisibility(true);
		Mesh->SetCastShadow(true);
	}
	Mesh->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponBone);
	//MeleeAttachment3P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, MeleeAttachmentPoint);

	if (IsEquipped)
	{
		Mesh->Activate();
		Mesh->SetComponentTickEnabled(true);
		Mesh->UpdateComponentToWorld(EUpdateTransformFlags::None, ETeleportType::None);
	}
}

USkeletalMeshComponent* ACsTpsWeapon::GetCharacterMesh()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
			return AnimInstance->GetSkeletalMeshComponent();
	}
	else
#endif // #if WITH_EDITOR
	{
		if (MyOwnerType == PawnWeaponOwner)
			return GetMyPawn()->GetMesh();
	}
	return nullptr;
}

#pragma endregion Owner

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
		Override_OnTick_ScriptEvent.Broadcast(WeaponSlot, DeltaSeconds);
		return;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
	{
	}
	// In Game
	else
#endif // #if WITH_EDITOR
	{
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponSlot, DeltaSeconds);
#endif // #if WITH_EDITOR

	OnTick_HandleStates();

	Last_IsFirePressed = IsFirePressed;
}

void ACsTpsWeapon::Show()
{
	Mesh->SetHiddenInGame(false);
	Mesh->SetComponentTickEnabled(true);
	Mesh->Activate();
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	Mesh->UpdateComponentToWorld();
}

void ACsTpsWeapon::Hide()
{
	Mesh->SetHiddenInGame(true);
	Mesh->Deactivate();
	Mesh->SetComponentTickEnabled(false);
	Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
}

#pragma endregion State

// Mesh
#pragma region

void ACsTpsWeapon::SetMesh()
{
	Mesh->SetAnimInstanceClass(nullptr);

	UCsData_ProjectileWeapon* Data_Weapon = GetMyData_Weapon<UCsData_ProjectileWeapon>();

	if (!Data_Weapon->UseMesh())
		return;

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(AltMesh);
			UCsLibrary_Common::SetMIDs(AltMesh, MeshMIDs, *Skin->GetMaterials());
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials);

			UCsLibrary_Common::SetMIDs(AltMesh, MeshMIDs, Materials);
		}
		return;
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh);
		Data_Weapon->SetAnimBlueprint(Mesh);

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh);
			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs, *Skin->GetMaterials());
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials);

			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs, Materials);
		}
		//Mesh->SetRelativeScale3D(Data_Weapon->MeshScale);
		Mesh->SetCastShadow(false);
	}
}

USkeletalMeshComponent* ACsTpsWeapon::GetMesh()
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

FVector ACsTpsWeapon::GetMuzzleLocation(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode)
{
	return GetMyData_Weapon<UCsData_ProjectileWeapon>()->GetMuzzleLocation(GetMesh(), FireMode, CurrentProjectilePerShotIndex[FireMode]);
}

#pragma endregion Firing