// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Settings/CsTypes_BeamSettings.h"

#include "CsPrjDataRootSet.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct CSBEAM_API FCsPrjDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> BeamClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Beams;

	FCsPrjDataRootSet() :
		BeamClasses(),
		Beams()
	{
	}
};