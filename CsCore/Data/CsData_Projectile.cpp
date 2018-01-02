// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
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

TCsProjectileType ACsData_Projectile::GetBaseProjectileType() { return ProjectileType_Internal; }

// Stats
#pragma region

float ACsData_Projectile::GetLifeTime() { return 0.0f; }

#pragma endregion Stats

// Movement
#pragma region

float ACsData_Projectile::GetInitialSpeed() { return 0.0f; }
float ACsData_Projectile::GetMaxSpeed() { return 0.0f; }
float ACsData_Projectile::GetGravityMultiplier() { return 0.0f; }

#pragma endregion Movement

// Damage
#pragma region

int32 ACsData_Projectile::GetDamage() { return 0; }
float ACsData_Projectile::GetDamageFalloffRate() { return 0.0f; }
float ACsData_Projectile::GetDamageFalloffFrequency() { return 0.0f; }
float ACsData_Projectile::GetDamageFalloffMinimum() { return 0.0f; }

#pragma endregion Damage

// Mesh
#pragma region

UStaticMesh* ACsData_Projectile::GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType) { return nullptr; }
float ACsData_Projectile::GetDrawDistance(const TEnumAsByte<ECsViewType::Type> &ViewType) { return 3000.0f; }
float ACsData_Projectile::GetDrawDistanceSq(const TEnumAsByte<ECsViewType::Type> &ViewType) { return GetDrawDistance(ViewType) * GetDrawDistance(ViewType); }

#pragma endregion Mesh

// Transform
#pragma region

FTransform ACsData_Projectile::GetTransform() { return FTransform::Identity; }

#pragma endregion Transform

// Collision
#pragma region

TEnumAsByte<ECollisionEnabled::Type> ACsData_Projectile::GetCollisionEnabled() { return ECollisionEnabled::NoCollision; }
TEnumAsByte<ECollisionChannel> ACsData_Projectile::GetCollisionObjectType() { return ECollisionChannel::ECC_MAX; }
FCollisionResponseContainer& ACsData_Projectile::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }
float ACsData_Projectile::GetSphereRadius() { return 0.0f; }

#pragma endregion Collision

// FX
#pragma region

FCsFxElement* ACsData_Projectile::GetTrailFX(const TCsViewType &ViewType) { return nullptr; }

#pragma endregion FX

// Impact
#pragma region

ACsData_ProjectileImpact* ACsData_Projectile::GetData_Impact() { return nullptr; }

#pragma endregion Impact