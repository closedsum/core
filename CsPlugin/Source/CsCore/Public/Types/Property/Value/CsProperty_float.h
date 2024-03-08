// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Value/CsProperty_Value.h"

struct FCsProperty_float : public TCsProperty<float>
{
private:
	typedef TCsProperty<float> Super;

public:

	FCsProperty_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~FCsProperty_float() {}

	FCsProperty_float& operator=(const float& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsProperty_float& operator+=(const float& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_float& operator-=(const float& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsProperty_float& operator*=(const float& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsProperty_float& Lhs, const float& Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const float& Lhs, const FCsProperty_float& Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsProperty_float TCsFloat;