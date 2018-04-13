// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsFpsWeapon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Common/CsCommon.h"

#include "Player/CsFpsPawn.h"
#include "Animation/CsAnimInstance_Character.h"
#include "Animation/CsAnimInstance_Weapon.h"

// Data
#include "Data/CsData_ProjectileWeapon.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_WeaponMaterialSkin.h"
// Components
#include "Components/CsSkeletalMeshComponent.h"

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

// Members
#pragma region

void ACsFpsWeapon::InitMultiValueMembers()
{
	Super::InitMultiValueMembers();

	const uint8 SIZE = (uint8)WeaponFireMode_MAX;
	
	// Spread
	{
		MovingSpreadBonus.Init(SIZE);
		MovingSpreadBonus.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetMovingSpreadBonus);
		JumpSpreadImpulse.Init(SIZE);
		JumpSpreadImpulse.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetJumpSpreadImpulse);
		ScopeAccuracyBonus.Init(SIZE);
		ScopeAccuracyBonus.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetScopeAccuracyBonus);
	}
	// Scope
	{
		DoScopePower.Init(SIZE);
		MaxScopePower.Init(SIZE);
		MaxScopePower.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetMaxScopePower);
		ScopePowerGrowthRate.Init(SIZE);
		ScopePowerGrowthRate.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetScopePowerGrowthRate);
		CurrentScopePower.Init(SIZE);
		LastScopePower.Init(SIZE);
	}
	// Movement
	{
		DoSlowWhileFiring.Init(SIZE);
		SlowWhileFiringRate.Init(SIZE);
		DoKickback.Init(SIZE);
		DoKickbackOnGround.Init(SIZE);
		KickbackStrength.Init(SIZE);
	}
}

	// Set
#pragma region

void ACsFpsWeapon::SetMemberValue_float(const uint8 &Member, const int32 &Index, const float &Value)
{
	if (Member < ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		SetMemberValue_float((TCsWeaponCacheMultiValueMember)Member, Index, Value);
	}
	else
	{
		const TCsFpsWeaponCacheMultiValueMember MemberType = (TCsFpsWeaponCacheMultiValueMember)Member;

		// Firing
		{
			// Scope
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::CurrentScopePower) { CurrentScopePower.Set(Index, Value); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::LastScopePower) { CurrentScopePower.Set(Index, Value); }
		}
	}
}

void ACsFpsWeapon::SetMemberValue_Script_float(const FString &MemberName, const int32 &Index, const float &Value)
{
#if WITH_EDITOR
	uint8 Member = (uint8)ECsWeaponCacheMultiValueMember::ToType(MemberName);

	if (Member == ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		Member = ECsFpsWeaponCacheMultiValueMember::ToType(MemberName);
	}
	SetMemberValue_float(Member, Index, Value);
#endif // #if WITH_EDITOR
}

