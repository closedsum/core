// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#pragma once

template<typename EnumType>
struct TCsEnumFlagMap
{
protected:
	FString MapName;
	FName MapFName;
	FString EnumName;
	FName EnumFName;
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
		EndPosition = 0;
	}
public:
	virtual ~TCsEnumFlagMap() {}

private:
	int32 EndPosition;
public:

	// Range-based for loop
	class ConstIterator
	{
		TCsEnumFlagMap<EnumType>* Map;
		int32 Position;
	public:
		ConstIterator(TCsEnumFlagMap<EnumType>* _Map, int32 _Position) :Map(_Map), Position(_Position) {}

		const EnumType& operator*() const { return Map->GetEnumAt(Position); }
		ConstIterator& operator++() { ++Position; return *this; }
		bool operator!=(const ConstIterator& It) const { return Position != It.Position; }
	};

public:

	ConstIterator const begin() { return { this, 0 }; }
	ConstIterator const end() { return { this, EndPosition }; }

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
		EndPosition = Count;
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

	FORCEINLINE bool IsValidFlag(const uint32& Flag) const
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index) const
	{
		return Index < Count ? Enums[Index] : First;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name) const
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name) const
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : First;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name) const
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name) const
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : First;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName) const
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumType& GetEnumByFlag(const uint32& Flag) const
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumType& GetSafeEnumByFlag(const uint32& Flag) const
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : First;
	}

	FORCEINLINE const int32& Num() const
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

#define CS_ENUM_FLAG_MAP_BODY(EnumMap, EnumType) \
	private: \
		typedef TCsEnumFlagMap<EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			MapFName = FName(#EnumMap); \
			EnumName = #EnumType; \
			EnumFName = FName(#EnumType); \
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
#define CS_ADD_TO_ENUM_FLAG_MAP(EnumElementName) const Type EnumElementName = EnumMapType::Get().Add(Type::EnumElementName, #EnumElementName)
#define CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(EnumElementName, DisplayName) const Type EnumElementName = EnumMapType::Get().Add(Type::EnumElementName, #EnumElementName, TEXT(DisplayName))