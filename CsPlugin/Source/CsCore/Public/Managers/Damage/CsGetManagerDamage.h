// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerDamage.generated.h"

class UCsManager_Damage;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerDamage : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetManagerDamage
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Damage* GetManager_Damage() const = 0;

	virtual void SetManager_Damage(UCsManager_Damage* InManager) = 0;
};