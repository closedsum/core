// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsData_Tower.generated.h"

UINTERFACE(Blueprintable)
class UCsData_Tower : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Tower
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const int32& GetMaxLevel() = 0;

	virtual int32 GetCost(const int32& InLevel) = 0;

	virtual int32 GetSellValue(const int32& InLevel) = 0;

	virtual float GetFireRate(const int32& InLevel) = 0;

	virtual float GetRange(const int32& InLevel) = 0;
};