// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

#pragma once

struct TCsIntegralType_TArray_Ref_uint8 : public TCsIntegralType_TArray_Ref<uint8>
{
private:
	typedef TCsIntegralType_TArray_Ref<uint8> Super;

public:

	TCsIntegralType_TArray_Ref_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArray_Ref_uint8() {}
};