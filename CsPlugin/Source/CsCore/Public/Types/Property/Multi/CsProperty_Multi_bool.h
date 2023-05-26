// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Multi/CsProperty_Multi.h"

#pragma once

template<uint8 SIZE>
struct TCsProperty_Multi_bool : public TCsProperty_Multi<bool, SIZE>
{
private:
	typedef TCsProperty_Multi<bool, SIZE> Super;

public:

	TCsProperty_Multi_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_Multi_bool() {}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and& = Values[I];
		}
		return and;
	}
};