void ACsFpsWeapon::SetMultiValueMembers()
{
	Super::SetMultiValueMembers();

	// Movement
	{
		// DoSlowWhileFiring
		SetMemberMultiRefValue<bool>(DoSlowWhileFiring, MovementDataFireMode, TEXT("DoSlowWhileFiring"));
		// SlowWhileFiringRate
		SetMemberMultiRefValue<float>(SlowWhileFiringRate, MovementDataFireMode, TEXT("SlowWhileFiringRate"));
		// DoKickback
		SetMemberMultiRefValue<bool>(DoKickback, MovementDataFireMode, TEXT("DoKickback"));
		// DoKickbackOnGround
		SetMemberMultiRefValue<bool>(DoKickbackOnGround, MovementDataFireMode, TEXT("DoKickbackOnGround"));
		// KickbackStrength
		SetMemberMultiRefValue<float>(KickbackStrength, MovementDataFireMode, TEXT("KickbackStrength"));
	}
	// Aiming
	{
		// MovingSpreadBonus
		SetMemberMultiRefValue<float>(MovingSpreadBonus, AimingDataFireMode, TEXT("MovingSpreadBonus"));
		// JumpSpreadImpulse
		SetMemberMultiRefValue<float>(JumpSpreadImpulse, AimingDataFireMode, TEXT("JumpSpreadImpulse"));
		// ScopeAccuracyBonus
		SetMemberMultiRefValue<float>(ScopeAccuracyBonus, AimingDataFireMode, TEXT("ScopeAccuracyBonus"));
	}
	// Scope
	{
		// DoScopePower
		SetMemberMultiRefValue<bool>(DoScopePower, ScopeDataFireMode, TEXT("DoScopePower"));
		// MaxScopePower
		SetMemberMultiRefValue<float>(MaxScopePower, ScopeDataFireMode, TEXT("MaxScopePower"));
		// ScopePowerGrowthRate
		SetMemberMultiRefValue<float>(ScopePowerGrowthRate, ScopeDataFireMode, TEXT("ScopePowerGrowthRate"));
		// CurrentScopePower
		SetMemberMultiValue<float>(CurrentScopePower, 0.0f);
	}
}

#pragma endregion Set

	// Get
#pragma region

bool ACsFpsWeapon::GetMemberValue_bool(const uint8 &Member, const int32 &Index)
{
	if (Member < ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		return GetMemberValue_bool((TCsWeaponCacheMultiValueMember)Member, Index);
	}
	else
	{
		const TCsFpsWeaponCacheMultiValueMember MemberType = (TCsFpsWeaponCacheMultiValueMember)Member;

		// Firing
		{
			// Scope
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::DoScopePower) { return DoScopePower.Get(Index); }
		}
		// Movement
		{
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::DoSlowWhileFiring) { return DoSlowWhileFiring.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::DoKickback) { return DoKickback.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::DoKickbackOnGround) { return DoKickbackOnGround.Get(Index); }
		}
	}
	return false;
}

bool ACsFpsWeapon::GetMemberValue_Script_bool(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	uint8 Member = (uint8)ECsWeaponCacheMultiValueMember::ToType(MemberName);

	if (Member == ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		Member = ECsFpsWeaponCacheMultiValueMember::ToType(MemberName);
	}
	return GetMemberValue_bool(Member, Index);
#endif // #if WITH_EDITOR
	return false;
}

float ACsFpsWeapon::GetMemberValue_float(const uint8 &Member, const int32 &Index)
{
	if (Member < ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		return GetMemberValue_float((TCsWeaponCacheMultiValueMember)Member, Index);
	}
	else
	{
		const TCsFpsWeaponCacheMultiValueMember MemberType = (TCsFpsWeaponCacheMultiValueMember)Member;

		// Firing
		{
			// Spread
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::MovingSpreadBonus) { return MovingSpreadBonus.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::JumpSpreadImpulse) { return JumpSpreadImpulse.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::ScopeAccuracyBonus) { return ScopeAccuracyBonus.Get(Index); }
			// Scope
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::MaxScopePower) { return MaxScopePower.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::ScopePowerGrowthRate) { return ScopePowerGrowthRate.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::CurrentScopePower) { return CurrentScopePower.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::LastScopePower) { return LastScopePower.Get(Index); }
		}
		// Movement
		{
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::SlowWhileFiringRate) { return SlowWhileFiringRate.Get(Index); }
			if (MemberType == ECsFpsWeaponCacheMultiValueMember::KickbackStrength) { return KickbackStrength.Get(Index); }
		}
	}
	return 0.0f;
}

float ACsFpsWeapon::GetMemberValue_Script_float(const FString &MemberName, const int32 &Index)
{
#if WITH_EDITOR
	uint8 Member = (uint8)ECsWeaponCacheMultiValueMember::ToType(MemberName);

	if (Member == ECS_WEAPON_CACHE_MULTI_VALUE_MEMBER_MAX)
	{
		Member = ECsFpsWeaponCacheMultiValueMember::ToType(MemberName);
	}
	return GetMemberValue_float(Member, Index);
#endif // #if WITH_EDITOR
	return 0.0f;
}

