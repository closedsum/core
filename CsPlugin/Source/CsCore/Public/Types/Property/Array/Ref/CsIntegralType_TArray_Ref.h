// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Array/Ref/CsProperty_TArray_Ref.h"

#pragma once

template<typename ValueType>
struct TCsIntegralType_TArray_Ref : public TCsProperty_TArray_Ref<ValueType>
{
private:
	typedef TCsProperty_TArray_Ref<ValueType> Super;

public:

	TCsIntegralType_TArray_Ref() : Super() {}
	~TCsIntegralType_TArray_Ref() {}

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