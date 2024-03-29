// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Map/CsProperty_TMap.h"

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMap : public TCsProperty_TMap<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMap<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMap() : Super(){}
	~TCsIntegralType_TMap() {}

	FORCEINLINE void Add(const ValueType& InValue)
	{
		Value += InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Add(const KeyType& Key, const ValueType& InValue)
	{
		Values[Key] += InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE void Subtract(const ValueType& InValue)
	{
		Value -= InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Subtract(const KeyType& Key, const ValueType& InValue)
	{
		Values[Index] -= inValue;
		UpdateIsDirty(Index);
	}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (KeyType)FMath::Max(max, Values[Keys[I]]);
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[Keys[I]]);
		}
		return min;
	}
};