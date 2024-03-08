// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Beam.h"

#include "CsData_GetBeamType.generated.h"


UINTERFACE(BlueprintType)
class CSBEAM_API UCsData_GetBeamType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsData_GetBeamType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const FECsBeam& GetBeamType() const = 0;
};