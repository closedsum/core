// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

#pragma once

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