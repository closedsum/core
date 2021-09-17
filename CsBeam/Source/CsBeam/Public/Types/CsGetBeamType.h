// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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