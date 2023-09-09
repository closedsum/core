// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Value/CsProperty_Value.h"

struct FCsProperty_uint32 : public TCsProperty<uint32>
{
private:
	typedef TCsProperty<uint32> Super;

public:

	FCsProperty_uint32() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_uint32() {}

	FCsProperty_uint32& operator=(const uint32& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsProperty_uint32& operator+=(const uint32& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_uint32& operator++()
	{
		++Value;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_uint32 operator++(int)
	{
		FCsProperty_uint32 Temp = *this;
		++*this;
		return Temp;
	}

	FCsProperty_uint32& operator-=(const uint32& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_uint32& operator--()
	{
		--Value;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_uint32 operator--(int)
	{
		FCsProperty_uint32 Temp = *this;
		--*this;
		return Temp;
	}

	FCsProperty_uint32& operator*=(const uint32& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsProperty_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const uint32& Lhs, const FCsProperty_uint32& Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsProperty_uint32 TCsUint32;