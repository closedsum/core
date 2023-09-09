// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Property/Value/CsProperty_Value.h"

struct FCsProperty_FString : public TCsProperty<FString>
{
private:
	typedef TCsProperty<FString> Super;

public:

	FCsProperty_FString() : Super()
	{
		DefaultValue.Reset();
	}
	~FCsProperty_FString() {}

	FCsProperty_FString& operator=(const FString& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FString& Lhs, const FCsProperty_FString& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_FString& Lhs, const FString& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const FCsProperty_FString& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_FString& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsProperty_FString TCsFString;