#pragma endregion Get

#pragma endregion Members

// Owner
#pragma region

void ACsFpsWeapon::AttachMeshToPawn()
{
	ACsData_Character* Data_Character	  = nullptr;
	const TCsViewType ViewType			  = GetCurrentViewType();
	USkeletalMeshComponent* CharacterMesh = GetCharacterMesh(ViewType);

#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
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

	// 1P
	if (ViewType == ECsViewType::FirstPerson)
	{
#if WITH_EDITOR 
		// In Editor Preview Window
		if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
		{
			Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
			Mesh1P->SetOnlyOwnerSee(false);
			Mesh1P->SetOwnerNoSee(false);
		}
#endif // #if WITH_EDITOR

		Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		SetRootComponent(Mesh1P);

		if (IsEquipped)
		{
			Mesh1P->SetHiddenInGame(false);
			Mesh1P->SetVisibility(true);
		}

		Mesh1P->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponBone);
		//Mesh1P->SetAnimInstanceClass(WeaponData->AnimBlueprints.Blueprint1P);
		//MeleeAttachment1P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, MeleeAttachmentPoint);

		if (IsEquipped)
		{
			Mesh1P->Activate();
			Mesh1P->SetComponentTickEnabled(true);
			Mesh1P->UpdateComponentToWorld(EUpdateTransformFlags::None, ETeleportType::None);
		}
		Mesh3P->SetHiddenInGame(true);
	}
	// 3P
	if (ViewType == ECsViewType::ThirdPerson)
	{
#if WITH_EDITOR 
		// In Editor Preview Window
		if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
		{
			Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
			Mesh3P->SetOnlyOwnerSee(false);
			Mesh3P->SetOwnerNoSee(false);
		}
#endif // #if WITH_EDITOR

		Mesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		SetRootComponent(Mesh3P);

		if (IsEquipped)
		{
			Mesh3P->SetHiddenInGame(false);
			Mesh3P->SetVisibility(true);
			Mesh3P->SetCastShadow(true);
		}
		Mesh3P->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponBone);
		//MeleeAttachment3P->AttachToComponent(PawnMesh1P, FAttachmentTransformRules::KeepRelativeTransform, MeleeAttachmentPoint);

		if (IsEquipped)
		{
			Mesh3P->Activate();
			Mesh3P->SetComponentTickEnabled(true);
			Mesh3P->UpdateComponentToWorld(EUpdateTransformFlags::None, ETeleportType::None);
		}
		Mesh1P->SetHiddenInGame(true);
	}
}

USkeletalMeshComponent* ACsFpsWeapon::GetCharacterMesh(const TEnumAsByte<ECsViewType::Type> &ViewType)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
			return AnimInstance->GetSkeletalMeshComponent();
	}
	else
#endif // #if WITH_EDITOR
	{
		ACsFpsPawn* Pawn = GetMyPawn<ACsFpsPawn>();

		if (MyOwnerType == PawnWeaponOwner)
			return ViewType == ECsViewType::FirstPerson ? Cast<USkeletalMeshComponent>(Pawn->Mesh1P) : Pawn->GetMesh();
	}
	return nullptr;
}

#pragma endregion Owner

// State
#pragma region

