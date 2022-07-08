// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StatusEffect.h"

#include "CsData_GetStatusEffectEventType.generated.h"

UINTERFACE(BlueprintType)
class CSSE_API UCsData_GetStatusEffectEventType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
* Interface to describe which Status Effect Event implementation to use.
* This is used to form an association between the Data and the Implementation.
* NOTE: Currently implementations are NOT UObjects, which is why this technique is
*	    being used. In the future if UObjects are used, then there should be 
*		a ClassHandler on the UCsCoordinator_StatusEffect to handle the association
*		between the Data and the Implementation (UClass).
*/
class CSSE_API ICsData_GetStatusEffectEventType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	* Get the type of Status Effect Event implementation.
	*
	* return Type.
	*/
	virtual const FECsStatusEffectEvent& GetStatusEffectEventType() const = 0;
};