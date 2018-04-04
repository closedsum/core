// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "CsCore.h"

// Data
#include "Data/CsData_ProjectileImpact.h"

ACsData_Projectile::ACsData_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultCollisionResponseContainer = FCollisionResponseContainer(ECR_Ignore);
}

void ACsData_Projectile::Load(const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::All*/)
{
	Super::Load(LoadFlags);
	
	if (ACsData_ProjectileImpact* Data = GetData_Impact())
		Data->Load(LoadFlags);
}

TCsProjectileType ACsData_Projectile::GetBaseProjectileType() { return BaseProjectileType; }

// Stats
#pragma region


const FName& ACsData_Projectile::GetItemShortCode() { return ECsCachedName::Name::None; }

const bool& ACsData_Projectile::GetOnAllocateDropItem() { return ECsCachedReferences::Ref::False;  }
const bool& ACsData_Projectile::GetOnAllocateConsumeItem() { return ECsCachedReferences::Ref::False; }

const float& ACsData_Projectile::GetLifeTime() { return ECsCachedReferences::Ref::Float; }
const float& ACsData_Projectile::GetMaxRange() { return ECsCachedReferences::Ref::Float; }

#pragma endregion Stats

// Movement
#pragma region

TEnumAsByte<ECsProjectileMovement::Type> ACsData_Projectile::GetMovementType() { return ECsProjectileMovement::Simulated; }
FVector ACsData_Projectile::EvaluateMovementFunction(const float &Time, const FVector &Location, const FTransform &Transform) { return Location; }

const float& ACsData_Projectile::GetInitialSpeed() { return ECsCachedReferences::Ref::Float; }
const float& ACsData_Projectile::GetMaxSpeed() { return ECsCachedReferences::Ref::Float; }
const float& ACsData_Projectile::GetGravityMultiplier() { return ECsCachedReferences::Ref::Float; }

#pragma endregion Movement

// Damage
#pragma region

const int32& ACsData_Projectile::GetDamage() { return ECsCachedReferences::Ref::SInt; }
const bool& ACsData_Projectile::CanDamageFalloff() { return ECsCachedReferences::Ref::False; }
float ACsData_Projectile::GetDamageFalloff(const float &Distance) { return 1.0f; }
const bool& ACsData_Projectile::CanDamageRadial() { return ECsCachedReferences::Ref::False; }
float ACsData_Projectile::GetDamageRadial(const FVector &Origin, const FVector &Location) { return 0.0f; }

#pragma endregion Damage

// Mesh
#pragma region

UStaticMesh* ACsData_Projectile::GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType) { return nullptr; }
float ACsData_Projectile::GetDrawDistance(const TEnumAsByte<ECsViewType::Type> &ViewType) { return 3000.0f; }
float ACsData_Projectile::GetDrawDistanceSq(const TEnumAsByte<ECsViewType::Type> &ViewType) { return GetDrawDistance(ViewType) * GetDrawDistance(ViewType); }

#pragma endregion Mesh

// Transform
#pragma region

const FTransform& ACsData_Projectile::GetTransform() { return FTransform::Identity; }

#pragma endregion Transform

// Collision
#pragma region

TEnumAsByte<ECollisionEnabled::Type> ACsData_Projectile::GetCollisionEnabled() { return ECollisionEnabled::NoCollision; }
TEnumAsByte<ECollisionChannel> ACsData_Projectile::GetCollisionObjectType() { return ECollisionChannel::ECC_MAX; }
FCollisionResponseContainer& ACsData_Projectile::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }
const float& ACsData_Projectile::GetSphereRadius() { return ECsCachedReferences::Ref::Float; }

#pragma endregion Collision

// FX
#pragma region

const bool& ACsData_Projectile::GetUseTrailFX() { return ECsCachedReferences::Ref::False; }
FCsFxElement* ACsData_Projectile::GetTrailFX(const TCsViewType &ViewType) { return nullptr; }

#pragma endregion FX

// Impact
#pragma region

ACsData_ProjectileImpact* ACsData_Projectile::GetData_Impact() { return nullptr; }

#pragma endregion Impact