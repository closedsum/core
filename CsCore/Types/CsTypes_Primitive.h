// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"

#include "CsTypes_Primitive.generated.h"
#pragma once

// String
#pragma region

namespace ECsCachedString
{
	namespace Str
	{
		const FString Empty = TEXT("");
		const FString None = TEXT("None");
		const FString Json = TEXT(".json");
		const FString INVALID = TEXT("INVALID");
		const FString Dot = TEXT(".");
		const FString True = TEXT("True");
		const FString _true = TEXT("true");
		const FString False = TEXT("False");
		const FString _false = TEXT("false");
		const FString Index = TEXT("Index");
		const FString PREVIEW = TEXT("PREVIEW");
		const FString Zero = TEXT("0");
		const FString One = TEXT("1");

		const FString Text = TEXT("Text");
		const FString Button = TEXT("Button");
		const FString Image = TEXT("Image");

		// Vector to String
		const FString XEquals = TEXT("X=");
		const FString YEquals = TEXT("Y=");
		const FString ZEquals = TEXT("Z=");
		// Rotator to String
		const FString RollEquals = TEXT("R=");
		const FString PitchEquals = TEXT("P=");
		const FString YawEquals = TEXT("Y=");
	}
}

#define CS_INVALID_ENUM_TO_STRING ECsCachedString::Str::INVALID

#pragma endregion String

// FName
#pragma region

namespace ECsCachedName
{
	namespace Name
	{
		const FName None = NAME_None;
		const FName Null = FName("NULL");
	}
}

#define CS_INVALID_SHORT_CODE ECsCachedName::Name::Null

#pragma endregion FName

// Primitive References
namespace ECsCachedReferences
{
	namespace Ref
	{
		const bool True = true;
		const bool False = false;
		const uint8 Byte = 0;
		const int8 SByte = 0;
		const uint16 Short = 0;
		const int16 SShort = 0;
		const uint32 Int = 0;
		const int32 SInt = 0;
		const uint64 Long = 0;
		const int32 SLong = 0;
		const float Float = 0.0f;
		const FString String = TEXT("");
		const FName Name = NAME_None;
	}
}

// Enum Union
#pragma region

#pragma endregion Enum Union

// Enums
#pragma region

