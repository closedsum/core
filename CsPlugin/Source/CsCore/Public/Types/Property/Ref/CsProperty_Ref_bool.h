// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/CsProperty_Ref.h"

struct FCsProperty_Ref_bool : public TCsProperty_Ref<bool>
{
private:
	typedef TCsProperty_Ref<bool> Super;

public:

	FCsProperty_Ref_bool() : Super()
	{
		DefaultValue = false;
	}
	~FCsProperty_Ref_bool() {}

	FORCEINLINE FCsProperty_Ref_bool& operator=(const bool& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator|(const bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return Lhs | *(Rhs.Value);
	}

	FORCEINLINE friend bool operator|(const FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		return *(Lhs.Value) | Rhs;
	}

	FORCEINLINE friend bool& operator|=(bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		Lhs = Lhs | *(Rhs.Value);
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_Ref_bool& operator|=(FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		*(Lhs.Value) = *(Lhs.Value) | Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}

	FORCEINLINE friend bool operator&(const bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return Lhs & *(Rhs.Value);
	}

	FORCEINLINE friend bool operator&(const FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		return *(Lhs.Value)&  Rhs;
	}

	FORCEINLINE friend bool& operator&=(bool& Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		Lhs = Lhs & *(Rhs.Value);
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_Ref_bool& operator&=(FCsProperty_Ref_bool& Lhs, const bool& Rhs)
	{
		*(Lhs.Value) = *(Lhs.Value)&  Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}
};

typedef FCsProperty_Ref_bool TCsBool_Ref;