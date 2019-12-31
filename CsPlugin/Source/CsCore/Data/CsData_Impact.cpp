#include "Data/CsData_Impact.h"
#include "CsCore.h"
#include "Managers/FX/CsManager_FX.h"
#include "Managers/Sound/CsManager_Sound.h"

UCsData_Impact::UCsData_Impact(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FCsFxElement* UCsData_Impact::GetImpactFX(const TCsSurfaceType& SurfaceType) { return nullptr; }

void UCsData_Impact::PlayImpactFX(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface>& PhysicalSurface, UObject* InOwner, const FVector& Location, const FVector& Normal)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsFxElement* FxElement			 = GetImpactFX(SurfaceType);

	if (!FxElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impact::PlayImpactFX: Attempting to Play a NULL ParticleSystem."));
		return;
	}

	AICsManager_FX* Manager_FX = AICsManager_FX::Get(InWorld);

	FCsFxPayload* Payload = Manager_FX->AllocatePayload();
	Payload->Set(FxElement);
	Payload->Owner = InOwner;
	Payload->Rotation = Normal.Rotation();

	Manager_FX->Play(Payload);
}

FCsSoundElement* UCsData_Impact::GetImpactSound(const TCsSurfaceType& SurfaceType) { return nullptr; }

void UCsData_Impact::PlayImpactSound(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface>& PhysicalSurface, UObject* InOwner, const FVector& Location)
{
	const TCsSurfaceType SurfaceType = (*PhysicalSurfaceToSurfaceType)(PhysicalSurface);
	FCsSoundElement* SoundElement	 = GetImpactSound(SurfaceType);

	if (!SoundElement->Get())
	{
		UE_LOG(LogCs, Warning, TEXT("UCsData_Impact::PlayImpactSound: Attempting to Play a NULL Sound."));
		return;
	}

	AICsManager_Sound* Manager_Sound = AICsManager_Sound::Get(InWorld);

	FCsSoundPayload* Payload = Manager_Sound->AllocatePayload();
	Payload->Set(SoundElement);
	Payload->Owner = InOwner;
	Payload->Location = Location;

	Manager_Sound->Play(Payload);
}