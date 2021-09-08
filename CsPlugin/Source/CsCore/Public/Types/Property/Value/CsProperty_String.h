// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Property/Value/CsProperty_Value.h"

#pragma once

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