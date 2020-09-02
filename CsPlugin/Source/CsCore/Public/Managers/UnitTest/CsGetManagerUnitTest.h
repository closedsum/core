// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerUnitTest.generated.h"

class UCsManager_UnitTest;

UINTERFACE(Blueprintable)
class UCsGetManagerUnitTest : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerUnitTest
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_UnitTest* GetManager_UnitTest() const = 0;

	virtual void SetManager_UnitTest(UCsManager_UnitTest* InManager) = 0;
};