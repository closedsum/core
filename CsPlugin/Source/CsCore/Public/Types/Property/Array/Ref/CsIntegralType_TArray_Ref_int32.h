// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

struct TCsIntegralType_TArray_Ref_int32 : public TCsIntegralType_TArray_Ref<int32>
{
private:
	typedef TCsIntegralType_TArray_Ref<int32> Super;

public:

	TCsIntegralType_TArray_Ref_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArray_Ref_int32() {}
};
