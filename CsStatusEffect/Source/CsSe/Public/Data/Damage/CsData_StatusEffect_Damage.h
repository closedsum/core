// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Containers/CsGetInterfaceMap.h"
#include "CsData_StatusEffect_Damage.generated.h"

UINTERFACE(Blueprintable)
class CSSE_API UCsData_StatusEffect_Damage : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Damage;

/**
*/
class CSSE_API ICsData_StatusEffect_Damage : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	/**
	*/
	virtual ICsData_Damage* GetDamageData() const = 0;
};