USTRUCT(BlueprintType)
struct FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enum")
	FString Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enum")
	FString DisplayName;

	FECsEnum(){}
	virtual ~FECsEnum(){}

	operator FString() const 
	{
		return Name;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const FECsEnum &Rhs)
	{
		return Lhs == Rhs.Name;
	}

	FORCEINLINE friend bool operator==(const FECsEnum &Lhs, const FString &Rhs)
	{
		return Lhs.Name == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const FECsEnum &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

USTRUCT(BlueprintType)
struct FECsEnum_uint8 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enum_uint8")
	uint8 Value;

	FECsEnum_uint8(){}

	FECsEnum_uint8(const uint8 &InValue, const FString &InName, const FString &InDisplayName)
	{
		Value = InValue;
		Name = InName;
		DisplayName = InDisplayName;
	}

	FECsEnum_uint8(const uint8 &InValue, const FString &InName)
	{
		FECsEnum_uint8(InValue, InName, InName);
	}

	virtual ~FECsEnum_uint8(){}

	operator uint8() const
	{
		return Value;
	}

	FECsEnum_uint8& operator=(const FECsEnum_uint8& B)
	{
		Value = B.Value;
		Name = B.Name;
		DisplayName = B.DisplayName;
		return *this;
	}

	bool operator==(const FECsEnum_uint8& B) const
	{
		return Value == B.Value && Name == B.Name;
	}

	bool operator!=(const FECsEnum_uint8& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const uint8 &Lhs, const FECsEnum_uint8 &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FECsEnum_uint8 &Lhs, const uint8 &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint8 &Lhs, const FECsEnum_uint8 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum_uint8 &Lhs, const uint8 &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

template<typename EnumStruct, typename EnumType>
struct TCsEnumMap
{
private:
	TArray<EnumStruct> Enums;
	int32 Count;
	TMap<FString, EnumStruct> NameMap;
	TMap<FString, EnumStruct> DisplayNameMap;
	TMap<EnumType, EnumStruct> TypeMap;
protected:
	TCsEnumMap() 
	{
		Count = 0;
	}
public:
	virtual ~TCsEnumMap() {}

	FORCEINLINE EnumStruct Create(const FString &Name, const FString &DisplayName)
	{
		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		TypeMap.Add(Index, E);
		return E;
	}

	FORCEINLINE EnumStruct Create(const FString &Name)
	{
		return Create(Name, Name);
	}
	
	FORCEINLINE const EnumStruct& operator[](const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE bool IsValidEnum(EnumStruct E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString &Name)
	{
		if (NameMap.Find(Name))
			return true;
		return false;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32 &Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString &DisplayName)
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}
};

USTRUCT(BlueprintType)
struct FECsEnumMask_int32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
	uint8 Value;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
	int32 Mask;

	FECsEnumMask_int32() {}

	FECsEnumMask_int32(const uint8 &InValue, const FString &InName, const FString &InDisplayName)
	{
		Value = InValue > CS_INT32_BIT_MAX ? CS_INT32_BIT_MAX : InValue;
		Mask = 1 << Value;
		Name = InName;
		DisplayName = InDisplayName;
	}

	FECsEnumMask_int32(const uint8 &InValue, const FString &InName)
	{
		FECsEnumMask_int32(InValue, InName, InName);
	}

	virtual ~FECsEnumMask_int32() {}

	operator int32() const
	{
		return Mask;
	}

	FECsEnumMask_int32& operator=(const FECsEnumMask_int32& B)
	{
		Value = B.Value;
		Mask = B.Mask;
		Name = B.Name;
		DisplayName = B.DisplayName;
		return *this;
	}

	bool operator==(const FECsEnumMask_int32& B) const
	{
		return Value == B.Value && Mask == B.Mask && Name == B.Name;
	}

	bool operator!=(const FECsEnumMask_int32& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const FECsEnumMask_int32 &Rhs)
	{
		return Lhs == Rhs.Mask;
	}

	FORCEINLINE friend bool operator==(const FECsEnumMask_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Mask == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const FECsEnumMask_int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnumMask_int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

USTRUCT(BlueprintType)
struct FECsEnumMask_uint32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
	uint8 Value;
	
	UPROPERTY()
	uint32 Mask;

	FECsEnumMask_uint32() {}

	FECsEnumMask_uint32(const uint8 &InValue, const FString &InName, const FString &InDisplayName)
	{
		Value = InValue > CS_UINT32_BIT_MAX ? CS_UINT32_BIT_MAX : InValue;
		Mask = 1 << Value;
		Name = InName;
		DisplayName = InDisplayName;
	}

	FECsEnumMask_uint32(const uint8 &InValue, const FString &InName)
	{
		FECsEnumMask_uint32(InValue, InName, InName);
	}

	virtual ~FECsEnumMask_uint32() {}

	operator uint32() const
	{
		return Mask;
	}

	FECsEnumMask_uint32& operator=(const FECsEnumMask_uint32& B)
	{
		Value = B.Value;
		Mask = B.Mask;
		Name = B.Name;
		DisplayName = B.DisplayName;
		return *this;
	}

	bool operator==(const FECsEnumMask_uint32& B) const
	{
		return Value == B.Value && Mask == B.Mask && Name == B.Name;
	}

	bool operator!=(const FECsEnumMask_uint32& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE friend bool operator==(const uint32 &Lhs, const FECsEnumMask_uint32 &Rhs)
	{
		return Lhs == Rhs.Mask;
	}

	FORCEINLINE friend bool operator==(const FECsEnumMask_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Mask == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32 &Lhs, const FECsEnumMask_uint32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnumMask_uint32 &Lhs, const uint32 &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

template<typename EnumStruct, typename EnumType>
struct TCsEnumMaskMap
{
private:
	TArray<EnumStruct> Enums;
	int32 Count;
	TMap<FString, EnumStruct> NameMap;
	TMap<FString, EnumStruct> DisplayNameMap;
	TMap<EnumType, EnumStruct> TypeMap;
protected:
	TCsEnumMaskMap()
	{
		Count = 0;
	}
public:
	virtual ~TCsEnumMaskMap() {}

	FORCEINLINE EnumStruct Create(const FString &Name, const FString &DisplayName)
	{
		EnumType Index = (EnumType)Enums.Num();

		// int32
		if (std::is_same<EnumType, int32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
			{
				UE_LOG(LogCs, Log, TEXT("TCsEnumMaskMap::Create: Reached limit of %d for EnumStruct of type FECsEnumMask_int32. Remaining Enums will be the same as 1<<%d."), Index, CS_INT32_BIT_MAX);
				return Enums[Index - 1];
			}
		}
		// unt32
		if (std::is_same<EnumType, uint32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
			{
				UE_LOG(LogCs, Log, TEXT("TCsEnumMaskMap::Create: Reached limit of %d for EnumStruct of type FECsEnumMask_uint32. Remaining Enums will be the same as 1<<%d."), Index, CS_INT32_BIT_MAX);
				return Enums[Index - 1];
			}
		}

		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		TypeMap.Add(Index, E);
		return E;
	}

	FORCEINLINE EnumStruct Create(const FString &Name)
	{
		return Create(Name, Name);
	}

	FORCEINLINE const EnumStruct& operator[](const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE bool IsValidEnum(EnumStruct E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString &Name)
	{
		if (NameMap.Find(Name))
			return true;
		return false;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32 &Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString &DisplayName)
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}
};

#pragma endregion Enums

// Primitive Types
#pragma region

template<typename T>
struct TCsPrimitiveType
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void, const T&> OnChange_Event;

public:
	TCsPrimitiveType(){}
	virtual ~TCsPrimitiveType(){}

	void SetDefaultValue(const T &inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	TCsPrimitiveType& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	bool operator==(const T& B) const
	{
		return Value == B;
	}

	bool operator!=(const T& B) const
	{
		return !(*this == B);
	}

	virtual void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	const T& Get() { return Value; }

	virtual void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;
	}

	void ResetValue()
	{
		Value	   = DefaultValue;
		Last_Value = Value;
		IsDirty	   = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }
	void MarkDirty() { IsDirty = true; }

	void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

struct FCsPrimitiveType_int32 : public TCsPrimitiveType<int32>
{
	FCsPrimitiveType_int32()
	{
		DefaultValue = 0;
	}
	~FCsPrimitiveType_int32(){}

	FCsPrimitiveType_int32& operator=(const int32& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_int32& operator+=(const int32& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_int32& operator++()
	{
		++Value;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_int32 operator++(int)
	{
		FCsPrimitiveType_int32 Temp = *this;
		++*this;
		UpdateIsDirty();
		return Temp;
	}

	FCsPrimitiveType_int32& operator-=(const int32& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_int32& operator--()
	{
		--Value;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_int32 operator--(int)
	{
		FCsPrimitiveType_int32 Temp = *this;
		--*this;
		UpdateIsDirty();
		return Temp;
	}

	FCsPrimitiveType_int32& operator*=(const int32& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsPrimitiveType_int32 &Lhs, const int32 &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const int32 &Lhs, const FCsPrimitiveType_int32 &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsPrimitiveType_int32 TCsInt32;

struct FCsPrimitiveType_uint32 : public TCsPrimitiveType<uint32>
{
	FCsPrimitiveType_uint32()
	{
		DefaultValue = 0;
	}
	~FCsPrimitiveType_uint32() {}

	FCsPrimitiveType_uint32& operator=(const uint32& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_uint32& operator+=(const uint32& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_uint32& operator++()
	{
		++Value;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_uint32 operator++(int)
	{
		FCsPrimitiveType_uint32 Temp = *this;
		++*this;
		UpdateIsDirty();
		return Temp;
	}

	FCsPrimitiveType_uint32& operator-=(const uint32& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_uint32& operator--()
	{
		--Value;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_uint32 operator--(int)
	{
		FCsPrimitiveType_uint32 Temp = *this;
		--*this;
		UpdateIsDirty();
		return Temp;
	}

	FCsPrimitiveType_uint32& operator*=(const uint32& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsPrimitiveType_uint32 &Lhs, const uint32 &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const uint32 &Lhs, const FCsPrimitiveType_uint32 &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsPrimitiveType_uint32 TCsUint32;

struct FCsPrimitiveType_float : public TCsPrimitiveType<float>
{
	FCsPrimitiveType_float()
	{
		DefaultValue = 0.0f;
	}
	~FCsPrimitiveType_float(){}

	FCsPrimitiveType_float& operator=(const float& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_float& operator+=(const float& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_float& operator-=(const float& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_float& operator*=(const float& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs.Value < Rhs.Value;
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs < Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs.Value <= Rhs.Value;
	}

	FORCEINLINE friend bool operator<=(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value <= Rhs;
	}

	FORCEINLINE friend bool operator<=(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs <= Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs.Value > Rhs.Value;
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs > Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs.Value >= Rhs.Value;
	}

	FORCEINLINE friend bool operator>=(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value >= Rhs;
	}

	FORCEINLINE friend bool operator>=(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs >= Rhs.Value;
	}

	FORCEINLINE friend float operator/(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value / Rhs;
	}

	FORCEINLINE friend float operator/(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs / Rhs.Value;
	}

	FORCEINLINE friend float operator*(const FCsPrimitiveType_float &Lhs, const float &Rhs)
	{
		return Lhs.Value * Rhs;
	}

	FORCEINLINE friend float operator*(const float &Lhs, const FCsPrimitiveType_float &Rhs)
	{
		return Lhs * Rhs.Value;
	}
};

typedef FCsPrimitiveType_float TCsFloat;

#define CS_AXES_2D 2
#define CS_AXES_3D 3
#define CS_AXIS_X 0
#define CS_AXIS_Y 1
#define CS_AXIS_Z 2
#define CS_AXES_3D_ALL 3

struct FCsPrimitiveType_FVector2D : public TCsPrimitiveType<FVector2D>
{

protected:
	bool IsDirtys[CS_AXES_2D];

public:

	FCsPrimitiveType_FVector2D()
	{
		DefaultValue = FVector2D::ZeroVector;
	}
	~FCsPrimitiveType_FVector2D() {}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsPrimitiveType_FVector2D& operator=(const FVector2D& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector2D &Lhs, const FCsPrimitiveType_FVector2D &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_FVector2D &Lhs, const FVector2D &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector2D &Lhs, const FCsPrimitiveType_FVector2D &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_FVector2D &Lhs, const FVector2D &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend FVector2D operator-(const FVector2D &Lhs, const FCsPrimitiveType_FVector2D &Rhs)
	{
		return Lhs - Rhs.Value;
	}

	FORCEINLINE friend FVector2D operator-(const FCsPrimitiveType_FVector2D &Lhs, const FVector2D &Rhs)
	{
		return Lhs.Value - Rhs;
	}

	FCsPrimitiveType_FVector2D& operator+=(const FVector2D& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_FVector2D& operator-=(const FVector2D& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_FVector2D& operator*=(const FVector2D& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector2D &inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FVector2D GetAxes(const int32 &Axes)
	{
		FVector2D V = FVector2D::ZeroVector;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = Value.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = Value.Y;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_X] = false;
		IsDirtys[CS_AXIS_Y] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Y)
			return true;
		return IsDirtys[Axis];
	}

	bool HasAxesChanged(const int32 &Axes)
	{
		if (!IsDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X) && IsDirtys[CS_AXIS_X])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y) && IsDirtys[CS_AXIS_Y])
			return true;
		return false;
	}
};

typedef FCsPrimitiveType_FVector2D TCsFVector2D;

struct FCsPrimitiveType_FVector : public TCsPrimitiveType<FVector>
{

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	FCsPrimitiveType_FVector()
	{
		DefaultValue = FVector::ZeroVector;
	}
	~FCsPrimitiveType_FVector(){}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_X] = Value.X != Last_Value.X;
		IsDirtys[CS_AXIS_Y] = Value.Y != Last_Value.Y;
		IsDirtys[CS_AXIS_Z] = Value.Z != Last_Value.Z;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsPrimitiveType_FVector& operator=(const FVector& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector &Lhs, const FCsPrimitiveType_FVector &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_FVector &Lhs, const FVector &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector &Lhs, const FCsPrimitiveType_FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_FVector &Lhs, const FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_FVector& operator+=(const FVector& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_FVector& operator-=(const FVector& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_FVector& operator*=(const FVector& B)
	{
		Value *= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FVector &inValue) override 
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FVector GetAxes(const int32 &Axes)
	{
		FVector V = FVector::ZeroVector;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X))
			V.X = Value.X;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y))
			V.Y = Value.Y;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z))
			V.Z = Value.Z;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_X] = false;
		IsDirtys[CS_AXIS_Y] = false;
		IsDirtys[CS_AXIS_Z] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_X || Axis > CS_AXIS_Z)
			return true;
		return IsDirtys[Axis];
	}

	bool HasAxesChanged(const int32 &Axes)
	{
		if (!IsDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_X) && IsDirtys[CS_AXIS_X])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Y) && IsDirtys[CS_AXIS_Y])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_Z) && IsDirtys[CS_AXIS_Z])
			return true;
		return false;
	}
};

typedef FCsPrimitiveType_FVector TCsFVector;

#define CS_AXIS_ROLL 0
#define CS_AXIS_PITCH 1
#define CS_AXIS_YAW 2


struct FCsPrimitiveType_FRotator : public TCsPrimitiveType<FRotator>
{

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	FCsPrimitiveType_FRotator()
	{
		DefaultValue = FRotator::ZeroRotator;
	}
	~FCsPrimitiveType_FRotator(){}

	virtual void UpdateIsDirty() override
	{
		IsDirty = Value != Last_Value;
		IsDirtys[CS_AXIS_ROLL] = Value.Roll != Last_Value.Roll;
		IsDirtys[CS_AXIS_PITCH] = Value.Pitch != Last_Value.Pitch;
		IsDirtys[CS_AXIS_YAW] = Value.Yaw != Last_Value.Yaw;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FCsPrimitiveType_FRotator& operator=(const FRotator& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FRotator &Lhs, const FCsPrimitiveType_FRotator &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_FRotator &Lhs, const FRotator &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FRotator &Lhs, const FCsPrimitiveType_FRotator &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_FRotator &Lhs, const FRotator &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FCsPrimitiveType_FRotator& operator+=(const FRotator& B)
	{
		Value += B;
		UpdateIsDirty();
		return *this;
	}

	FCsPrimitiveType_FRotator& operator-=(const FRotator& B)
	{
		Value -= B;
		UpdateIsDirty();
		return *this;
	}

	virtual void Set(const FRotator &inValue) override
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FRotator GetAxes(const int32 &Axes)
	{
		FRotator V = FRotator::ZeroRotator;

		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL))
			V.Roll = Value.Roll;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH))
			V.Pitch = Value.Pitch;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW))
			V.Yaw = Value.Yaw;
		return V;
	}

	virtual void Clear() override
	{
		Last_Value = Value;
		IsDirty = false;
		IsDirtys[CS_AXIS_ROLL] = false;
		IsDirtys[CS_AXIS_PITCH] = false;
		IsDirtys[CS_AXIS_YAW] = false;
	}

	bool HasAxisChanged(const uint8 &Axis)
	{
		if (!IsDirty)
			return false;
		if (Axis < CS_AXIS_PITCH || Axis > CS_AXIS_ROLL)
			return true;
		return IsDirtys[Axis];
	}

	bool HasAxesChanged(const int32 &Axes)
	{
		if (!IsDirty)
			return false;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_ROLL) && IsDirtys[CS_AXIS_ROLL])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_PITCH) && IsDirtys[CS_AXIS_PITCH])
			return true;
		if (CS_TEST_BLUEPRINT_BITFLAG(Axes, CS_AXIS_YAW) && IsDirtys[CS_AXIS_YAW])
			return true;
		return false;
	}
};

typedef FCsPrimitiveType_FRotator TCsFRotator;

struct FCsPrimitiveType_FString : public TCsPrimitiveType<FString>
{
public:

	FCsPrimitiveType_FString()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~FCsPrimitiveType_FString() {}

	FCsPrimitiveType_FString& operator=(const FString& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const FCsPrimitiveType_FString &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_FString &Lhs, const FString &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const FCsPrimitiveType_FString &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_FString &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsPrimitiveType_FString TCsFString;

struct FCsPrimitiveType_FLinearColor : public TCsPrimitiveType<FLinearColor>
{
public:

	FCsPrimitiveType_FLinearColor()
	{
		DefaultValue = FLinearColor::White;
	}
	~FCsPrimitiveType_FLinearColor() {}

	FCsPrimitiveType_FLinearColor& operator=(const FLinearColor& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FLinearColor &Lhs, const FCsPrimitiveType_FLinearColor &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_FLinearColor &Lhs, const FLinearColor &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FLinearColor &Lhs, const FCsPrimitiveType_FLinearColor &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_FLinearColor &Lhs, const FLinearColor &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsPrimitiveType_FLinearColor TCsFLinearColor;

// Ref
#pragma region

template<typename T>
struct TCsPrimitiveType_Ref
{
public:
	T DefaultValue;
	T* Value;
	T Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void, const T&> OnChange_Event;

public:
	TCsPrimitiveType_Ref(){}
	virtual ~TCsPrimitiveType_Ref(){}

	virtual void UpdateIsDirty()
	{
		IsDirty = *Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(*Value);
	}

	TCsPrimitiveType_Ref& operator=(const T& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	bool operator==(const T& B) const
	{
		return Value == B;
	}

	bool operator!=(const T& B) const
	{
		return !(*this == B);
	}

	void Set(T* inValue)
	{
		Value   = inValue;
		UpdateIsDirty();
	}

	void Set(const T &inValue)
	{
		*Value  = inValue;
		UpdateIsDirty();
	}

	const T& Get() { return *Value; }

	void Clear()
	{
		Last_Value = *Value;
		IsDirty	   = false;
	}

	void ResetValue()
	{
		Value	   = nullptr;
		Last_Value = DefaultValue;
		IsDirty	   = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }

	void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

struct FCsPrimitiveType_Ref_bool : public TCsPrimitiveType_Ref<bool>
{
	FCsPrimitiveType_Ref_bool()
	{
		DefaultValue = false;
	}
	~FCsPrimitiveType_Ref_bool() {}

	FORCEINLINE friend bool operator==(const bool &Lhs, const FCsPrimitiveType_Ref_bool &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_Ref_bool &Lhs, const bool &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const bool &Lhs, const FCsPrimitiveType_Ref_bool &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_Ref_bool &Lhs, const bool &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsPrimitiveType_Ref_bool TCsBool_Ref;

struct FCsPrimitiveType_Ref_int32 : public TCsPrimitiveType_Ref<int32>
{
	FCsPrimitiveType_Ref_int32()
	{
		DefaultValue = 0;
	}
	~FCsPrimitiveType_Ref_int32() {}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const FCsPrimitiveType_Ref_int32 &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const FCsPrimitiveType_Ref_int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32 &Lhs, const FCsPrimitiveType_Ref_int32 &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32 &Lhs, const FCsPrimitiveType_Ref_int32 &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsPrimitiveType_Ref_int32 TCsInt32_Ref;

struct FCsPrimitiveType_Ref_float : public TCsPrimitiveType_Ref<float>
{
	FCsPrimitiveType_Ref_float()
	{
		DefaultValue = 0.0f;
	}
	~FCsPrimitiveType_Ref_float(){}

	FORCEINLINE friend bool operator==(const float &Lhs, const FCsPrimitiveType_Ref_float &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsPrimitiveType_Ref_float &Lhs, const float &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const FCsPrimitiveType_Ref_float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsPrimitiveType_Ref_float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsPrimitiveType_Ref_float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const FCsPrimitiveType_Ref_float &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsPrimitiveType_Ref_float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const FCsPrimitiveType_Ref_float &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsPrimitiveType_Ref_float TCsFloat_Ref;

#pragma endregion Ref

#define CS_PRIMITIVE_TYPE_DEFAULT -1
#define CS_PRIMITIVE_TYPE_GET_DELEGATE -2

// MultiValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct TCsPrimitiveType_MultiValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	T Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_MultiValue(){}
	virtual ~TCsPrimitiveType_MultiValue(){}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = Values[Index] != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, Values[Index]);
	}

	TCsPrimitiveType_MultiValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_MultiValue& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_MultiValue& B) const
	{
		return !(*this == B);
	}

	void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, const T &inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, const T &inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	const T& Get() { return Value; }
	const T& Get(const U &Index) { return Get((int64)Index); }

	const T& Get(const int64 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : Values[Index];
	}

	void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Last_Values[I] = Values[I];
			IsDirtys[I]	   = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = Value;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }
	bool HasChanged(const U &Index) { return HasChanged((int64)Index); }
	bool HasChanged(const int64 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

	void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirtys(I);
		}
		Clear();
	}
};

template<typename T, typename U, uint8 SIZE>
struct TCsIntegralType_MultiValue : public TCsPrimitiveType_MultiValue<T, U, SIZE>
{
	TCsIntegralType_MultiValue(){}
	~TCsIntegralType_MultiValue(){}

	void Add(const T &inValue) 
	{ 
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const U &Index, const T &inValue) { Add((int64)Index, inValue); }

	void Add(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirtys(Index);
		}
	}

	void Subtract(const T &inValue) 
	{ 
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const U &Index, const T &inValue) { Subtract((int64)Index, inValue); }

	void Subtract(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirtys(Index);
		}
	}

	T Max()
	{
		T max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (T)FMath::Max(max, Values[I]);
		}
		return max;
	}

	T Min()
	{
		T min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (T)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

template<typename U, uint8 SIZE>
struct TCsPrimitiveType_MultiValue_bool : public TCsPrimitiveType_MultiValue<bool, U, SIZE>
{
	TCsPrimitiveType_MultiValue_bool()
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_MultiValue_bool(){}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= Values[I];
		}
		return and;
	}
};

template<typename U, uint8 SIZE>
struct TCsPrimitiveType_MultiValue_FString : public TCsPrimitiveType_MultiValue<FString, U, SIZE>
{
	TCsPrimitiveType_MultiValue_FString()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString(){}
};

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

struct TCsPrimitiveType_MultiValue_FString_Enum_TwoParams : public TCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_TWO_PARAMS>
{
	TCsPrimitiveType_MultiValue_FString_Enum_TwoParams()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString_Enum_TwoParams(){}

	TCsPrimitiveType_MultiValue_FString_Enum_TwoParams(const FString &inValue1, const FString &inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_MultiValue_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

struct TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams : public TCsPrimitiveType_MultiValue_FString<int32, CS_FSTRING_ENUM_THREE_PARAMS>
{
	TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams()
	{
		DefaultValue = ECsCachedString::Str::Empty;
	}
	~TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(){}

	TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams(const FString &inValue1, const FString &inValue2, const FString &inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

#pragma endregion MultiValue

// MultiRefValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32, uint8 SIZE = 1>
struct TCsPrimitiveType_MultiRefValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	T* Values[SIZE];
	T Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_MultiRefValue(){}
	virtual ~TCsPrimitiveType_MultiRefValue(){}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = *(Values[Index]) != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, *(Values[Index]));
	}

	TCsPrimitiveType_MultiRefValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_MultiRefValue& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_MultiRefValue& B) const
	{
		return !(*this == B);
	}

	void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, T* inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, T* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	const T& Get() { return Value; }
	const T& Get(const U &Index) { return Get((int64)Index); }

	const T& Get(const int64 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : *(Values[Index]);
	}

	void Clear()
	{
		Last_Value = Value;
		IsDirty	   = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Last_Values[I] = *(Values[I]);
			IsDirtys[I]	   = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = nullptr;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }

	bool HasChanged(const U &Index) 
	{ 
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}

	void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirtys(I);
		}
		Clear();
	}
};

template<typename T, typename U, uint8 SIZE>
struct TCsIntegralType_MultiRefValue : public TCsPrimitiveType_MultiRefValue<T, U, SIZE>
{
	TCsIntegralType_MultiRefValue(){}
	~TCsIntegralType_MultiRefValue(){}

	T Max()
	{
		T max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (T)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	T Min()
	{
		T min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (T)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

template<typename U, uint8 SIZE>
struct TCsPrimitiveType_MultiRefValue_bool : public TCsPrimitiveType_MultiRefValue<bool, U, SIZE>
{
	TCsPrimitiveType_MultiRefValue_bool()
	{
		DefaultValue = bool;
	}
	~TCsPrimitiveType_MultiRefValue_bool(){}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= Values[I];
		}
		return and;
	}
};

#pragma endregion MultiRefValue

// TArrayValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32>
struct TCsPrimitiveType_TArrayValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	TArray<T> Values;
	TArray<T> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<T, const U&> GetDelegate;
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;

public:

	TCsPrimitiveType_TArrayValue() {}
	virtual ~TCsPrimitiveType_TArrayValue() {}

	void SetDefaultValue(const T& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = Values[Index] != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)Index, Values[Index]);
	}

	TCsPrimitiveType_TArrayValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_TArrayValue& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_TArrayValue& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNumZeroed(SIZE, true);
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, const T &inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, const T &inValue)
	{
		const int64 I = (int64)Index;

		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	const T& Get() { return Value; }
	const T& Get(const U &Index) { return Get((int64)Index); }
	const T& Get(const int64 &Index){ return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : Values[Index]; }

	T GetEX(const U &Index) { return GetDelegate.Execute(Index); }

	void Clear()
	{
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Last_Values[I] = Values[I];
			IsDirtys[I] = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = Value;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }
	bool HasChanged(const U &Index) { return HasChanged((int64)Index); }
	bool HasChanged(const int64 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

	void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirtys(I);
		}
		Clear();
	}
};

