// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Weapon/CsFpsWeapon.h"
#include "CsCore.h"
#include "CsCVars.h"
#include "Library/CsLibrary_Common.h"

#include "Player/CsFpsPawn.h"
#include "Animation/CsAnimInstance_Character.h"
#include "Animation/CsAnimInstance_Weapon.h"

// Data
#include "Data/CsData_ProjectileWeapon.h"
#include "Data/CsData_Character.h"
#include "Data/CsData_WeaponMaterialSkin.h"
// Components
#include "Components/CsSkeletalMeshComponent.h"

// Enums
#pragma region

namespace ECsFpsWeaponMultiValueMember
{
	// Spread
	CSCORE_API const FECsWeaponMultiValueMember MovingSpreadBonus = EMCsWeaponMultiValueMember::Get().Create(TEXT("MovingSpreadBonus"));
	CSCORE_API const FECsWeaponMultiValueMember JumpSpreadImpulse = EMCsWeaponMultiValueMember::Get().Create(TEXT("JumpSpreadImpulse"));
	CSCORE_API const FECsWeaponMultiValueMember ScopeAccuracyBonus = EMCsWeaponMultiValueMember::Get().Create(TEXT("ScopeAccuracyBonus"));
	// Scope
	CSCORE_API const FECsWeaponMultiValueMember DoScopePower = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoScopePower"));
	CSCORE_API const FECsWeaponMultiValueMember MaxScopePower = EMCsWeaponMultiValueMember::Get().Create(TEXT("MaxScopePower"));
	CSCORE_API const FECsWeaponMultiValueMember ScopePowerGrowthRate = EMCsWeaponMultiValueMember::Get().Create(TEXT("ScopePowerGrowthRate"));
	CSCORE_API const FECsWeaponMultiValueMember CurrentScopePower = EMCsWeaponMultiValueMember::Get().Create(TEXT("CurrentScopePower"));
	CSCORE_API const FECsWeaponMultiValueMember LastScopePower = EMCsWeaponMultiValueMember::Get().Create(TEXT("LastScopePower"));
	// Movement
	CSCORE_API const FECsWeaponMultiValueMember DoSlowWhileFiring = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoSlowWhileFiring"));
	CSCORE_API const FECsWeaponMultiValueMember SlowWhileFiringRate = EMCsWeaponMultiValueMember::Get().Create(TEXT("SlowWhileFiringRate"));
	CSCORE_API const FECsWeaponMultiValueMember DoKickback = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoKickback"));
	CSCORE_API const FECsWeaponMultiValueMember DoKickbackOnGround = EMCsWeaponMultiValueMember::Get().Create(TEXT("DoKickbackOnGround"));
	CSCORE_API const FECsWeaponMultiValueMember KickbackStrength = EMCsWeaponMultiValueMember::Get().Create(TEXT("KickbackStrength"));
}

#pragma endregion Enums

ACsFpsWeapon::ACsFpsWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh1P"));
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
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
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
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

	// Spread
	{
		InitMultiRefValueMember<float>(MovingSpreadBonus, 0.0f);
		MovingSpreadBonus.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetMovingSpreadBonus);
		InitMultiRefValueMember<float>(JumpSpreadImpulse, 0.0f);
		JumpSpreadImpulse.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetJumpSpreadImpulse);
		InitMultiRefValueMember<float>(ScopeAccuracyBonus, 0.0f);
		ScopeAccuracyBonus.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetScopeAccuracyBonus);
	}
	// Scope
	{
		InitMultiRefValueMember<bool>(DoScopePower, false);
		InitMultiRefValueMember<float>(MaxScopePower, 0.0f);
		MaxScopePower.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetMaxScopePower);
		InitMultiRefValueMember<float>(ScopePowerGrowthRate, 0.0f);
		ScopePowerGrowthRate.GetDelegate.BindUObject(this, &ACsFpsWeapon::GetScopePowerGrowthRate);
		InitMultiValueMember<float>(CurrentScopePower, 0.0f);
		InitMultiValueMember<float>(LastScopePower, 0.0f);
	}
	// Movement
	{
		InitMultiRefValueMember<bool>(DoSlowWhileFiring, false);
		InitMultiRefValueMember<float>(SlowWhileFiringRate, 0.0f);
		InitMultiRefValueMember<bool>(DoKickback, false);
		InitMultiRefValueMember<bool>(DoKickbackOnGround, false);
		InitMultiRefValueMember<float>(KickbackStrength, 0.0f);
	}
}

	// Set
#pragma region

