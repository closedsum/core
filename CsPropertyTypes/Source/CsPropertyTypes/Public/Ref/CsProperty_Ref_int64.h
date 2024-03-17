// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Ref/CsProperty_Ref.h"

struct FCsProperty_Ref_int64 : public TCsProperty_Ref<int64>
{
private:
	typedef TCsProperty_Ref<int64> Super;

public:

	FCsProperty_Ref_int64() : Super()
	{
		DefaultValue = 0L;
	}
	~FCsProperty_Ref_int64() {}

	FORCEINLINE FCsProperty_Ref_int64& operator=(const int32& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32& Lhs, const FCsProperty_Ref_int64& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_int64& Lhs, const int32& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32& Lhs, const FCsProperty_Ref_int64& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_int64& Lhs, const int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_int64& Lhs, const int32& Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32& Lhs, const FCsProperty_Ref_int64& Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_int64& Lhs, const int32& Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32& Lhs, const FCsProperty_Ref_int64& Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_int64 TCsInt64_Ref;