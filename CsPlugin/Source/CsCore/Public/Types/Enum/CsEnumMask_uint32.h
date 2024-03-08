// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum.h"

#include "CsEnumMask_uint32.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnumMask_uint32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	uint8 Value;
	
	UPROPERTY(EditAnywhere, Category = "CsCore|Enum")
	uint32 Mask;

	FECsEnumMask_uint32() :
		Super(),
		Value(0),
		Mask(0)
	{
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
		Name_Internal = B.Name_Internal;
		return *this;
	}

	FORCEINLINE bool operator==(const FECsEnumMask_uint32& B) const
	{
		return Value == B.Value && Mask == B.Mask && Name_Internal == B.Name_Internal;
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

	FORCEINLINE void SetMask(const int32& InMask)
	{
		Mask = InMask;
	}

	FORCEINLINE const uint32& GetMask() const
	{
		return Mask;
	}

	FORCEINLINE void UpdateMask()
	{
		Mask = 1 << Value;
	}

	FORCEINLINE FString ToGraphPinString() const
	{
		return TEXT("(Value=") + FString::FromInt(Value) + TEXT(",Mask=") + FString::FromInt(Mask) + TEXT(",Name_Internal=\"") + Name_Internal.ToString() + TEXT("\")");
	}
};

#define CS_ENUM_MASK_UINT32_BODY(Enum) \
	private: \
		typedef FECsEnumMask_int32 Super; \
	public: \
		Enum() {} \
		Enum(const uint8& InValue, const FString& InName, const FString& InDisplayName) \
		{ \
			Value = InValue > CS_UINT32_BIT_MAX ? CS_UINT32_BIT_MAX : InValue; \
			Mask = 1 << Value; \
			Name_Internal = FName(*InName); \
			\
			for (int32 I = GetNames().Num(); I <= Value; ++I) \
			{ \
				GetNames().AddDefaulted(); \
				GetDisplayNames().AddDefaulted(); \
			} \
			\
			GetNames()[Value] = InName; \
			GetDisplayNames()[Value] = InDisplayName; \
		} \
		Enum(const uint8& InValue, const FString& InName) : Enum(InValue, InName, InName) {} \
		~Enum() {} \
		\
		FORCEINLINE bool operator==(const Enum& B) const \
		{ \
			return Value == B.Value && Mask == B.Mask && Name_Internal == B.Name_Internal; \
		} \
		\
		\ FORCEINLINE bool operator!=(const Enum& B) const \
		{ \
			return !(*this == B); \
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
		FORCEINLINE void SetValue(const uint8& InValue) \
		{ \
			FString CurrentName = GetName(); \
			FString CurrentDisplayName = GetDisplayName(); \
			Value = InValue; \
			\
			for (int32 I = GetNames().Num(); I <= Value; ++I) \
			{ \
				GetNames().AddDefaulted(); \
				GetDisplayNames().AddDefaulted(); \
			} \
			\
			SetName(CurrentName); \
			SetDisplayName(CurrentDisplayName); \
		} \
		\
		FORCEINLINE operator FString() const \
		{ \
			return GetName(); \
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
			return TEXT("Name: ") + GetName() + TEXT(" Value: ") + FString::FromInt(Value) + TEXT(" Mask: ") + FString::FromInt(Mask); \
		}