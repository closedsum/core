// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsTdGetManagerCreep.generated.h"

class UCsTdManager_Creep;

UINTERFACE(Blueprintable)
class UCsTdGetManagerCreep : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTD_API ICsTdGetManagerCreep
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsTdManager_Creep* GetManager_Creep() const = 0;

	virtual void SetManager_Creep(UCsTdManager_Creep* InManager) = 0;
};