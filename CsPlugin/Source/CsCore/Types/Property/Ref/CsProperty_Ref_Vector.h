// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Ref/CsProperty_Ref.h"

#pragma once

struct FCsProperty_Ref_FVector : public TCsProperty_Ref<FVector>
{
private:
	typedef TCsProperty_Ref<FVector> Super;

public:

	FCsProperty_Ref_FVector() : Super()
	{
		DefaultValue = FVector::ZeroVector;
	}
	~FCsProperty_Ref_FVector() {}

	FORCEINLINE FCsProperty_Ref_FVector& operator=(const FVector& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector& Lhs, const FCsProperty_Ref_FVector& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_FVector& Lhs, const FVector& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector& Lhs, const FCsProperty_Ref_FVector& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_FVector& Lhs, const FVector& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsProperty_Ref_FVector TCsFVector_Ref;