// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Ref/CsProperty_Ref.h"

struct CSCORE_API FCsProperty_Ref_uint32 : public TCsProperty_Ref<uint32>
{
private:
	typedef TCsProperty_Ref<uint32> Super;

public:

	FCsProperty_Ref_uint32() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_Ref_uint32() {}

	FORCEINLINE FCsProperty_Ref_uint32& operator=(const uint32& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const uint32& Lhs, const FCsProperty_Ref_uint32& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_uint32& Lhs, const uint32& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32& Lhs, const FCsProperty_Ref_uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_uint32& Lhs, const uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_uint32& Lhs, const uint32& Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const uint32& Lhs, const FCsProperty_Ref_uint32& Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_uint32& Lhs, const uint32& Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const uint32& Lhs, const FCsProperty_Ref_uint32& Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_uint32 TCsUint32_Ref;