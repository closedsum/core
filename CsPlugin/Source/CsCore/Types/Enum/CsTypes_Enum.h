// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#include "Types/CsCached.h"

#include "CsTypes_Enum.generated.h"
#pragma once

#define CS_INVALID_ENUM_TO_STRING NCsCached::Str::INVALID
#define CS_INVALID_ENUM_TO_NAME NCsCached::Name::None

// EnumMap
#pragma region

template<typename EnumType>
struct TCsEnumMap
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
	EnumType MAX;
protected:
	TCsEnumMap()
	{
		Count = 0;
		bExplicitMAX = false;
		EndPosition = 0;
	}
public:
	virtual ~TCsEnumMap() {}

protected:
	bool bExplicitMAX;
private:
	int32 EndPosition;
public:

	// Range-based for loop
	class ConstIterator
	{
		TCsEnumMap<EnumType>* Map;
		int32 Position;
	public:
		ConstIterator(TCsEnumMap<EnumType>* _Map, int32 _Position) :Map(_Map), Position(_Position) {}

		const EnumType& operator*() const { return Map->GetEnumAt(Position); }
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

	FORCEINLINE const FName& GetFName()
	{
		return MapFName;
	}

	FORCEINLINE const FString& GetEnumName()
	{
		return EnumName;
	}

	FORCEINLINE const FName& GetEnumFName()
	{
		return EnumFName;
	}

	FORCEINLINE EnumType Add(const EnumType& Enum, const FString& Name, const FString& DisplayName)
	{
		Enums.Add(Enum);
		MAX = Enum;
		++Count;
		EndPosition = bExplicitMAX ? Count - 1 : Count;
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

	FORCEINLINE const TCHAR* ToChar(const EnumType& Enum)
	{
		return *ToString(Enum);
	}

	FORCEINLINE const TCHAR* ToChar(const int32& Index)
	{
		return ToChar(Enums[Index]);
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

#define CS_ENUM_MAP_BODY(EnumMap, EnumType) \
	private: \
		typedef TCsEnumMap<EnumType> Super; \
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

#define CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EnumMap, EnumType) \
	private: \
		typedef TCsEnumMap<EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			MapFName = FName(#EnumMap); \
			EnumName = #EnumType; \
			EnumFName = FName(#EnumType); \
			bExplicitMAX = true; \
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

#define CS_ADD_TO_ENUM_MAP(EnumMap, EnumElementName) const Type EnumElementName = EnumMap::Get().Add(Type::EnumElementName, #EnumElementName)
#define CS_ADD_TO_ENUM_MAP_CUSTOM(EnumMap, EnumElementName, DisplayName) const Type EnumElementName = EnumMap::Get().Add(Type::EnumElementName, #EnumElementName, TEXT(DisplayName))

#pragma endregion EnumMap

// EnumMaskMap
#pragma region

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

#pragma endregion EnumMaskMap

// EnumFlagMap
#pragma region

template<typename EnumType>
struct TCsEnumFlagMap
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

#define CS_ENUM_FLAG_MAP_BODY(EnumMap, EnumType) \
	private: \
		typedef TCsEnumFlagMap<EnumType> Super; \
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

#pragma endregion EnumFlagMap

// FECsEnum
#pragma region

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

	FECsEnum() :
		Name(),
		DisplayName(),
		Name_Internal(NAME_None)
	{
	}

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

	FORCEINLINE const FString& GetName() const 
	{
		return Name;
	}

	FORCEINLINE const FName& GetFName() const 
	{
		return Name_Internal;
	}

	FORCEINLINE const FString& GetDisplayName() const 
	{
		return DisplayName;
	}
};

#pragma endregion FECsEnum

// Enum_uint8
#pragma region

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

#pragma endregion Enum_uint8

// EnumStructMap
#pragma region

template<typename EnumStruct, typename EnumType>
struct TCsEnumStructMap
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
	EnumStruct MAX;
protected:
	TCsEnumStructMap()
	{
		Count = 0;
		MAX.Value = (EnumType)0;
		MAX.Name = TEXT("MAX");
		MAX.DisplayName = TEXT("MAX");
		bExplicitMAX = false;
		EndPosition = 0;
	}
public:
	virtual ~TCsEnumStructMap() {}

protected:
	bool bExplicitMAX;
private:
	int32 EndPosition;
public:

	// Range-based for loop
	class ConstIterator
	{
		TCsEnumStructMap<EnumStruct, EnumType>* Map;
		int32 Position;
	public:
		ConstIterator(TCsEnumStructMap<EnumStruct, EnumType>* _Map, int32 _Position) :Map(_Map), Position(_Position) {}

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

	FORCEINLINE const FName& GetFName()
	{
		return MapFName;
	}

	FORCEINLINE const FString& GetEnumName()
	{
		return EnumName;
	}

	FORCEINLINE const FName& GetEnumFName()
	{
		return EnumFName;
	}

	FORCEINLINE EnumStruct Create(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		EnumType Index = (EnumType)Enums.Num();
		EnumStruct E(Index, Name, DisplayName);

		Enums.Add(E);
		++Count;
		EndPosition = bExplicitMAX ? Count - 1 : Count;
		if (UserDefinedEnum)
		{
			UserDefinedEnums.Add(E);
			UserDefinedNameMap.Add(Name, E);
		}
		NameMap.Add(Name, E);
		DisplayNameMap.Add(DisplayName, E);
		NameInternalMap.Add(E.Name_Internal, E);
		TypeMap.Add(Index, E);
		if (bExplicitMAX)
			MAX = E;
		else
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

	void ClearUserDefinedEnums()
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

#define CS_ENUM_STRUCT_MAP_BODY(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMap<EnumStruct, EnumType> Super; \
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

#define CS_ENUM_STRUCT_MAP_BODY_WITH_EXPLICIT_MAX(EnumMap, EnumStruct, EnumType) \
	private: \
		typedef TCsEnumStructMap<EnumStruct, EnumType> Super; \
	protected: \
		EnumMap() : Super() \
		{ \
			MapName = #EnumMap; \
			EnumName = #EnumStruct; \
			bExplicitMAX = true; \
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

#define CS_CREATE_ENUM_STRUCT(EnumMap, EnumElementName) const Type EnumElementName = EnumMap::Get().Create(#EnumElementName, false)
#define CS_CREATE_ENUM_STRUCT_CUSTOM(EnumMap, EnumElementName, DisplayName) const Type EnumElementName = EnumMap::Get().Create(#EnumElementName, TEXT(DisplayName), false)


#pragma endregion EnumStructMap

// EnumMask_int32
#pragma region

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

#pragma endregion EnumMask_int32

// EnumMask_uint32
#pragma region

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

#pragma endregion EnumMask_uint32

// EnumStructMaskMap
#pragma region

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

#pragma endregion EnumStructMaskMap

// UserDefinedEnum
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsUserDefinedEnum : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserDefinedEnum)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserDefinedEnum)

struct CSCORE_API EMCsUserDefinedEnum : public TCsEnumStructMap<FECsUserDefinedEnum, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserDefinedEnum, FECsUserDefinedEnum, uint8)
};

namespace NCsUserDefinedEnum
{
	typedef FECsUserDefinedEnum Type;

	extern CSCORE_API const Type FECsDataType;
	extern CSCORE_API const Type FECsDataCollectionType;
	extern CSCORE_API const Type FECsInputAction;
	extern CSCORE_API const Type FECsInputActionMap;
	extern CSCORE_API const Type FECsGameEvent;
}

#pragma endregion UserDefinedEnum

// FCsUserDefinedEnum
#pragma region

class UUserDefinedEnum;

USTRUCT(BlueprintType)
struct CSCORE_API FCsUserDefinedEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UUserDefinedEnum> Enum;

	UPROPERTY(Transient, BlueprintReadOnly)
	UUserDefinedEnum* Enum_Internal;

	FCsUserDefinedEnum() :
		Enum(),
		Enum_Internal()
	{
	}

	FORCEINLINE UUserDefinedEnum* Get() { return Enum_Internal; }
};

#pragma endregion FCsUserDefinedEnum