// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum.h"

#include "CsEnumMask_uint32.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnumMask_uint32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Value;
	
	UPROPERTY()
	uint32 Mask;

	FECsEnumMask_uint32() :
		Value(0),
		Mask(0)
	{
	}

	FECsEnumMask_uint32(const uint8& InValue, const FString& InName, const FString& InDisplayName)
	{
		Value = InValue > CS_UINT32_BIT_MAX ? CS_UINT32_BIT_MAX : InValue;
		Mask = 1 << Value;
		Name = InName;
		DisplayName = InDisplayName;
	}

	FECsEnumMask_uint32(const uint8& InValue, const FString& InName)
	{
		FECsEnumMask_uint32(InValue, InName, InName);
	}

	virtual ~FECsEnumMask_uint32() {}

	FORCEINLINE operator uint32() const
	{
		return Mask;
	}

	FORCEINLINE FECsEnumMask_uint32& operator=(const FECsEnumMask_uint32& B)
	{
		Value = B.Value;
		Mask = B.Mask;
		Name = B.Name;
		DisplayName = B.DisplayName;
		return *this;
	}

	FORCEINLINE bool operator==(const FECsEnumMask_uint32& B) const
	{
		return Value == B.Value && Mask == B.Mask && Name == B.Name;
	}

	FORCEINLINE bool operator!=(const FECsEnumMask_uint32& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const uint32& Lhs, const FECsEnumMask_uint32& Rhs)
	{
		return Lhs == Rhs.Mask;
	}

	FORCEINLINE friend bool operator==(const FECsEnumMask_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Mask == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32& Lhs, const FECsEnumMask_uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnumMask_uint32& Lhs, const uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE uint32 operator|(const FECsEnumMask_uint32& B) const
	{
		return Mask | B.Mask;
	}

	FORCEINLINE friend uint32 operator|(const FECsEnumMask_uint32& Lhs, const uint8& Rhs)
	{
		return Lhs.Mask | Rhs;
	}

	FORCEINLINE friend uint32 operator|(const uint8& Lhs, const FECsEnumMask_uint32& Rhs)
	{
		return Lhs | Rhs.Mask;
	}

	FORCEINLINE friend uint32 operator|(const FECsEnumMask_uint32& Lhs, const int32& Rhs)
	{
		return Lhs.Mask | Rhs;
	}

	FORCEINLINE friend uint32 operator|(const int32& Lhs, const FECsEnumMask_uint32& Rhs)
	{
		return Lhs | Rhs.Mask;
	}

	FORCEINLINE friend uint32 operator|(const FECsEnumMask_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Mask | Rhs;
	}

	FORCEINLINE friend uint32 operator|(const uint32& Lhs, const FECsEnumMask_uint32& Rhs)
	{
		return Lhs | Rhs.Mask;
	}

	FORCEINLINE const uint8& GetValue() const
	{
		return Value;
	}

	FORCEINLINE const uint32& GetMask() const
	{
		return Mask;
	}

	FORCEINLINE virtual FString ToString() const override
	{
		return TEXT("Name: ") + Name + TEXT(" Value: ") + FString::FromInt(Value) + TEXT(" Mask: ") + FString::FromInt(Mask);
	}
};