// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Array/CsIntegralType_TArray.h"

struct TCsIntegralType_TArray_float : public TCsIntegralType_TArray<float>
{
private:
	typedef TCsIntegralType_TArray<float> Super;

public:

	TCsIntegralType_TArray_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArray_float() {}
};