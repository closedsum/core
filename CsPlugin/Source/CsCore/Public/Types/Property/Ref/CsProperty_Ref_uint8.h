// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/CsProperty_Ref.h"

struct FCsProperty_Ref_uint8 : public TCsProperty_Ref<uint8>
{
private:
	typedef TCsProperty_Ref<uint8> Super;

public:

	FCsProperty_Ref_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_Ref_uint8() {}

	FORCEINLINE FCsProperty_Ref_uint8& operator=(const uint8& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const uint8& Lhs, const FCsProperty_Ref_uint8& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_uint8& Lhs, const uint8& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint8& Lhs, const FCsProperty_Ref_uint8& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_uint8& Lhs, const uint8& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_uint8& Lhs, const uint8& Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const uint8& Lhs, const FCsProperty_Ref_uint8& Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_uint8& Lhs, const uint8& Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const uint8& Lhs, const FCsProperty_Ref_uint8& Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_uint8 TCsUint8_Ref;