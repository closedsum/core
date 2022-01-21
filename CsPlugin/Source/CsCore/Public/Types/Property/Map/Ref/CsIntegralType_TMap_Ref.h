// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/Ref/CsProperty_TMap_Ref.h"

#pragma once

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