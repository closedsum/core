// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Value/CsProperty_Value.h"

#pragma once

struct CSCORE_API FCsProperty_float : public TCsProperty<float>
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