template<typename T, typename U>
struct TCsIntegralType_TArrayValue : public TCsPrimitiveType_TArrayValue<T, U>
{
	TCsIntegralType_TArrayValue() {}
	~TCsIntegralType_TArrayValue() {}

	void Add(const T &inValue)
	{
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const U &Index, const T &inValue) { Add((int64)Index, inValue); }

	void Add(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirtys(Index);
		}
	}

	void Subtract(const T &inValue)
	{
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const U &Index, const T &inValue) { Subtract((int64)Index, inValue); }

	void Subtract(const int64 &Index, const T &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirtys(Index);
		}
	}

	T Max()
	{
		T max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (T)FMath::Max(max, Values[I]);
		}
		return max;
	}

	T Min()
	{
		T min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (T)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

template<typename U>
struct TCsIntegralType_TArrayValue_uint8 : public TCsIntegralType_TArrayValue<uint8, U>
{
	TCsIntegralType_TArrayValue_uint8()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayValue_uint8(){}
};

template<typename U>
struct TCsIntegralType_TArrayValue_float : public TCsIntegralType_TArrayValue<float, U>
{
	TCsIntegralType_TArrayValue_float()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayValue_float() {}
};

template<typename U>
struct TCsPrimitiveType_TArrayValue_bool : public TCsPrimitiveType_TArrayValue<bool, U>
{
	TCsPrimitiveType_TArrayValue_bool() 
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_TArrayValue_bool() {}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= Values[I];
		}
		return and;
	}
};

