// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_ProjectileDamage.generated.h"

UINTERFACE(BlueprintType)
class CSPRJ_API UCsData_ProjectileDamage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class ICsDamageExpression;

/**
*
*/
class CSPRJ_API ICsData_ProjectileDamage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual ICsDamageExpression* GetDamageExpression() const = 0;
};