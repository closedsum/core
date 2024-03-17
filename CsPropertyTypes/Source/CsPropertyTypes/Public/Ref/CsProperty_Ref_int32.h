// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Ref/CsProperty_Ref.h"

struct FCsProperty_Ref_int32 : public TCsProperty_Ref<int32>
{
private:
	typedef TCsProperty_Ref<int32> Super;

public:

	FCsProperty_Ref_int32() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_Ref_int32() {}

	FORCEINLINE FCsProperty_Ref_int32& operator=(const int32& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32& Lhs, const FCsProperty_Ref_int32& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_int32& Lhs, const int32& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32& Lhs, const FCsProperty_Ref_int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_int32& Lhs, const int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_int32& Lhs, const int32& Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32& Lhs, const FCsProperty_Ref_int32& Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_int32& Lhs, const int32& Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32& Lhs, const FCsProperty_Ref_int32& Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_int32 TCsInt32_Ref;