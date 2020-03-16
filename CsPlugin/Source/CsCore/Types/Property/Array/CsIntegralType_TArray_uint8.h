// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/CsIntegralType_TArray.h"

#pragma once

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