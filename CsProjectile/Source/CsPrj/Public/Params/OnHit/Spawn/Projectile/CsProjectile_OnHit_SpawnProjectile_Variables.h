// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

						int32 Generation;

						UObject* Instigator;

						UObject* Owner;

						FVector3f Location;

						FVector3f Direction;

						SpawnProjectileOnHitDataType* SpawnProjectileOnHitData;
						
						AActor* OtherActor;

						UPrimitiveComponent* OtherComp;

						TArray<AllocatedModifierType> Modifiers;

						FVariables() :
							Generation(0),
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
							Generation = 0;
							Instigator = nullptr;
							Owner = nullptr;
							Location = FVector3f::ZeroVector;
							Direction = FVector3f::ZeroVector;
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