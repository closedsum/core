// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Array/Ref/CsIntegralType_TArray_Ref.h"

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