// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerStatusEffect.generated.h"

class UCsManager_StatusEffect;

UINTERFACE(Blueprintable)
class CSSE_API UCsGetManagerStatusEffect : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSSE_API ICsGetManagerStatusEffect
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_StatusEffect* GetManager_StatusEffect() const = 0;

	virtual void SetManager_StatusEffect(UCsManager_StatusEffect* InManager) = 0;
};