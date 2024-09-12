// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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