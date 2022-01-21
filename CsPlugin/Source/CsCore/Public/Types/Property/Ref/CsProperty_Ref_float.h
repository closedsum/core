// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/CsProperty_Ref.h"

#pragma once

struct FCsProperty_Ref_float : public TCsProperty_Ref<float>
{
private:
	typedef TCsProperty_Ref<float> Super;

public:

	FCsProperty_Ref_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~FCsProperty_Ref_float() {}

	FORCEINLINE FCsProperty_Ref_float& operator=(const float& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const float& Lhs, const FCsProperty_Ref_float& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_float& Lhs, const float& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float& Lhs, const FCsProperty_Ref_float& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_float& Lhs, const float& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_float& Lhs, const float& Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const float& Lhs, const FCsProperty_Ref_float& Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_float& Lhs, const float& Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const float& Lhs, const FCsProperty_Ref_float& Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_float TCsFloat_Ref;