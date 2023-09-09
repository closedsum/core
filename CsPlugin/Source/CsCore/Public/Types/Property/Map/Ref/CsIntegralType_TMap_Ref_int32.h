// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Map/Ref/CsIntegralType_TMap_Ref.h"

template<typename KeyType>
struct TCsIntegralType_TMap_Ref_int32 : public TCsIntegralType_TMap_Ref<KeyType, int32>
{
private:
	typedef TCsIntegralType_TMap_Ref<KeyType, int32> Super;

public:

	TCsIntegralType_TMap_Ref_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMap_Ref_int32() {}
};
