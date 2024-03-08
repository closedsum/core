// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Multi/CsProperty_Multi.h"

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_Multi_Value : public TCsProperty_Multi<ValueType, SIZE>
{
private:
	typedef TCsProperty_Multi<ValueType, SIZE> Super;

public:

	TCsIntegralType_Multi_Value() : Super(){}
	~TCsIntegralType_Multi_Value(){}

	void Add(const ValueType& inValue)
	{ 
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PROPERTY_MULTI_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirty(Index);
		}
	}

	void Subtract(const ValueType& inValue)
	{ 
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const int32& Index, const ValueType& inValue)
	{
		if (Index <= CS_PROPERTY_MULTI_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirty(Index);
		}
	}

	ValueType Max()
	{
		ValueType max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, Values[I]);
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[I]);
		}
		return min;
	}
};