// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Multi/Ref/CsProperty_Multi_Ref.h"

#pragma once

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_Multi_Ref : public TCsProperty_Multi_Ref<ValueType, SIZE>
{
private:
	typedef TCsProperty_Multi_Ref<ValueType, SIZE> Super;

public:

	TCsIntegralType_Multi_Ref() : Super(){}
	~TCsIntegralType_Multi_Ref(){}

	ValueType Max()
	{
		ValueType max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};