// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#pragma once

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

	FORCEINLINE const FString& GetName()
	{
		return MapName;
	}

	FORCEINLINE const FString& GetEnumName()
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