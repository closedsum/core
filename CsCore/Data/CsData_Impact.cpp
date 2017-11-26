#include "Data/CsData_Impact.h"
#include "CsCore.h"
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"

ACsData_Impact::ACsData_Impact(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsFxElement* ACsData_Impact::GetImpactFX(const TCsSurfaceType &SurfaceType) { return nullptr; }

void ACsData_Impact::PlayImpactFX(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location, const FVector &Normal)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsFxElement* FxElement			 = GetImpactFX(SurfaceType);
	ACsManager_FX* Manager_FX		 = ACsManager_FX::Get(InWorld);

	Manager_FX->Play(FxElement, InOwner, Location, Normal.Rotation());
}

FCsSoundElement* ACsData_Impact::GetImpactSound(const TCsSurfaceType &SurfaceType) { return nullptr; }

void ACsData_Impact::PlayImpactSound(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsSoundElement* SoundElement	 = GetImpactSound(SurfaceType);
	ACsManager_Sound* Manager_Sound	 = ACsManager_Sound::Get(InWorld);

	Manager_Sound->Play(SoundElement, InOwner, Location);
}