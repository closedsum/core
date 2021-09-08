// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/Ref/CsIntegralType_TMap_Ref.h"

#pragma once

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
