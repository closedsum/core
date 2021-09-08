// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsTypes_Sound.h"
#include "Engine/DataTable.h"

#include "CsTypes_Sound_Impact.generated.h"
#pragma once

// FCsSoundImpact
#pragma region

/**
* Container holding general information for a Sound.
* and the associated Physics Surface
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSoundImpact : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSound Sound;

public:

	FCsSoundImpact() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		Sound()
	{
	}
};

#pragma endregion FCsSoundImpact