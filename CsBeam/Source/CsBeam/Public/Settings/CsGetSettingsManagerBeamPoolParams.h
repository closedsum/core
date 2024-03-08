// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Beam/CsSettings_Manager_Beam.h"

#include "CsGetSettingsManagerBeamPoolParams.generated.h"

UINTERFACE(BlueprintType)
class CSBEAM_API UCsGetSettingsManagerBeamPoolParams : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsGetSettingsManagerBeamPoolParams
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const TMap<FECsBeam, FCsSettings_Manager_Beam_PoolParams>& GetSettingsManagerBeamPoolParams() const = 0;
};