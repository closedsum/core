// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/CsIntegralType_TArray.h"

#pragma once

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