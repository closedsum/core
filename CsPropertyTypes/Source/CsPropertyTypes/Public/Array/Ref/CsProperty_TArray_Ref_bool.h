// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Array/Ref/CsProperty_TArray_Ref.h"

struct TCsProperty_TArray_Ref_bool : public TCsProperty_TArray_Ref<bool>
{
private:
	typedef TCsProperty_TArray_Ref<bool> Super;

public:

	TCsProperty_TArray_Ref_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TArray_Ref_bool() {}

	bool Or()
	{
		bool or = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= *(Values[I]);
		}
		return or ;
	}

	bool And()
	{
		bool and = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= *(Values[I]);
		}
		return and;
	}
};