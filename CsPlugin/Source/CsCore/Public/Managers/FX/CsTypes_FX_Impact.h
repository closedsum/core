// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/FX/CsTypes_FX.h"
#include "Engine/DataTable.h"

#include "CsTypes_FX_Impact.generated.h"

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
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsFXImpact