// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"

#include "CsTypes_Primitive.generated.h"
#pragma once

// Cached
#pragma region

namespace NCsCached
{
	namespace Str
	{
		extern CSCORE_API const FString Empty;// = TEXT("");
		extern CSCORE_API const FString None;// = TEXT("None");
		extern CSCORE_API const FString INVALID;// = TEXT("INVALID");
		extern CSCORE_API const FString Dot;// = TEXT(".");
		extern CSCORE_API const FString True;// = TEXT("True");
		extern CSCORE_API const FString _true;// = TEXT("true");
		extern CSCORE_API const FString False;// = TEXT("False");
		extern CSCORE_API const FString _false;// = TEXT("false");
		extern CSCORE_API const FString Index;// = TEXT("Index");
		extern CSCORE_API const FString PREVIEW;// = TEXT("PREVIEW");
		extern CSCORE_API const FString Zero;// = TEXT("0");
		extern CSCORE_API const FString One;// = TEXT("1");

		extern CSCORE_API const FString Text;// = TEXT("Text");
		extern CSCORE_API const FString Button;// = TEXT("Button");
		extern CSCORE_API const FString Image;// = TEXT("Image");

		// Vector to String
		extern CSCORE_API const FString XEquals;// = TEXT("X=");
		extern CSCORE_API const FString YEquals;// = TEXT("Y=");
		extern CSCORE_API const FString ZEquals;// = TEXT("Z=");
		// Rotator to String
		extern CSCORE_API const FString RollEquals;// = TEXT("R=");
		extern CSCORE_API const FString PitchEquals;// = TEXT("P=");
		extern CSCORE_API const FString YawEquals;// = TEXT("Y=");
	}

	namespace Ref
	{
		extern CSCORE_API const bool True;// = true;
		extern CSCORE_API const bool False;// = false;
		extern CSCORE_API const uint8 Byte;// = 0;
		extern CSCORE_API const int8 SByte;// = 0;
		extern CSCORE_API const uint16 Short;// = 0;
		extern CSCORE_API const int16 SShort;// = 0;
		extern CSCORE_API const uint32 Int;// = 0;
		extern CSCORE_API const int32 SInt;// = 0;
		extern CSCORE_API const uint64 Long;// = 0;
		extern CSCORE_API const uint64 Long_MAX;// = UINT64_MAX;
		extern CSCORE_API const int64 SLong;// = 0;
		extern CSCORE_API const float Float;// = 0.0f;
		extern CSCORE_API const FString String;// = TEXT("");
		extern CSCORE_API const FName Name;// = NAME_None;
	}

	namespace Name
	{
		extern CSCORE_API const FName None;// = NAME_None;
		extern CSCORE_API const FName Null;// = FName("NULL");
	}

	namespace Ext
	{
		extern CSCORE_API const FString json;// = TEXT(".json");
		extern CSCORE_API const FString txt;// = TEXT(".txt");
		extern CSCORE_API const FString js;// = TEXT(".js");
	}
}

#define CS_INVALID_ENUM_TO_STRING NCsCached::Str::INVALID
#define CS_INVALID_ENUM_TO_NAME NCsCached::Name::None
#define CS_INVALID_SHORT_CODE NCsCached::Name::Null

#pragma endregion Cached

// Enum Union
#pragma region

#pragma endregion Enum Union

// Enums
#pragma region

