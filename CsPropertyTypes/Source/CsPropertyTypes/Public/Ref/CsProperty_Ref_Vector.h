// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Ref/CsProperty_Ref.h"

struct FCsProperty_Ref_FVector : public TCsProperty_Ref<FVector3d>
{
private:
	typedef TCsProperty_Ref<FVector3d> Super;

public:

	FCsProperty_Ref_FVector() : Super()
	{
		DefaultValue = FVector3d::ZeroVector;
	}
	~FCsProperty_Ref_FVector() {}

	FORCEINLINE FCsProperty_Ref_FVector& operator=(const FVector3d& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector3d& Lhs, const FCsProperty_Ref_FVector& Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_FVector& Lhs, const FVector3d& Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector3d& Lhs, const FCsProperty_Ref_FVector& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_FVector& Lhs, const FVector3d& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsProperty_Ref_FVector TCsFVector_Ref;