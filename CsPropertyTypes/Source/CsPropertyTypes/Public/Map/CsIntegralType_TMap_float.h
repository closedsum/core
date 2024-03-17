// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Map/CsIntegralType_TMap.h"

template<typename KeyType>
struct TCsIntegralType_TMap_float : public TCsIntegralType_TMap<KeyType, float>
{
private:
	typedef TCsIntegralType_TMap<KeyType, float> Super;

public:

	TCsIntegralType_TMap_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMap_float() {}
};