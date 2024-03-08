// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Types/CsTypes_Beam.h"

#include "CsGetBeamType.generated.h"

UINTERFACE(BlueprintType)
class CSBEAM_API UCsGetBeamType : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*
*/
class CSBEAM_API ICsGetBeamType
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const FECsBeam& GetBeamType() const = 0;
};