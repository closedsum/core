// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerLevel.generated.h"

class UCsManager_Level;

UINTERFACE(Blueprintable)
class UCsGetManagerLevel : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerLevel
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Level* GetManager_Level() const = 0;

	virtual void SetManager_Level(UCsManager_Level* InManager) = 0;
};