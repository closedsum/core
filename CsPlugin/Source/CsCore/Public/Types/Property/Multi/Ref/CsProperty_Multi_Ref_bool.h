// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Multi/Ref/CsProperty_Multi_Ref.h"

template<uint8 SIZE>
struct TCsProperty_Multi_Ref_bool : public TCsProperty_Multi_Ref<bool, SIZE>
{
private:
	typedef TCsProperty_Multi_Ref<bool, SIZE> Super;

public:

	TCsProperty_Multi_Ref_bool() : Super()
	{
		DefaultValue = bool;
	}
	~TCsProperty_Multi_Ref_bool(){}

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