template<typename EnumType>
struct TCsEnumMap
{
private:
	TArray<EnumType> Enums;
	int32 Count;
	TMap<FString, EnumType> FromNameMap;
	TMap<EnumType, FString> ToNameMap;
	TMap<FString, EnumType> FromDisplayNameMap;
	TMap<EnumType, FString> ToDisplayNameMap;
	TMap<FName, EnumType> FromNameInternalMap;
	TMap<EnumType, FName> ToNameInternalMap;
	EnumType MAX;
protected:
	TCsEnumMap()
	{
		Count = 0;
	}
public:
	virtual ~TCsEnumMap() {}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name, const FString& DisplayName)
	{
		Enums.Add(Enum);
		MAX = Enum;
		++Count;
		FromNameMap.Add(Name, Enum);
		ToNameMap.Add(Enum, Name);
		FromDisplayNameMap.Add(DisplayName, Enum);
		ToDisplayNameMap.Add(Enum, DisplayName);
		FromNameInternalMap.Add(FName(*Name), Enum);
		ToNameInternalMap.Add(Enum, FName(*Name));
		return Enum;
	}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name)
	{
		return Add(Enum, Name, Name);
	}

	FORCEINLINE const EnumType& operator[](const uint8& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& operator[](const FString& Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& operator[](const FName& Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumType& E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return FromNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return FromNameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index)
	{
		return Index < Count ? Enums[Index] : MAX;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name)
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : MAX;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name)
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : MAX;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName)
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}

	FORCEINLINE const EnumType& GetMAX()
	{
		return MAX;
	}

	FORCEINLINE const FString& ToString(const EnumType& Enum)
	{
		if (FString* Name = ToNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const int32& Index)
	{
		if (Index >= Count)
			return CS_INVALID_ENUM_TO_STRING;
		return ToString(Enums[Index]);
	}

	FORCEINLINE const FName& ToName(const EnumType& Enum)
	{
		if (FName* Name = ToNameInternalMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_NAME;
	}

	FORCEINLINE const FString& ToDisplayName(const EnumType& Enum)
	{
		if (FString* Name = ToDisplayNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const EnumType& ToType(const FString& Name)
	{
		if (EnumType* Enum = FromNameMap.Find(Name))
			return *Enum;
		return MAX;
	}

	FORCEINLINE const EnumType& ToType(const FName& Name)
	{
		if (EnumType* Enum = FromNameInternalMap.Find(Name))
			return *Enum;
		return MAX;
	}
};

#define CS_DECLARE_ENUM_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

template<typename EnumType>
struct TCsEnumMaskMap
{
private:
	TArray<EnumType> Enums;
	int32 Count;
	TMap<FString, EnumType> FromNameMap;
	TMap<EnumType, FString> ToNameMap;
	TMap<FString, EnumType> FromDisplayNameMap;
	TMap<EnumType, FString> ToDisplayNameMap;
	TMap<FName, EnumType> FromNameInternalMap;
	TMap<EnumType, FName> ToNameInternalMap;
	TMap<uint64, EnumType> FlagMap;
	EnumType None;
protected:
	TCsEnumMaskMap()
	{
		Count = 0;
		None = (EnumType)0;
	}
public:
	virtual ~TCsEnumMaskMap() {}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name, const FString& DisplayName)
	{
		Enums.Add(Enum);
		++Count;
		FromNameMap.Add(Name, Enum);
		ToNameMap.Add(Enum, Name);
		FromDisplayNameMap.Add(DisplayName, Enum);
		ToDisplayNameMap.Add(Enum, DisplayName);
		FromNameInternalMap.Add(FName(*Name), Enum);
		ToNameInternalMap.Add(Enum, FName(*Name));
		FlagMap.Add((uint64)Enum, Enum);
		return Enum;
	}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name)
	{
		return Add(Enum, Name, Name);
	}

	FORCEINLINE const EnumType& operator[](const FString &Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& operator[](const FName &Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumType& E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return FromNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return FromNameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidFlag(const uint64& Flag)
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index)
	{
		return Index < Count ? Enums[Index] : None;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name)
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : None;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name)
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : None;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName)
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumType& GetEnumByFlag(const uint64& Flag)
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumType& GetSafeEnumByFlag(const uint64& Flag)
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : None;
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}

	FORCEINLINE const FString& ToString(const EnumType& Enum)
	{
		if (FString* Name = ToNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const int32& Index)
	{
		if (Index >= Count)
			return CS_INVALID_ENUM_TO_STRING;
		return ToString(Enums[Index]);
	}

	FORCEINLINE FString MaskToString(const uint64& Mask)
	{
		//  TEXT("")
		FString String = NCsCached::Str::Empty;
		bool IsFirst   = true;

		for (const EnumType& Enum : Enums)
		{
			if (CS_TEST_BITFLAG(Mask, Enum))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += ToString(Enum);
				IsFirst = false;
			}
		}

		// (String == TEXT(""))
		if (String == NCsCached::Str::Empty)
			return NCsCached::Str::None;
		// TEXT("None")
		return String;
	}

	FORCEINLINE const FName& ToName(const EnumType& Enum)
	{
		if (FName* Name = ToNameInternalMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_NAME;
	}

	FORCEINLINE const FString& ToDisplayName(const EnumType& Enum)
	{
		if (FString* Name = ToDisplayNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const EnumType& ToType(const FString& Name)
	{
		if (EnumType* Enum = FromNameMap.Find(Name))
			return *Enum;
		return None;
	}

	FORCEINLINE const EnumType& ToType(const FName& Name)
	{
		if (EnumType* Enum = FromNameInternalMap.Find(Name))
			return *Enum;
		return None;
	}
};

#define CS_DECLARE_ENUM_MASK_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_MASK_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

template<typename EnumType>
struct TCsEnumFlagMap
{
private:
	TArray<EnumType> Enums;
	int32 Count;
	TMap<FString, EnumType> FromNameMap;
	TMap<EnumType, FString> ToNameMap;
	TMap<FString, EnumType> FromDisplayNameMap;
	TMap<EnumType, FString> ToDisplayNameMap;
	TMap<FName, EnumType> FromNameInternalMap;
	TMap<EnumType, FName> ToNameInternalMap;
	TMap<uint32, EnumType> FlagMap;
	TArray<uint32> Flags;
	EnumType First;
protected:
	TCsEnumFlagMap()
	{
		Count = 0;
		First = (EnumType)0;
	}
public:
	virtual ~TCsEnumFlagMap() {}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name, const FString& DisplayName)
	{
		Enums.Add(Enum);
		++Count;
		FromNameMap.Add(Name, Enum);
		ToNameMap.Add(Enum, Name);
		FromDisplayNameMap.Add(DisplayName, Enum);
		ToDisplayNameMap.Add(Enum, DisplayName);
		FromNameInternalMap.Add(FName(*Name), Enum);
		ToNameInternalMap.Add(Enum, FName(*Name));
		FlagMap.Add(1 << static_cast<uint32>(Enum), Enum);
		Flags.Add(1 << static_cast<uint32>(Enum));
		return Enum;
	}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name)
	{
		return Add(Enum, Name, Name);
	}

	FORCEINLINE const EnumType& operator[](const FString &Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& operator[](const FName &Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumType& E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return FromNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return FromNameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidFlag(const uint32& Flag)
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index)
	{
		return Index < Count ? Enums[Index] : First;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name)
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name)
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : First;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name)
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name)
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : First;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName)
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumType& GetEnumByFlag(const uint32& Flag)
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumType& GetSafeEnumByFlag(const uint32& Flag)
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : First;
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}

	FORCEINLINE const FString& ToString(const EnumType& Enum)
	{
		if (FString* Name = ToNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const int32& Index)
	{
		if (Index >= Count)
			return CS_INVALID_ENUM_TO_STRING;
		return ToString(Enums[Index]);
	}

	FORCEINLINE const FString& ToString(const uint32& Flag)
	{
		if (IsValidFlag(Flag))
			return ToNameMap[FlagMap[Flag]];
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE FString MaskToString(const uint32& Mask)
	{
		//  TEXT("")
		FString String = NCsCached::Str::Empty;
		bool IsFirst = true;

		for (const uint32& Flag : Flags)
		{
			if (CS_TEST_BITFLAG(Mask, Flag))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += ToString(Flag);
				IsFirst = false;
			}
		}

		// (String == TEXT(""))
		if (String == NCsCached::Str::Empty)
			return NCsCached::Str::None;
		// TEXT("None")
		return String;
	}

	FORCEINLINE uint32 StringToMask(const FString& MaskAsString)
	{
		uint32 Mask = 0;

		for (const uint32& Flag : Flags)
		{
			const FString& String = ToString(Flag);

			if (MaskAsString.Contains(String))
				CS_SET_BITFLAG(Mask, Flag);
		}
		return Mask;
	}

	FORCEINLINE const FName& ToName(const EnumType& Enum)
	{
		if (FName* Name = ToNameInternalMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_NAME;
	}

	FORCEINLINE const FString& ToDisplayName(const EnumType& Enum)
	{
		if (FString* Name = ToDisplayNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToDisplayName(const int32& Index)
	{
		if (Index >= Enums.Num())
			return CS_INVALID_ENUM_TO_STRING;
		return ToDisplayNameMap[Enums[Index]];
	}

	FORCEINLINE const EnumType& ToType(const FString& Name)
	{
		if (EnumType* Enum = FromNameMap.Find(Name))
			return *Enum;
		return First;
	}

	FORCEINLINE const EnumType& ToType(const FName& Name)
	{
		if (EnumType* Enum = FromNameInternalMap.Find(Name))
			return *Enum;
		return First;
	}
};

#define CS_DECLARE_ENUM_FLAG_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_FLAG_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enum")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enum")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enum")
	FName Name_Internal;

	FECsEnum(){}
	virtual ~FECsEnum(){}

	FORCEINLINE operator FString() const
	{
		return Name;
	}

	FORCEINLINE friend bool operator==(const FString& Lhs, const FECsEnum& Rhs)
	{
		return Lhs == Rhs.Name;
	}

	FORCEINLINE friend bool operator==(const FECsEnum& Lhs, const FString& Rhs)
	{
		return Lhs.Name == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FString& Lhs, const FECsEnum& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FECsEnum& Lhs, const FString& Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE virtual FString ToString() const
	{
		return TEXT("Name: ") + Name;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnum_uint8 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enum_uint8")
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

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMap
{
private:
	TArray<EnumStruct> Enums;
	int32 Count;
	TArray<EnumStruct> UserDefinedEnums;
	TMap<FString, EnumStruct> UserDefinedNameMap;
	TMap<FString, EnumStruct> NameMap;
	TMap<FString, EnumStruct> DisplayNameMap;
	TMap<FName, EnumStruct> NameInternalMap;
	TMap<EnumType, EnumStruct> TypeMap;
	EnumStruct MAX;
protected:
	TCsEnumStructMap()
	{
		Count = 0;
		MAX.Value = (EnumType)0;
		MAX.Name = TEXT("MAX");
		MAX.DisplayName = TEXT("MAX");
	}
public:
	virtual ~TCsEnumStructMap() {}

	FORCEINLINE EnumStruct Create(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		MAX.Value = (EnumType)Count;
		return E;
	}

	FORCEINLINE EnumStruct Create(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return Create(Name, Name, UserDefinedEnum);
	}
	
#if WITH_EDITOR

	FORCEINLINE void CreateSafe(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		// Check Name already exists
		if (NameMap.Find(Name) != nullptr)
			return;
		// Check DisplayName already exists
		if (DisplayNameMap.Find(DisplayName) != nullptr)
			return;

		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		MAX.Value = (EnumType)Count;
	}

	FORCEINLINE void CreateSafe(const FString& Name, const bool& UserDefinedEnum = false)
	{
		CreateSafe(Name, Name, UserDefinedEnum);
	}

#endif // #if WITH_EDITOR
	
	FORCEINLINE const EnumStruct& operator[](const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& operator[](const FName &Name)
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumStruct& E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return NameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return NameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumAt(const int32& Index)
	{
		return Index < Count ? Enums[Index] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString& Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FString& Name)
	{
		return IsValidEnum(Name) ? NameMap[Name] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FName& Name)
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FName& Name)
	{
		return IsValidEnum(Name) ? NameInternalMap[Name] : MAX;
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType& Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString& DisplayName)
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}

	FORCEINLINE const EnumStruct& GetMAX()
	{
		return MAX;
	}
	
#if WITH_EDITOR

	FORCEINLINE void ClearUserDefinedEnums()
	{
		const int32 StartSize = Enums.Num();

		for (int32 I = StartSize - 1; I >= 0; --I)
		{
			const EnumStruct& E = Enums[I];

			if (EnumStruct* EnumPtr = UserDefinedNameMap.Find(E.Name))
			{
				NameMap.Remove(E.Name);
				DisplayNameMap.Remove(E.DisplayName);
				NameInternalMap.Remove(E.Name_Internal);
				TypeMap.Remove((EnumType)E.Value);
				Enums.RemoveAt(I);

				Count = Enums.Num();
				
				for (int32 J = I; J < Count; ++J)
				{
					Enums[J].Value = J;
				}
			}
		}
		UserDefinedEnums.Reset();
		UserDefinedNameMap.Reset();
	}

#endif // #if WITH_EDITOR
};

#define CS_DECLARE_ENUM_STRUCT_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_STRUCT_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnumMask_int32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
	uint8 Value;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
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

USTRUCT(BlueprintType)
struct CSCORE_API FECsEnumMask_uint32 : public FECsEnum
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnumMask_uint32")
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

	FORCEINLINE virtual FString ToString() const override
	{
		return TEXT("Name: ") + Name + TEXT(" Value: ") + FString::FromInt(Value) + TEXT(" Mask: ") + FString::FromInt(Mask);
	}
};

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMaskMap
{
private:
	TArray<EnumStruct> Enums;
	int32 Count;
	TArray<EnumStruct> UserDefinedEnums;
	TMap<FString, EnumStruct> UserDefinedNameMap;
	TMap<FString, EnumStruct> NameMap;
	TMap<FString, EnumStruct> DisplayNameMap;
	TMap<FName, EnumStruct> NameInternalMap;
	TMap<EnumType, EnumStruct> TypeMap;
	TMap<uint64, EnumStruct> FlagMap;
	EnumStruct NONE;
protected:
	TCsEnumStructMaskMap()
	{
		Count = 0;
		NONE.Value = 0;
		NONE.Mask = 0;
		NONE.Name = TEXT("NONE");
		NONE.DisplayName = TEXT("NONE");
	}
public:
	virtual ~TCsEnumStructMaskMap() {}

	FORCEINLINE EnumStruct Create(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		EnumType Index = (EnumType)Enums.Num();

		// int32
		if (std::is_same<EnumType, int32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
			{
				return Enums[Index - 1];
			}
		}
		// uint32
		if (std::is_same<EnumType, uint32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
			{
				return Enums[Index - 1];
			}
		}

		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		FlagMap.Add((uint64)E.Mask, E);
		return E;
	}

	FORCEINLINE EnumStruct Create(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return Create(Name, Name, UserDefinedEnum);
	}

#if WITH_EDITOR

	FORCEINLINE void CreateSafe(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		// Check Name already exists
		if (NameMap.Find(Name) != nullptr)
			return;
		// Check DisplayName already exists
		if (DisplayNameMap.Find(DisplayName) != nullptr)
			return;

		EnumType Index = (EnumType)Enums.Num();

		// int32
		if (std::is_same<EnumType, int32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
				return;
		}
		// uint32
		if (std::is_same<EnumType, uint32>::value)
		{
			if (Index > CS_INT32_BIT_MAX)
				return;
		}

		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		FlagMap.Add((uint64)E.Mask, E);
	}

	FORCEINLINE void CreateSafe(const FString& Name, const bool& UserDefinedEnum = false)
	{
		CreateSafe(Name, Name, UserDefinedEnum);
	}

#endif // #if WITH_EDITOR

	FORCEINLINE const EnumStruct& operator[](const EnumType &Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString &Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& operator[](const FName &Name)
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumStruct& E)
	{
		return Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return NameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return NameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidFlag(const uint64& Flag)
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32& Index)
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumAt(const int32& Index)
	{
		return Index < Count ? Enums[Index] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString& Name)
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FString& Name)
	{
		return IsValidEnum(Name) ? NameMap[Name] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FName& Name)
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FName& Name)
	{
		return IsValidEnum(Name) ? NameInternalMap[Name] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType& Type)
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString& DisplayName)
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumStruct& GetEnumByFlag(const uint64& Flag)
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumByFlag(const uint64& Flag)
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : NONE;
	}

	FORCEINLINE const int32& Num()
	{
		return Count;
	}

	FORCEINLINE const EnumStruct& GetNONE()
	{
		return NONE;
	}

	FORCEINLINE FString MaskToString(const uint64& Mask)
	{
		//  TEXT("")
		FString String = NCsCached::Str::Empty;
		bool IsFirst = true;

		for (const EnumStruct& Enum : Enums)
		{
			if (CS_TEST_BITFLAG(Mask, Enum.Mask))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += Enum.Name;
				IsFirst = false;
			}
		}

		// (String == TEXT(""))
		if (String == NCsCached::Str::Empty)
			return NCsCached::Str::None;
		// TEXT("None")
		return String;
	}

#if WITH_EDITOR

	FORCEINLINE void ClearUserDefinedEnums()
	{
		const int32 StartSize = Enums.Num();

		for (int32 I = StartSize - 1; I >= 0; --I)
		{
			const EnumStruct& E = Enums[I];

			if (EnumStruct* EnumPtr = UserDefinedNameMap.Find(E.Name))
			{
				NameMap.Remove(E.Name);
				DisplayNameMap.Remove(E.DisplayName);
				NameInternalMap.Remove(E.Name_Internal);
				TypeMap.Remove((EnumType)E.Value);
				FlagMap.Remove((uint64)E.Mask);
				Enums.RemoveAt(I);

				Count = Enums.Num();

				for (int32 J = I; J < Count; ++J)
				{
					Enums[J].Value = J;
				}
			}
		}
		UserDefinedEnums.Reset();
		UserDefinedNameMap.Reset();
	}

#endif // #if WITH_EDITOR
};

#define CS_DECLARE_ENUM_STRUCT_MASK_MAP_BODY(EnumMap) \
	protected: \
		EnumMap() {} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
	private: \
		static EnumMap* Instance; \
		\
	public: \
		static EnumMap& Get();

#define CS_DEFINE_ENUM_STRUCT_MASK_MAP_BODY(EnumMap) \
	EnumMap* EnumMap::Instance; \
	\
	EnumMap& EnumMap::Get() \
	{ \
		if (!Instance) \
			Instance = new EnumMap(); \
		return *Instance; \
	}

#pragma endregion Enums

// Property Types
#pragma region

	// Value
#pragma region

