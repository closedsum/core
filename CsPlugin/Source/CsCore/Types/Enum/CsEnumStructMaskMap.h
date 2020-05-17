// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#pragma once

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMaskMap
{
protected:
	FString MapName;
	FString EnumName;
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
		NONE.Name_Internal = FName("MAX");
		NONE.DisplayName = TEXT("NONE");
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

	FORCEINLINE const FString& GetName()
	{
		return MapName;
	}

	FORCEINLINE const FString& GetEnumName()
	{
		return EnumName;
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
		EndPosition = 0;
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
		EndPosition = 0;
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

#define CS_ENUM_STRUCT_MASK_MAP_BODY(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMaskMap<EnumStruct, EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			EnumName = #EnumStruct; \
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