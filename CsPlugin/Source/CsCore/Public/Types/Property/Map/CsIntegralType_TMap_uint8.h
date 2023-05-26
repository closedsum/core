// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/CsIntegralType_TMap.h"

#pragma once

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