template<typename T>
struct TCsProperty
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
	TCsProperty()
	{
		IsDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsProperty(){}

	void SetDefaultValue(const T &inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty	   = Value != Last_Value;
		Last_Value = Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE TCsProperty& operator=(const T& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const T& B) const
	{
		return Value == B;
	}

	FORCEINLINE bool operator!=(const T& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE virtual void Set(const T &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const T& Get() { return Value; }

	FORCEINLINE virtual void Clear()
	{
		IsDirty	= false;
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

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE void MarkDirty() { IsDirty = true; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

struct CSCORE_API FCsProperty_bool : public TCsProperty<bool>
{
private:
	typedef TCsProperty<bool> Super;

public:

	FCsProperty_bool() : Super()
	{
		DefaultValue = false;
	}
	~FCsProperty_bool() {}

	FORCEINLINE FCsProperty_bool& operator=(const bool& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const bool &Lhs, const FCsProperty_bool &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const FCsProperty_bool &Lhs, const bool &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const bool &Lhs, const FCsProperty_bool &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_bool &Lhs, const bool &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator|(const bool &Lhs, const FCsProperty_bool& Rhs)
	{
		return Lhs | Rhs.Value;
	}

	FORCEINLINE friend bool operator|(const FCsProperty_bool &Lhs, const bool& Rhs)
	{
		return Lhs.Value | Rhs;
	}

	FORCEINLINE friend bool& operator|=(bool &Lhs, const FCsProperty_bool& Rhs)
	{
		Lhs = Lhs | Rhs.Value;
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_bool& operator|=(FCsProperty_bool &Lhs, const bool& Rhs)
	{
		Lhs.Value = Lhs.Value | Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}

	FORCEINLINE friend bool operator&(const bool &Lhs, const FCsProperty_bool& Rhs)
	{
		return Lhs & Rhs.Value;
	}

	FORCEINLINE friend bool operator&(const FCsProperty_bool &Lhs, const bool& Rhs)
	{
		return Lhs.Value & Rhs;
	}

	FORCEINLINE friend bool& operator&=(bool &Lhs, const FCsProperty_bool& Rhs)
	{
		Lhs = Lhs & Rhs.Value;
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_bool& operator&=(FCsProperty_bool &Lhs, const bool& Rhs)
	{
		Lhs.Value = Lhs.Value & Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}
};

typedef FCsProperty_bool TCsBool;

struct CSCORE_API FCsPrimitiveType_int32 : public TCsProperty<int32>
{
private:
	typedef TCsProperty<int32> Super;

public:

	FCsPrimitiveType_int32() : Super()
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

struct CSCORE_API FCsPrimitiveType_uint32 : public TCsProperty<uint32>
{
private:
	typedef TCsProperty<uint32> Super;

public:

	FCsPrimitiveType_uint32() : Super()
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

struct CSCORE_API FCsPrimitiveType_float : public TCsProperty<float>
{
private:
	typedef TCsProperty<float> Super;

public:

	FCsPrimitiveType_float() : Super()
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

struct CSCORE_API FCsPrimitiveType_FVector2D : public TCsProperty<FVector2D>
{
private:
	typedef TCsProperty<FVector2D> Super;

protected:
	bool IsDirtys[CS_AXES_2D];

public:

	FCsPrimitiveType_FVector2D() : Super()
	{
		for (bool& b : IsDirtys)
		{
			b = false;
		}
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

struct CSCORE_API FCsPrimitiveType_FVector : public TCsProperty<FVector>
{
private:
	typedef TCsProperty<FVector> Super;

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	FCsPrimitiveType_FVector() : Super()
	{
		for (bool& b : IsDirtys)
		{
			b = false;
		}
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


struct CSCORE_API FCsPrimitiveType_FRotator : public TCsProperty<FRotator>
{
private:
	typedef TCsProperty<FRotator> Super;

protected:
	bool IsDirtys[CS_AXES_3D];

public:

	FCsPrimitiveType_FRotator() : Super()
	{
		for (bool& b : IsDirtys)
		{
			b = false;
		}
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

struct CSCORE_API FCsPrimitiveType_FString : public TCsProperty<FString>
{
private:
	typedef TCsProperty<FString> Super;

public:

	FCsPrimitiveType_FString() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
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

struct CSCORE_API FCsPrimitiveType_FLinearColor : public TCsProperty<FLinearColor>
{
private:
	typedef TCsProperty<FLinearColor> Super;

public:

	FCsPrimitiveType_FLinearColor() : Super()
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

#pragma endregion Value

	// Ref
#pragma region

template<typename ValueType>
struct TCsProperty_Ref
{
public:
	ValueType DefaultValue;
	ValueType* Value;
	ValueType Last_Value;
protected:
	bool IsDirty;
public:
	TMulticastDelegate<void, const ValueType&> OnChange_Event;

public:
	TCsProperty_Ref()
	{
		IsDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsProperty_Ref(){}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty	   = *Value != Last_Value;
		Last_Value = *Value;

		if (IsDirty)
			OnChange_Event.Broadcast(*Value);
	}

	FORCEINLINE TCsProperty_Ref& operator=(const ValueType& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const ValueType& B) const
	{
		return *Value == B;
	}

	FORCEINLINE bool operator!=(const ValueType& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(ValueType* inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const ValueType &inValue)
	{
		*Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const ValueType& Get() { return *Value; }

	FORCEINLINE void Clear()
	{
		IsDirty	= false;
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

	FORCEINLINE bool HasChanged() { return IsDirty; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

struct CSCORE_API FCsProperty_Ref_bool : public TCsProperty_Ref<bool>
{
private:
	typedef TCsProperty_Ref<bool> Super;

public:

	FCsProperty_Ref_bool() : Super()
	{
		DefaultValue = false;
	}
	~FCsProperty_Ref_bool() {}

	FORCEINLINE FCsProperty_Ref_bool& operator=(const bool& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const bool &Lhs, const FCsProperty_Ref_bool &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_bool &Lhs, const bool &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const bool &Lhs, const FCsProperty_Ref_bool &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_bool &Lhs, const bool &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator|(const bool &Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return Lhs | *(Rhs.Value);
	}

	FORCEINLINE friend bool operator|(const FCsProperty_Ref_bool &Lhs, const bool& Rhs)
	{
		return *(Lhs.Value) | Rhs;
	}

	FORCEINLINE friend bool& operator|=(bool &Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		Lhs = Lhs | *(Rhs.Value);
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_Ref_bool& operator|=(FCsProperty_Ref_bool &Lhs, const bool& Rhs)
	{
		*(Lhs.Value) = *(Lhs.Value) | Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}

	FORCEINLINE friend bool operator&(const bool &Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		return Lhs & *(Rhs.Value);
	}

	FORCEINLINE friend bool operator&(const FCsProperty_Ref_bool &Lhs, const bool& Rhs)
	{
		return *(Lhs.Value) & Rhs;
	}

	FORCEINLINE friend bool& operator&=(bool &Lhs, const FCsProperty_Ref_bool& Rhs)
	{
		Lhs = Lhs & *(Rhs.Value);
		return Lhs;
	}

	FORCEINLINE friend FCsProperty_Ref_bool& operator&=(FCsProperty_Ref_bool &Lhs, const bool& Rhs)
	{
		*(Lhs.Value) = *(Lhs.Value) & Rhs;
		Lhs.UpdateIsDirty();
		return Lhs;
	}
};

typedef FCsProperty_Ref_bool TCsBool_Ref;

struct CSCORE_API FCsProperty_Ref_int32 : public TCsProperty_Ref<int32>
{
private:
	typedef TCsProperty_Ref<int32> Super;

public:

	FCsProperty_Ref_int32() : Super()
	{
		DefaultValue = 0;
	}
	~FCsProperty_Ref_int32() {}

	FORCEINLINE FCsProperty_Ref_int32& operator=(const int32& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const int32 &Lhs, const FCsProperty_Ref_int32 &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const int32 &Lhs, const FCsProperty_Ref_int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const int32 &Lhs, const FCsProperty_Ref_int32 &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_int32 &Lhs, const int32 &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const int32 &Lhs, const FCsProperty_Ref_int32 &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_int32 TCsInt32_Ref;

struct CSCORE_API FCsProperty_Ref_float : public TCsProperty_Ref<float>
{
private:
	typedef TCsProperty_Ref<float> Super;

public:

	FCsProperty_Ref_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~FCsProperty_Ref_float(){}

	FORCEINLINE FCsProperty_Ref_float& operator=(const float& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const float &Lhs, const FCsProperty_Ref_float &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_float &Lhs, const float &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const float &Lhs, const FCsProperty_Ref_float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_float &Lhs, const float &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator<(const FCsProperty_Ref_float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) < Rhs;
	}

	FORCEINLINE friend bool operator<(const float &Lhs, const FCsProperty_Ref_float &Rhs)
	{
		return Lhs < (*Rhs.Value);
	}

	FORCEINLINE friend bool operator>(const FCsProperty_Ref_float &Lhs, const float &Rhs)
	{
		return (*Lhs.Value) > Rhs;
	}

	FORCEINLINE friend bool operator>(const float &Lhs, const FCsProperty_Ref_float &Rhs)
	{
		return Lhs > (*Rhs.Value);
	}
};

typedef FCsProperty_Ref_float TCsFloat_Ref;

struct CSCORE_API FCsProperty_Ref_FVector : public TCsProperty_Ref<FVector>
{
private:
	typedef TCsProperty_Ref<FVector> Super;

public:

	FCsProperty_Ref_FVector() : Super()
	{
		DefaultValue = FVector::ZeroVector;
	}
	~FCsProperty_Ref_FVector() {}

	FORCEINLINE FCsProperty_Ref_FVector& operator=(const FVector& B)
	{
		*Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FVector &Lhs, const FCsProperty_Ref_FVector &Rhs)
	{
		return Lhs == *(Rhs.Value);
	}

	FORCEINLINE friend bool operator==(const FCsProperty_Ref_FVector &Lhs, const FVector &Rhs)
	{
		return *(Lhs.Value) == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FVector &Lhs, const FCsProperty_Ref_FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const FCsProperty_Ref_FVector &Lhs, const FVector &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef FCsProperty_Ref_FVector TCsFVector_Ref;

#pragma endregion Ref

#define CS_PRIMITIVE_TYPE_DEFAULT -1
#define CS_PRIMITIVE_TYPE_GET_DELEGATE -2

// Multi
#pragma region

template<typename ValueType, uint8 SIZE = 1>
struct TCsProperty_Multi
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	ValueType Values[SIZE];
	ValueType Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeEX_Event;

public:

	TCsProperty_Multi()
	{
		IsDirty = false;

		for (bool& b : IsDirtys)
		{
			b = false;
		}
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}
	virtual ~TCsProperty_Multi(){}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32 &Index)
	{
		IsDirtys[Index]		= Values[Index] != Last_Values[Index];
		Last_Values[Index]	= Values[Index];

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast(Index, Values[Index]);
	}

	FORCEINLINE TCsProperty_Multi& operator=(const TCsProperty_Multi& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_Multi& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B.Value;
	}

	FORCEINLINE bool operator!=(const TCsProperty_Multi& B) const
	{
		return !(*this == B);
	}

	void Set(const ValueType &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const int32 &Index, const ValueType &inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	FORCEINLINE const ValueType& Get() { return Value; }

	FORCEINLINE const ValueType& Get(const int32 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : Values[Index];
	}

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I] = false;
		}
	}

	FORCEINLINE void Clear(const int32 &Index)
	{
		IsDirtys[Index]	= false;
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

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const int32 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirty(I);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const int32 &Index)
	{
		UpdateIsDirty(Index);
		Clear(Index);
	}
};

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_MultiValue : public TCsProperty_Multi<ValueType, SIZE>
{
private:
	typedef TCsProperty_Multi<ValueType, SIZE> Super;

public:

	TCsIntegralType_MultiValue() : Super(){}
	~TCsIntegralType_MultiValue(){}

	void Add(const ValueType &inValue)
	{ 
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const int32 &Index, const ValueType &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirty(Index);
		}
	}

	void Subtract(const ValueType &inValue)
	{ 
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const int32 &Index, const ValueType &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirty(Index);
		}
	}

	ValueType Max()
	{
		ValueType max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, Values[I]);
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

template<uint8 SIZE>
struct TCsProperty_Multi_bool : public TCsProperty_Multi<bool, SIZE>
{
private:
	typedef TCsProperty_Multi<bool, SIZE> Super;

public:

	TCsProperty_Multi_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_Multi_bool(){}

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

template<uint8 SIZE>
struct TCsProperty_Multi_FString : public TCsProperty_Multi<FString, SIZE>
{
private:
	typedef TCsProperty_Multi<FString, SIZE> Super;

public:

	TCsProperty_Multi_FString() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString(){}
};

#define CS_FSTRING_ENUM_TWO_PARAMS 2
#define CS_FSTRING_ENUM_THREE_PARAMS 3
#define CS_FSTRING_ENUM_DEFAULT_VALUE 0
#define CS_FSTRING_ENUM_LOWER_VALUE 1
#define CS_FSTRING_ENUM_ALT_1_VALUE 2

struct CSCORE_API TCsProperty_Multi_FString_Enum_TwoParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_TWO_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_TwoParams() : Super()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString_Enum_TwoParams(){}

	TCsProperty_Multi_FString_Enum_TwoParams(const FString &inValue1, const FString &inValue2)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE] = inValue2;
	}

	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsProperty_Multi_FString_Enum_TwoParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_TWO_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsProperty_Multi_FString_Enum_TwoParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_TwoParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

struct CSCORE_API TCsProperty_Multi_FString_Enum_ThreeParams : public TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS>
{
private:
	typedef TCsProperty_Multi_FString<CS_FSTRING_ENUM_THREE_PARAMS> Super;

public:

	TCsProperty_Multi_FString_Enum_ThreeParams()
	{
		DefaultValue = NCsCached::Str::Empty;
	}
	~TCsProperty_Multi_FString_Enum_ThreeParams(){}

	TCsProperty_Multi_FString_Enum_ThreeParams(const FString &inValue1, const FString &inValue2, const FString &inValue3)
	{
		Value = inValue1;

		Values[CS_FSTRING_ENUM_DEFAULT_VALUE] = inValue1;
		Values[CS_FSTRING_ENUM_LOWER_VALUE]   = inValue2;
		Values[CS_FSTRING_ENUM_ALT_1_VALUE]   = inValue3;
	}
	
	FORCEINLINE friend bool operator==(const FString &Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams &Rhs)
	{
		const FString Lower = Lhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Rhs.Values[I] == Lhs || Rhs.Values[I] == Lower)
				return true;
		}
		return Rhs.Value == Lhs || Rhs.Value == Lower;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_Multi_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		const FString Lower = Rhs.ToLower();

		for (uint8 I = 0; I < CS_FSTRING_ENUM_THREE_PARAMS; ++I)
		{
			if (Lhs.Values[I] == Rhs || Lhs.Values[I] == Lower)
				return true;
		}
		return Lhs.Value == Rhs || Lhs.Value == Lower;
	}

	FORCEINLINE friend bool operator!=(const FString &Lhs, const TCsProperty_Multi_FString_Enum_ThreeParams &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_Multi_FString_Enum_ThreeParams &Lhs, const FString &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

#pragma endregion MultiValue

// MultiRef
#pragma region

template<typename ValueType, uint8 SIZE = 1>
struct TCsProperty_MultiRef
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	ValueType* Values[SIZE];
	ValueType Last_Values[SIZE];
protected:
	bool IsDirty;

	bool IsDirtys[SIZE];
public:
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeEX_Event;

public:

	TCsProperty_MultiRef()
	{
		IsDirty = false;

		for (bool& b : IsDirtys)
		{
			b = false;
		}
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}
	virtual ~TCsProperty_MultiRef(){}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;
		Value	= Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32 &Index)
	{
		IsDirtys[Index]		= *(Values[Index]) != Last_Values[Index];
		Last_Values[Index]	= *(Values[Index]);

		if (IsDirtys[Index])
			OnChangeEX_Event.Broadcast((U)(int32)Index, *(Values[Index]));
	}

	FORCEINLINE TCsProperty_MultiRef& operator=(const ValueType& B)
	{
		Value = B;
		UpdateIsDirty;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_MultiRef& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_MultiRef& B) const
	{
		return !(*this == B);
	}

	void Set(const ValueType &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	void Set(const int32 &Index, ValueType* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	FORCEINLINE const ValueType& Get() { return Value; }

	FORCEINLINE const ValueType& Get(const int32 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? Value : *(Values[Index]);
	}

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I]	= false;
		}
	}

	FORCEINLINE void Clear(const int32 &Index)
	{
		Last_Values[Index] = *(Values[Index]);
		IsDirtys[Index]	   = false;
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

	FORCEINLINE bool HasChanged() { return IsDirty; }

	FORCEINLINE bool HasChanged(const int32 &Index)
	{ 
		const int32 I = (int32)Index;
		return I <= CS_PRIMITIVE_TYPE_DEFAULT || I >= SIZE ? IsDirty : IsDirtys[I];
	}

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirty(I);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const int32 &Index)
	{
		UpdateIsDirty(Index);
		Clear(Index);
	}
};

template<typename ValueType, uint8 SIZE>
struct TCsIntegralType_MultiRef : public TCsProperty_MultiRef<ValueType, SIZE>
{
private:
	typedef TCsProperty_MultiRef<ValueType, SIZE> Super;

public:

	TCsIntegralType_MultiRef() : Super(){}
	~TCsIntegralType_MultiRef(){}

	ValueType Max()
	{
		ValueType max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

template<uint8 SIZE>
struct TCsProperty_MultiRef_bool : public TCsProperty_MultiRef<bool, SIZE>
{
private:
	typedef TCsProperty_MultiRef<bool, SIZE> Super;

public:

	TCsProperty_MultiRef_bool() : Super()
	{
		DefaultValue = bool;
	}
	~TCsProperty_MultiRef_bool(){}

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

#pragma endregion MultiRef

// TArray
#pragma region

template<typename ValueType>
struct TCsProperty_TArray
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TArray<ValueType> Values;
	TArray<ValueType> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const int32&> GetDelegate;
	TBaseDelegate<const ValueType&, const int32&> Override_Get;
	TBaseDelegate<const ValueType&, const int32&> Override_Subscript_Const;
	TBaseDelegate<ValueType&, const int32&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeArray_Event;

public:

	TCsProperty_TArray() 
	{
		SIZE = 0;
		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		Override_Subscript_Const.Unbind();
		OnChange_Event.Clear();
		OnChangeArray_Event.Clear();
	}
	virtual ~TCsProperty_TArray() {}

	void SetDefaultValue(const ValueType& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32 &Index)
	{
		IsDirtys[Index]		= Values[Index] != Last_Values[Index];
		Last_Values[Index]	= Values[Index];

		if (IsDirtys[Index])
			OnChangeArray_Event.Broadcast(Index, Values[Index]);
	}

	FORCEINLINE TCsProperty_TArray& operator=(const TCsProperty_TArray& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TArray& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TArray& B) const
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

	FORCEINLINE void Set(const ValueType &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const int32 &Index, const ValueType &inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(inValue);
		}
	}

	FORCEINLINE ValueType& operator[](const int32 &Index)
	{
		if (Override_Subscript.IsBound())
			return Override_Subscript.Execute(Index);
		return Values[Index];
	}

	FORCEINLINE const ValueType& operator[](const int32 &Index) const
	{
		if (Override_Subscript_Const.IsBound())
			return Override_Subscript_Const.Execute(Index);
		return Values[Index];
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const int32 &Index)
	{
		if (Override_Get.IsBound())
			return Override_Get.Execute(Index);
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : Values[Index]; 
	}

	FORCEINLINE ValueType GetEX(const int32 &Index) { return GetDelegate.Execute(Index); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I] = false;
		}
	}

	FORCEINLINE void Clear(const int32 &Index)
	{
		IsDirtys[Index] = false;
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
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		Override_Subscript_Const.Unbind();
		OnChange_Event.Clear();
		OnChangeEX_Event.Clear();
	}

	FORCEINLINE const bool& HasChanged() { return IsDirty; }
	FORCEINLINE const bool& HasChanged(const int32 &Index) { return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirty(I);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const int32 &Index)
	{
		UpdateIsDirty(Index);
		Clear(Index);
	}
};

template<typename ValueType>
struct TCsIntegralType_TArray : public TCsProperty_TArray<ValueType>
{
private:
	typedef TCsProperty_TArray<ValueType> Super;

public:

	TCsIntegralType_TArray() : Super(){}
	~TCsIntegralType_TArray() {}

	void Add(const ValueType &inValue)
	{
		Value += inValue;
		UpdateIsDirty();
	}

	void Add(const int32 &Index, const ValueType &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Add(inValue);
		}
		else
		{
			Values[Index] += inValue;
			UpdateIsDirty(Index);
		}
	}

	void Subtract(const ValueType &inValue)
	{
		Value -= inValue;
		UpdateIsDirty();
	}

	void Subtract(const int32 &Index, const ValueType &inValue)
	{
		if (Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE)
		{
			Subtract(inValue);
		}
		else
		{
			Values[Index] -= inValue;
			UpdateIsDirty(Index);
		}
	}

	ValueType Max()
	{
		ValueType max = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, Values[I]);
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = Values[0];

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[I]);
		}
		return min;
	}
};

struct TCsIntegralType_TArray_uint8 : public TCsIntegralType_TArray<uint8>
{
private:
	typedef TCsIntegralType_TArray<uint8> Super;

public:

	TCsIntegralType_TArray_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArray_uint8(){}
};

struct TCsIntegralType_TArray_float : public TCsIntegralType_TArray<float>
{
private:
	typedef TCsIntegralType_TArray<float> Super;

public:

	TCsIntegralType_TArray_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArray_float() {}
};

struct TCsProperty_TArray_bool : public TCsProperty_TArray<bool>
{
private:
	typedef TCsProperty_TArray<bool> Super;

public:

	TCsProperty_TArray_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TArray_bool() {}

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

#pragma endregion TArray

// TArrayRef
#pragma region

template<typename ValueType>
struct TCsProperty_TArrayRef
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TArray<ValueType*> Values;
	TArray<ValueType> Last_Values;

protected:
	uint8 SIZE;
	bool IsDirty;

	TArray<bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const int32&> GetDelegate;
	TBaseDelegate<const ValueType&, const int32&> Override_Get;
	TBaseDelegate<const ValueType&, const int32&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const int32&, const ValueType&> OnChangeArray_Event;
public:

	TCsProperty_TArrayRef() 
	{
		SIZE = 0;
		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		OnChange_Event.Clear();
		OnChangeArray_Event.Clear();
	}
	virtual ~TCsProperty_TArrayRef() {}

	void SetDefaultValue(const ValueType& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty	   = Value != Last_Value;
		Last_Value = Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const int32 &Index)
	{
		IsDirtys[Index]		= *(Values[Index]) != Last_Values[Index];
		Last_Values[Index]	= *(Values[Index]);

		if (IsDirtys[Index])
			OnChangeArray_Event.Broadcast(Index, *(Values[Index]));
	}

	FORCEINLINE TCsProperty_TArrayRef& operator=(const TCsProperty_TArrayRef& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			Values[I] = B.Values[I];
			UpdateIsDirty(I);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TArrayRef& B) const
	{
		for (uint8 I = 0; I < SIZE; ++I)
		{
			if (Values[I] != B.Values[I])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TArrayRef& B) const
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

	FORCEINLINE const uint8& Num() { return SIZE; }

	FORCEINLINE void Set(ValueType &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const int32 &Index, ValueType* inValue)
	{
		if (Index > CS_PRIMITIVE_TYPE_DEFAULT && Index < SIZE)
		{
			Values[Index] = inValue;
			UpdateIsDirty(Index);
		}
		else
		{
			Set(*inValue);
		}
	}

	FORCEINLINE const ValueType& operator[](const int32 &Index)
	{
		if (Override_Subscript.IsBound())
			return Override_Subscript.Execute(Index);
		return *(Values[Index]);
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const int32 &Index)
	{
		if (Override_Get.IsBound())
			return Override_Get.Execute(Index);
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT ? Value : *(Values[Index]); 
	}

	FORCEINLINE ValueType GetEX(const int32 &Index) { return GetDelegate.Execute(Index); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

		for (uint8 I = 0; I < SIZE; ++I)
		{
			IsDirtys[I] = false;
		}
	}

	FORCEINLINE void Clear(const int32 &Index)
	{
		IsDirtys[Index]	= false;
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
		OnChangeArray_Event.Clear();
	}

	FORCEINLINE const bool& HasChanged() { return IsDirty; }

	FORCEINLINE const bool& HasChanged(const int32 &Index)
	{
		return Index <= CS_PRIMITIVE_TYPE_DEFAULT || Index >= SIZE ? IsDirty : IsDirtys[Index];
	}

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		for (uint8 I = 0; I < SIZE; ++I)
		{
			UpdateIsDirty(I);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const int32 &Index)
	{
		UpdateIsDirty(Index);
		Clear(Index);
	}
};

template<typename ValueType>
struct TCsIntegralType_TArrayRef : public TCsProperty_TArrayRef<ValueType>
{
private:
	typedef TCsProperty_TArrayRef<ValueType> Super;

public:

	TCsIntegralType_TArrayRef() : Super(){}
	~TCsIntegralType_TArrayRef() {}

	ValueType Max()
	{
		ValueType max = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[I]));
		}
		return max;
	}

	ValueType Min()
	{
		ValueType min = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[I]));
		}
		return min;
	}
};

struct TCsIntegralType_TArrayRef_uint8 : public TCsIntegralType_TArrayRef<uint8>
{
private:
	typedef TCsIntegralType_TArrayRef<uint8> Super;

public:

	TCsIntegralType_TArrayRef_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRef_uint8() {}
};

struct TCsIntegralType_TArrayRef_int32 : public TCsIntegralType_TArrayRef<int32>
{
private:
	typedef TCsIntegralType_TArrayRef<int32> Super;

public:

	TCsIntegralType_TArrayRef_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TArrayRef_int32() {}
};

struct TCsIntegralType_TArrayRef_float : public TCsIntegralType_TArrayRef<float>
{
private:
	typedef TCsIntegralType_TArrayRef<float> Super;

public:

	TCsIntegralType_TArrayRef_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TArrayRef_float() {}
};

struct TCsProperty_TArrayRef_bool : public TCsProperty_TArrayRef<bool>
{
private:
	typedef TCsProperty_TArrayRef<bool> Super;

public:

	TCsProperty_TArrayRef_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TArrayRef_bool() {}

	bool Or()
	{
		bool or = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			or |= *(Values[I]);
		}
		return or ;
	}

	bool And()
	{
		bool and = *(Values[0]);

		for (uint8 I = 1; I < SIZE; ++I)
		{
			and &= *(Values[I]);
		}
		return and;
	}
};

#pragma endregion TArrayRef

// TMap
#pragma region

template<typename KeyType, typename ValueType>
struct TCsProperty_TMap
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;

public:

	TCsProperty_TMap() 
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMap() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType &Key)
	{
		Values.Add(Key, DefaultValue);
		Last_Values.Add(Key, DefaultValue);
		IsDirtys.Add(Key, false);
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const KeyType &Key)
	{
		IsDirtys[Key]	 = Values[Key] != Last_Values[Key];
		Last_Values[Key] = Values[Key];

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, Values[Key]);
	}

	FORCEINLINE TCsProperty_TMap& operator=(const TCsProperty_TMap& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = B.Values[Key];
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMap& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (Values[Key] != B.Values[Key])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMap& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType &InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, const ValueType &InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE ValueType& operator[](const KeyType &Key)
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& operator[](const KeyType &Key) const
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return Values[Key]; }

	FORCEINLINE ValueType GetEX(const KeyType &Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			IsDirtys[Key] = false;
		}
	}

	FORCEINLINE void Clear(const KeyType &Key)
	{
		IsDirtys[Key] = false;
	}

	void ResetValues()
	{
		Value	   = DefaultValue;
		Last_Value = Value;
		IsDirty	   = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key]	     = Value;
			Last_Values[Key] = Value;
			IsDirtys[Key]    = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const KeyType &Key) { return IsDirtys[Key]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			UpdateIsDirty(Key);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const KeyType &Key)
	{
		UpdateIsDirty(Key);
		Clear(Key);
	}
};

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMap : public TCsProperty_TMap<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMap<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMap() : Super(){}
	~TCsIntegralType_TMap() {}

	FORCEINLINE void Add(const ValueType& InValue)
	{
		Value += InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Add(const KeyType &Key, const ValueType &InValue)
	{
		Values[Key] += InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE void Subtract(const ValueType &InValue)
	{
		Value -= InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Subtract(const KeyType &Key, const ValueType &InValue)
	{
		Values[Index] -= inValue;
		UpdateIsDirty(Index);
	}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (KeyType)FMath::Max(max, Values[Keys[I]]);
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, Values[Keys[I]]);
		}
		return min;
	}
};

template<typename KeyType>
struct TCsIntegralType_TMap_uint8 : public TCsIntegralType_TMap<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMap<KeyType, uint8> Super;

public:

	TCsIntegralType_TMap_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMap_uint8() {}
};

template<typename KeyType>
struct TCsIntegralType_TMap_float : public TCsIntegralType_TMap<KeyType, float>
{
private:
	typedef TCsIntegralType_TMap<KeyType, float> Super;

public:

	TCsIntegralType_TMap_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMap_float() {}
};

template<typename KeyType>
struct TCsProperty_TMap_bool : public TCsProperty_TMap<KeyType, bool>
{
private:
	typedef TCsProperty_TMap<KeyType, bool> Super;

public:

	TCsProperty_TMap_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TMap_bool() {}

	FORCEINLINE bool Or()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool or = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			or |= Values[Keys[I]];
		}
		return or ;
	}

	FORCEINLINE bool And()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool and = Values[Keys[0]];

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			and &= Values[Keys[I]];
		}
		return and;
	}
};

