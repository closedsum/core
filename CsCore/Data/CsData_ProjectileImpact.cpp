#include "Data/CsData_ProjectileImpact.h"
#include "CsCore.h"
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"

ACsData_ProjectileImpact::ACsData_ProjectileImpact(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsFxElement* ACsData_ProjectileImpact::GetImpactFX(const TCsProjectileType &ProjectileType, const TCsSurfaceType &SurfaceType) { return nullptr; }

void ACsData_ProjectileImpact::PlayImpactFX(UWorld* InWorld, const TCsProjectileType &ProjectileType, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location, const FVector &Normal)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsFxElement* FxElement			 = GetImpactFX(ProjectileType, SurfaceType);
	ACsManager_FX* Manager_FX		 = ACsManager_FX::Get(InWorld);

	Manager_FX->Play(FxElement, InOwner, Location, Normal.Rotation());
}

FCsSoundElement* ACsData_ProjectileImpact::GetImpactSound(const TCsProjectileType &ProjectileType, const TCsSurfaceType &SurfaceType) { return nullptr; }

void ACsData_ProjectileImpact::PlayImpactSound(UWorld* InWorld, const TCsProjectileType &ProjectileType, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsSoundElement* SoundElement	 = GetImpactSound(ProjectileType, SurfaceType);
	ACsManager_Sound* Manager_Sound	 = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}