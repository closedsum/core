// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/Ref/CsIntegralType_TMap_Ref.h"

#pragma once

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