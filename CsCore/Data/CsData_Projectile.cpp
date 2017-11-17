// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "CsCore.h"

ACsData_Projectile::ACsData_Projectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultCollisionResponseContainer = FCollisionResponseContainer(ECR_Ignore);
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

FCsFxElement* ACsData_Projectile::GetTrailFX() { return nullptr; }

#pragma endregion FX