void ACsFpsWeapon::OnTick(const float &DeltaSeconds)
{
#if WITH_EDITOR 
	if (Override_OnTick_ScriptEvent.IsBound())
	{
		if (CsCVarLogOverrideFunctions->GetInt() == CS_CVAR_DISPLAY)
		{
			UE_LOG(LogCs, Warning, TEXT("ACsFpsWeapon::OnTick (%s): Using Override Function."), *GetName());
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
		const float TimeSeconds = GetWorld()->GetTimeSeconds();

		ACsPawn* MyPawn = GetMyPawn();

		// Spread
		for (uint8 I = 0; I < WEAPON_FIRE_MODE_MAX; ++I)
		{
			const TCsWeaponFireMode FireMode = (TCsWeaponFireMode)I;

			if (DoSpread.Get(I))
			{
				// Jumping
				if (!Last_OwnerIsFalling && MyPawn->GetCharacterMovement()->IsFalling())
				{
					CurrentBaseSpread.Add(CS_WEAPON_DATA_VALUE, JumpSpreadImpulse.Get(I));
				}
				Last_OwnerIsFalling = MyPawn->GetCharacterMovement()->IsFalling();
				// Firing
				if (TimeSeconds - LastSpreadFireTime.Get(I) > FiringSpreadRecoveryDelay.Get(I))
				{
					CurrentBaseSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Max(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE) - (SpreadRecoveryRate.GetEX(FireMode) * DeltaSeconds), MinSpread.GetEX(FireMode)));
				}
				// Moving
				const float MovingThreshold = 0.5f;
				const bool IsMoving			= MyPawn->CurrentSpeed > MovingThreshold;
				float Bonus					= IsMoving ? MovingSpreadBonus.Get(I) : 0.f;
				Bonus					   -= IsScopeActive ? ScopeAccuracyBonus.Get(I) : 0.f;
				CurrentSpread.Set(CS_WEAPON_DATA_VALUE, FMath::Clamp(CurrentBaseSpread.Get(CS_WEAPON_DATA_VALUE) + Bonus, 0.f, MaxSpread.Get(I)));
			}
		}
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponIndex, DeltaSeconds);
#endif // #if WITH_EDITOR

	OnTick_HandleStates();

	Last_IsFirePressed = IsFirePressed;
}

void ACsFpsWeapon::Disable()
{
	Super::Disable();

	IsScopeActive = false;
	IsScopeActive_Toggle = false;
}

void ACsFpsWeapon::Show()
{
	const TCsViewType ViewType = GetCurrentViewType();

	Mesh1P->SetHiddenInGame(ViewType != ECsViewType::FirstPerson);
	Mesh1P->SetVisibility(ViewType == ECsViewType::FirstPerson);
	Mesh1P->SetComponentTickEnabled(ViewType == ECsViewType::FirstPerson);

	// 1P
	if (ViewType == ECsViewType::FirstPerson)
	{
		Mesh1P->Activate();
		Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
		Mesh1P->UpdateComponentToWorld();
	}

	// 3P
	if (ViewType == ECsViewType::ThirdPerson ||
		Role == ROLE_Authority)
	{
		if (ViewType == ECsViewType::ThirdPerson)
		{
			Mesh3P->SetHiddenInGame(false);
			Mesh3P->SetVisibility(true);
		}
		Mesh3P->Activate();
		Mesh3P->SetComponentTickEnabled(true);
		Mesh3P->UpdateComponentToWorld();
	}
}

void ACsFpsWeapon::Hide()
{
	// 1P
	Mesh1P->SetHiddenInGame(true);
	Mesh1P->SetVisibility(false);
	Mesh1P->Deactivate();
	Mesh1P->SetComponentTickEnabled(false);
	//Cast<UCsAnimInstance>(Mesh1P->GetAnimInstance())->StopAllMontagesEX(0.0f);
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	// 3P
	Mesh3P->SetHiddenInGame(true);
	Mesh3P->SetVisibility(false);
	Mesh3P->Deactivate();
	Mesh3P->SetComponentTickEnabled(false);
	//Cast<UCsAnimInstance>(Mesh3P->GetAnimInstance())->StopAllMontagesEX(0.0f);
	Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
}

#pragma endregion State

// Mesh
#pragma region

