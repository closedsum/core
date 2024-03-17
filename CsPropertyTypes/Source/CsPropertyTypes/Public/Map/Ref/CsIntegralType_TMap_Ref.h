// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Map/Ref/CsProperty_TMap_Ref.h"

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMap_Ref : public TCsProperty_TMap_Ref<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMap_Ref<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMap_Ref() : Super() {}
	~TCsIntegralType_TMap_Ref() {}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[Keys[I]]));
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[Keys[I]]));
		}
		return min;
	}
};