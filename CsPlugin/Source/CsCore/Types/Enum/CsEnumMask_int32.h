// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum.h"

#include "CsEnumMask_int32.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnumMask_int32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Value;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Mask;

	FECsEnumMask_int32() :
		Value(0),
		Mask(0)
	{
	}

	FECsEnumMask_int32(const uint8& InValue, const FString& InName, const FString& InDisplayName)
	{
		Value = InValue > CS_INT32_BIT_MAX ? CS_INT32_BIT_MAX : InValue;
		Mask = 1 << Value;
		Name = InName;
		DisplayName = InDisplayName;
	}

	FECsEnumMask_int32(const uint8& InValue, const FString& InName)
	{
		FECsEnumMask_int32(InValue, InName, InName);
	}

	virtual ~FECsEnumMask_int32() {}

	FORCEINLINE operator int32() const
	{
		return Mask;
	}

	FORCEINLINE FECsEnumMask_int32& operator=(const FECsEnumMask_int32& B)
	{
		Value = B.Value;
		Mask = B.Mask;
		Name = B.Name;
		DisplayName = B.DisplayName;
		return *this;
	}

	FORCEINLINE bool operator==(const FECsEnumMask_int32& B) const
	{
		return Value == B.Value && Mask == B.Mask && Name_Internal == B.Name_Internal;
	}

	FORCEINLINE bool operator!=(const FECsEnumMask_int32& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const int32& Lhs, const FECsEnumMask_int32& Rhs)
	{
		return Lhs == Rhs.Mask;
	}

	FORCEINLINE friend bool operator==(const FECsEnumMask_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Mask == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32& Lhs, const FECsEnumMask_int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnumMask_int32& Lhs, const int32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE int32 operator|(const FECsEnumMask_int32& B) const
	{
		return Mask | B.Mask;
	}

	FORCEINLINE friend int32 operator|(const FECsEnumMask_int32& Lhs, const uint8& Rhs)
	{
		return Lhs.Mask | Rhs;
	}

	FORCEINLINE friend int32 operator|(const uint8& Lhs, const FECsEnumMask_int32& Rhs)
	{
		return Lhs | Rhs.Mask;
	}

	FORCEINLINE friend int32 operator|(const FECsEnumMask_int32& Lhs, const int32& Rhs)
	{
		return Lhs.Mask | Rhs;
	}

	FORCEINLINE friend int32 operator|(const int32& Lhs, const FECsEnumMask_int32& Rhs)
	{
		return Lhs | Rhs.Mask;
	}

	FORCEINLINE const uint8& GetValue() const 
	{
		return Value;
	}

	FORCEINLINE const int32& GetMask() const
	{
		return Mask;
	}

	FORCEINLINE virtual FString ToString() const override
	{
		return TEXT("Name: ") + Name + TEXT(" Value: ") + FString::FromInt(Value) + TEXT(" Mask: ") + FString::FromInt(Mask);
	}
};

#define CS_ENUM_MASK_INT32_BODY(Enum) \
	private: \
		typedef FECsEnumMask_int32 Super; \
	public: \
		Enum() {} \
		Enum(const uint8& InValue, const FString& InName, const FString& InDisplayName) : Super(InValue, InName, InDisplayName) {} \
		Enum(const uint8& InValue, const FString& InName) : Super(InValue, InName) {} \
		~Enum() {} \
		\
		FORCEINLINE bool operator==(const FECsEnumMask_int32& B) const \
		{ \
			return Value == B.Value && Mask == B.Mask && Name_Internal == B.Name_Internal; \
		}