void ACsFpsWeapon::SetMemberValue_float(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode, const float &Value)
{
	if (Member.Value < ECsFpsWeaponMultiValueMember::MovingSpreadBonus.Value)
	{
		Super::SetMemberValue_float(Member, FireMode, Value);
	}
	else
	{
		// Firing
		{
			// Scope
			if (Member == ECsFpsWeaponMultiValueMember::CurrentScopePower) { CurrentScopePower.Set(FireMode, Value); }
			if (Member == ECsFpsWeaponMultiValueMember::LastScopePower) { CurrentScopePower.Set(FireMode, Value); }
		}
	}
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

bool ACsFpsWeapon::GetMemberValue_bool(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	if (Member.Value < ECsFpsWeaponMultiValueMember::MovingSpreadBonus.Value)
	{
		return GetMemberValue_bool(Member, FireMode);
	}
	else
	{
		// Firing
		{
			// Scope
			if (Member == ECsFpsWeaponMultiValueMember::DoScopePower) { return DoScopePower[FireMode]; }
		}
		// Movement
		{
			if (Member == ECsFpsWeaponMultiValueMember::DoSlowWhileFiring) { return DoSlowWhileFiring[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::DoKickback) { return DoKickback[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::DoKickbackOnGround) { return DoKickbackOnGround[FireMode]; }
		}
	}
	return false;
}

float ACsFpsWeapon::GetMemberValue_float(const FECsWeaponMultiValueMember& Member, const FECsWeaponFireMode& FireMode)
{
	if (Member.Value < ECsFpsWeaponMultiValueMember::MovingSpreadBonus.Value)
	{
		return GetMemberValue_float(Member, FireMode);
	}
	else
	{
		// Firing
		{
			// Spread
			if (Member == ECsFpsWeaponMultiValueMember::MovingSpreadBonus) { return MovingSpreadBonus[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::JumpSpreadImpulse) { return JumpSpreadImpulse[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::ScopeAccuracyBonus) { return ScopeAccuracyBonus[FireMode]; }
			// Scope
			if (Member == ECsFpsWeaponMultiValueMember::MaxScopePower) { return MaxScopePower[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::ScopePowerGrowthRate) { return ScopePowerGrowthRate[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::CurrentScopePower) { return CurrentScopePower[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::LastScopePower) { return LastScopePower[FireMode]; }
		}
		// Movement
		{
			if (Member == ECsFpsWeaponMultiValueMember::SlowWhileFiringRate) { return SlowWhileFiringRate[FireMode]; }
			if (Member == ECsFpsWeaponMultiValueMember::KickbackStrength) { return KickbackStrength[FireMode]; }
		}
	}
	return 0.0f;
}

#pragma endregion Get

#pragma endregion Members

// Owner
#pragma region

void ACsFpsWeapon::AttachMeshToPawn()
{
	UCsData_Character* Data_Character	  = nullptr;
	const ECsViewType ViewType			  = GetCurrentViewType();
	USkeletalMeshComponent* CharacterMesh = GetCharacterMesh(ViewType);

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

	// 1P
	if (ViewType == ECsViewType::FirstPerson)
	{
#if WITH_EDITOR 
		// In Editor Preview Window
		if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		{
			Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
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
		if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
		{
			Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
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

USkeletalMeshComponent* ACsFpsWeapon::GetCharacterMesh(const ECsViewType& ViewType)
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
		const float TimeSeconds = GetWorld()->GetTimeSeconds();

		ACsPawn* MyOwnerAsPawn = GetMyPawn();

		// Spread
		const int32& Count = EMCsWeaponFireMode::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsWeaponFireMode& FireMode = EMCsWeaponFireMode::Get().GetEnumAt(I);

			if (DoSpread[FireMode])
			{
				// Jumping
				if (!Last_OwnerIsFalling && MyOwnerAsPawn->GetCharacterMovement()->IsFalling())
				{
					CurrentBaseSpread.Add(FireMode, JumpSpreadImpulse[FireMode]);
				}
				Last_OwnerIsFalling = MyOwnerAsPawn->GetCharacterMovement()->IsFalling();
				// Firing
				if (TimeSeconds - LastSpreadFireTime[FireMode] > FiringSpreadRecoveryDelay[FireMode])
				{
					CurrentBaseSpread.Set(FireMode, FMath::Max(CurrentBaseSpread[FireMode] - (SpreadRecoveryRate.GetEX(FireMode) * DeltaSeconds), MinSpread.GetEX(FireMode)));
				}
				// Moving
				const float MovingThreshold = 0.5f;
				const bool IsMoving			= MyOwnerAsPawn->CurrentSpeed > MovingThreshold;
				float Bonus					= IsMoving ? MovingSpreadBonus[FireMode]: 0.f;
				Bonus					   -= IsScopeActive ? ScopeAccuracyBonus[FireMode]: 0.f;
				CurrentSpread.Set(FireMode, FMath::Clamp(CurrentBaseSpread[FireMode] + Bonus, 0.f, MaxSpread[FireMode]));
			}
		}
	}

#if WITH_EDITOR 
	OnTick_ScriptEvent.Broadcast(WeaponSlot, DeltaSeconds);
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
	const ECsViewType ViewType = GetCurrentViewType();

	Mesh1P->SetHiddenInGame(ViewType != ECsViewType::FirstPerson);
	Mesh1P->SetVisibility(ViewType == ECsViewType::FirstPerson);
	Mesh1P->SetComponentTickEnabled(ViewType == ECsViewType::FirstPerson);

	// 1P
	if (ViewType == ECsViewType::FirstPerson)
	{
		Mesh1P->Activate();
		Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
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
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	// 3P
	Mesh3P->SetHiddenInGame(true);
	Mesh3P->SetVisibility(false);
	Mesh3P->Deactivate();
	Mesh3P->SetComponentTickEnabled(false);
	//Cast<UCsAnimInstance>(Mesh3P->GetAnimInstance())->StopAllMontagesEX(0.0f);
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
}

#pragma endregion State

// Mesh
#pragma region

void ACsFpsWeapon::SetMesh()
{
	const ECsViewType ViewType = GetCurrentViewType();

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

	UCsData_Weapon* Data_Weapon = GetMyData_Weapon();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh, ECsViewType::FirstPerson);
			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs1P, *Skin->GetMaterials(ECsViewType::FirstPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::FirstPerson);

			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs1P, Materials);
		}
		return;
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh1P, ECsViewType::FirstPerson);
		Data_Weapon->SetAnimBlueprint(Mesh1P, ECsViewType::FirstPerson);

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh1P, ECsViewType::FirstPerson);
			UCsLibrary_Common::SetMIDs(Mesh1P, MeshMIDs1P, *Skin->GetMaterials(ECsViewType::FirstPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::FirstPerson);

			UCsLibrary_Common::SetMIDs(Mesh1P, MeshMIDs1P, Materials);
		}
		//Mesh1P->SetRelativeScale3D(Data_Weapon->Mesh1PScale);
	}
}

void ACsFpsWeapon::SetMesh3P()
{
	Mesh3P->SetAnimInstanceClass(nullptr);

	UCsData_Weapon* Data_Weapon = GetMyData_Weapon();

#if WITH_EDITOR
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh, ECsViewType::ThirdPerson);
			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs3P, *Skin->GetMaterials(ECsViewType::ThirdPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::ThirdPerson);

			UCsLibrary_Common::SetMIDs(Mesh, MeshMIDs3P, Materials);
		}
		return;
	}
	// In Game
#endif // #if WITH_EDITOR
	{
		Data_Weapon->SetMesh(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);
		Data_Weapon->SetAnimBlueprint(Mesh3P, ECsViewType::ThirdPerson, UseMesh3PLow);

		if (UCsData_WeaponMaterialSkin* Skin = GetMyData_WeaponMaterialSkin())
		{
			Skin->SetMaterials(Mesh3P, ECsViewType::ThirdPerson);
			UCsLibrary_Common::SetMIDs(Mesh3P, MeshMIDs3P, *Skin->GetMaterials(ECsViewType::ThirdPerson));
		}
		else
		{
			TArray<UMaterialInstanceConstant*> Materials;
			Data_Weapon->GetDefaultMaterials(Materials, ECsViewType::ThirdPerson);

			UCsLibrary_Common::SetMIDs(Mesh3P, MeshMIDs3P, Materials);
		}
		//Mesh3P->SetRelativeScale3D(WeaponData->Mesh3PScale);
		Mesh3P->SetCastShadow(false);
	}
}

USkeletalMeshComponent* ACsFpsWeapon::GetMesh(const ECsViewType& ViewType)
{
#if WITH_EDITOR 
	// In Editor Preview Window
	if (UCsLibrary_Common::IsPlayInEditorPreview(GetWorld()))
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

FVector ACsFpsWeapon::GetMuzzleLocation(const ECsViewType& ViewType, const FECsWeaponFireMode& FireMode)
{
	return GetMyData_Weapon<UCsData_ProjectileWeapon>()->GetMuzzleLocation(GetMesh(ViewType), ViewType, FireMode, CurrentProjectilePerShotIndex.Get(FireMode));
}

float ACsFpsWeapon::GetMovingSpreadBonus(const FECsWeaponFireMode& FireMode) { return MovingSpreadBonus.Get(FireMode); }
float ACsFpsWeapon::GetJumpSpreadImpulse(const FECsWeaponFireMode& FireMode) { return JumpSpreadImpulse.Get(FireMode); }
float ACsFpsWeapon::GetScopeAccuracyBonus(const FECsWeaponFireMode& FireMode) { return ScopeAccuracyBonus.Get(FireMode); }
float ACsFpsWeapon::GetMaxScopePower(const FECsWeaponFireMode& FireMode) { return MaxScopePower.Get(FireMode); }
float ACsFpsWeapon::GetScopePowerGrowthRate(const FECsWeaponFireMode& FireMode) { return ScopePowerGrowthRate.Get(FireMode); }

void ACsFpsWeapon::FireProjectile_Internal(const FECsWeaponFireMode& FireMode, FCsProjectileFirePayload* Payload)
{
	ACsPawn* MyOwnerAsPawn = GetMyPawn();

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
		if (MyOwnerAsPawn->GetCharacterMovement()->IsFalling() || DoKickbackOnGround.Get(FireMode))
		{
			//KickbackPlayer(FireMode, -ShootDir);
		}
	}
}

#pragma endregion Firing