// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/CsIntegralType_TMap.h"

#pragma once

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