void ACsFpsWeapon::SetMesh()
{
	const TCsViewType ViewType = GetCurrentViewType();

	// 1P
	if (ViewType == ECsViewType::FirstPerson)
		SetMesh1P();
	// 3P
	if (ViewType == ECsViewType::ThirdPerson)
		SetMesh3P();
}

void ACsFpsWeapon::SetMesh1P()
{
	Mesh1P->SetAnimInstanceClass(nullptr);

	ACsData_Weapon* Data_Weapon = GetMyData_Weapon();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsCommon::IsPlayInEditorPreview(GetWorld()))
	{
		USkeletalMeshComponent* Mesh = nullptr;

		// Character
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
		{
			Mesh = Mesh1P;

			Data_Weapon->SetMesh(Mesh, ECsViewType::FirstPerson);
			Data_Weapon->SetAnimBlueprint(Mesh, ECsViewType::FirstPerson);
		}
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = GetMyOwner<UCsAnimInstance_Weapon>())
			Mesh = AnimInstance->GetSkeletalMeshComponent();

		if (!Mesh)
			return;

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
		USkeletalMeshComponent* Mesh = nullptr;

		// Character
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
		{
			Mesh = Mesh3P;

			Data_Weapon->SetMesh(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);
			Data_Weapon->SetAnimBlueprint(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);
		}
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = GetMyOwner<UCsAnimInstance_Weapon>())
			Mesh = AnimInstance->GetSkeletalMeshComponent();

		if (!Mesh)
			return;

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
		// Character
		if (UCsAnimInstance_Character* AnimInstance = GetMyOwner<UCsAnimInstance_Character>())
		{
			if (ViewType == ECsViewType::FirstPerson)
				return Mesh1P;
			if (ViewType == ECsViewType::ThirdPerson)
				return Mesh3P;
		}
		// Weapon
		if (UCsAnimInstance_Weapon* AnimInstance = GetMyOwner<UCsAnimInstance_Weapon>())
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

// Firing
#pragma region

FVector ACsFpsWeapon::GetMuzzleLocation(const TCsViewType &ViewType, const TCsWeaponFireMode &FireMode)
{
	return GetMyData_Weapon<ACsData_ProjectileWeapon>()->GetMuzzleLocation(GetMesh(ViewType), ViewType, FireMode, CurrentProjectilePerShotIndex.Get(FireMode));
}

float ACsFpsWeapon::GetMovingSpreadBonus(const TCsWeaponFireMode &FireMode) { return MovingSpreadBonus.Get(FireMode); }
float ACsFpsWeapon::GetJumpSpreadImpulse(const TCsWeaponFireMode &FireMode) { return JumpSpreadImpulse.Get(FireMode); }
float ACsFpsWeapon::GetScopeAccuracyBonus(const TCsWeaponFireMode &FireMode) { return ScopeAccuracyBonus.Get(FireMode); }
float ACsFpsWeapon::GetMaxScopePower(const TCsWeaponFireMode &FireMode) { return MaxScopePower.Get(FireMode); }
float ACsFpsWeapon::GetScopePowerGrowthRate(const TCsWeaponFireMode &FireMode) { return ScopePowerGrowthRate.Get(FireMode); }

void ACsFpsWeapon::FireProjectile_Internal(const TCsWeaponFireMode &FireMode, FCsProjectileFirePayload* Payload)
{
	ACsPawn* MyPawn = GetMyPawn();

	// Scope
	if (DoScopePower.Get(FireMode))
	{
		LastScopePower.Set(FireMode, CurrentScopePower.Get(FireMode));
		CurrentScopePower.Set(FireMode, 0.f);

		ScopeActiveStartTime = GetWorld()->TimeSeconds;
	}
	// Kickback
	if (DoKickback.Get(FireMode))
	{
		if (MyPawn->GetCharacterMovement()->IsFalling() || DoKickbackOnGround.Get(FireMode))
		{
			//KickbackPlayer(FireMode, -ShootDir);
		}
	}
}

#pragma endregion Firing