// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerDamage.generated.h"

class UCsManager_Damage;

UINTERFACE(Blueprintable)
class CSDMG_API UCsGetManagerDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSDMG_API ICsGetManagerDamage
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Damage* GetManager_Damage() const = 0;

	virtual void SetManager_Damage(UCsManager_Damage* InManager) = 0;
};