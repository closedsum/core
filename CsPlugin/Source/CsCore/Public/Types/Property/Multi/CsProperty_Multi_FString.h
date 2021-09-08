// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Multi/CsProperty_Multi.h"

#pragma once

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

template<uint8 SIZE>
struct TCsProperty_Multi_FString : public TCsProperty_Multi<FString, SIZE>
{
private:
	typedef TCsProperty_Multi<FString, SIZE> Super;

public:

	TCsProperty_Multi_FString() : Super()
	{
		//DefaultValue.Empty();
	}
	~TCsProperty_Multi_FString() {}
};