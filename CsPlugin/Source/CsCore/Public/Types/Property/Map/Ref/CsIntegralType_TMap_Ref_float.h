// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Map/Ref/CsIntegralType_TMap_Ref.h"

template<typename KeyType>
struct TCsIntegralType_TMap_Ref_float : public TCsIntegralType_TMap_Ref<KeyType, float>
{
private:
	typedef TCsIntegralType_TMap_Ref<KeyType, float> Super;

public:

	TCsIntegralType_TMap_Ref_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMap_Ref_float() {}
};