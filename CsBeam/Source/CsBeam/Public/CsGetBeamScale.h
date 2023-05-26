// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"

#include "CsGetBeamScale.generated.h"

UINTERFACE(BlueprintType)
class CSBEAM_API UCsGetBeamScale : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface for getting the scale of a Beam. This is typically 
* implemented by the Owner of a Beam and the Beam can update / adjust
* its own scale via access to this interface.
*/
class CSBEAM_API ICsGetBeamScale : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FVector GetBeamScale() const = 0;
};