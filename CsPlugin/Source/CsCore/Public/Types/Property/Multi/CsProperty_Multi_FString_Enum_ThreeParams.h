// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Multi/CsProperty_Multi_FString.h"

struct TCsProperty_Multi_FString_Enum_ThreeParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_ThreeParams()
	{
		//DefaultValue.Empty();
	}
	~TCsProperty_Multi_FString_Enum_ThreeParams(){}

	TCsProperty_Multi_FString_Enum_ThreeParams(const FString& inValue1, const FString& inValue2, const FString& inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString& Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams& Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_ThreeParams& Lhs, const FString& Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_ThreeParams& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}
};
