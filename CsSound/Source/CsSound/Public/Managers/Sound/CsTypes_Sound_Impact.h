// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Chaos/ChaosEngineInterface.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Sound_Impact.generated.h"

// FCsSoundImpact
#pragma region

/**
* Container holding general information for a Sound.
* and the associated Physics Surface
*/
USTRUCT(BlueprintType)
struct CSSOUND_API FCsSoundImpact : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Sound")
	FCsSound Sound;

public:

	FCsSoundImpact() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		Sound()
	{
	}
};

#pragma endregion FCsSoundImpact