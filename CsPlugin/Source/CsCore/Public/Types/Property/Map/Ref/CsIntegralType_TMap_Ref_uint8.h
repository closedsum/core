// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/Ref/CsIntegralType_TMap_Ref.h"

#pragma once

template<typename KeyType>
struct TCsIntegralType_TMap_Ref_uint8 : public TCsIntegralType_TMap_Ref<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMap_Ref<KeyType, uint8> Super;

public:

	TCsIntegralType_TMap_Ref_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMap_Ref_uint8() {}
};