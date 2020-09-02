// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Map/Ref/CsProperty_TMap_Ref.h"

#pragma once

template<typename KeyType>
struct TCsProperty_TMap_Ref_bool : public TCsProperty_TMap_Ref<KeyType, bool>
{
private:
	typedef TCsProperty_TMap_Ref<KeyType, bool> Super;

public:

	TCsProperty_TMap_Ref_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TMap_Ref_bool() {}

	FORCEINLINE bool Or()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool or = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			or |= *(Values[Keys[I]]);
		}
		return or ;
	}

	FORCEINLINE bool And()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool and = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			and& = *(Values[Keys[I]]);
		}
		return and;
	}
};