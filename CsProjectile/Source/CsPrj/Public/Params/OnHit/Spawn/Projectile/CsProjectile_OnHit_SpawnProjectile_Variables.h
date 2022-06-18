// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"

// NCsProjectile::NData::NOnHit::NSpawn::NProjectile::IProjectile
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NData, NOnHit, NSpawn, NProjectile, IProjectile)

class UObject;

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NVariables
				{
					struct CSPRJ_API FVariables
					{
					public:

					#define SpawnProjectileOnHitDataType NCsProjectile::NData::NOnHit::NSpawn::NProjectile::IProjectile
					#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

						UObject* Instigator;

						UObject* Owner;

						FVector Location;

						FVector Direction;

						SpawnProjectileOnHitDataType* SpawnProjectileOnHitData;
						
						AActor* OtherActor;

						UPrimitiveComponent* OtherComp;

						TArray<AllocatedModifierType> Modifiers;

						FVariables() :
							Instigator(nullptr),
							Owner(nullptr),
							Location(0.0f),
							Direction(0.0f),
							SpawnProjectileOnHitData(nullptr),
							OtherActor(nullptr),
							OtherComp(nullptr),
							Modifiers()
						{
						}

						FORCEINLINE void Reset()
						{
							Instigator = nullptr;
							Owner = nullptr;
							Location = FVector::ZeroVector;
							Direction = FVector::ZeroVector;
							SpawnProjectileOnHitData = nullptr;
							OtherActor = nullptr;
							OtherComp = nullptr;

							Modifiers.Reset(Modifiers.Max());
						}

					#undef SpawnProjectileOnHitDataType
					#undef AllocatedModifierType
					};

					struct CSPRJ_API FResource final : public TCsResourceContainer<FVariables>
					{
					};

					struct CSPRJ_API FManager final : public NCsResource::NManager::NValue::TFixed<FVariables, FResource, 0>
					{
					};
				}
			}
		}
	}
}