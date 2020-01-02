// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileBase.h"
#include "CsCore.h"

// Data
#include "Data/CsData_ProjectileImpact.h"

UCsData_ProjectileBase::UCsData_ProjectileBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultCollisionResponseContainer = FCollisionResponseContainer(ECR_Ignore);
}

void UCsData_ProjectileBase::Load(const ECsLoadFlags& LoadFlags /*=ECsLoadFlags::All*/)
{
	Super::Load(LoadFlags);
	
	if (UCsData_ProjectileImpact* Data = GetData_Impact())
		Data->Load(LoadFlags);
}

const FECsProjectile& UCsData_ProjectileBase::GetProjectileType() { return EMCsProjectile::Get().GetMAX(); }

// Stats
#pragma region


const FName& UCsData_ProjectileBase::GetItemShortCode() { return NCsCached::Name::None; }

const bool& UCsData_ProjectileBase::GetOnAllocateDropItem() { return NCsCached::Ref::False;  }
const bool& UCsData_ProjectileBase::GetOnAllocateConsumeItem() { return NCsCached::Ref::False; }

const float& UCsData_ProjectileBase::GetLifeTime() { return NCsCached::Ref::Float; }
const float& UCsData_ProjectileBase::GetMaxRange() { return NCsCached::Ref::Float; }

#pragma endregion Stats

// Movement
#pragma region

ECsProjectileMovement UCsData_ProjectileBase::GetMovementType() { return ECsProjectileMovement::Simulated; }
FVector UCsData_ProjectileBase::EvaluateMovementFunction(const float& Time, const FVector& Location, const FTransform& Transform) { return Location; }

const float& UCsData_ProjectileBase::GetInitialSpeed() { return NCsCached::Ref::Float; }
const float& UCsData_ProjectileBase::GetMaxSpeed() { return NCsCached::Ref::Float; }
const float& UCsData_ProjectileBase::GetGravityMultiplier() { return NCsCached::Ref::Float; }

#pragma endregion Movement

// Damage
#pragma region

const int32& UCsData_ProjectileBase::GetDamage() { return NCsCached::Ref::SInt; }
const bool& UCsData_ProjectileBase::CanDamageFalloff() { return NCsCached::Ref::False; }
float UCsData_ProjectileBase::GetDamageFalloff(const float &Distance) { return 1.0f; }
const bool& UCsData_ProjectileBase::CanDamageRadial() { return NCsCached::Ref::False; }
float UCsData_ProjectileBase::GetDamageRadial(const FVector& Origin, const FVector& Location) { return 0.0f; }

#pragma endregion Damage

// Mesh
#pragma region

UStaticMesh* UCsData_ProjectileBase::GetMesh(const ECsViewType& ViewType) { return nullptr; }
float UCsData_ProjectileBase::GetDrawDistance(const ECsViewType& ViewType) { return 3000.0f; }
float UCsData_ProjectileBase::GetDrawDistanceSq(const ECsViewType& ViewType) { return GetDrawDistance(ViewType) * GetDrawDistance(ViewType); }

#pragma endregion Mesh

// Transform
#pragma region

const FTransform& UCsData_ProjectileBase::GetMyTransform() { return FTransform::Identity; }

#pragma endregion Transform

// Collision
#pragma region

TEnumAsByte<ECollisionEnabled::Type> UCsData_ProjectileBase::GetCollisionEnabled() { return ECollisionEnabled::NoCollision; }
TEnumAsByte<ECollisionChannel> UCsData_ProjectileBase::GetCollisionObjectType() { return ECollisionChannel::ECC_MAX; }
FCollisionResponseContainer& UCsData_ProjectileBase::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }
const float& UCsData_ProjectileBase::GetSphereRadius() { return NCsCached::Ref::Float; }

#pragma endregion Collision

// FX
#pragma region

const bool& UCsData_ProjectileBase::GetUseTrailFX() { return NCsCached::Ref::False; }
FCsFxElement* UCsData_ProjectileBase::GetTrailFX(const ECsViewType& ViewType) { return nullptr; }

#pragma endregion FX

// Impact
#pragma region

UCsData_ProjectileImpact* UCsData_ProjectileBase::GetData_Impact() { return nullptr; }

#pragma endregion Impact