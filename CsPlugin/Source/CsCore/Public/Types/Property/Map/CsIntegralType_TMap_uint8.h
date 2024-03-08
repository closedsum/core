// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Map/CsIntegralType_TMap.h"

template<typename KeyType>
struct TCsIntegralType_TMap_uint8 : public TCsIntegralType_TMap<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMap<KeyType, uint8> Super;

public:

	TCsIntegralType_TMap_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMap_uint8() {}
};