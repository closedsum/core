// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"
#include "Engine/DataTable.h"

#include "CsTypes_FX_Impact.generated.h"
#pragma once

// FCsFXImpact
#pragma region

/**
* Container holding general information for an FX System.
* and the associated Physics Surface
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsFXImpact : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsFX FX;

public:

	FCsFXImpact() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		FX()
	{
	}
};

#pragma endregion FCsFXImpact