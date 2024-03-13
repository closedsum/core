// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Chaos/ChaosEngineInterface.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_FX_Impact.generated.h"

// FCsFXImpact
#pragma region

/**
* Container holding general information for an FX System.
* and the associated Physics Surface
*/
USTRUCT(BlueprintType)
struct CSFX_API FCsFXImpact : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	TEnumAsByte<EPhysicalSurface> Surface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	FCsFX FX;

public:

	FCsFXImpact() :
		Surface(EPhysicalSurface::SurfaceType_Default),
		FX()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsFX::FLog::Warning) const;
};

#pragma endregion FCsFXImpact