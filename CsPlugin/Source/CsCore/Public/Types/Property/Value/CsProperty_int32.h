// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Value/CsProperty_Value.h"

#pragma once

struct FCsProperty_int32 : public TCsProperty<int32>
{
private:
	typedef TCsProperty<int32> Super;

public:

	FCsProperty_int32() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_int32() {}

	FCsProperty_int32& operator=(const int32& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsProperty_int32& operator+=(const int32& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_int32& operator++()
	{
		++Value;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_int32 operator++(int)
	{
		FCsProperty_int32 Temp = *this;
		++*this;
		return Temp;
	}

	FCsProperty_int32& operator-=(const int32& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_int32& operator--()
	{
		--Value;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_int32 operator--(int)
	{
		FCsProperty_int32 Temp = *this;
		--*this;
		return Temp;
	}

	FCsProperty_int32& operator*=(const int32& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsProperty_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const int32& Lhs, const FCsProperty_int32& Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsProperty_int32 TCsInt32;