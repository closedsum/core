#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes_Projectile.h"
#include "CsData_ProjectileImpact.generated.h"

/* Current Order of Categories

01. Impacts

*/

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_ProjectileImpact : public ACsData
{
	GENERATED_UCLASS_BODY()

// Impacts
#pragma region

	CS_DECLARE_SURFACE_TYPE_FUNCTIONS

	virtual FCsFxElement* GetImpactFX(const TCsProjectileType &ProjectileType, const TCsSurfaceType &SurfaceType);
	virtual void PlayImpactFX(UWorld* InWorld, const TCsProjectileType &ProjectileType, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location, const FVector &Normal);

	virtual FCsSoundElement* GetImpactSound(const TCsProjectileType &ProjectileType, const TCsSurfaceType &SurfaceType);
	virtual void PlayImpactSound(UWorld* InWorld, const TCsProjectileType &ProjectileType, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location);

#pragma endregion Impacts

};