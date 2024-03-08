// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

struct TCsIntegralType_TArray_Ref_float : public TCsIntegralType_TArray_Ref<float>
{
private:
	typedef TCsIntegralType_TArray_Ref<float> Super;

public:

	TCsIntegralType_TArray_Ref_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArray_Ref_float() {}
};