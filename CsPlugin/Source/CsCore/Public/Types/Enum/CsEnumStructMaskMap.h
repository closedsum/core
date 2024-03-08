// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsTypes_Enum.h"

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMaskMap
{
protected:
	FString MapName;
	FName MapFName;
	FString EnumName;
	FName EnumFName;
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
		NONE = EnumStruct((EnumType)0, TEXT("NONE"), TEXT("NONE"));
		NONE.SetFName(FName("MAX"));
		NONE.SetMask(0);
		EndPosition = 0;
	}
public:
	virtual ~TCsEnumStructMaskMap() {}

private:
	int32 EndPosition;
public:

	// Range-based for loop
	class ConstIterator
	{
		TCsEnumStructMaskMap<EnumStruct, EnumType>* Map;
		int32 Position;
	public:
		ConstIterator(TCsEnumStructMaskMap<EnumStruct, EnumType>* _Map, int32 _Position) :Map(_Map), Position(_Position) {}

		const EnumStruct& operator*() const { return Map->GetEnumAt(Position); }
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

	FORCEINLINE const FName& GetFName() const
	{
		return MapFName;
	}

	FORCEINLINE const FString& GetEnumName() const
	{
		return EnumName;
	}

	FORCEINLINE const FName& GetEnumFName() const
	{
		return EnumFName;
	}

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
		EndPosition = Count;
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
		EndPosition = Count;
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

	FORCEINLINE const EnumStruct& operator[](const EnumType& Type) const
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& operator[](const FString& Name) const
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& operator[](const FName& Name) const
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE bool IsValidEnum(const EnumStruct& Enum) const
	{
		return Enum.IsValid() && Enum != NONE && Enums.Find(Enum) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name) const
	{
		return NameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name) const
	{
		return NameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnumChecked(const EnumStruct& Enum) const
	{
		const bool Result = Enum.IsValid() && Enum != NONE && Enums.Find(Enum) > INDEX_NONE;

		checkf(Result, TEXT("%s::IsValidEnumChecked: Enum: %s is NOT Valid"), *MapName, *(Enum.GetFName().ToString()));

		return Result;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const EnumStruct& Enum) const
	{
		const bool Result = Enum.IsValid() && Enum != NONE && Enums.Find(Enum) > INDEX_NONE;

		checkf(Result, TEXT("%s: Enum: %s is NOT Valid"), *Context, *(Enum.GetFName().ToString()));

		return Result;
	}

	FORCEINLINE bool IsValidEnumChecked(const FString& Context, const FString& EnumElementName, const EnumStruct& Enum) const
	{
		const bool Result = Enum.IsValid() && Enum != NONE && Enums.Find(Enum) > INDEX_NONE;

		checkf(Result, TEXT("%s: %s: %s is NOT Valid"), *Context, *EnumElementName, *(Enum.GetFName().ToString()));

		return Result;
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

	FORCEINLINE bool IsValidEnumByDisplayName(const FString& Name) const
	{
		return DisplayNameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidFlag(const uint64& Flag) const
	{
		return FlagMap.Find(Flag) != nullptr;
	}

	FORCEINLINE const EnumStruct& GetEnumAt(const int32& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumAt(const int32& Index) const
	{
		return Index < Count ? Enums[Index] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FString& Name) const
	{
		return NameMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FString& Name) const
	{
		return IsValidEnum(Name) ? NameMap[Name] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const FName& Name) const
	{
		return NameInternalMap[Name];
	}

	FORCEINLINE const EnumStruct& GetSafeEnum(const FName& Name) const
	{
		return IsValidEnum(Name) ? NameInternalMap[Name] : NONE;
	}

	FORCEINLINE const EnumStruct& GetEnum(const EnumType& Type) const
	{
		return TypeMap[Type];
	}

	FORCEINLINE const EnumStruct& GetEnumByDisplayName(const FString& DisplayName) const
	{
		return DisplayNameMap[DisplayName];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumByDisplayName(const FString& DisplayName) const
	{
		if (const EnumStruct* EnumPtr = DisplayNameMap.Find(DisplayName))
			return *EnumPtr;
		return NONE;
	}

	FORCEINLINE const EnumStruct& GetEnumByFlag(const uint64& Flag) const
	{
		return FlagMap[Flag];
	}

	FORCEINLINE const EnumStruct& GetSafeEnumByFlag(const uint64& Flag) const
	{
		return IsValidFlag(Flag) ? FlagMap[Flag] : NONE;
	}

	FORCEINLINE const int32& Num() const
	{
		return Count;
	}

	FORCEINLINE const EnumStruct& GetNONE() const
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
			if (CS_TEST_BITFLAG(Mask, Enum.GetMask()))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += Enum.GetName();
				IsFirst = false;
			}
		}

		// (String == TEXT(""))
		if (String == NCsCached::Str::Empty)
			return NCsCached::Str::None;
		// TEXT("None")
		return String;
	}

	FORCEINLINE void ClearUserDefinedEnums()
	{
		const int32 StartSize = Enums.Num();

		for (int32 I = StartSize - 1; I >= 0; --I)
		{
			const EnumStruct& E = Enums[I];

			if (EnumStruct* EnumPtr = UserDefinedNameMap.Find(E.GetName()))
			{
				NameMap.Remove(E.GetName());
				DisplayNameMap.Remove(E.GetDisplayName());
				NameInternalMap.Remove(E.GetFName());
				TypeMap.Remove((EnumType)E.GetValue());
				FlagMap.Remove((uint64)E.GetMask());
				Enums.RemoveAt(I);
			}
		}

		// Reset maps with the update values 
		Count = Enums.Num();
		EndPosition = Count;

		for (int32 I = 0; I < Count; ++I)
		{
			EnumStruct& E = Enums[I];

			E.SetValue((EnumType)I);
			E.UpdateMask();

			NameMap[E.GetName()] = E;
			DisplayNameMap[E.GetDisplayName()] = E;
			NameInternalMap[E.GetFName()] = E;
			TypeMap[E.GetValue()] = E;
			FlagMap[E.GetMask()] = E;
		}

		UserDefinedEnums.Reset();
		UserDefinedNameMap.Reset();
	}
};

#define CS_ENUM_STRUCT_MASK_MAP_BODY(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMaskMap<EnumStruct, EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			MapFName = FName(*MapName); \
			EnumName = #EnumStruct; \
			EnumFName = FName(*EnumName); \
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