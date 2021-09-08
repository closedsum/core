// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

#pragma once

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