#pragma endregion TMap

// TMapRef
#pragma region

template<typename KeyType, typename ValueType>
struct TCsProperty_TMapRef
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType*> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Get;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;
public:

	TCsProperty_TMapRef() 
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMapRef() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType &Key)
	{
		Values.Add(Key, nullptr);
		Last_Values.Add(Key, DefaultValue);
		IsDirtys.Add(Key, false);
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const KeyType &Key)
	{
		IsDirtys[Key]	 = *(Values[Key]) != Last_Values[Key];
		Last_Values[Key] = *(Values[Key]);

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, *(Values[Key]));
	}

	FORCEINLINE TCsProperty_TMapRef& operator=(const TCsProperty_TMapRef& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			*(Values[Key]) = *(B.Values[Key]);
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMapRef& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (*(Values[Key]) != *(B.Values[Key]))
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMapRef& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType &InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, ValueType* InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE const ValueType& operator[](const KeyType &Key)
	{
		return *(Values[Key]);
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return *(Values[Key]); }

	FORCEINLINE ValueType GetEX(const KeyType &Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			IsDirtys[Key] = false;
		}
	}

	FORCEINLINE void Clear(const KeyType &Key)
	{
		IsDirtys[Key] = false;
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = nullptr;
			Last_Values[Key] = Value;
			IsDirtys[Key] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const KeyType &Key) { return IsDirtys[Key]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			UpdateIsDirty(Key);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const KeyType &Key)
	{
		UpdateIsDirty(Key);
		Clear(Key);
	}
};

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMapRef : public TCsProperty_TMapRef<KeyType, ValueType>
{
private:
	typedef TCsProperty_TMapRef<KeyType, ValueType> Super;

public:

	TCsIntegralType_TMapRef() : Super(){}
	~TCsIntegralType_TMapRef() {}

	FORCEINLINE ValueType Max()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType max = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			max = (ValueType)FMath::Max(max, *(Values[Keys[I]]));
		}
		return max;
	}

	FORCEINLINE ValueType Min()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		ValueType min = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			min = (ValueType)FMath::Min(min, *(Values[Keys[I]]));
		}
		return min;
	}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_uint8 : public TCsIntegralType_TMapRef<KeyType, uint8>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, uint8> Super;