#pragma endregion TArrayValue

// TArrayRefValue
#pragma region

// DON'T USE int64 for U
template<typename T, typename U = int32>
struct TCsPrimitiveType_TArrayRefValue
{
public:
	T DefaultValue;
	T Value;
	T Last_Value;

	TArray<T*> Values;
	TArray<T> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<T, const U&> GetDelegate;
	TMulticastDelegate<void, const T&> OnChange_Event;
	TMulticastDelegate<void, const U&, const T&> OnChangeEX_Event;
public:

	TCsPrimitiveType_TArrayRefValue() {}
	virtual ~TCsPrimitiveType_TArrayRefValue() {}

	void SetDefaultValue(const T& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	virtual void UpdateIsDirtys(const int64 &Index)
	{
		IsDirtys[Index] = *(Values[Index]) != Last_Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)Index, *(Values[Index]));
	}

	TCsPrimitiveType_TArrayRefValue& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirtys(I);
		}
		return *this;
	}

	bool operator==(const TCsPrimitiveType_TArrayRefValue& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	bool operator!=(const TCsPrimitiveType_TArrayRefValue& B) const
	{
		return !(*this == B);
	}

	void Init(const uint8 &inSIZE)
	{
		SIZE = inSIZE;
		Values.SetNum(SIZE, true);

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = nullptr;
		}
		Last_Values.SetNumZeroed(SIZE, true);
		IsDirtys.SetNumZeroed(SIZE, true);
	}

	void Set(T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const U &Index, T* inValue)
	{
		Set((int64)Index, inValue);
	}

	void Set(const int64 &Index, T* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirtys(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	const T& Get() { return Value; }
	const T& Get(const U &Index) { return Get((int64)Index); }
	const T& Get(const int64 &Index){ return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : *(Values[Index]); }

	T GetEX(const U &Index) { return GetDelegate.Execute(Index); }

	void Clear()
	{
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Last_Values[I] = *(Values[I]);
			IsDirtys[I] = false;
		}
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = nullptr;
			Last_Values[I] = Value;
			IsDirtys[I] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	bool HasChanged() { return IsDirty; }

	bool HasChanged(const U &Index)
	{
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}

	void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirtys(I);
		}
		Clear();
	}
};

