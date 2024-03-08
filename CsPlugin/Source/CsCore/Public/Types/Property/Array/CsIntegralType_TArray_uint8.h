// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Array/CsIntegralType_TArray.h"

struct TCsIntegralType_TArray_uint8 : public TCsIntegralType_TArray<uint8>
{
private:
	typedef TCsIntegralType_TArray<uint8> Super;

public:

	TCsIntegralType_TArray_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArray_uint8(){}
};