public:

	TCsIntegralType_TMapRef_uint8() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMapRef_uint8() {}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_int32 : public TCsIntegralType_TMapRef<KeyType, int32>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, int32> Super;

public:

	TCsIntegralType_TMapRef_int32() : Super()
	{
		DefaultValue = 0;
	}
	~TCsIntegralType_TMapRef_int32() {}
};

template<typename KeyType>
struct TCsIntegralType_TMapRef_float : public TCsIntegralType_TMapRef<KeyType, float>
{
private:
	typedef TCsIntegralType_TMapRef<KeyType, float> Super;

public:

	TCsIntegralType_TMapRef_float() : Super()
	{
		DefaultValue = 0.0f;
	}
	~TCsIntegralType_TMapRef_float() {}
};

template<typename KeyType>
struct TCsProperty_TMapRef_bool : public TCsProperty_TMapRef<KeyType, bool>
{
private:
	typedef TCsProperty_TMapRef<KeyType, bool> Super;

public:

	TCsProperty_TMapRef_bool() : Super()
	{
		DefaultValue = false;
	}
	~TCsProperty_TMapRef_bool() {}

	FORCEINLINE bool Or()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool or = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			or |= *(Values[Keys[I]]);
		}
		return or ;
	}

	FORCEINLINE bool And()
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		bool and = *(Values[Keys[0]]);

		const uint8 Count = Keys.Num();

		for (uint8 I = 1; I < Count; ++I)
		{
			and &= *(Values[Keys[I]]);
		}
		return and;
	}
};

