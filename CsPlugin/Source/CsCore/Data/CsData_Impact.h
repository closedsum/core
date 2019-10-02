#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_FX.h"
#include "Types/CsTypes_Sound.h"
#include "CsData_Impact.generated.h"

/* Current Order of Categories

01. Impacts

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Impact : public ACsData
{
	GENERATED_UCLASS_BODY()

// Impacts
#pragma region

	CS_DECLARE_SURFACE_TYPE_FUNCTIONS

	virtual FCsFxElement* GetImpactFX(const TCsSurfaceType &SurfaceType);

	UFUNCTION(BlueprintCallable, Category = "Impacts")
	virtual void PlayImpactFX(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location, const FVector &Normal);

	virtual FCsSoundElement* GetImpactSound(const TCsSurfaceType &SurfaceType);

	UFUNCTION(BlueprintCallable, Category = "Impacts")
	virtual void PlayImpactSound(UWorld* InWorld, const TEnumAsByte<EPhysicalSurface> &PhysicalSurface, UObject* InOwner, const FVector &Location);

#pragma endregion Impacts

};