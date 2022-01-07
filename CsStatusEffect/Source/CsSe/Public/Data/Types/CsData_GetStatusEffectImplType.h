// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_StatusEffect.h"

#include "CsData_GetStatusEffectImplType.generated.h"

UINTERFACE(BlueprintType)
class CSSE_API UCsData_GetStatusEffectImplType : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class CSSE_API ICsData_GetStatusEffectImplType : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

	/**
	*
	*
	* return
	*/
	virtual const FECsStatusEffectImpl& GetStatusEffectImplType() const = 0;
};