#pragma endregion TMapRef

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
	typedef TCsProperty_Multi_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern CSCORE_API const TCsString Bool;
		extern CSCORE_API const TCsString Uint8;
		extern CSCORE_API const TCsString Int32;
		extern CSCORE_API const TCsString Float;
		extern CSCORE_API const TCsString _FString;
		extern CSCORE_API const TCsString FName;
		extern CSCORE_API const TCsString FVector;
		extern CSCORE_API const TCsString FRotator;
		extern CSCORE_API const TCsString FColor;
	}

	namespace Ref
	{
		extern CSCORE_API const Type Bool;
		extern CSCORE_API const Type Uint8;
		extern CSCORE_API const Type Int32;
		extern CSCORE_API const Type Float;
		extern CSCORE_API const Type _FString;
		extern CSCORE_API const Type FName;
		extern CSCORE_API const Type FVector;
		extern CSCORE_API const Type FRotator;
		extern CSCORE_API const Type FColor;
		extern CSCORE_API const Type ECsMemberType_MAX;
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

#pragma endregion Property Types

// Blueprint Property Types
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsBpProperty_bool
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property bool")
	bool DefaultValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property bool")
	bool Value;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property bool")
	bool Last_Value;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property bool")
	bool IsDirty;
public:
	TMulticastDelegate<void, const bool&> OnChange_Event;

public:
	FCsBpProperty_bool() :
		DefaultValue(false),
		Value(false),
		Last_Value(false),
		IsDirty(false)
	{
	}
	~FCsBpProperty_bool() {}

	void SetDefaultValue(const bool &inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE FCsBpProperty_bool& operator=(const bool& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const bool& B) const
	{
		return Value == B;
	}

	FORCEINLINE bool operator!=(const bool& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const bool &inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const bool& Get() { return Value; }

	FORCEINLINE void Clear()
	{
		Last_Value = Value;
		IsDirty = false;
	}

	void ResetValue()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE void MarkDirty() { IsDirty = true; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

#pragma endregion Blueprint Property Types

// Vector Types
#pragma region

// TODO: Look at FIntPoint, FVector ... etc for proper setup

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8Point
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

	FORCEINLINE FCsUint8Point& operator=(const FCsUint8Point& B)
	{
		X = B.X;
		Y = B.Y;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8Point& B) const
	{
		return X == B.X && Y == B.Y;
	}

	FORCEINLINE bool operator!=(const FCsUint8Point& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // X
			 + 8;// Y
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8MatrixDimension
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

	FORCEINLINE FCsUint8MatrixDimension& operator=(const FCsUint8MatrixDimension& B)
	{
		RowSpan	   = B.RowSpan;
		ColumnSpan = B.ColumnSpan;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixDimension& B) const
	{
		return RowSpan == B.RowSpan && ColumnSpan == B.ColumnSpan;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixDimension& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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

	FORCEINLINE void Set(const uint8 &InRowSpan, const uint8 &InColumnSpan)
	{
		RowSpan    = InRowSpan;
		ColumnSpan = InColumnSpan;
	}

	FORCEINLINE uint8 GetRow(const int32 &Index)
	{
		return (Index / RowSpan) % RowSpan;
	}

	FORCEINLINE uint8 GetColumn(const int32 &Index)
	{
		return Index % RowSpan;
	}

	FORCEINLINE uint16 GetSize()
	{
		return RowSpan * ColumnSpan;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // RowSpan
			 + 8;// ColumnSpan
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsUint8MatrixCoordinate
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

	FORCEINLINE FCsUint8MatrixCoordinate& operator=(const FCsUint8MatrixCoordinate& B)
	{
		Row    = B.Row;
		Column = B.Column;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixCoordinate& B) const
	{
		return Row == B.Row && Column == B.Column;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixCoordinate& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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

	FORCEINLINE void Set(const uint8 &InRow, const uint8 &InColumn)
	{
		Row    = InRow;
		Column = InColumn;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // Row
			 + 8;// Column
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsVectorFlag
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

	FORCEINLINE FCsVectorFlag& operator=(const FCsVectorFlag& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsVectorFlag& B) const
	{
		return X == B.X && Y == B.Y && Z == B.Z;
	}

	FORCEINLINE bool operator!=(const FCsVectorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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
		return Value ? NCsCached::Str::True : NCsCached::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = Z = false;

		// The initialization is only successful if the X, Y and Z values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, NCsCached::Str::XEquals, X) && 
								 InitFromString_Internal(InSourceString, NCsCached::Str::YEquals, Y) &&
								 InitFromString_Internal(InSourceString, NCsCached::Str::ZEquals, Z);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool &Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == NCsCached::Str::_true || Bool == NCsCached::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == NCsCached::Str::_false || Bool == NCsCached::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool &InX, const bool &InY, const bool &InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	FORCEINLINE void ApplyLock(FVector &V)
	{
		V.X = X ? 0.0f : V.X;
		V.Y = Y ? 0.0f : V.Y;
		V.Z = Z ? 0.0f : V.Z;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // X
			 + 1 // Y
			 + 1;// Z
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsRotatorFlag
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

	FORCEINLINE bool operator==(const FCsRotatorFlag& B) const
	{
		return Roll == B.Roll && Pitch == B.Pitch && Yaw == B.Yaw;
	}

	FORCEINLINE bool operator!=(const FCsRotatorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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
		return Value ? NCsCached::Str::True : NCsCached::Str::False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		Roll = Pitch = Yaw = false;

		// The initialization is only successful if the Roll, Pitch and Yaw values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, NCsCached::Str::RollEquals, Roll) &&
								 InitFromString_Internal(InSourceString, NCsCached::Str::PitchEquals, Pitch) &&
								 InitFromString_Internal(InSourceString, NCsCached::Str::YawEquals, Yaw);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool &Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == NCsCached::Str::_true || Bool == NCsCached::Str::One)
		{
			Value = true;
			return true;
		}
		if (Bool == NCsCached::Str::_false || Bool == NCsCached::Str::Zero)
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool &InRoll, const bool &InPitch, const bool &InYaw)
	{
		Roll = InRoll;
		Pitch = InPitch;
		Yaw = InYaw;
	}

	FORCEINLINE void ApplyLock(FRotator &R)
	{
		R.Roll = Roll ? 0.0f : R.Roll;
		R.Pitch = Pitch ? 0.0f : R.Pitch;
		R.Yaw = Yaw ? 0.0f : R.Yaw;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // Roll
			 + 1 // Pitch
			 + 1;// Yaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalVectorInterval
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

	FORCEINLINE FCsOptionalVectorInterval& operator=(const FCsOptionalVectorInterval& B)
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

	FORCEINLINE bool operator==(const FCsOptionalVectorInterval& B) const
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

	FORCEINLINE bool operator!=(const FCsOptionalVectorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Vector
			   + 1 // bIntervalX
			   + (2 * 64) // IntervalX
			   + 1 // bIntervalY
			   + (2 * 64) // IntervalY
			   + 1 // bIntervalZ
			   + (2 * 64); // IntervalZ
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Vector.X = bIntervalX ? FMath::RandRange(IntervalX.Min, IntervalX.Max) : Vector.X;
		Vector.Y = bIntervalY ? FMath::RandRange(IntervalY.Min, IntervalY.Max) : Vector.Y;
		Vector.Z = bIntervalZ ? FMath::RandRange(IntervalZ.Min, IntervalZ.Max) : Vector.Z;
	}

	FORCEINLINE const FVector& Get()
	{
		return Vector;
	}
};

USTRUCT(BlueprintType)
struct CSCORE_API FCsOptionalRotatorInterval
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

	FORCEINLINE FCsOptionalRotatorInterval& operator=(const FCsOptionalRotatorInterval& B)
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

	FORCEINLINE bool operator==(const FCsOptionalRotatorInterval& B) const
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

	FORCEINLINE bool operator!=(const FCsOptionalRotatorInterval& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
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

	FORCEINLINE uint32 GetBits() const
	{
		return  (3 * 64) // Rotator
				+ 1 // bIntervalRoll
				+ (2 * 64) // IntervalRoll
				+ 1 // bIntervalPitch
				+ (2 * 64) // IntervalPitch
				+ 1 // bIntervalYaw
				+ (2 * 64); // IntervalYaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}

	void Seed()
	{
		Rotator.Roll = bIntervalRoll ? FMath::RandRange(IntervalRoll.Min, IntervalRoll.Max) : Rotator.Roll;
		Rotator.Pitch = bIntervalPitch ? FMath::RandRange(IntervalPitch.Min, IntervalPitch.Max) : Rotator.Pitch;
		Rotator.Yaw = bIntervalYaw ? FMath::RandRange(IntervalYaw.Min, IntervalYaw.Max) : Rotator.Yaw;
	}

	FORCEINLINE const FRotator& Get()
	{
		return Rotator;
	}
};

#pragma endregion Vector Types

// String
#pragma region

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

struct CSCORE_API EMCsStringCompare : public TCsEnumMap<ECsStringCompare::Type>
{
protected:
	EMCsStringCompare() {}
	EMCsStringCompare(const EMCsStringCompare &) = delete;
	EMCsStringCompare(EMCsStringCompare &&) = delete;
public:
	~EMCsStringCompare() {}
private:
	static EMCsStringCompare* Instance;

public:
	static EMCsStringCompare& Get();
};

namespace ECsStringCompare
{
	namespace Ref
	{
		extern CSCORE_API const Type Equals;
		extern CSCORE_API const Type StartsWith;
		extern CSCORE_API const Type EndsWith;
		extern CSCORE_API const Type Contains;
		extern CSCORE_API const Type ECsStringCompare_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return EMCsStringCompare::Get().ToString(EType);
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		return EMCsStringCompare::Get().ToType(String);
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

#pragma endregion String

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ShortCode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	uint8 Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data_ShortCode")
	FName ShortCode;

public:
	FCsData_ShortCode()
	{
		Type = UINT8_MAX;
		ShortCode = CS_INVALID_SHORT_CODE;
	}
	virtual ~FCsData_ShortCode() {}

	FORCEINLINE FCsData_ShortCode& operator=(const FCsData_ShortCode& B)
	{
		Type = B.Type;
		ShortCode = B.ShortCode;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsData_ShortCode& B) const
	{
		if (Type != B.Type)
			return false;
		if (ShortCode != B.ShortCode)
			return false;
		return true;
	}

	FORCEINLINE bool operator!=(const FCsData_ShortCode& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool IsValid()
	{
		if (Type == UINT8_MAX)
			return false;
		if (ShortCode == CS_INVALID_SHORT_CODE)
			return false;
		return true;
	}
};
