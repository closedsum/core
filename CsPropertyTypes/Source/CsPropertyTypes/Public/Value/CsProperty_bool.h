// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Value/CsProperty_Value.h"

struct FCsProperty_bool : public TCsProperty<bool>
{
private:
	typedef TCsProperty<bool> Super;

public:

	FCsProperty_bool() : Super()
	{
		DefaultValue = false;
	}
	~FCsProperty_bool() {}

	FORCEINLINE FCsProperty_bool& operator=(const bool& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const bool& Lhs, const FCsProperty_bool& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_bool& Lhs, const bool& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const bool& Lhs, const FCsProperty_bool& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_bool& Lhs, const bool& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator|(const bool& Lhs, const FCsProperty_bool& Rhs)
	{
		return Lhs | Rhs.Value;
	}

	FORCEINLINE friend bool operator|(const FCsProperty_bool& Lhs, const bool& Rhs)
	{
		return Lhs.Value | Rhs;
	}

	FORCEINLINE friend bool& operator|=(bool& Lhs, const FCsProperty_bool& Rhs)
	{
		Lhs = Lhs | Rhs.Value;
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_bool& operator|=(FCsProperty_bool& Lhs, const bool& Rhs)
	{
		Lhs.Value = Lhs.Value | Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}

	FORCEINLINE friend bool operator&(const bool& Lhs, const FCsProperty_bool& Rhs)
	{
		return Lhs & Rhs.Value;
	}

	FORCEINLINE friend bool operator&(const FCsProperty_bool& Lhs, const bool& Rhs)
	{
		return Lhs.Value&  Rhs;
	}

	FORCEINLINE friend bool& operator&=(bool& Lhs, const FCsProperty_bool& Rhs)
	{
		Lhs = Lhs & Rhs.Value;
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_bool& operator&=(FCsProperty_bool& Lhs, const bool& Rhs)
	{
		Lhs.Value = Lhs.Value&  Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}
};

typedef FCsProperty_bool TCsBool;