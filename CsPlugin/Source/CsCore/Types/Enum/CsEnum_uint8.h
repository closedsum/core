// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum.h"

#include "CsEnum_uint8.generated.h"
#pragma once

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum_uint8 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 Value;

	FECsEnum_uint8() :
		Value(0)
	{
	}

	FECsEnum_uint8(const uint8& InValue, const FString& InName, const FString& InDisplayName)
	{
		Value = InValue;
		Name = InName;
		DisplayName = InDisplayName;
		Name_Internal = FName(*Name);
	}

	FECsEnum_uint8(const uint8& InValue, const FString& InName)
	{
		FECsEnum_uint8(InValue, InName, InName);
	}

	virtual ~FECsEnum_uint8(){}

	FORCEINLINE operator uint8() const
	{
		return Value;
	}

	FORCEINLINE FECsEnum_uint8& operator=(const FECsEnum_uint8& B)
	{
		Value = B.Value;
		Name = B.Name;
		DisplayName = B.DisplayName;
		Name_Internal = B.Name_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FECsEnum_uint8& B) const
	{
		return Value == B.Value && Name_Internal == B.Name_Internal;
	}

	FORCEINLINE bool operator!=(const FECsEnum_uint8& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const uint8& Lhs, const FECsEnum_uint8& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FECsEnum_uint8& Lhs, const uint8& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint8& Lhs, const FECsEnum_uint8& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum_uint8& Lhs, const uint8& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE const uint8& GetValue() const
	{
		return Value;
	}

	FORCEINLINE virtual FString ToString() const override
	{
		return TEXT("Name: ") + Name + TEXT(" Value: ") + FString::FromInt(Value);
	}

	FORCEINLINE FString ToGraphPinString() const
	{
		return TEXT("(Name=\"") + Name + TEXT("\",DisplayName=\"") + DisplayName + TEXT("\",Name_Internal=\"") + Name_Internal.ToString() + TEXT("\",Value=") + FString::FromInt(Value) + TEXT(")");
	}
};

#define CS_ENUM_UINT8_BODY(Enum) \
	private: \
		typedef FECsEnum_uint8 Super; \
	public: \
		Enum() {} \
		Enum(const uint8& InValue, const FString& InName, const FString& InDisplayName) : Super(InValue, InName, InDisplayName) {} \
		Enum(const uint8& InValue, const FString& InName) : Super(InValue, InName) {} \
		~Enum() {} \
		\
		FORCEINLINE bool operator==(const Enum& B) const \
		{ \
			return Value == B.Value && Name_Internal == B.Name_Internal; \
		} \
		\
		FORCEINLINE virtual FString ToString() const override { return Super::ToString(); }

#define CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(Enum) \
	FORCEINLINE uint32 GetTypeHash(const Enum& b) \
	{ \
		return GetTypeHash(b.Name_Internal) ^ GetTypeHash(b.Value); \
	}