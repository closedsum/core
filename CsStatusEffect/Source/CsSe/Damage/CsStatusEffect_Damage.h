// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"
#include "CsStatusEffect_Damage.generated.h"

UINTERFACE(Blueprintable)
class CSSE_API UCsStatusEffect_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class ICsDamageExpression;

/**
*/
class CSSE_API ICsStatusEffect_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual ICsDamageExpression* GetDamageExpression() const = 0;
};