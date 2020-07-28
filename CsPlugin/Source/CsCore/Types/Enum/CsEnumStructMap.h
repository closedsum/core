// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"

#pragma once

#define CS_INVALID_ENUM_TO_STRING NCsCached::Str::INVALID
#define CS_INVALID_ENUM_TO_NAME NCsCached::Name::None

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
		MAX.Name_Internal = FName("MAX");
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

	const EnumStruct& Create(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
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
		return Enums.Last();
	}

	FORCEINLINE const EnumStruct& Create(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return Create(Name, Name, UserDefinedEnum);
	}
	
#if WITH_EDITOR

	bool CreateSafe(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum = false)
	{
		// Check Name already exists
		if (NameMap.Find(Name) != nullptr)
			return false;
		// Check DisplayName already exists
		if (DisplayNameMap.Find(DisplayName) != nullptr)
			return false;

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
		return true;
	}

	FORCEINLINE bool CreateSafe(const FString& Name, const bool& UserDefinedEnum = false)
	{
		return CreateSafe(Name, Name, UserDefinedEnum);
	}

#endif // #if WITH_EDITOR
	
	bool Remove(const EnumStruct& E)
	{
		bool Success = Enums.Remove(E) > 0;
		UserDefinedEnums.Remove(E);
		UserDefinedNameMap.Remove(E.GetName());
		NameMap.Remove(E.GetName());
		DisplayNameMap.Remove(E.GetDisplayName());
		NameInternalMap.Remove(E.GetFName());
		TypeMap.Remove(E.GetValue());

		MAX.Value = (EnumType)Enums.Num();

		return Success;
	}

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
		return E.IsValid() && E.GetValue() < Count && Enums.Find(E) > INDEX_NONE;
	}

	FORCEINLINE bool IsValidEnum(const FString& Name)
	{
		return NameMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnum(const FName& Name)
	{
		return NameInternalMap.Find(Name) != nullptr;
	}

	FORCEINLINE bool IsValidEnumByDisplayName(const FString& Name)
	{
		return DisplayNameMap.Find(Name) != nullptr;
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