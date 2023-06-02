// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsTypes_Enum.h"

template<typename EnumType>
struct TCsEnumMaskMap
{
protected:
	FString MapName;
	FString EnumName;
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

	FORCEINLINE const FString& GetName() const
	{
		return MapName;
	}

	FORCEINLINE const FString& GetEnumName() const
	{
		return EnumName;
	}

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

	FORCEINLINE const EnumType& operator[](const FString &Name) const
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& operator[](const FName &Name) const
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumType& Enum) const
	{
		return Enums.Find(Enum) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name) const
	{
		return FromNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name) const
	{
		return FromNameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const EnumType& Enum) const
	{
		checkf(IsValidEnum(Enum), TEXT("%s: Enum: %s is NOT Valid"), *Context, *(ToString(Enum)));

		return true;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const FString& EnumElementName, const EnumType& Enum) const
	{
		checkf(IsValidEnum(Enum), TEXT("%s: %s: %s is NOT Valid"), *Context, *EnumElementName, *(ToString(Enum)));

		return true;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const FString& Name) const
	{
		checkf(IsValidEnum(Name), TEXT("%s: There is NO Enum with Name: %s."), *Context, *Name);

		return true;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const FName& Name) const
	{
		checkf(IsValidEnum(Name), TEXT("%s: There is NO Enum with Name: %s."), *Context, *(Name.ToString()));

		return true;
	}

	FORCEINLINE bool IsValidFlag(const uint64& Flag) const
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE bool IsValidFlagChecked(const FString& Context, const uint64& Flag) const
	{
		checkf(FlagMap.Find(Flag) != nullptr, TEXT("%s: Flag: %llu is NOT Valid"), *Context, Flag);

		return true;
	}

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index) const
	{
		return Index < Count ? Enums[Index] : None;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name) const
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name) const
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : None;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name) const
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name) const
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : None;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName) const
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumType& GetEnumByFlag(const uint64& Flag) const
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumType& GetSafeEnumByFlag(const uint64& Flag) const
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : None;
	}

	FORCEINLINE const int32& Num() const
	{
		return Count;
	}

	FORCEINLINE const FString& ToString(const EnumType& Enum) const
	{
		if (const FString* Name = ToNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const int32& Index) const
	{
		if (Index >= Count)
			return CS_INVALID_ENUM_TO_STRING;
		return ToString(Enums[Index]);
	}

	FORCEINLINE const TCHAR* ToChar(const EnumType& Enum)
	{
		return *ToString(Enum);
	}

	FORCEINLINE const TCHAR* ToChar(const int32& Index)
	{
		return ToChar(Enums[Index]);
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

	FORCEINLINE const FName& ToName(const EnumType& Enum) const
	{
		if (const FName* Name = ToNameInternalMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_NAME;
	}

	FORCEINLINE const FString& ToDisplayName(const EnumType& Enum) const
	{
		if (const FString* Name = ToDisplayNameMap.Find(Enum))
			return *Name;
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const EnumType& ToType(const FString& Name) const
	{
		if (const EnumType* Enum = FromNameMap.Find(Name))
			return *Enum;
		return None;
	}

	FORCEINLINE const EnumType& ToType(const FName& Name) const
	{
		if (const EnumType* Enum = FromNameInternalMap.Find(Name))
			return *Enum;
		return None;
	}
};

#define CS_ENUM_MASK_MAP_BODY(EnumMap, EnumType) \
	private: \
		typedef TCsEnumMaskMap<EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			EnumName = #EnumType; \
		} \
		EnumMap(const EnumMap &) = delete; \
		EnumMap(EnumMap &&) = delete; \
	public: \
		~EnumMap() {} \
		\
		static EnumMap& Get() \
		{ \
			static EnumMap Instance; \
			return Instance; \
		}

// Assume typedef "EnumType" Type and typedef "EnumMapType" EnumMapType
#define CS_ADD_TO_ENUM_MASK_MAP(EnumElementName) const Type EnumElementName = EnumMapType::Get().Add(Type::EnumElementName, #EnumElementName)
#define CS_ADD_TO_ENUM_MASK_MAP_CUSTOM(EnumElementName, DisplayName) const Type EnumElementName = EnumMapType::Get().Add(Type::EnumElementName, #EnumElementName, TEXT(DisplayName))