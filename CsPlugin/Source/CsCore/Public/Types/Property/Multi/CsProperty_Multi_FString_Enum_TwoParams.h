// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Multi/CsProperty_Multi_FString.h"

#pragma once

struct TCsProperty_Multi_FString_Enum_TwoParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_TwoParams() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString_Enum_TwoParams(){}

	TCsProperty_Multi_FString_Enum_TwoParams(const FString& inValue1, const FString& inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString& Lhs, const TCsProperty_Multi_FString_Enum_TwoParams& Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_TwoParams& Lhs, const FString& Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const TCsProperty_Multi_FString_Enum_TwoParams& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_TwoParams& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}
};