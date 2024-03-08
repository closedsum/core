// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Value/CsProperty_Value.h"

struct FCsProperty_FLinearColor : public TCsProperty<FLinearColor>
{
private:
	typedef TCsProperty<FLinearColor> Super;

public:

	FCsProperty_FLinearColor() : Super()
	{
		DefaultValue = FLinearColor::White;
	}
	~FCsProperty_FLinearColor() {}

	FCsProperty_FLinearColor& operator=(const FLinearColor& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FLinearColor& Lhs, const FCsProperty_FLinearColor& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_FLinearColor& Lhs, const FLinearColor& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FLinearColor& Lhs, const FCsProperty_FLinearColor& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_FLinearColor& Lhs, const FLinearColor& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsProperty_FLinearColor TCsFLinearColor;