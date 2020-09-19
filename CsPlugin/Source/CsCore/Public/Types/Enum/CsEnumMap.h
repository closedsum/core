// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#pragma once

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

	FORCEINLINE const EnumType& operator[](const uint8& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& operator[](const FString& Name) const
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& operator[](const FName& Name) const
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

	FORCEINLINE const EnumType& GetEnumAt(const int32& Index) const
	{
		return Enums[Index];
	}

	FORCEINLINE const EnumType& GetSafeEnumAt(const int32& Index) const
	{
		return Index < Count ? Enums[Index] : MAX;
	}

	FORCEINLINE const EnumType& GetEnum(const FString& Name) const
	{
		return FromNameMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FString& Name) const
	{
		return IsValidEnum(Name) ? FromNameMap[Name] : MAX;
	}

	FORCEINLINE const EnumType& GetEnum(const FName& Name) const
	{
		return FromNameInternalMap[Name];
	}

	FORCEINLINE const EnumType& GetSafeEnum(const FName& Name) const
	{
		return IsValidEnum(Name) ? FromNameInternalMap[Name] : MAX;
	}

	FORCEINLINE const EnumType& GetEnumByDisplayName(const FString& DisplayName) const
	{
		return FromDisplayNameMap[DisplayName];
	}

	FORCEINLINE const int32& Num() const
	{
		return Count;
	}

	FORCEINLINE const EnumType& GetMAX() const
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


#define CS_NESTED_ENUM_ADD_TO_ENUM_MAP(Class, Namespace, Ref, EnumMap, EnumType, EnumElementName) const Class::EnumType Class::Namespace::Ref::EnumElementName = Class::EnumMap::Get().Add(Class::EnumType::EnumElementName, #EnumElementName);