template<typename T, typename U>
struct TCsIntegralType_TArrayRefValue : public TCsPrimitiveType_TArrayRefValue<T, U>
{
	TCsIntegralType_TArrayRefValue() {}
	~TCsIntegralType_TArrayRefValue() {}

	T Max()
	{
		T max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (T)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	T Min()
	{
		T min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (T)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

template<typename U>
struct TCsIntegralType_TArrayRefValue_uint8 : public TCsIntegralType_TArrayRefValue<uint8, U>
{
	TCsIntegralType_TArrayRefValue_uint8() 
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRefValue_uint8() {}
};

template<typename U>
struct TCsIntegralType_TArrayRefValue_int32 : public TCsIntegralType_TArrayRefValue<int32, U>
{
	TCsIntegralType_TArrayRefValue_int32()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRefValue_int32() {}
};

template<typename U>
struct TCsIntegralType_TArrayRefValue_float : public TCsIntegralType_TArrayRefValue<float, U>
{
	TCsIntegralType_TArrayRefValue_float()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayRefValue_float() {}
};

template<typename U>
struct TCsPrimitiveType_TArrayRefValue_bool : public TCsPrimitiveType_TArrayRefValue<bool, U>
{
	TCsPrimitiveType_TArrayRefValue_bool() 
	{
		DefaultValue = false;
	}
	~TCsPrimitiveType_TArrayRefValue_bool() {}

	bool Or()
	{
		bool or = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= Values[I];
		}
		return or ;
	}

	bool And()
	{
		bool and = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= Values[I];
		}
		return and;
	}
};

#pragma endregion TArrayRefValue

UENUM(BlueprintType)
namespace ECsMemberType
{
	enum Type
	{
		Bool				UMETA(DisplayName = "Bool"),
		Uint8				UMETA(DisplayName = "Uint8"),
		Int32				UMETA(DisplayName = "Int32"),
		Float				UMETA(DisplayName = "Float"),
		_FString			UMETA(DisplayName = "FString"),
		FName				UMETA(DisplayName = "FName"),
		FVector				UMETA(DisplayName = "FVector"),
		FRotator			UMETA(DisplayName = "FRotator"),
		FColor				UMETA(DisplayName = "FColor"),
		ECsMemberType_MAX	UMETA(Hidden),
	};
}

namespace ECsMemberType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Bool = TCsString(TEXT("Bool"), TEXT("bool"));
		const TCsString Uint8 = TCsString(TEXT("Uint8"), TEXT("uint8"));
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
		const TCsString _FString = TCsString(TEXT("FString"), TEXT("fstring"));
		const TCsString FName = TCsString(TEXT("FName"), TEXT("fname"));
		const TCsString FVector = TCsString(TEXT("FVector"), TEXT("fvector"));
		const TCsString FRotator = TCsString(TEXT("FRotator"), TEXT("frotator"));
		const TCsString FColor = TCsString(TEXT("FColor"), TEXT("fcolor"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Bool) { return Str::Bool.Value; }
		if (EType == Type::Uint8) { return Str::Uint8.Value; }
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		if (EType == Type::_FString) { return Str::_FString.Value; }
		if (EType == Type::FName) { return Str::FName.Value; }
		if (EType == Type::FVector) { return Str::FVector.Value; }
		if (EType == Type::FRotator) { return Str::FRotator.Value; }
		if (EType == Type::FColor) { return Str::FColor.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Bool) { return Type::Bool; }
		if (String == Str::Uint8) { return Type::Uint8; }
		if (String == Str::Int32) { return Type::Int32; }
		if (String == Str::Float) { return Type::Float; }
		if (String == Str::_FString) { return Type::_FString; }
		if (String == Str::FName) { return Type::FName; }
		if (String == Str::FVector) { return Type::FVector; }
		if (String == Str::FRotator) { return Type::FRotator; }
		if (String == Str::FColor) { return Type::FColor; }
		return Type::ECsMemberType_MAX;
	}
}

