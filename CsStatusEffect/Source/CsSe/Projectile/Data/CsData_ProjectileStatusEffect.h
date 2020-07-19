// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsGetInterfaceMap.h"
#include "CsData_ProjectileStatusEffect.generated.h"

UINTERFACE(BlueprintType)
class CSSE_API UCsData_ProjectileStatusEffect : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

class ICsStatusEffect;

/**
*
*/
class CSSE_API ICsData_ProjectileStatusEffect : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual const TArray<ICsStatusEffect*>& GetStatusEffects() const = 0;
};