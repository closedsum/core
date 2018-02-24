#pragma once
#include "Data/CsData_Impact.h"
#include "CsData_ProjectileImpact.generated.h"

/* Current Order of Categories

01. Impacts

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_ProjectileImpact : public ACsData_Impact
{
	GENERATED_UCLASS_BODY()

};