// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsBeamDataRootSet.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsBeamDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data")
	TSoftObjectPtr<UDataTable> BeamClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data")
	TSoftObjectPtr<UDataTable> Beams;

	FCsBeamDataRootSet() :
		BeamClasses(),
		Beams()
	{
	}
};