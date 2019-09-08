#include "Player/CsFpsPawn.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

// Component
#include "Components/CsSkeletalMeshComponent.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/CsData_WeaponMaterialSkin.h"

#include "Player/CsPlayerState.h"
#include "Weapon/CsGunWeapon.h"

ACsFpsPawn::ACsFpsPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = true;
	/*
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	*/

	Eye = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Eye"));
	Eye->SetupAttachment(GetCapsuleComponent());
	Eye->SetHiddenInGame(false);
	Eye->SetVisibility(true);
	Eye->SetMobility(EComponentMobility::Movable);

	Mesh1P = ObjectInitializer.CreateDefaultSubobject<UCsSkeletalMeshComponent>(this, TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(Eye);
	Mesh1P->SetHiddenInGame(true);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Mesh1P->SetCollisionObjectType(ECC_Pawn);
	Mesh1P->KinematicBonesUpdateType = EKinematicBonesUpdateToPhysics::SkipAllBones;
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh1P->SetGenerateOverlapEvents(false);
	Mesh1P->Deactivate();
	/*
	GetMesh()->SetHiddenInGame(true);
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	GetMesh()->ClothTickFunction.bCanEverTick = true;
	GetMesh()->bGenerateOverlapEvents = false;
	GetMesh()->Deactivate();

	GetMesh()->ClothTickFunction.bStartWithTickEnabled = false;
	GetCharacterMovement()->PrimaryComponentTick.bStartWithTickEnabled = false;
	GetCharacterMovement()->bAutoActivate = false;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	*/

	/*
	bAlwaysRelevant		   = true;
	NetDormancy			   = ENetDormancy::DORM_Never;
	NetCullDistanceSquared = FMath::Square(100000);
	*/

	// View
	bPerformViewTrace = true;

	ViewTraceInfo.bAsync = false;
	ViewTraceInfo.bForce = true;
}

void ACsFpsPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// SetNetDormancy(ENetDormancy::DORM_Never);

	Eye->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Eye->SetRelativeTransform(FTransform::Identity);

	//UCsCommon::DisableComponent(Mesh1P, false, true);
	//UCsCommon::DisableComponent(GetMesh(), false, true);
	//GetCharacterMovement()->PrimaryComponentTick.bStartWithTickEnabled = false;

	/*
	FCollisionResponseContainer CapsuleResponseContainer(ECR_Ignore);

	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_Camera, ECR_Ignore);
	//CapsuleResponseContainer.SetResponse(COLLISION_WEAPON, ECR_Ignore);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_Destructible, ECR_Ignore);
	//CapsuleResponseContainer.SetResponse(COLLISION_PROJECTILE, ECR_Ignore);

	//CapsuleResponseContainer.SetResponse(COLLISION_PICKUP, ECR_Overlap);

	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_Visibility, ECR_Block);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_WorldDynamic, ECR_Block);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_Pawn, ECR_Block);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_PhysicsBody, ECR_Block);
	CapsuleResponseContainer.SetResponse(ECollisionChannel::ECC_Vehicle, ECR_Block);
	//CapsuleResponseContainer.SetResponse(COLLISION_TRIGGER, ECR_Overlap);

	GetCapsuleComponent()->SetCollisionResponseToChannels(CapsuleResponseContainer);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->RegisterAllComponentTickFunctions(true);
	GetCapsuleComponent()->SetComponentTickEnabled(true);
	GetCapsuleComponent()->SetActive(true);

	GetMesh()->RegisterAllComponentTickFunctions(true);
	Mesh1P->RegisterAllComponentTickFunctions(true);

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCharacterMovement()->RegisterAllComponentTickFunctions(true);
	GetCharacterMovement()->SetComponentTickEnabled(true);
	GetCharacterMovement()->SetActive(true);
	*/

	//SetActorTickEnabled(true);
}

// View
#pragma region

TEnumAsByte<ECsViewType::Type> ACsFpsPawn::GetCurrentViewType()
{
	return UCsCommon::IsLocalPawn(GetWorld(), this) ? ECsViewType::FirstPerson : ECsViewType::ThirdPerson;
}

#pragma endregion View

// Camera
#pragma region

FVector ACsFpsPawn::GetPawnViewLocation() const
{
	return GetFeetLocation() + FVector(0.0f, 0.0f, EyeHeight);
}

FVector ACsFpsPawn::GetFeetLocation() const
{
	return GetActorLocation() - FVector(0.0f, 0.0f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

#pragma endregion Camera

// Mesh
#pragma region

USkeletalMeshComponent* ACsFpsPawn::GetCurrentMesh()
{
	return UCsCommon::IsLocalPawn(GetWorld(), this) ? Cast<USkeletalMeshComponent>(Mesh1P) : GetMesh();
}

#pragma endregion Mesh

// Weapons
#pragma region

void ACsFpsPawn::ApplyData_Weapon()
{
	for (int32 I = 0; I < CurrentWeaponCount; I++)
	{
		ACsGunWeapon* Weapon = Cast<ACsGunWeapon>(Weapons[I]);

		const FECsWeaponSlot& Slot = EMCsWeaponSlot::Get().GetEnumAt(I);

		ACsData_Weapon* Data_Weapon							= GetData_Weapon(Slot);
		ACsData_WeaponMaterialSkin* Data_WeaponMaterialSkin = GetData_WeaponMaterialSkin(Slot);

		Weapon->ApplyData_Weapon(Slot, Data_Weapon, Data_WeaponMaterialSkin, CurrentWeaponIndex == I);
	}
}

#pragma endregion Weapons