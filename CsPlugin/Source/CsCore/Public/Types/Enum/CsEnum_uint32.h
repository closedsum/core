// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnum.h"

#include "CsEnum_uint32.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum_uint32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "CsCore|Enum")
	uint32 Value;

	FECsEnum_uint32() :
		Super(),
		Value(0)
	{
	}

	virtual ~FECsEnum_uint32(){}

	FORCEINLINE bool operator==(const FECsEnum_uint32& B) const
	{
		return Value == B.Value && Name_Internal == B.Name_Internal;
	}

	FORCEINLINE bool operator!=(const FECsEnum_uint32& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE operator uint32() const
	{
		return Value;
	}

	FORCEINLINE friend bool operator==(const uint32& Lhs, const FECsEnum_uint32& Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FECsEnum_uint32& Lhs, const uint32& Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32& Lhs, const FECsEnum_uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum_uint32& Lhs, const uint32& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE const uint32& GetValue() const
	{
		return Value;
	}

	FORCEINLINE FString ToGraphPinString() const
	{
		return TEXT("(Value=") + FString::FromInt(Value) + TEXT(",Name_Internal=\"") + Name_Internal.ToString() + TEXT("\")");
	}
};

#define CS_ENUM_UINT32_BODY(Enum) \
	public: \
		Enum() : Super() {} \
		Enum(const uint32& InValue, const FString& InName, const FString& InDisplayName) : Super() \
		{ \
			Value = InValue; \
			Name_Internal = FName(*InName); \
			\
			for (uint32 I = GetNames().Num(); I <= Value; ++I) \
			{ \
				GetNames().AddDefaulted(); \
				GetDisplayNames().AddDefaulted(); \
			} \
			\
			GetNames()[Value] = InName; \
			GetDisplayNames()[Value] = InDisplayName; \
		} \
		Enum(const uint32& InValue, const FString& InName) : Enum(InValue, InName, InName) {} \
		~Enum() {} \
		\
		FORCEINLINE bool operator==(const Enum& B) const \
		{ \
			return Value == B.Value && Name_Internal == B.Name_Internal; \
		} \
		\
		FORCEINLINE bool operator!=(const Enum& B) const \
		{ \
			return !(*this == B); \
		} \
		\
		FORCEINLINE operator FString() const \
		{ \
			return GetName(); \
		} \
		\
		FORCEINLINE friend bool operator==(const FString& Lhs, const Enum& Rhs) \
		{ \
			return Lhs == Rhs.GetName(); \
		} \
		\
		FORCEINLINE friend bool operator==(const Enum& Lhs, const FString& Rhs) \
		{ \
			return Lhs.GetName() == Rhs; \
		} \
		\
		FORCEINLINE friend bool operator!=(const FString& Lhs, const Enum& Rhs) \
		{ \
			return !(Lhs == Rhs); \
		} \
		\
		FORCEINLINE friend bool operator!=(const FECsEnum& Lhs, const Enum& Rhs) \
		{ \
			return !(Lhs == Rhs); \
		} \
		\
		FORCEINLINE void SetValue(const uint32& InValue) \
		{ \
			FString CurrentName = GetName(); \
			FString CurrentDisplayName = GetDisplayName(); \
			Value = InValue; \
			\
			for (uint32 I = GetNames().Num(); I <= Value; ++I) \
			{ \
				GetNames().AddDefaulted(); \
				GetDisplayNames().AddDefaulted(); \
			} \
			\
			SetName(CurrentName); \
			SetDisplayName(CurrentDisplayName); \
		} \
		\
		FORCEINLINE void SetName(const FString& InName) \
		{ \
			GetNames()[Value] = InName; \
		} \
		\
		FORCEINLINE const FString& GetName() const \
		{ \
			return GetNames()[Value]; \
		} \
		\
		FORCEINLINE void SetDisplayName(const FString& InDisplayName) \
		{ \
			GetDisplayNames()[Value] = InDisplayName; \
		} \
		\
		FORCEINLINE const FString& GetDisplayName() const \
		{ \
			return GetDisplayNames()[Value]; \
		} \
		\
		FORCEINLINE const TCHAR* ToChar() const \
		{ \
			return *(GetName()); \
		} \
		\
		FORCEINLINE const TCHAR* DisplayNameToChar() const \
		{ \
			return *(GetDisplayName()); \
		} \
	private: \
		static TArray<FString>& GetNames() \
		{ \
			static TArray<FString> Names; \
			return Names; \
		} \
		\
		static TArray<FString>& GetDisplayNames() \
		{ \
			static TArray<FString> DisplayNames; \
			return DisplayNames; \
		} \
	public: \
		FORCEINLINE FString ToString() const \
		{ \
			return TEXT("Name: ") + GetName() + TEXT(" Value: ") + FString::FromInt(Value); \
		}

#define CS_DEFINE_ENUM_UINT32_GET_TYPE_HASH(Enum) \
	FORCEINLINE uint32 GetTypeHash(const Enum& b) \
	{ \
		return GetTypeHash(b.Name_Internal) ^ GetTypeHash(b.Value); \
	}