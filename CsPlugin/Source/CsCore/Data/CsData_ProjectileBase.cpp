// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileBase.h"
#include "CsCore.h"

// Data
#include "Data/CsData_ProjectileImpact.h"

ACsData_ProjectileBase::ACsData_ProjectileBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultCollisionResponseContainer = FCollisionResponseContainer(ECR_Ignore);
}

void ACsData_ProjectileBase::Load(const ECsLoadFlags &LoadFlags /*=ECsLoadFlags::All*/)
{
	Super::Load(LoadFlags);
	
	if (ACsData_ProjectileImpact* Data = GetData_Impact())
		Data->Load(LoadFlags);
}

const FECsProjectileType& ACsData_ProjectileBase::GetProjectileType() { return EMCsProjectileType::Get().GetMAX(); }

// Stats
#pragma region


const FName& ACsData_ProjectileBase::GetItemShortCode() { return NCsCached::Name::None; }

const bool& ACsData_ProjectileBase::GetOnAllocateDropItem() { return NCsCached::Ref::False;  }
const bool& ACsData_ProjectileBase::GetOnAllocateConsumeItem() { return NCsCached::Ref::False; }

const float& ACsData_ProjectileBase::GetLifeTime() { return NCsCached::Ref::Float; }
const float& ACsData_ProjectileBase::GetMaxRange() { return NCsCached::Ref::Float; }

#pragma endregion Stats

// Movement
#pragma region

TEnumAsByte<ECsProjectileMovement::Type> ACsData_ProjectileBase::GetMovementType() { return ECsProjectileMovement::Simulated; }
FVector ACsData_ProjectileBase::EvaluateMovementFunction(const float &Time, const FVector &Location, const FTransform &Transform) { return Location; }

const float& ACsData_ProjectileBase::GetInitialSpeed() { return NCsCached::Ref::Float; }
const float& ACsData_ProjectileBase::GetMaxSpeed() { return NCsCached::Ref::Float; }
const float& ACsData_ProjectileBase::GetGravityMultiplier() { return NCsCached::Ref::Float; }

#pragma endregion Movement

// Damage
#pragma region

const int32& ACsData_ProjectileBase::GetDamage() { return NCsCached::Ref::SInt; }
const bool& ACsData_ProjectileBase::CanDamageFalloff() { return NCsCached::Ref::False; }
float ACsData_ProjectileBase::GetDamageFalloff(const float &Distance) { return 1.0f; }
const bool& ACsData_ProjectileBase::CanDamageRadial() { return NCsCached::Ref::False; }
float ACsData_ProjectileBase::GetDamageRadial(const FVector &Origin, const FVector &Location) { return 0.0f; }

#pragma endregion Damage

// Mesh
#pragma region

UStaticMesh* ACsData_ProjectileBase::GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType) { return nullptr; }
float ACsData_ProjectileBase::GetDrawDistance(const TEnumAsByte<ECsViewType::Type> &ViewType) { return 3000.0f; }
float ACsData_ProjectileBase::GetDrawDistanceSq(const TEnumAsByte<ECsViewType::Type> &ViewType) { return GetDrawDistance(ViewType) * GetDrawDistance(ViewType); }

#pragma endregion Mesh

// Transform
#pragma region

const FTransform& ACsData_ProjectileBase::GetMyTransform() { return FTransform::Identity; }

#pragma endregion Transform

// Collision
#pragma region

TEnumAsByte<ECollisionEnabled::Type> ACsData_ProjectileBase::GetCollisionEnabled() { return ECollisionEnabled::NoCollision; }
TEnumAsByte<ECollisionChannel> ACsData_ProjectileBase::GetCollisionObjectType() { return ECollisionChannel::ECC_MAX; }
FCollisionResponseContainer& ACsData_ProjectileBase::GetCollisionResponseContainer() { return DefaultCollisionResponseContainer; }
const float& ACsData_ProjectileBase::GetSphereRadius() { return NCsCached::Ref::Float; }

#pragma endregion Collision

// FX
#pragma region

const bool& ACsData_ProjectileBase::GetUseTrailFX() { return NCsCached::Ref::False; }
FCsFxElement* ACsData_ProjectileBase::GetTrailFX(const TCsViewType &ViewType) { return nullptr; }

#pragma endregion FX

// Impact
#pragma region

ACsData_ProjectileImpact* ACsData_ProjectileBase::GetData_Impact() { return nullptr; }

#pragma endregion Impact