#define ECS_MEMBER_TYPE_MAX (uint8)ECsMemberType::ECsMemberType_MAX
typedef ECsMemberType::Type TCsMemberType;

#define CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(Type, Integral, Value) const Type Integral = 1; \
																		  Type* ptr = (Type*)(&Integral); \
																		  *ptr = Value;

#pragma endregion Primitive Types

// Vector Types
#pragma region

// TODO: Look at FIntPoint, FVector ... etc for proper setup

USTRUCT(BlueprintType)
struct FCsUint8Point
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UInt8Point")
	uint8 X; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UInt8Point")
	uint8 Y; // 8 bits

	FCsUint8Point()
	{
		Reset();
	}
	~FCsUint8Point(){}

	FCsUint8Point& operator=(const FCsUint8Point& B)
	{
		X = B.X;
		Y = B.Y;
		return *this;
	}

	bool operator==(const FCsUint8Point& B) const
	{
		return X == B.X && Y == B.Y;
	}

	bool operator!=(const FCsUint8Point& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		X = 0;
		Y = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("X=%d Y=%d"), X, Y);
	}

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = 0;

		// The initialization is only successful if the X and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("X="), X) && FParse::Value(*InSourceString, TEXT("Y="), Y);

		return bSuccessful;
	}

	uint32 GetBits() const
	{
		return 8 // X
			 + 8;// Y
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsUint8MatrixDimension
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixDimension")
	uint8 RowSpan; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixDimension")
	uint8 ColumnSpan; // 8 bits

	FCsUint8MatrixDimension()
	{
		Reset();
	}

	FCsUint8MatrixDimension(const uint8 &InRowSpan, const uint8 &InColumnSpan)
	{
		RowSpan	   = InRowSpan;
		ColumnSpan = InColumnSpan;
	}
	~FCsUint8MatrixDimension() {}

	FCsUint8MatrixDimension& operator=(const FCsUint8MatrixDimension& B)
	{
		RowSpan	   = B.RowSpan;
		ColumnSpan = B.ColumnSpan;
		return *this;
	}

	bool operator==(const FCsUint8MatrixDimension& B) const
	{
		return RowSpan == B.RowSpan && ColumnSpan == B.ColumnSpan;
	}

	bool operator!=(const FCsUint8MatrixDimension& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		RowSpan	   = 0;
		ColumnSpan = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("RowSpan=%d ColumnSpan=%d"), RowSpan, ColumnSpan);
	}

	bool InitFromString(const FString& InSourceString)
	{
		RowSpan = ColumnSpan = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("RowSpan="), RowSpan) && FParse::Value(*InSourceString, TEXT("ColumnSpan="), ColumnSpan);

		return bSuccessful;
	}

	void Set(const uint8 &InRowSpan, const uint8 &InColumnSpan)
	{
		RowSpan    = InRowSpan;
		ColumnSpan = InColumnSpan;
	}

	uint8 GetRow(const int32 &Index)
	{
		return (Index / RowSpan) % RowSpan;
	}

	uint8 GetColumn(const int32 &Index)
	{
		return Index % RowSpan;
	}

	uint16 GetSize()
	{
		return RowSpan * ColumnSpan;
	}

	uint32 GetBits() const
	{
		return 8 // RowSpan
			 + 8;// ColumnSpan
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsUint8MatrixCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixCoordinate")
	uint8 Row; // 8 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Uint8MatrixCoordinate")
	uint8 Column; // 8 bits

	FCsUint8MatrixCoordinate()
	{
		Reset();
	}
	~FCsUint8MatrixCoordinate() {}

	FCsUint8MatrixCoordinate& operator=(const FCsUint8MatrixCoordinate& B)
	{
		Row    = B.Row;
		Column = B.Column;
		return *this;
	}

	bool operator==(const FCsUint8MatrixCoordinate& B) const
	{
		return Row == B.Row && Column == B.Column;
	}

	bool operator!=(const FCsUint8MatrixCoordinate& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Row	   = 0;
		Column = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Row=%d Column=%d"), Row, Column);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Row = Column = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Row="), Row) && FParse::Value(*InSourceString, TEXT("Column="), Column);

		return bSuccessful;
	}

	void Set(const uint8 &InRow, const uint8 &InColumn)
	{
		Row    = InRow;
		Column = InColumn;
	}

	uint32 GetBits() const
	{
		return 8 // Row
			 + 8;// Column
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsVectorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool X; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool Y; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	bool Z; // 1 bits

	FCsVectorFlag()
	{
		Reset();
	}
	~FCsVectorFlag() {}

	FCsVectorFlag& operator=(const FCsVectorFlag& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	bool operator==(const FCsVectorFlag& B) const
	{
		return X == B.X && Y == B.Y && Z == B.Z;
	}

	bool operator!=(const FCsVectorFlag& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		X = false;
		Y = false;
		Z = false;
	}
	
	FString ToString() const
	{
		return FString::Printf(TEXT("X=%s Y=%s Z=%s"), (*ToString_Internal(X)), (*ToString_Internal(Y)), (*ToString_Internal(Z)));
	}
	
private:

	const FString& ToString_Internal(const bool &Value) const 
	{
		return Value ? ECsCachedString::Str::True : ECsCachedString::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = Z = false;

		// The initialization is only successful if the X, Y and Z values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, ECsCachedString::Str::XEquals, X) && 
								 InitFromString_Internal(InSourceString, ECsCachedString::Str::YEquals, Y) &&
								 InitFromString_Internal(InSourceString, ECsCachedString::Str::ZEquals, Z);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool &Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == ECsCachedString::Str::_true || Bool == ECsCachedString::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == ECsCachedString::Str::_false || Bool == ECsCachedString::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	void Set(const bool &InX, const bool &InY, const bool &InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	void ApplyLock(FVector &V)
	{
		V.X = X ? 0.0f : V.X;
		V.Y = Y ? 0.0f : V.Y;
		V.Z = Z ? 0.0f : V.Z;
	}

	uint32 GetBits() const
	{
		return 1 // X
			 + 1 // Y
			 + 1;// Z
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsRotatorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Roll; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Pitch; // 1 bits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	bool Yaw; // 1 bits

	FCsRotatorFlag()
	{
		Reset();
	}
	~FCsRotatorFlag() {}

	FCsRotatorFlag& operator=(const FCsRotatorFlag& B)
	{
		Roll  = B.Roll;
		Pitch = B.Pitch;
		Yaw   = B.Yaw;
		return *this;
	}

	bool operator==(const FCsRotatorFlag& B) const
	{
		return Roll == B.Roll && Pitch == B.Pitch && Yaw == B.Yaw;
	}

	bool operator!=(const FCsRotatorFlag& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Roll = false;
		Pitch = false;
		Yaw = false;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("R=%s P=%s Y=%s"), (*ToString_Internal(Roll)), (*ToString_Internal(Pitch)), (*ToString_Internal(Yaw)));
	}

private:

	const FString& ToString_Internal(const bool &Value) const
	{
		return Value ? ECsCachedString::Str::True : ECsCachedString::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		Roll = Pitch = Yaw = false;

		// The initialization is only successful if the Roll, Pitch and Yaw values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, ECsCachedString::Str::RollEquals, Roll) &&
								 InitFromString_Internal(InSourceString, ECsCachedString::Str::PitchEquals, Pitch) &&
								 InitFromString_Internal(InSourceString, ECsCachedString::Str::YawEquals, Yaw);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool &Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == ECsCachedString::Str::_true || Bool == ECsCachedString::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == ECsCachedString::Str::_false || Bool == ECsCachedString::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	void Set(const bool &InRoll, const bool &InPitch, const bool &InYaw)
	{
		Roll = InRoll;
		Pitch = InPitch;
		Yaw = InYaw;
	}

	void ApplyLock(FRotator &R)
	{
		R.Roll = Roll ? 0.0f : R.Roll;
		R.Pitch = Pitch ? 0.0f : R.Pitch;
		R.Yaw = Yaw ? 0.0f : R.Yaw;
	}

	uint32 GetBits() const
	{
		return 1 // Roll
			 + 1 // Pitch
			 + 1;// Yaw
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct FCsOptionalVectorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector")
	FVector Vector; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalX; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalX; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalY; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalY; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector", meta = (InlineEditConditionToggle))
	bool bIntervalZ;
	UPROPERTY(EditAnywhere, Category = "Vector", meta = (editcondition = "bIntervalX"))
	FFloatInterval IntervalZ;

	FCsOptionalVectorInterval()
	{
		Reset();
	}
	~FCsOptionalVectorInterval() {}

	FCsOptionalVectorInterval& operator=(const FCsOptionalVectorInterval& B)
	{
		Vector = B.Vector;
		// X
		bIntervalX = B.bIntervalX;
		IntervalX.Min = B.IntervalX.Min;
		IntervalX.Max = B.IntervalX.Max;
		// Y
		bIntervalY = B.bIntervalY;
		IntervalY.Min = B.IntervalY.Min;
		IntervalY.Max = B.IntervalY.Max;
		// Z
		bIntervalZ = B.bIntervalZ;
		IntervalZ.Min = B.IntervalZ.Min;
		IntervalZ.Max = B.IntervalZ.Max;
		return *this;
	}

	bool operator==(const FCsOptionalVectorInterval& B) const
	{
		return	Vector == B.Vector && 
				bIntervalX == B.bIntervalX && 
				IntervalX.Min == B.IntervalX.Min &&
				IntervalX.Max == B.IntervalX.Max &&
				bIntervalY == B.bIntervalY &&
				IntervalY.Min == B.IntervalY.Min &&
				IntervalY.Max == B.IntervalY.Max &&
				bIntervalZ == B.bIntervalZ &&
				IntervalZ.Min == B.IntervalZ.Min &&
				IntervalZ.Max == B.IntervalZ.Max;
	}

	bool operator!=(const FCsOptionalVectorInterval& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Vector = FVector::ZeroVector;
		// X
		bIntervalX = false;
		IntervalX.Min = 0.0f;
		IntervalX.Max = 0.0f;
		// Y
		bIntervalY = false;
		IntervalY.Min = 0.0f;
		IntervalY.Max = 0.0f;
		// Z
		bIntervalZ = false;
		IntervalZ.Min = 0.0f;
		IntervalZ.Max = 0.0f;
	}

	uint32 GetBits() const
	{
		return  (3 * 64) // Vector
			   + 1 // bIntervalX
			   + (2 * 64) // IntervalX
			   + 1 // bIntervalY
			   + (2 * 64) // IntervalY
			   + 1 // bIntervalZ
			   + (2 * 64); // IntervalZ
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Vector.X = bIntervalX ? FMath::RandRange(IntervalX.Min, IntervalX.Max) : Vector.X;
		Vector.Y = bIntervalY ? FMath::RandRange(IntervalY.Min, IntervalY.Max) : Vector.Y;
		Vector.Z = bIntervalZ ? FMath::RandRange(IntervalZ.Min, IntervalZ.Max) : Vector.Z;
	}

	const FVector& Get()
	{
		return Vector;
	}
};

USTRUCT(BlueprintType)
struct FCsOptionalRotatorInterval
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator")
	FRotator Rotator; // 3 x 64 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalRoll; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalRoll"))
	FFloatInterval IntervalRoll; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalPitch; // 1 bit
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalPitch"))
	FFloatInterval IntervalPitch; // 2 x 16 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotator", meta = (InlineEditConditionToggle))
	bool bIntervalYaw;
	UPROPERTY(EditAnywhere, Category = "Rotator", meta = (editcondition = "bIntervalYaw"))
	FFloatInterval IntervalYaw;

	FCsOptionalRotatorInterval()
	{
		Reset();
	}
	~FCsOptionalRotatorInterval() {}

	FCsOptionalRotatorInterval& operator=(const FCsOptionalRotatorInterval& B)
	{
		Rotator = B.Rotator;
		// Roll
		bIntervalRoll = B.bIntervalRoll;
		IntervalRoll.Min = B.IntervalRoll.Min;
		IntervalRoll.Max = B.IntervalRoll.Max;
		// Pitch
		bIntervalPitch = B.bIntervalPitch;
		IntervalPitch.Min = B.IntervalPitch.Min;
		IntervalPitch.Max = B.IntervalPitch.Max;
		// Yaw
		bIntervalYaw = B.bIntervalYaw;
		IntervalYaw.Min = B.IntervalYaw.Min;
		IntervalYaw.Max = B.IntervalYaw.Max;
		return *this;
	}

	bool operator==(const FCsOptionalRotatorInterval& B) const
	{
		return	Rotator == B.Rotator &&
				bIntervalRoll == B.bIntervalRoll &&
				IntervalRoll.Min == B.IntervalRoll.Min &&
				IntervalRoll.Max == B.IntervalRoll.Max &&
				bIntervalPitch == B.bIntervalPitch &&
				IntervalPitch.Min == B.IntervalPitch.Min &&
				IntervalPitch.Max == B.IntervalPitch.Max &&
				bIntervalYaw == B.bIntervalYaw &&
				IntervalYaw.Min == B.IntervalYaw.Min &&
				IntervalYaw.Max == B.IntervalYaw.Max;
	}

	bool operator!=(const FCsOptionalRotatorInterval& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Rotator = FRotator::ZeroRotator;
		// Roll
		bIntervalRoll = false;
		IntervalRoll.Min = 0.0f;
		IntervalRoll.Max = 0.0f;
		// Pitch
		bIntervalPitch = false;
		IntervalPitch.Min = 0.0f;
		IntervalPitch.Max = 0.0f;
		// Yaw
		bIntervalYaw = false;
		IntervalYaw.Min = 0.0f;
		IntervalYaw.Max = 0.0f;
	}

	uint32 GetBits() const
	{
		return  (3 * 64) // Rotator
				+ 1 // bIntervalRoll
				+ (2 * 64) // IntervalRoll
				+ 1 // bIntervalPitch
				+ (2 * 64) // IntervalPitch
				+ 1 // bIntervalYaw
				+ (2 * 64); // IntervalYaw
	}

	float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Rotator.Roll = bIntervalRoll ? FMath::RandRange(IntervalRoll.Min, IntervalRoll.Max) : Rotator.Roll;
		Rotator.Pitch = bIntervalPitch ? FMath::RandRange(IntervalPitch.Min, IntervalPitch.Max) : Rotator.Pitch;
		Rotator.Yaw = bIntervalYaw ? FMath::RandRange(IntervalYaw.Min, IntervalYaw.Max) : Rotator.Yaw;
	}

	const FRotator& Get()
	{
		return Rotator;
	}
};

#pragma endregion Vector Types

namespace ECsStringCompare
{
	enum Type
	{
		Equals,
		StartsWith,
		EndsWith,
		Contains,
		ECsStringCompare_MAX,
	};
}

namespace ECsStringCompare
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Equals = TCsString(TEXT("Equals"), TEXT("equals"), TEXT("equals"));
		const TCsString StartsWith = TCsString(TEXT("StartsWith"), TEXT("startswith"), TEXT("starts with"));
		const TCsString EndsWith = TCsString(TEXT("EndsWith"), TEXT("endswith"), TEXT("ends with"));
		const TCsString Contains = TCsString(TEXT("Contains"), TEXT("contains"), TEXT("contains"));
	}

	namespace Ref
	{
		const ECsStringCompare::Type Equals = Type::Equals;
		const ECsStringCompare::Type StartsWith = Type::StartsWith;
		const ECsStringCompare::Type EndsWith = Type::EndsWith;
		const ECsStringCompare::Type Contains = Type::Contains;
		const ECsStringCompare::Type ECsStringCompare_MAX = Type::ECsStringCompare_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Equals) { return Str::Equals.Value; }
		if (EType == Type::StartsWith) { return Str::StartsWith.Value; }
		if (EType == Type::EndsWith) { return Str::EndsWith.Value; }
		if (EType == Type::Contains) { return Str::Contains.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Equals) { return Ref::Equals; }
		if (String == Str::StartsWith) { return Ref::StartsWith; }
		if (String == Str::EndsWith) { return Ref::EndsWith; }
		if (String == Str::Contains) { return Ref::Contains; }
		return Ref::ECsStringCompare_MAX;
	}

	FORCEINLINE bool Compare(const FString &Source, const FString &String, const Type &EType)
	{
		if (EType == Type::Equals) { return Source == String; }
		if (EType == Type::StartsWith) { return Source.StartsWith(String); }
		if (EType == Type::EndsWith) { return Source.EndsWith(String); }
		if (EType == Type::Contains) { return Source.Contains(String); }
		return false;
	}
}

#define ECS_STRING_COMPARE_MAX (uint8)ECsStringCompare::ECsStringCompare_MAX
typedef ECsStringCompare::Type TCsStringCompare;